#ifndef SOFTWARE_CHECKER_HPP
#define SOFTWARE_CHECKER_HPP

#include <string>

class SoftwareChecker {
public:
    static bool isPython3Installed();
    static bool isGitInstalled();
    static void installPython3(const std::string& os);
    static void installGit(const std::string& os);
};

#endif // SOFTWARE_CHECKER_HPP
