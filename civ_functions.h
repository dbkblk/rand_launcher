#ifndef civ_function

#include <QString>
#define civ_function

bool dirExists(const std::string &dirName_in);
bool clearCache();
bool setConfigParam(QString param, QString newValue);
QString readConfigParam(QString param);
const char* readCheckerParam(QString param);
const char* setCheckerParam(QString param, QString newValue);
bool restoreBackup();
void replaceAll(std::string& str, const std::string& from, const std::string& to);
bool currentVersion();
bool installMod();
bool cleanUp();
bool rollBack();
bool checkUpdate();
const char* readColors();
int readColorsCounter();
bool setColors(const char* color);
const char* readXML(const char* file, const char* tag);
bool writeXML(const char* file, const char* tag, const char* newValue);
void launchGame();

#endif
