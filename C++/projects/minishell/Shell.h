#pragma once
#include <string>
#include <vector>

struct Command {
    enum class RedirectionType {
        NONE,
        TRUNCATE,
        APPEND,
    };

    std::vector<std::string> args;
    std::string inputFile;                  // empty = no input redirection
    std::string outputFile;                 // empty = no output redirection
    RedirectionType redirectionType = RedirectionType::NONE;
};

class Shell {
	public:
		void run();
		std::string readInput() const;
		std::vector<Command> parseInput(const std::string& input) const;
		void executePipeline(std::vector<Command>& cmds);
		void handleBuiltin(std::vector<std::string>& args);
		bool isBuiltin(const std::string& cmd) const;
};
