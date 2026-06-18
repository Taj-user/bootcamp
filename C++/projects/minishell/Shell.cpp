#include "Shell.h"
#include <iostream>
#include <iomanip>
#include <array>
#include <sstream>
#include <unistd.h>
#include <cstdio>
#include <cstdlib>
#include <csignal>
#include <fcntl.h>
// #include <cerrno>                    // use for more precise error handling
#include <sys/wait.h>
#include <sys/types.h>

volatile bool childRunning = false;

bool Shell::isBuiltin(const std::string& cmd) const {
	return cmd == "cd" || cmd ==  "exit" || cmd == "pwd" || cmd == "history";
}

std::string Shell::readInput() const {
	char cwd[1024];
    if(getcwd(cwd, sizeof(cwd))) std::cout << cwd << "> " << std::flush;
    else std::cout << "> " << std::flush;

    RawModeGuard guard;
    std::string buffer;
    size_t historyIndex = cmdHistory.size();

    char c;
    while(true) {
        ssize_t bytesRead = read(STDIN_FILENO, &c, 1);
        if(bytesRead <= 0) return "";
        if(c == '\r' || c == '\n') {
            std::cout << "\n" << std::flush;
            return buffer;
        }
        else if(c == 0x7F) {
            if(!buffer.empty()) {
                buffer.pop_back();
                std::cout << "\b \b" << std::flush;
            }
        }
        else if(c == 0x1B) {
            char seq1, seq2;
            ssize_t bytesRead1 = read(STDIN_FILENO, &seq1, 1);
            if(bytesRead1 <= 0) return "";
            ssize_t bytesRead2 = read(STDIN_FILENO, &seq2, 1);
            if(bytesRead2 <= 0) return "";

            if(seq1 == '[' && (seq2 == 'A' || seq2 == 'B')) {
                if(seq2 == 'A') {
                    bool changed = false;
                    if(historyIndex == cmdHistory.size() && !cmdHistory.empty()) {
                        historyIndex = cmdHistory.size() - 1;
                        changed = true;
                    }
                    else if(historyIndex > 0) {
                        historyIndex--;
                        changed = true;
                    }
                    if(changed) {
                        if(buffer.length() > 0) std::cout << "\x1b[" << buffer.length() << "D";
                        std::cout << "\x1b[K" << std::flush;
                        std::string recalledCommand = cmdHistory[historyIndex];
                        std::cout << recalledCommand << std::flush;
                        buffer = recalledCommand;
                    }
                }
                else if(seq2 == 'B'){
                    if(historyIndex < cmdHistory.size() - 1) {
                        historyIndex++;
                        if(buffer.length() > 0) std::cout << "\x1b[" << buffer.length() << "D";
                        std::cout << "\x1b[K" << std::flush;
                        std::string recalledCommand = cmdHistory[historyIndex];
                        std::cout << recalledCommand << std::flush;
                        buffer = recalledCommand;
                    }
                    else if(historyIndex == cmdHistory.size() - 1) {
                        historyIndex = cmdHistory.size();
                        if(buffer.length() > 0) std::cout << "\x1b[" << buffer.length() << "D";
                        std::cout << "\x1b[K" << std::flush;
                        buffer = "";
                    }
                }
            }
        }
        else {
            buffer += c;
            std::cout << c << std::flush;
        }
    }
}

std::vector<Command> Shell::parseInput(const std::string& input) const {
    std::vector<Command> commands;
    std::stringstream pipeStream(input);
    std::string seg;
    while(std::getline(pipeStream, seg, '|')) {
	    std::stringstream tokenStream(seg);
	    std::vector<std::string> tokens;
	    std::string token;
	    while(tokenStream >> token) tokens.push_back(token);
	    if(tokens.empty()) continue;

	    Command cmd;
	    for(size_t i = 0; i < tokens.size(); i++) {
	        if((tokens[i] == ">" || tokens[i] == ">>" || tokens[i] == "<") && i + 1 < tokens.size()) {
	            if(tokens[i] == ">") {
	                cmd.redirectionType = Command::RedirectionType::TRUNCATE;
                    cmd.outputFile = tokens[i + 1];
                    i++;
	            }
	            else if(tokens[i] == ">>") {
	                cmd.redirectionType = Command::RedirectionType::APPEND;
	                cmd.outputFile = tokens[i + 1];
	                i++;
	            }
	            else {
	                cmd.inputFile = tokens[i + 1];
	                i++;
	            }
	        }
	        else {
	            cmd.args.push_back(tokens[i]);
	        }
	    }
        commands.push_back(cmd);
    }
    return commands;
}

