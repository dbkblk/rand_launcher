#include "f_binaries.h"

#include <QDir>
#include <QtXml>

/* How to use :
 * To generate base files :
 *          // Generate a list of files
            QStringList ListBinaries();
            // Generate a hash of files
            void GenerateHashFile(QStringList file_list, QString file_name);
            // Copy the files in the list in a temp folder (need 7za.exe in checker folder)
            void CopyToTempFolder(QStringList file_list);
            // Compress the temp folder to a 7z file
            void CompressTempFolder(QString file_name);
 * To generate update files:
            // Download base files signatures
            // Generate a list of files
            QStringList ListBinaries();
            // Generate a hash of files
            void GenerateHashFile(QStringList file_list, QString file_name);
            // Compare the existing with the base files signature
            QStringList CompareHashs(QString file_base, QString file_update);
            // Check new files
            QStringList CheckNewFiles(QString file_base, QStringList existing_files);
            // Check missing files
            QStringList CheckMissingFiles(QString file_base, QStringList existing_files);
            // Copy the modified and new files list in a temp folder (need 7za.exe in checker folder)
            void CopyToTempFolder(QStringList file_list);
            // Compress the temp folder to a 7z file
            void CompressTempFolder(QString file_name);
            */

PackBinaries::PackBinaries()
{
    QDir temp_dir("temp/");
    temp_dir.removeRecursively();
    temp_dir.mkdir("temp/");
}

QStringList PackBinaries::ListBinaries()
{
    QStringList binaries_ext;
    binaries_ext << "*.jar" << "*.tga" << "*.dds" << "*.bik" << "*.fpk" << "*.mp3" << "*.wav" << "*.exe";

    QStringList exclusion_list;
    exclusion_list << "Assets/MCP0.FPK" << "Assets/Modules/Custom_Civilizations_MCP/" << "Assets/Sounds/NEW/" << "Assets/Sounds/Soundtrack/OpeningMenuCiv4.mp3" << "checker/" << "and2_checker.exe";

    QStringList binaries_list;


    QDir root(".");

    // Generate a list of binaries and remove exceptions
    qDebug() << "Checking binary files...";
    QDirIterator iterator(".", binaries_ext, QDir::Files | QDir::NoDotAndDotDot,  QDirIterator::Subdirectories);
    do
    {
        QString filepath;
        QString filedir;
        QString exclusion_check;
        filepath = root.relativeFilePath(iterator.filePath());

        //qDebug() << filepath << " | " << filedir;
        foreach (exclusion_check, exclusion_list)
        {
            if(filepath.startsWith(exclusion_check) || filepath == exclusion_check)
            {

                filepath = "";
            }
        }
        if(filepath != "")
        {
            // Add entry to the list
            binaries_list << filepath;
        }
        iterator.next();
    } while (iterator.hasNext());

    return binaries_list;
}

void PackBinaries::CopyToTempFolder(QStringList file_list)
{
    // Copy files
    int f = 0;
    QString file;
    QString filedir;
    QDir temp_dir("temp/");
    foreach(file, file_list)
    {
        filedir = QFileInfo(file).dir().path();
        // Copy file
        temp_dir.mkpath(filedir);
        qDebug() << "Cloning " << file;
        QFile::copy(file,"temp/" + file);
        f++;
    }

    qDebug() << "Copied " << f << " files";
}

void PackBinaries::GenerateHashFile(QStringList file_list, QString file_name)
{
    qDebug() << "Generating a list of files...";
    QFile output_list(file_name);
    QString file;
    output_list.open(QIODevice::WriteOnly | QIODevice::Truncate);
    QTextStream out_enc(&output_list);
    QDomDocument xml;
    QDomElement xml_root = xml.createElement("root");
    xml.appendChild(xml_root);
    foreach (file, file_list) {
        QDomElement new_file = xml.createElement("file");
        new_file.appendChild(xml.createTextNode(file));
        xml_root.appendChild(new_file);

        // Generating md5 sum of the file
        QCryptographicHash crypto(QCryptographicHash::Md5);
        QFile hashed_file(file);
        hashed_file.open(QFile::ReadOnly);
        while(!hashed_file.atEnd()){
        crypto.addData(hashed_file.read(8192));
        }
        QByteArray hash = crypto.result().toHex();
        QString hash_string = hash;
        new_file.setAttribute("hash",hash_string);
        // qDebug() << "Generated hash " << hash_string << " of " << file;
        hashed_file.close();
    }
    out_enc << xml.toString();
    output_list.close();
}

