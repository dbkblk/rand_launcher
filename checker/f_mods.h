#ifndef F_MODS_H
#define F_MODS_H
#include <QtCore>

QStringList listDefaultModFolders();
QStringList listModFolders();
QStringList getModExtraFiles(QString modName);
void generateModsExclusion();
void generateModsMLFFile();

#endif // F_MODS_H
