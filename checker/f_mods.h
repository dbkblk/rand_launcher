#ifndef F_MODS_H
#define F_MODS_H
#include <QtCore>

QStringList listDefaultModFolders();
QStringList listModFolders();
QStringList getModExtraFiles(QString modName);
bool getModActivationStatus(QString mod_name);
void setModActivationStatus(QString mod_name, bool status);
void generateModsExclusion();
void generateModsMLFFile();

class f_injection : public QObject
{
    Q_OBJECT

public:
    explicit f_injection(QObject *parent = 0);
    void requestWork();
    void abort();

private:
    bool _abort;
    bool _working;
    QMutex mutex;

signals:
    void workRequested();

public slots:
    void start();
};

// Civ4_audio_xml_injector code v1.0
void preInjectXML();
QString getOfficialFile(QString fileSuffix);
bool injectXml(QString defaultFile, QStringList fileList, QString fileSuffix);
QString getIDTag(QString fileSuffix);
QString getStartTag(QString fileSuffix);
QString getRootTag(QString fileSuffix);

#endif // F_MODS_H
