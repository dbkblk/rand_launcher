#include "updatemanager.h"
#include "ui_updatemanager.h"
#include "civ_functions.h"
#include "updatebox.h"

#include "QObject"
#include <QTimer>
#include <QEventLoop>
#include <QThread>
#include <QDebug>
#include <QProcess>
#include <QSettings>
#include <QMessageBox>
#include <QFile>
#include <QDesktopWidget>
#include <QVBoxLayout>
#include <QDir>

updateManager::updateManager(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::updateManager)
{
    ui->setupUi(this);
}

updateManager::~updateManager()
{
    delete ui;
}

Worker::Worker(QObject *parent) :
    QObject(parent)
{
    _working =false;
    _abort = false;
}

void Worker::requestWork()
{
    mutex.lock();
    _working = true;
    _abort = false;
    qDebug()<<"Request worker start in Thread "<<thread()->currentThreadId();
    mutex.unlock();

    emit workRequested();
}

void Worker::abort()
{
    mutex.lock();
    if (_working) {
        _abort = true;
        qDebug()<<"Request worker aborting in Thread "<<thread()->currentThreadId();
    }
    mutex.unlock();
}

void Worker::UMCheckLauncherUpdate()
{
    // Wait 5s before to check for update
    QEventLoop loop;
    QTimer::singleShot(10000, &loop, SLOT(quit()));
    loop.exec();

    // Begin processing
    qDebug()<<"Starting worker process in Thread "<<thread()->currentThreadId();
    bool update;
    QProcess download;
    download.start("checker/wget.exe -c -t 10 --retry-connrefused --no-check-certificate --waitretry=10 https://raw.githubusercontent.com/dbkblk/and2_checker/master/update.ini");
    //download.start("checker/wget.exe -c -t 10 --retry-connrefused --no-check-certificate --waitretry=10 https://dl.dropboxusercontent.com/u/369241/update.ini");

    if (download.waitForFinished(60000))
    {
        QSettings upd_ini("update.ini", QSettings::IniFormat);
        float loc_version = readCheckerParam("MAIN/CheckerVersion").toFloat();
        float dist_version = upd_ini.value("VERSION/CheckerVersion").toFloat();
        setCheckerParam("MAIN/Changelog",upd_ini.value("VERSION/Changelog").toString());
        setCheckerParam("MAIN/DistantCheckerVersion",upd_ini.value("VERSION/CheckerVersion").toString());
        qDebug() << "Local version : " << loc_version;
        qDebug() << "Distant version : " << dist_version;
        if(loc_version < dist_version) {
            qDebug() << "An update is available";
            update = true;
            qDebug() << "Update is " << update;
        }
        else
        {
            qDebug() << "No update is required";
            QFile::remove("update.ini");
            update = false;
        }
    }

    // Set _working to false, meaning the process can't be aborted anymore.
    mutex.lock();
    _working = false;
    mutex.unlock();

    qDebug()<<"Worker process finished in Thread "<<thread()->currentThreadId();

    // Finished signal
    emit finished(update);
}

bool launcherUpdate()
{
    QSettings upd_ini("update.ini", QSettings::IniFormat);
    QString downloadlink = upd_ini.value("VERSION/DownloadLink").toString();
    QString downloadfile = upd_ini.value("VERSION/DownloadFile").toString();
    qDebug() << "Link : " << downloadlink << endl << "File : " << downloadfile;
    char cmd[512];
    QFile::copy("checker/7za.exe","7za.exe");
    sprintf(cmd, "taskkill /f /im and2_checker.exe && SLEEP 1 && checker\\wget.exe -c --no-check-certificate %s && SLEEP 1 && 7za.exe x -y %s && SLEEP 1 && del 7za.exe && SLEEP 1 && del update.ini && SLEEP 1 && del %s && SLEEP 1 && start and2_checker.exe", downloadlink.toStdString().c_str(), downloadfile.toStdString().c_str(), downloadfile.toStdString().c_str());
    qDebug() << "Update command : " << cmd;
    system(cmd);
    return 0;
}

// Clear the cache folder

