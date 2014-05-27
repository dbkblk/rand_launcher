#ifndef civ_function

#include <QString>
#define civ_function


bool setConfigParam(QString param, QString newValue);
QString readConfigParam(QString param);
QString readCheckerParam(QString param);
bool setCheckerParam(QString param, QString newValue);
bool cleanUp();
bool rollBack();
bool checkUpdate();
const char* readColors();
int readColorsCounter();
bool setColors(const char* color);
const char* readXML(const char* file, const char* tag);
bool writeXML(const char* file, const char* tag, const char* newValue);
void launchGame();
int launcherCheck();
QString check_addon_mcp();
QString check_addon_more_music();
QString check_addon_more_handicaps();
bool readOptionFormations();
bool setOptionFormations(bool value);

#endif