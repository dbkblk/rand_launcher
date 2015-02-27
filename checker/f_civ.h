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
QStringList getColorSet();
QString getColorName(QStringList color_set);
QStringList getColorSetFromNumber(int number);
QStringList getColorSetFromName(QString color_name);
int getColorNumberFromSet(QStringList color_set);
void setColorSet(QStringList color_set);
bool setColorCustomDefinition(QStringList color_set);
const char* readXML(const char* file, const char* tag);
bool writeXML(const char* file, const char* tag, const char* newValue);
void launchGame(QString executable);
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
void setTextureTerrainSet(int index);
QString checkMd5(QString file_path);
#endif
