#include "Shell.h"
#include <iostream>
#include <array>
#include <sstream>
#include <unistd.h>
#include <cstdio>
#include <cstdlib>
#include <cerrno>
#include <sys/wait.h>
#include <sys/types.h>

bool Shell::isBuiltin(const std::string& cmd) const {
	return cmd == "cd" || cmd ==  "exit" || cmd == "pwd";
}

std::string Shell::readInput() const {
	std::string input;
	std::cout << "> ";
	std::getline(std::cin, input);
	return input;
}

std::vector<std::vector<std::string>> Shell::parseInput(const std::string& input) const {
    std::vector<std::vector<std::string>> tokens;
    std::stringstream pipeStream(input);
    std::string arg;
    while(std::getline(pipeStream, arg, '|')) {
	    std::stringstream tokenStream(arg);
	    std::vector<std::string> args;
	    std::string token;
	    while(tokenStream >> token) args.push_back(token);
	    if(!args.empty()) tokens.push_back(args);
    }
    return tokens;
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
}

void Shell::executePipeline(std::vector<std::vector<std::string>>& cmds) {
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
    for(int i = 0; i < numCmds; i++) {
        pid_t pid = fork();
        if(pid < 0) {
            perror("fork");
            return;
        }
        else if(pid == 0) {
            if(i > 0) {
                dup2(pipes[i - 1][0], STDIN_FILENO);
            }
            if(i < numCmds - 1) {
                dup2(pipes[i][1], STDOUT_FILENO);
            }
            for(auto& p : pipes) {
                close(p[0]);
                close(p[1]);
            }

            std::vector<char*> cArgs;
            for(auto& cmd : cmds[i]) {
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
}

void Shell::run() {
    while(true) {
        std::string input = readInput();
        if(input.empty()) continue;
        std::vector<std::vector<std::string>> cmds = parseInput(input);
        if(cmds.empty()) continue;
        if(cmds.size() == 1 && isBuiltin(cmds[0][0])) handleBuiltin(cmds[0]);
        else executePipeline(cmds);
    }
}
