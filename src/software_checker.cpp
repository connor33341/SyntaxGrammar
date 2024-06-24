#include "software_checker.hpp"
#include <cstdlib>
#include <iostream>

bool SoftwareChecker::isPython3Installed() {
    int result = std::system("python3 --version > /dev/null 2>&1");
    return (result == 0);
}

bool SoftwareChecker::isGitInstalled() {
    int result = std::system("git --version > /dev/null 2>&1");
    return (result == 0);
}

void SoftwareChecker::installPython3(const std::string& os) {
    if (os == "Windows") {
        std::cout << "Please install Python 3 manually from https://www.python.org/downloads/windows/" << std::endl;
    } else if (os == "macOS") {
        std::system("brew install python");
    } else if (os == "Linux") {
        std::system("sudo apt-get update && sudo apt-get install -y python3");
    } else {
        std::cout << "Unsupported OS for automatic Python 3 installation. Please install manually." << std::endl;
    }
}

void SoftwareChecker::installGit(const std::string& os) {
    if (os == "Windows") {
        std::cout << "Please install Git manually from https://git-scm.com/download/win" << std::endl;
    } else if (os == "macOS") {
        std::system("brew install git");
    } else if (os == "Linux") {
        std::system("sudo apt-get update && sudo apt-get install -y git");
    } else {
        std::cout << "Unsupported OS for automatic Git installation. Please install manually." << std::endl;
    }
}