void Shell::handleBuiltin(std::vector<std::string>& args) {
    if(args.empty()) return;
    if(args.front() == "exit") std::exit(0);
    else if(args.front() == "cd") {
        if(args.size() < 2) {
            std::cerr << "cd: missing argument\n";
            return;
        }
        if(chdir(args[1].c_str()) == -1) {
            perror("cd");
            return;
        }
    }
    else if(args.front() == "pwd") {
        char cwd[1024];
        if(getcwd(cwd, sizeof(cwd))) std::cout << cwd << "\n";
        return;
    }
    else if(args.front() == "history") {
        for(size_t i = 0; i < cmdHistory.size(); i++) {
            std::cout << std::setw(4) << (i + 1) << " " << cmdHistory[i] << "\n";
        }
        return;
    }
}

void Shell::executePipeline(std::vector<Command>& cmds) {
    int numCmds= cmds.size();
    int numPipes = numCmds - 1;
    std::vector<std::array<int, 2>> pipes(numPipes);

    for(int i = 0; i < numPipes; i++) {
        if(pipe(pipes[i].data()) == -1) {
            perror("pipe");
            return;
        }
    }

    std::vector<pid_t> childPids;
    childRunning = true;
    for(int i = 0; i < numCmds; i++) {
        pid_t pid = fork();
        if(pid < 0) {
            perror("fork");
            childRunning = false;
            return;
        }
        else if(pid == 0) {
            signal(SIGINT, SIG_DFL);
            // STDIN SETUP
            if(!cmds[i].inputFile.empty()) {
                int fd = open(cmds[i].inputFile.c_str(), O_RDONLY);
                if(fd == -1) {
                    perror(cmds[i].inputFile.c_str());
                    exit(1);
                }
                dup2(fd, STDIN_FILENO);
                close(fd);
            }
            else if(i > 0) {
                dup2(pipes[i-1][0], STDIN_FILENO);
            }
            // STDOUT SETUP
            if(!cmds[i].outputFile.empty()) {
                int flags = O_WRONLY | O_CREAT;
                flags |= (cmds[i].redirectionType == Command::RedirectionType::APPEND) ? O_APPEND : O_TRUNC;
                int fd = open(cmds[i].outputFile.c_str(), flags, 0644);
                if(fd == -1) {
                    perror(cmds[i].outputFile.c_str());
                    exit(1);
                }
                dup2(fd, STDOUT_FILENO);
                close(fd);
            }
            else if( i < numCmds - 1) {
                dup2(pipes[i][1], STDOUT_FILENO);
            }

            for(auto& p : pipes) {
                close(p[0]);
                close(p[1]);
            }

            std::vector<char*> cArgs;
            for(auto& cmd : cmds[i].args) {
                cArgs.push_back(const_cast<char*>(cmd.c_str()));
            }
            cArgs.push_back(nullptr);
            execvp(cArgs[0], cArgs.data());
            perror(cArgs[0]);
            exit(127);
        }
        else {
            childPids.push_back(pid);
        }
    }

    for(auto& p : pipes) {
        close(p[0]);
        close(p[1]);
    }

    for(pid_t pid : childPids) {
        int status;
        waitpid(pid, &status, 0);
    }
    childRunning = false;
}

// helper function
void sigintHandler([[maybe_unused]] int sig) {
    if(!childRunning)
        write(STDOUT_FILENO, "\n", 1);
}

void Shell::run() {
    signal(SIGINT, sigintHandler);
    while(true) {
        std::string input = readInput();
        if(input.empty()) continue;
        if(cmdHistory.size() >= maxHistorySize) cmdHistory.pop_front();
        cmdHistory.push_back(input);
        std::vector<Command> cmds = parseInput(input);
        if(cmds.empty()) continue;
        if(cmds.size() == 1 && isBuiltin(cmds[0].args[0])) handleBuiltin(cmds[0].args);
        else executePipeline(cmds);
    }
}

RawModeGuard::RawModeGuard() {
    if(tcgetattr(STDIN_FILENO, &oldSettings) == -1) perror("tcgetattr");
    struct termios newSettings = oldSettings;
    newSettings.c_lflag &= ~(ICANON | ECHO);
    if(tcsetattr(STDIN_FILENO, TCSANOW, &newSettings) == -1) perror("tcsetattr");
}

RawModeGuard::~RawModeGuard() {
    tcsetattr(STDIN_FILENO, TCSANOW, &oldSettings);
}