bool clearCache()
{
    // Getting the cache path
    std::string cacheDir;
    std::string delCmd = "DEL /Q ";
    std::string quote = "\"";
    std::string finalDir = "\\My Games\\Beyond the Sword\\cache\\";
    std::string dat = "*";
    char* Appdata = getenv("LOCALAPPDATA");
    cacheDir = delCmd + quote + Appdata + finalDir + dat + quote;
    // cout << cacheDir << endl;

    return 0;
}

int svnLocalInfo(){
    // Get the info from the distant server
    QProcess svn_loc;
    svn_loc.setStandardOutputFile("svn.txt");
    svn_loc.start("checker\\svn.exe", QStringList() << "info");
    svn_loc.waitForFinished(-1);

    // Open the output file
    QFile svn_out_loc("svn.txt");
    QString svn;
    QString rev;

    // Find the local revision
    if(svn_out_loc.open(QFile::ReadWrite  |QFile::Text))
    {
        while(!svn_out_loc.atEnd())
        {
            svn += svn_out_loc.readLine();
        }
        int j = 0;
        while ((j = svn.indexOf("Revision: ", j)) != -1) {
             rev = svn.mid(j+10,3);
             ++j;
         }
        qDebug() << "Local revision : " << rev;
    setCheckerParam("MAIN/LocalRev",rev);
    svn_out_loc.close();
    QFile::remove("svn.txt");
    return rev.toInt();
    }

    return 0;
}

int svnDistantInfo()
{
        // Get the info from the distant server
        QProcess svn_dist;
        svn_dist.setStandardOutputFile("svn_dist.txt");
        svn_dist.start("checker\\svn.exe", QStringList() << "info" << "-r" << "HEAD");
        svn_dist.waitForFinished(-1);

        // Open the output file
        QFile svn_out_dist("svn_dist.txt");
        QString svn_str_dist;
        QString rev_dist;

        // Find the local revision
        if(svn_out_dist.open(QFile::ReadWrite  |QFile::Text))
        {
            while(!svn_out_dist.atEnd())
            {
                svn_str_dist += svn_out_dist.readLine();
            }
            int j = 0;
            while ((j = svn_str_dist.indexOf("Revision: ", j)) != -1) {
                 rev_dist = svn_str_dist.mid(j+10,3);
                 ++j;
             }
            qDebug() << "Distant revision : " << rev_dist;
        setCheckerParam("MAIN/DistantRev",rev_dist);
        svn_out_dist.close();
        QFile::remove("svn_dist.txt");
        }
        return rev_dist.toInt();
}

Addons::Addons(QWidget *)
{
     // Layout
    QVBoxLayout *layout = new QVBoxLayout(this);
    QHBoxLayout *buttons = new QHBoxLayout(this);

    this->setWindowTitle("Addon manager");
    const QRect screen = QApplication::desktop()->screenGeometry();
    this->setGeometry(0,0,300,100);
    this->setFixedSize(size());
    this->move(screen.center() - this->rect().center() );

    // Add widgets
    addon_civ_mega_pack = new QCheckBox(this);
    addon_civ_mega_pack->setText("Civ Mega Pack");
    layout->addWidget(addon_civ_mega_pack);

    addon_more_music = new QCheckBox(this);
    addon_more_music->setText("More music");
    layout->addWidget(addon_more_music);

    buttons->addStretch();
    addon_close = new QPushButton(this) ;
    addon_close->setText("Close");
    buttons->addWidget(addon_close);

    addon_apply = new QPushButton(this) ;
    addon_apply->setText("Apply changes");
    buttons->addWidget(addon_apply);

    layout->addLayout(buttons);

    // Check for addons
    addon_civ_mega_pack->setText("Civ Mega Pack (already installed)");
    addon_civ_mega_pack->setCheckable(false);
    addon_more_music->setText("More music (already installed)");
    addon_more_music->setCheckable(false);
    // Signals
    connect(addon_close,SIGNAL(clicked()),this,SLOT(close()));
    connect(addon_apply,SIGNAL(clicked()),this,SLOT(addons_installation()));
}

Addons::~Addons()
{

}