void PackBinaries::CompressTempFolder(QString file_name)
{
    // Compressing folder
    qDebug() << "Compressing folder";
    QProcess compress;
    QString command;
    command = QString("checker/7za.exe a -mx=9 -mmt=on %1 ./temp/*").arg(file_name);
    qDebug() << command;
    compress.execute(command);
}

QStringList PackBinaries::CompareHashs(QString file_base, QString file_update)
{
    qDebug() << "Comparing hashs...";

    // Declaring base file
    QFile f_base(file_base);
    QDomDocument xml_base;
    if(!f_base.open(QIODevice::ReadOnly))
     {
         qDebug() << "Error opening " << file_base;
         return QStringList("0");
     }
    xml_base.setContent(&f_base);
    QDomNode base_node_base = xml_base.firstChild();
    QDomElement base_node_file = base_node_base.firstChildElement("file").toElement();

    // Declaring update file
    QFile f_update(file_update);
    QDomDocument xml_update;
    if(!f_update.open(QIODevice::ReadOnly))
     {
         qDebug() << "Error opening " << file_update;
         return QStringList("0");
     }
    xml_update.setContent(&f_update);
    QDomNode update_node_base = xml_update.firstChild();

    // Comparing documents
    QStringList modified_files;

    for(base_node_file;!base_node_file.isNull();base_node_file = base_node_file.nextSiblingElement())
    {
        QString base_hash = base_node_file.attribute("hash");
        QString base_file = base_node_file.text();
        QDomElement update_node_file = update_node_base.firstChildElement("file").toElement();

        for(update_node_file;!update_node_file.isNull();update_node_file = update_node_file.nextSiblingElement())
        {
            //qDebug() << base_file;
            QString update_hash = update_node_file.attribute("hash");
            QString update_file = update_node_file.text();

            qDebug() << "Comparing " << base_file << " with " << update_file;

            if (base_file == update_file)
            {
                if (base_hash != update_hash)
                {
                    qDebug() << update_file << " hash is different";
                    modified_files << update_file;
                }
            }
        }
    }
    f_base.close();
    f_update.close();

    return modified_files;

}

QStringList PackBinaries::CheckMissingFiles(QString file_base, QStringList existing_files)
{
    qDebug() << "Check for missing files";

    // Declaring base file
    QFile f_base(file_base);
    QDomDocument xml_base;
    if(!f_base.open(QIODevice::ReadOnly))
     {
         qDebug() << "Error opening " << file_base;
         return QStringList("0");
     }
    xml_base.setContent(&f_base);
    QDomNode base_node_base = xml_base.firstChild();


    // Comparing documents
    QString existing;
    QStringList missing_files;

    // Check for files that are in the pack but not in the update

    QDomElement base_node_file = base_node_base.firstChildElement("file").toElement();
    for(base_node_file;!base_node_file.isNull();base_node_file = base_node_file.nextSiblingElement())
    {
        int m = 0;

        foreach(existing,existing_files)
        {
            if(base_node_file.text() == existing)
            {
                m++;
            }
        }
        if (m == 0)
        {
            qDebug() << "File" << base_node_file.text() << "not found";
            missing_files << base_node_file.text();
        }
    }

    return missing_files;
}

QStringList PackBinaries::CheckNewFiles(QString file_base, QStringList existing_files)
{
    qDebug() << "Check for new files";

    // Declaring base file
    QFile f_base(file_base);
    QDomDocument xml_base;
    if(!f_base.open(QIODevice::ReadOnly))
     {
         qDebug() << "Error opening " << file_base;
         return QStringList("0");
     }
    xml_base.setContent(&f_base);
    QDomNode base_node_base = xml_base.firstChild();

    // Comparing documents
    QString existing;
    QStringList new_files;

    // Check for existing files that are not in base pack

    foreach(existing,existing_files)
    {
        int n = 0;
        QDomElement base_node_file = base_node_base.firstChildElement("file").toElement();

        for(base_node_file;!base_node_file.isNull();base_node_file = base_node_file.nextSiblingElement())
        {
            if(base_node_file.text() == existing)
            {
                n++;
            }
        }

        if (n == 0)
        {
            qDebug() << "File" << existing << "is new";
            new_files << existing;
        }
     }

    return new_files;
}
