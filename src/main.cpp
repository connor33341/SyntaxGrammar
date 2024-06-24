#include <iostream>
#include <sys/stat.h>
#include <tinyxml2.h>
#include "os_detector.hpp"
#include "software_checker.hpp"
#include "script_runner.hpp"
#include <lua.hpp>

extern "C" {
    #include "python.h"
}
using namespace tinyxml2;

void runLuaScript(const std::string& scriptName) {
    lua_State *L = luaL_newstate();  // Create a new Lua state
    luaL_openlibs(L);                // Open the standard libraries

    if (luaL_dofile(L, scriptName.c_str())) {
        std::cerr << "Failed to run Lua script: " << lua_tostring(L, -1) << std::endl;
    }

    lua_close(L);  // Close the Lua state
}

void createConfigDirectory() {
#if defined(_WIN32) || defined(_WIN64)
    _mkdir("config");
#else
    mkdir("config", 0777);
#endif
}

void writeXML(const std::string& os, bool pythonInstalled, bool gitInstalled) {
    XMLDocument doc;
    XMLElement* root = doc.NewElement("SystemInfo");
    doc.InsertFirstChild(root);

    XMLElement* osElement = doc.NewElement("OperatingSystem");
    osElement->SetText(os.c_str());
    root->InsertEndChild(osElement);

    XMLElement* pythonElement = doc.NewElement("Python3Installed");
    pythonElement->SetText(pythonInstalled ? "Yes" : "No");
    root->InsertEndChild(pythonElement);

    XMLElement* gitElement = doc.NewElement("GitInstalled");
    gitElement->SetText(gitInstalled ? "Yes" : "No");
    root->InsertEndChild(gitElement);

    doc.SaveFile("config/osdata.xml");
}

int main() {
    std::string os = OSDetector::detectOS();
    std::cout << "Detected Operating System: " << os << std::endl;

    bool pythonInstalled = SoftwareChecker::isPython3Installed();
    if (pythonInstalled) {
        std::cout << "Python 3 is already installed." << std::endl;
    } else {
        std::cout << "Python 3 is not installed. Attempting to install..." << std::endl;
        SoftwareChecker::installPython3(os);
        pythonInstalled = SoftwareChecker::isPython3Installed();  // Recheck after installation attempt
    }

    bool gitInstalled = SoftwareChecker::isGitInstalled();
    if (gitInstalled) {
        std::cout << "Git is already installed." << std::endl;
    } else {
        std::cout << "Git is not installed. Attempting to install..." << std::endl;
        SoftwareChecker::installGit(os);
        gitInstalled = SoftwareChecker::isGitInstalled();  // Recheck after installation attempt
    }

    createConfigDirectory();
    writeXML(os, pythonInstalled, gitInstalled);

    std::cout << "Running main.lua script..." << std::endl;
    runLuaScript("src/main.lua");

    return 0;
}
