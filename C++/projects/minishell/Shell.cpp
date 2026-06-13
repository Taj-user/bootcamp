#include "Shell.h"
#include <iostream>
#include <unistd.h>
#include <sys/syscall.h>
#include <sys/types.h>

bool Shell::isBuiltin(std::vector<std::string>& cmd) const {
	return cmd == "cd" || cmd ==  "exit" || cmd == "pwd";
}

std::string Shell::readInput() const {
	std::string input;
	std::cout << "> ";
	std::getline(std::cin, input);
	return input;
}
