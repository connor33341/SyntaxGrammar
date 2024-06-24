#include <iostream>
#include <sys/stat.h>
#include <tinyxml2.h>
#include "os_detector.hpp"
#include "software_checker.hpp"

extern "C" {
    #include <Python.h>
}

using namespace tinyxml2;

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

    if (pythonInstalled) {
        std::cout << "Running main.py script..." << std::endl;
        runPythonScript("main.py");
    } else {
        std::cerr << "Cannot run main.py script because Python 3 is not installed." << std::endl;
    }

    return 0;
}
