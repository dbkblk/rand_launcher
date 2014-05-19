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

updateManager::updateManager(QWidget *parent)
{
    QVBoxLayout *vert_layout;
    QHBoxLayout *button_layout;

    // Layout
    this->setGeometry(0,0,550,300);
    this->setWindowTitle("Components manager");
    const QRect screen = QApplication::desktop()->screenGeometry();
    this->setFixedSize(size());
    this->move(screen.center() - this->rect().center() );

    // Table definition
    tab_updates = new QTableWidget(this);
    tab_updates->setRowCount(5);
    tab_updates->setColumnCount(3);
    tab_updates->setGeometry(10,10,530,280);
    tab_updates->setEditTriggers(QAbstractItemView::NoEditTriggers);

    QStringList tab_updates_header;
    tab_updates_header << "Local vers." << "Distant vers." << "Update ?";
    tab_updates->setHorizontalHeaderLabels(tab_updates_header);
    QStringList tab_updates_columns;
    tab_updates_columns << "Core mod" << "Launcher" << "Addon: Mega civ pack" << "Addon: More music" << "Addon: More handicaps";
    tab_updates->setVerticalHeaderLabels(tab_updates_columns);



    /* Local revisions */
    // Core mod

    QTableWidgetItem *item_local_vers = new QTableWidgetItem;
    QString local_version = QString::number(svnLocalInfo());
    item_local_vers->setText(local_version);
    tab_updates->setItem(0,0,item_local_vers);

    // Launcher
    QTableWidgetItem *item_local_launcher = new QTableWidgetItem;
    item_local_launcher->setText(readCheckerParam("Main/CheckerVersion"));
    tab_updates->setItem(1,0,item_local_launcher);

    // Addon MCP
    QTableWidgetItem *item_local_addon_MCP = new QTableWidgetItem;
    item_local_addon_MCP->setText(readCheckerParam("ADDON_MEGACIVPACK/FilesVersion"));
    tab_updates->setItem(2,0,item_local_addon_MCP);

    // Addon More music
    QTableWidgetItem *item_local_addon_MoreMusic = new QTableWidgetItem;
    item_local_addon_MoreMusic->setText(readCheckerParam("ADDON_MOREMUSIC/Version"));
    tab_updates->setItem(3,0,item_local_addon_MoreMusic);

    // Addon More handicaps
    QTableWidgetItem *item_local_addon_MoreHandicaps = new QTableWidgetItem;
    item_local_addon_MoreHandicaps->setText(readCheckerParam("ADDON_MOREHANDICAPS/Version"));
    tab_updates->setItem(4,0,item_local_addon_MoreHandicaps);

/*
    vert_layout->addWidget(tab_updates);
    vert_layout->addLayout(button_layout);*/
    this->show();
}

