#include <iostream>
#include "os_detector.hpp"
#include "software_checker.hpp"

extern "C" {
    #include <Python.h>
}

void runPythonScript(const std::string& scriptName) {
    Py_Initialize();
    FILE* fp = fopen(scriptName.c_str(), "r");
    if (fp) {
        PyRun_SimpleFile(fp, scriptName.c_str());
        fclose(fp);
    } else {
        std::cerr << "Failed to open Python script: " << scriptName << std::endl;
    }
    Py_Finalize();
}

int main() {
    std::string os = OSDetector::detectOS();
    std::cout << "Detected Operating System: " << os << std::endl;

    if (SoftwareChecker::isPython3Installed()) {
        std::cout << "Python 3 is already installed." << std::endl;
    } else {
        std::cout << "Python 3 is not installed. Attempting to install..." << std::endl;
        SoftwareChecker::installPython3(os);
    }

    if (SoftwareChecker::isGitInstalled()) {
        std::cout << "Git is already installed." << std::endl;
    } else {
        std::cout << "Git is not installed. Attempting to install..." << std::endl;
        SoftwareChecker::installGit(os);
    }

    std::cout << "Running main.py script..." << std::endl;
    runPythonScript("main.py");

    return 0;
}
