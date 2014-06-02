#ifndef PACKBINARIES_H
#define PACKBINARIES_H

#include "lib_packbinaries_global.h"
#include <QStringList>

class LIB_PACKBINARIESSHARED_EXPORT PackBinaries
{

public:
    PackBinaries();
    QStringList ListBinaries();
    void CopyToTempFolder(QStringList file_list);
    void GenerateHashFile(QStringList file_list, QString file_name);
    void CompressTempFolder(QString file_name);
    QStringList CompareHashs(QString file_base, QString file_update);
    QStringList CheckMissingFiles(QString file_base, QStringList existing_files);
    QStringList CheckNewFiles(QString file_base, QStringList existing_files);

};

#endif // PACKBINARIES_H
