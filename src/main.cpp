#include <iostream>
#include "os_detector.hpp"
#include "software_checker.hpp"

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

    return 0;
}
