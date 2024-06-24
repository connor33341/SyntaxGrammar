#ifndef SCRIPT_RUNNER_HPP
#define SCRIPT_RUNNER_HPP

#include <iostream>
#include <cstdlib>

class ScriptRunner {
public:
    static void runScript(const std::string& scriptPath) {
        int result = system(scriptPath.c_str());
        if (result != 0) {
            std::cerr << "Failed to run script: " << scriptPath << std::endl;
        } else {
            std::cout << "Script " << scriptPath << " executed successfully." << std::endl;
        }
    }
};

#endif // SCRIPT_RUNNER_HPP