void Addons::addons_installation()
{
    addon_setup = new updatebox(this);
    addon_setup->addonsMode();
    addon_setup->show();

    // Check for checkbox state
    qDebug() << "Install Civ Mega Pack is" << addon_civ_mega_pack->isChecked();
    qDebug() << "Install More music is" << addon_more_music->isChecked();

    // Create a loop to wait for process execution
    QEventLoop wait_install;
    QTimer wait_timer;
    wait_timer.setInterval(2000);
    wait_timer.setSingleShot(true);
    connect(addon_setup,SIGNAL(finished()),&wait_install,SLOT(quit()));
    connect(&wait_timer, SIGNAL(timeout()), &wait_install, SLOT(quit()));

    if(addon_civ_mega_pack->isChecked())
    {
        // Write text and wait 2s
        addon_setup->appendText("\n\n****************************************\n\n");
        addon_setup->appendText("Downloading Civ Mega Pack addon (835MB)\n\n");
        addon_setup->appendText("****************************************\n\n");
        wait_timer.start();
        wait_install.exec();

        // Download addon
        QString download_addon_cmp = "checker/wget.exe -c -t 10 --retry-connrefused --no-check-certificate --waitretry=10 https://dl.dropboxusercontent.com/u/369241/AND2_CMP_BASE_V1.7z";
        bool cursor = false;
        addon_setup->execute(download_addon_cmp,cursor);
        wait_install.exec();
        QString download_addon_cmp2 = "checker/wget.exe -c -t 10 --retry-connrefused --no-check-certificate --waitretry=10 https://dl.dropboxusercontent.com/u/369241/AND2_CMP_FILES_V1.2.1.7z";
        addon_setup->execute(download_addon_cmp2,cursor);
        wait_install.exec();

        // Write text and wait 2s
        addon_setup->appendText("\n\n****************************************\n\n");
        addon_setup->appendText("Extracting Civ Mega Pack Addon\n\n");
        addon_setup->appendText("****************************************\n\n");
        wait_timer.start();
        wait_install.exec();

        QString extract_addon_cmp1 = "checker/7za.exe x -y AND2_CMP_BASE_V1.7z";
        addon_setup->execute(extract_addon_cmp1,cursor);
        wait_install.exec();

        QString extract_addon_cmp2 = "checker/7za.exe x -y AND2_CMP_FILES_V1.2.1.7z";
        addon_setup->execute(extract_addon_cmp2,cursor);
        wait_install.exec();

        // Write text and wait 2s
        addon_setup->appendText("\n\n****************************************\n\n");
        addon_setup->appendText("Civ Mega Pack addon installation finished !\n\n");
        addon_setup->appendText("****************************************\n\n");
        wait_timer.start();
        wait_install.exec();

        QFile::remove("AND2_CMP_BASE_V1.7z");
        QFile::remove("AND2_CMP_FILES_V1.2.1.7z");
    }

    if(addon_more_music->isChecked())
    {
        // Write text and wait 2s
        addon_setup->appendText("\n\n****************************************\n\n");
        addon_setup->appendText("Downloading Music Addon (500MB)\n\n");
        addon_setup->appendText("****************************************\n\n");
        wait_timer.start();
        wait_install.exec();

        // Download addon
        QString download_addon_music = "checker/wget.exe -c -t 10 --retry-connrefused --no-check-certificate --waitretry=10 https://dl.dropboxusercontent.com/u/369241/AND2_MUSIC_ADDON.7z";
        bool cursor = false;
        addon_setup->execute(download_addon_music,cursor);
        wait_install.exec();

        // Write text and wait 2s
        addon_setup->appendText("\n\n****************************************\n\n");
        addon_setup->appendText("Extracting Music Addon\n\n");
        addon_setup->appendText("****************************************\n\n");
        wait_timer.start();
        wait_install.exec();

        QString extract_addon_music = "checker/7za.exe x -y AND2_MUSIC_ADDON.7z";
        addon_setup->execute(extract_addon_music,cursor);
        wait_install.exec();

        // Write text and wait 2s
        addon_setup->appendText("\n\n****************************************\n\n");
        addon_setup->appendText("More music addon installation finished !\n\n");
        addon_setup->appendText("****************************************\n\n");
        wait_timer.start();
        wait_install.exec();
        QFile::remove("AND2_MUSIC_ADDON.7z");
    }

}
