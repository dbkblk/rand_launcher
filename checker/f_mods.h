#ifndef F_MODS_H
#define F_MODS_H
#include <QtCore>

QStringList listDefaultModFolders();
QStringList listModFolders();
QStringList getModExtraFiles(QString modName);
void generateModsExclusion();
void generateModsMLFFile();

// Civ4_audio_xml_injector code v1.0
void preInjectXML();
QString getOfficialFile(QString fileSuffix);
bool injectXml(QString defaultFile, QStringList fileList, QString fileSuffix);
QString getIDTag(QString fileSuffix);
QString getStartTag(QString fileSuffix);
QString getRootTag(QString fileSuffix);

#endif // F_MODS_H
