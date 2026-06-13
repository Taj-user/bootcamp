#pragma once
#include <string>
#include <vector>

class Shell {
	public:
		void run();
		std::string readInput() const;
		std::vector<std::string> parseInput(const std::string& input) const;
		void execute(std::vector<std::string>& args);
		void handleBuiltin(std::vector<std::string>& args);
		bool isBuiltin(const std::string& cmd) const;
};
