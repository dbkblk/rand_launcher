#ifndef civ_function
#define civ_function

bool dirExists(const std::string &dirName_in);
bool clearCache();
bool setStartup();
bool restoreBackup();
void replaceAll(std::string& str, const std::string& from, const std::string& to);
bool currentVersion();
bool checkInstall();
bool cleanUp();
bool rollBack();
bool checkUpdate();
//bool readXML(const char* file, const char* tag);
//bool writeXML(const char* file, const char* tag, const char* newValue);

#endif
