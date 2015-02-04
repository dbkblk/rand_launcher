#ifndef civ_function

#include <QString>
#define civ_function


bool setGameOption(QString param, QString newValue);
QString readGameOption(QString param);
QString readCheckerParam(QString param);
bool setCheckerParam(QString param, QString newValue);
bool cleanUp();
bool rollBack();
bool checkUpdate();
int readColors();
int readColorsCounter();
bool setColors(int index);
const char* readXML(const char* file, const char* tag);
bool writeXML(const char* file, const char* tag, const char* newValue);
void launchGame();
int launcherCheck();
QString check_addon_mcp();
QString check_addon_more_music();
QString check_addon_more_handicaps();
bool readOptionFormations();
bool setOptionFormations(bool value);
bool clearCache();
bool clearGameOptions();
int checkDoubleInstallation();
void unTarXz(QString file);
#endif
