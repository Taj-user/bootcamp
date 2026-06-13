#include "Shell.h"
#include <iostream>
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

std::vector<std::string> Shell::parseInput(const std::string& input) const {
    std::vector<std::string> tokens;
    std::stringstream ss(input);
    std::string field;
    while(ss >> field) tokens.push_back(field);
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

void Shell::execute(std::vector<std::string>& args) {
    if(args.empty()) return;
    std::vector<char*> cArgs;
    for(auto& arg : args) {
        cArgs.push_back(const_cast<char*>(arg.c_str()));
    }
    cArgs.push_back(nullptr);

    pid_t pid = fork();
    if(pid < 0) {
        std::cerr << "fork failed\n";
        return;
    }
    else if(pid == 0) {
        execvp(cArgs[0], cArgs.data());
        perror(args[0].c_str());
        exit(127);
    }
    else {
        int status;
        waitpid(pid, &status, 0);
    }
}

void Shell::run() {
    while(true) {
        std::string input = readInput();
        if(input.empty()) continue;
        std::vector<std::string> args = parseInput(input);
        if(args.empty()) continue;
        if(isBuiltin(args[0])) handleBuiltin(args);
        else execute(args);
    }
}