updateManager::~updateManager()
{
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
    //download.start("checker/curl.exe -O -J -L -C - -# --retry 10 --insecure https://raw.githubusercontent.com/dbkblk/and2_checker/master/update.ini");
    download.start("checker/curl.exe -O -J -L -C - -# --retry 10 --insecure https://dl.dropboxusercontent.com/u/369241/update.ini");

    if (download.waitForFinished(60000))
    {
        QSettings upd_ini("update.ini", QSettings::IniFormat);
        float loc_version = readCheckerParam("Main/CheckerVersion").toFloat();
        float dist_version = upd_ini.value("VERSION/CheckerVersion").toFloat();
        setCheckerParam("Update/Changelog",upd_ini.value("VERSION/Changelog").toString());
        setCheckerParam("Update/DistantCheckerVersion",upd_ini.value("VERSION/CheckerVersion").toString());
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
    QFile::remove("7za.exe");
    QSettings upd_ini("update.ini", QSettings::IniFormat);
    QString downloadlink = upd_ini.value("VERSION/DownloadLink").toString();
    char cmd[512];
    QFile::copy("checker/7za.exe","7za.exe");
    sprintf(cmd, "taskkill /f /im and2_checker.exe && SLEEP 1 && checker\\curl.exe -o AND2_CHECKER_UPDATE.7z -J -L -C - -# --retry 10 --insecure  %s && SLEEP 1 && 7za.exe x -y AND2_CHECKER_UPDATE.7z && SLEEP 1 && del 7za.exe && SLEEP 1 && del update.ini && SLEEP 1 && del AND2_CHECKER_UPDATE.7z && SLEEP 1 && start and2_checker.exe", downloadlink.toStdString().c_str());
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
    setCheckerParam("Main/LocalRev",rev);
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
        setCheckerParam("Update/DistantRev",rev_dist);
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
    this->setGeometry(0,0,300,120);
    this->setFixedSize(size());
    this->move(screen.center() - this->rect().center() );

    // Add widgets
    addon_mega_civ_pack = new QCheckBox(this);
    addon_mega_civ_pack->setText("Mega Civ Pack");
    addon_mega_civ_pack->setCheckable(true);
    layout->addWidget(addon_mega_civ_pack);

    addon_more_music = new QCheckBox(this);
    addon_more_music->setText("More music");
    addon_more_music->setCheckable(true);
    layout->addWidget(addon_more_music);

    addon_more_handicaps = new QCheckBox(this);
    addon_more_handicaps->setText("More handicaps");
    addon_more_handicaps->setCheckable(true);
    layout->addWidget(addon_more_handicaps);

    buttons->addStretch();
    addon_close = new QPushButton(this) ;
    addon_close->setText("Close");
    buttons->addWidget(addon_close);

    addon_apply = new QPushButton(this) ;
    addon_apply->setText("Apply changes");
    buttons->addWidget(addon_apply);

    layout->addLayout(buttons);

    // Check for unknown versions
    if(readCheckerParam("ADDON_MEGACIVPACK/FilesVersion").toInt() == 0)
    {
        addon_mega_civ_pack->setText("Mega Civ Pack detected (Unknown version)");
        addon_mega_civ_pack->setCheckable(true);
    }
    if(readCheckerParam("ADDON_MOREMUSIC/Version").toInt() == 0)
    {
        addon_more_music->setText("More music detected (Unknown version)");
        addon_more_music->setCheckable(true);
    }

    if(readCheckerParam("ADDON_MOREHANDICAPS/Version").toInt() == 0)
    {
        addon_more_handicaps->setText("More handicaps detected (Unknown version)");
        addon_more_handicaps->setCheckable(true);
    }

    // Check for known versions
    if(readCheckerParam("ADDON_MEGACIVPACK/FilesVersion").toFloat() > 0)
    {
        QString megacivpack_version = "Mega Civ Pack detected, version : " + readCheckerParam("ADDON_MEGACIVPACK/FilesVersion");
        addon_mega_civ_pack->setText(megacivpack_version);
        addon_mega_civ_pack->setCheckable(false);
    }
    if(readCheckerParam("ADDON_MOREMUSIC/Version").toFloat() > 0)
    {
        QString moremusic_version = "More music detected, version : " + readCheckerParam("ADDON_MOREMUSIC/Version");
        addon_more_music->setText(moremusic_version);
        addon_more_music->setCheckable(false);
    }

    if(readCheckerParam("ADDON_MOREHANDICAPS/Version").toFloat() > 0)
    {
        QString morehandicaps_version = "More handicaps detected, version : " + readCheckerParam("ADDON_MOREHANDICAPS/Version");
        addon_more_handicaps->setText(morehandicaps_version);
        addon_more_handicaps->setCheckable(false);
    }

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
    qDebug() << "Install Mega Civ Pack is" << addon_mega_civ_pack->isChecked();
    qDebug() << "Install More music is" << addon_more_music->isChecked();

    // Create a loop to wait for process execution
    QEventLoop wait_install;
    QTimer wait_timer;
    wait_timer.setInterval(2000);
    wait_timer.setSingleShot(true);
    connect(addon_setup,SIGNAL(finished()),&wait_install,SLOT(quit()));
    connect(&wait_timer, SIGNAL(timeout()), &wait_install, SLOT(quit()));

    if(addon_mega_civ_pack->isChecked())
    {
        // Write text and wait 2s
        addon_setup->appendText("\n\n****************************************\nDownloading Mega Civ Pack addon (835MB)\n****************************************\n\n");
        wait_timer.start();
        wait_install.exec();

        // Download addon
        QString download_addon_cmp = "checker/curl.exe -o AND2_MCP_BASE.7z -J -L -C - -# --retry 10 --insecure https://dl.dropboxusercontent.com/u/369241/AND2_MCP_BASE_V1.0.7z";
        bool cursor = false;
        addon_setup->execute(download_addon_cmp,cursor);
        wait_install.exec();
        QString download_addon_cmp2 = "checker/curl.exe -o AND2_MCP_FILES.7z -J -L -C - -# --retry 10 --insecure https://dl.dropboxusercontent.com/u/369241/AND2_MCP_FILES_V1.2.1.7z";
        addon_setup->execute(download_addon_cmp2,cursor);
        wait_install.exec();

        // Write text and wait 2s
        addon_setup->appendText("\n\n****************************************\nExtracting Mega Civ Pack Addon\n****************************************\n\n");
        wait_timer.start();
        wait_install.exec();

        QString extract_addon_cmp1 = "checker/7za.exe x -y AND2_MCP_BASE.7z";
        addon_setup->execute(extract_addon_cmp1,cursor);
        wait_install.exec();

        QString extract_addon_cmp2 = "checker/7za.exe x -y AND2_MCP_FILES.7z";
        addon_setup->execute(extract_addon_cmp2,cursor);
        wait_install.exec();

        // Write text and wait 2s
        addon_setup->appendText("\n\n****************************************\nMega Civ Pack addon installation finished !\n****************************************\n\n");
        wait_timer.start();
        wait_install.exec();

        QFile::remove("AND2_MCP_BASE.7z");
        QFile::remove("AND2_MCP_FILES.7z");
        check_addon_mcp();

        if(readCheckerParam("Addons/MCPVersion").toFloat() > 0)
        {
            QString megacivpack_version = "Mega Civ Pack detected, version : " + readCheckerParam("Addons/MCPVersion");
            addon_mega_civ_pack->setText(megacivpack_version);
            addon_mega_civ_pack->setCheckable(false);
        }
    }

    if(addon_more_music->isChecked())
    {
        // Write text and wait 2s
        addon_setup->appendText("\n\n****************************************\nDownloading Music Addon (500MB)\n****************************************\n\n");
        wait_timer.start();
        wait_install.exec();

        // Download addon
        QString download_addon_music = "checker/curl.exe -o AND2_MUSIC_ADDON.7z -J -L -C - --retry 10 --insecure https://dl.dropboxusercontent.com/u/369241/AND2_MUSIC_ADDON_V1.0.7z";
        bool cursor = false;
        addon_setup->execute(download_addon_music,cursor);
        wait_install.exec();

        // Write text and wait 2s
        addon_setup->appendText("\n\n****************************************\nExtracting Music Addon\n****************************************\n");
        wait_timer.start();
        wait_install.exec();

        QString extract_addon_music = "checker/7za.exe x -y AND2_MUSIC_ADDON.7z";
        addon_setup->execute(extract_addon_music,cursor);
        wait_install.exec();

        // Write text and wait 2s
        addon_setup->appendText("\n\n****************************************\nMore music addon installation finished !\n****************************************\n\n");
        wait_timer.start();
        wait_install.exec();
        QFile::remove("AND2_MUSIC_ADDON.7z");
        check_addon_more_music();

        if(readCheckerParam("Addons/MoreMusicVersion").toFloat() > 0)
        {
            QString moremusic_version = "More music detected, version : " + readCheckerParam("Addons/MoreMusicVersion");
            addon_more_music->setText(moremusic_version);
            addon_more_music->setCheckable(false);
        }
    }

    if(addon_more_handicaps->isChecked())
    {
        // Write text and wait 2s
        addon_setup->appendText("\n\n****************************************\nDownloading Handicaps Addon (0.02MB)\n****************************************\n\n");
        wait_timer.start();
        wait_install.exec();

        // Download addon
        QString download_addon_handicaps = "checker/curl.exe -o AND2_HANDICAP_ADDON.7z -J -L -C - -# --retry 10 --insecure https://dl.dropboxusercontent.com/u/369241/AND2_HANDICAP_ADDON_V1.2.7z";
        bool cursor = false;
        addon_setup->execute(download_addon_handicaps,cursor);
        wait_install.exec();

        // Write text and wait 2s
        addon_setup->appendText("\n\n****************************************\nExtracting Handicaps Addon\n****************************************\n");
        wait_timer.start();
        wait_install.exec();

        QString extract_addon_music = "checker/7za.exe x -y AND2_HANDICAP_ADDON.7z";
        addon_setup->execute(extract_addon_music,cursor);
        wait_install.exec();

        // Write text and wait 2s
        addon_setup->appendText("\n\n****************************************\nMore handicaps addon installation finished !\n****************************************\n\n");
        wait_timer.start();
        wait_install.exec();
        QFile::remove("AND2_HANDICAP_ADDON.7z");
        check_addon_more_handicaps();
        if(readCheckerParam("Addons/MoreHandicapsVersion").toFloat() > 0)
        {
            QString morehandicaps_version = "More handicaps detected, version : " + readCheckerParam("Addons/MoreHandicapsVersion");
            addon_more_handicaps->setText(morehandicaps_version);
            addon_more_handicaps->setCheckable(false);
        }
    }
}
