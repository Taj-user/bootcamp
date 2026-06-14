#pragma once
#include <string>
#include <vector>

class Shell {
	public:
		void run();
		std::string readInput() const;
		std::vector<std::vector<std::string>> parseInput(const std::string& input) const;
		void executePipeline(std::vector<std::vector<std::string>>& cmds);
		void handleBuiltin(std::vector<std::string>& args);
		bool isBuiltin(const std::string& cmd) const;
};
