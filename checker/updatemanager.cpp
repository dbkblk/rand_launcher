#include "updatemanager.h"
#include "ui_updatemanager.h"
#include "civ_functions.h"
#include "updatebox.h"
#include "mainwindow.h"

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
    QVBoxLayout *vert_layout = new QVBoxLayout(this);
    QHBoxLayout *button_layout = new QHBoxLayout(this);
    changelog_box = new updatebox(this);
    addon_setup = new updatebox(this);

    // Layout
    this->setGeometry(0,0,550,300);
    this->setWindowTitle("Components manager");
    const QRect screen = QApplication::desktop()->screenGeometry();
    this->setFixedSize(size());
    this->move(screen.center() - this->rect().center() );

    // Table definition
    tab_updates = new QTableWidget(this);
    tab_updates->setRowCount(5);
    tab_updates->setColumnCount(4);
    tab_updates->setGeometry(10,10,530,280);
    tab_updates->setEditTriggers(QAbstractItemView::NoEditTriggers);
    tab_updates->setSortingEnabled(false);
    tab_updates->setSelectionMode(QAbstractItemView::NoSelection);
    tab_updates->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);
    tab_updates->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    tab_updates->setColumnWidth(0,100);
    tab_updates->setColumnWidth(1,100);
    tab_updates->setColumnWidth(2,90);
    tab_updates->setColumnWidth(3,100);

    QStringList tab_updates_header;
    tab_updates_header << "Local version" << "Distant version" << "Install / update" << "Changelog";
    tab_updates->setHorizontalHeaderLabels(tab_updates_header);
    QStringList tab_updates_columns;
    tab_updates_columns << "Core mod" << "Launcher" << "Addon: Mega civ pack" << "Addon: More music" << "Addon: More handicaps";
    tab_updates->setVerticalHeaderLabels(tab_updates_columns);
    tab_updates->horizontalHeader()->setSectionResizeMode(0,QHeaderView::Fixed);
    tab_updates->horizontalHeader()->setSectionResizeMode(1,QHeaderView::Fixed);
    tab_updates->horizontalHeader()->setSectionResizeMode(2,QHeaderView::Fixed);
    tab_updates->horizontalHeader()->setSectionResizeMode(3,QHeaderView::Fixed);
    tab_updates->verticalHeader()->setSectionResizeMode(0,QHeaderView::Fixed);
    tab_updates->verticalHeader()->setSectionResizeMode(1,QHeaderView::Fixed);
    tab_updates->verticalHeader()->setSectionResizeMode(2,QHeaderView::Fixed);
    tab_updates->verticalHeader()->setSectionResizeMode(3,QHeaderView::Fixed);
    tab_updates->verticalHeader()->setSectionResizeMode(4,QHeaderView::Fixed);

    /* Local revisions */
    // Core mod

    QTableWidgetItem *item_local_vers = new QTableWidgetItem;
    QString local_version = QString::number(svnLocalInfo());
    item_local_vers->setText(local_version);
    item_local_vers->setTextAlignment(Qt::AlignCenter);
    tab_updates->setItem(0,0,item_local_vers);

    // Launcher
    QTableWidgetItem *item_local_launcher = new QTableWidgetItem;
    item_local_launcher->setText(readCheckerParam("Main/CheckerMajorVersion") + "." + readCheckerParam("Main/CheckerMinorVersion"));
    item_local_launcher->setTextAlignment(Qt::AlignCenter);
    tab_updates->setItem(1,0,item_local_launcher);

    // Addon MCP
    QTableWidgetItem *item_local_addon_MCP = new QTableWidgetItem;
    item_local_addon_MCP->setText(readCheckerParam("ADDON_MEGACIVPACK/FilesVersion"));
    item_local_addon_MCP->setTextAlignment(Qt::AlignCenter);
    tab_updates->setItem(2,0,item_local_addon_MCP);

    // Addon More music
    QTableWidgetItem *item_local_addon_MoreMusic = new QTableWidgetItem;
    item_local_addon_MoreMusic->setText(readCheckerParam("ADDON_MOREMUSIC/Version"));
    item_local_addon_MoreMusic->setTextAlignment(Qt::AlignCenter);
    tab_updates->setItem(3,0,item_local_addon_MoreMusic);

    // Addon More handicaps
    QTableWidgetItem *item_local_addon_MoreHandicaps = new QTableWidgetItem;
    item_local_addon_MoreHandicaps->setText(readCheckerParam("ADDON_MOREHANDICAPS/Version"));
    item_local_addon_MoreHandicaps->setTextAlignment(Qt::AlignCenter);
    tab_updates->setItem(4,0,item_local_addon_MoreHandicaps);

    /* Distant revisions */
    // Core
    item_distant_vers = new QTableWidgetItem;
    tab_updates->setItem(0,1,item_distant_vers);
    item_distant_vers->setText(readCheckerParam("Update/DistantRev"));
    item_distant_vers->setTextAlignment(Qt::AlignCenter);

    // Launcher
    item_distant_launcher = new QTableWidgetItem;
    tab_updates->setItem(1,1,item_distant_launcher);
    item_distant_launcher->setText(readCheckerParam("Update/DistantCheckerMajorVersion") + "." + readCheckerParam("Update/DistantCheckerMinorVersion"));
    item_distant_launcher->setTextAlignment(Qt::AlignCenter);

    // Addon MCP
    item_distant_addon_MCP = new QTableWidgetItem;
    tab_updates->setItem(2,1,item_distant_addon_MCP);
    item_distant_addon_MCP->setText(readCheckerParam("ADDON_MEGACIVPACK/DistantBaseVersion"));
    item_distant_addon_MCP->setTextAlignment(Qt::AlignCenter);

    // Addon More music
    item_distant_addon_MoreMusic = new QTableWidgetItem;
    tab_updates->setItem(3,1,item_distant_addon_MoreMusic);
    item_distant_addon_MoreMusic->setText(readCheckerParam("ADDON_MOREMUSIC/DistantVersion"));
    item_distant_addon_MoreMusic->setTextAlignment(Qt::AlignCenter);

    // Addon More handicaps
    item_distant_addon_MoreHandicaps = new QTableWidgetItem;
    tab_updates->setItem(4,1,item_distant_addon_MoreHandicaps);
    item_distant_addon_MoreHandicaps->setText(readCheckerParam("ADDON_MOREHANDICAPS/DistantVersion"));
    item_distant_addon_MoreHandicaps->setTextAlignment(Qt::AlignCenter);

    /* Checkboxes */
    QWidget *update_core_widget = new QWidget();
    update_core_checkbox = new QCheckBox(this);
    QHBoxLayout *update_core_layout = new QHBoxLayout(update_core_widget);
    update_core_layout->addWidget(update_core_checkbox);
    update_core_layout->setAlignment(Qt::AlignCenter);
    update_core_layout->setContentsMargins(0,0,0,0);
    update_core_widget->setLayout(update_core_layout);
    tab_updates->setCellWidget(0,2,update_core_widget);

    QWidget *update_launcher_widget = new QWidget();
    update_launcher_checkbox = new QCheckBox(this);
    QHBoxLayout *update_launcher_layout = new QHBoxLayout(update_launcher_widget);
    update_launcher_layout->addWidget(update_launcher_checkbox);
    update_launcher_layout->setAlignment(Qt::AlignCenter);
    update_launcher_layout->setContentsMargins(0,0,0,0);
    update_launcher_widget->setLayout(update_launcher_layout);
    tab_updates->setCellWidget(1,2,update_launcher_widget);

    QWidget *update_addon_MCP_widget = new QWidget();
    update_addon_MCP_checkbox = new QCheckBox(this);
    QHBoxLayout *update_addon_MCP_layout = new QHBoxLayout(update_addon_MCP_widget);
    update_addon_MCP_layout->addWidget(update_addon_MCP_checkbox);
    update_addon_MCP_layout->setAlignment(Qt::AlignCenter);
    update_addon_MCP_layout->setContentsMargins(0,0,0,0);
    update_addon_MCP_widget->setLayout(update_addon_MCP_layout);
    tab_updates->setCellWidget(2,2,update_addon_MCP_widget);

    QWidget *update_addon_moremusic_widget = new QWidget();
    update_addon_moremusic_checkbox = new QCheckBox(this);
    QHBoxLayout *update_addon_moremusic_layout = new QHBoxLayout(update_addon_moremusic_widget);
    update_addon_moremusic_layout->addWidget(update_addon_moremusic_checkbox);
    update_addon_moremusic_layout->setAlignment(Qt::AlignCenter);
    update_addon_moremusic_layout->setContentsMargins(0,0,0,0);
    update_addon_moremusic_widget->setLayout(update_addon_moremusic_layout);
    tab_updates->setCellWidget(3,2,update_addon_moremusic_widget);

    QWidget *update_addon_morehandicaps_widget = new QWidget();
    update_addon_morehandicaps_checkbox = new QCheckBox(this);
    QHBoxLayout *update_addon_morehandicaps_layout = new QHBoxLayout(update_addon_morehandicaps_widget);
    update_addon_morehandicaps_layout->addWidget(update_addon_morehandicaps_checkbox);
    update_addon_morehandicaps_layout->setAlignment(Qt::AlignCenter);
    update_addon_morehandicaps_layout->setContentsMargins(0,0,0,0);
    update_addon_morehandicaps_widget->setLayout(update_addon_morehandicaps_layout);
    tab_updates->setCellWidget(4,2,update_addon_morehandicaps_widget);

    /* Changelog buttons */
    QWidget *button_core_widget = new QWidget();
    QPushButton *button_core_checkbox = new QPushButton(this);
    button_core_checkbox->setText("View");
    button_core_checkbox->setEnabled(true);
    QHBoxLayout *button_core_layout = new QHBoxLayout(button_core_widget);
    button_core_layout->addWidget(button_core_checkbox);
    button_core_layout->setAlignment(Qt::AlignCenter);
    button_core_layout->setContentsMargins(0,0,0,0);
    button_core_widget->setLayout(button_core_layout);
    tab_updates->setCellWidget(0,3,button_core_widget);

    QWidget *button_launcher_widget = new QWidget();
    QPushButton *button_launcher_checkbox = new QPushButton();
    button_launcher_checkbox->setText("View");
    QHBoxLayout *button_launcher_layout = new QHBoxLayout(button_launcher_widget);
    button_launcher_layout->addWidget(button_launcher_checkbox);
    button_launcher_layout->setAlignment(Qt::AlignCenter);
    button_launcher_layout->setContentsMargins(0,0,0,0);
    button_launcher_widget->setLayout(button_launcher_layout);
    tab_updates->setCellWidget(1,3,button_launcher_widget);

    QWidget *button_addon_MCP_widget = new QWidget();
    QPushButton *button_addon_MCP_checkbox = new QPushButton();
    button_addon_MCP_checkbox->setText("View");
    QHBoxLayout *button_addon_MCP_layout = new QHBoxLayout(button_addon_MCP_widget);
    button_addon_MCP_layout->addWidget(button_addon_MCP_checkbox);
    button_addon_MCP_layout->setAlignment(Qt::AlignCenter);
    button_addon_MCP_layout->setContentsMargins(0,0,0,0);
    button_addon_MCP_widget->setLayout(button_addon_MCP_layout);
    tab_updates->setCellWidget(2,3,button_addon_MCP_widget);

    QWidget *button_addon_moremusic_widget = new QWidget();
    QPushButton *button_addon_moremusic_checkbox = new QPushButton();
    button_addon_moremusic_checkbox->setText("View");
    QHBoxLayout *button_addon_moremusic_layout = new QHBoxLayout(button_addon_moremusic_widget);
    button_addon_moremusic_layout->addWidget(button_addon_moremusic_checkbox);
    button_addon_moremusic_layout->setAlignment(Qt::AlignCenter);
    button_addon_moremusic_layout->setContentsMargins(0,0,0,0);
    button_addon_moremusic_widget->setLayout(button_addon_moremusic_layout);
    tab_updates->setCellWidget(3,3,button_addon_moremusic_widget);

    QWidget *button_addon_morehandicaps_widget = new QWidget();
    QPushButton *button_addon_morehandicaps_checkbox = new QPushButton();
    button_addon_morehandicaps_checkbox->setText("View");
    QHBoxLayout *button_addon_morehandicaps_layout = new QHBoxLayout(button_addon_morehandicaps_widget);
    button_addon_morehandicaps_layout->addWidget(button_addon_morehandicaps_checkbox);
    button_addon_morehandicaps_layout->setAlignment(Qt::AlignCenter);
    button_addon_morehandicaps_layout->setContentsMargins(0,0,0,0);
    button_addon_morehandicaps_widget->setLayout(button_addon_morehandicaps_layout);
    tab_updates->setCellWidget(4,3,button_addon_morehandicaps_widget);

    // Buttons
    vert_layout->addWidget(tab_updates);
    QWidget *buttons = new QWidget();
    apply->setEnabled(false);
    apply->setText("Apply changes");
    cancel->setText("Cancel");
    button_layout->addStretch();
    button_layout->addWidget(cancel);
    button_layout->addWidget(apply);
    vert_layout->addLayout(button_layout);

    // Setting initial state


    // Actions
    connect(update_core_checkbox,SIGNAL(clicked()),this,SLOT(on_checkbox_clicked()));
    connect(update_launcher_checkbox,SIGNAL(clicked()),this,SLOT(on_checkbox_clicked()));
    connect(update_addon_MCP_checkbox,SIGNAL(clicked()),this,SLOT(on_checkbox_clicked()));
    connect(update_addon_morehandicaps_checkbox,SIGNAL(clicked()),this,SLOT(on_checkbox_clicked()));
    connect(update_addon_moremusic_checkbox,SIGNAL(clicked()),this,SLOT(on_checkbox_clicked()));
    connect(button_core_checkbox,SIGNAL(clicked()),this,SLOT(changelogCore()));
    connect(button_launcher_checkbox,SIGNAL(clicked()),this,SLOT(on_launcher_changelog_clicked()));
    connect(button_addon_MCP_checkbox,SIGNAL(clicked()),this,SLOT(on_addon_megacivpack_clicked()));
    connect(button_addon_morehandicaps_checkbox,SIGNAL(clicked()),this,SLOT(on_addon_sogroon_clicked()));
    connect(button_addon_moremusic_checkbox,SIGNAL(clicked()),this,SLOT(on_addon_sogroon_clicked()));
    connect(cancel,SIGNAL(clicked()),this,SLOT(close()));
    connect(apply,SIGNAL(clicked()),this,SLOT(addons_installation()));

}

updateManager::~updateManager()
{
    QProcess::execute("taskkill /f /im curl.exe");
}

void updateManager::updateDistantInfos()
{
    qDebug() << "Update infos";
    /* Update revisions */
    QString distant_version = QString::number(svnDistantInfo());
    this->item_distant_vers->setText(distant_version);
    this->item_distant_launcher->setText(readCheckerParam("Update/DistantCheckerMajorVersion") + "." + readCheckerParam("Update/DistantCheckerMinorVersion"));
    this->item_distant_addon_MCP->setText(readCheckerParam("ADDON_MEGACIVPACK/DistantBaseVersion"));
    this->item_distant_addon_MoreMusic->setText(readCheckerParam("ADDON_MOREMUSIC/DistantVersion"));
    this->item_distant_addon_MoreHandicaps->setText(readCheckerParam("ADDON_MOREMUSIC/DistantVersion"));
}

void updateManager::changelogCore()
{
    // Calculate changelog difference
    int chglog_diff = readCheckerParam("Update/DistantRev").toInt() - readCheckerParam("Main/LocalRev").toInt();
    qDebug() << "The changelog diff is equal to " << chglog_diff;

    bool value = true;
    QString command("checker/svn.exe log -l 10");
    //sprintf(command,"checker/svn.exe log -l %d -r HEAD:BASE",chglog_diff);
    changelog_box->changelogMode();
    changelog_box->show();
    changelog_box->execute(command,value);
    //connect(changelog_box,SIGNAL(finished()),this,SLOT(close()));
}

void updateManager::addons_installation()
{
    addon_setup->addonsMode();
    addon_setup->show();
    addon_setup->bt_chglog_close->setText("Close");

    // Check for checkbox state
    qDebug() << "Update core mod is" << update_core_checkbox->isChecked();
    qDebug() << "Update launcher is" << update_launcher_checkbox->isChecked();
    qDebug() << "Install Mega Civ Pack is" << update_addon_MCP_checkbox->isChecked();
    qDebug() << "Install More music is" << update_addon_moremusic_checkbox->isChecked();
    qDebug() << "Install More handicaps is" << update_addon_morehandicaps_checkbox->isChecked();

    // Create a loop to wait for process execution
    QEventLoop wait_install;
    QEventLoop wait_svn;
    QTimer wait_timer;
    wait_timer.setInterval(2000);
    wait_timer.setSingleShot(true);
    connect(addon_setup,SIGNAL(finished()),&wait_install,SLOT(quit()));
    connect(&wait_timer, SIGNAL(timeout()), &wait_install, SLOT(quit()));
    connect(addon_setup,SIGNAL(updated()), &wait_svn,SLOT(quit()));

    QSettings upd_ini("checker/update.ini", QSettings::IniFormat);

    // Core mod update
    if(update_core_checkbox->isChecked())
    {
        addon_setup->appendText("\n\n****************************************\nUpdating core mod\n****************************************\n");
        wait_timer.start();
        wait_install.exec();
        bool cursor = false;
        addon_setup->execute("checker/svn.exe update", cursor);
        wait_svn.exec();
        clearCache();
        clearGameOptions();
    }

    if(update_addon_MCP_checkbox->isChecked())
    {
        // Write text and wait 2s
        addon_setup->appendText("\n\n****************************************\nDownloading Mega Civ Pack addon (835MB)\n****************************************\n");
        wait_timer.start();
        wait_install.exec();

        // Download addon
        QString download_addon_mcp = "checker/curl.exe -o AND2_MCP_BASE.7z -J -L -C - --retry 10 --insecure " + upd_ini.value("ADDON_MEGACIVPACK/BaseLink").toString();
        bool cursor = false;
        addon_setup->execute(download_addon_mcp,cursor);
        wait_install.exec();
        QString download_addon_mcp2 = "checker/curl.exe -o AND2_MCP_FILES.7z -J -L -C - -# --retry 10 --insecure " + upd_ini.value("ADDON_MEGACIVPACK/FilesLink").toString();
        addon_setup->execute(download_addon_mcp2,cursor);
        wait_install.exec();

        // Write text and wait 2s
        addon_setup->appendText("\n\n****************************************\nExtracting Mega Civ Pack Addon\n****************************************\n");
        wait_timer.start();
        wait_install.exec();

        QString extract_addon_mcp1 = "checker/7za.exe x -y -otemp/ AND2_MCP_BASE.7z";
        addon_setup->execute(extract_addon_mcp1,cursor);
        wait_install.exec();

        QString extract_addon_mcp2 = "checker/7za.exe x -y -otemp/ AND2_MCP_FILES.7z";
        addon_setup->execute(extract_addon_mcp2,cursor);
        wait_install.exec();

        // Scan temp directory and generate a list of files
        QStringList addon_list;
        QDirIterator iterator("temp/", QDir::Files | QDir::NoDotAndDotDot,  QDirIterator::Subdirectories);
        while (iterator.hasNext())
        {
            iterator.next();
            QString filepath;
            filepath = iterator.filePath();
            if (filepath.endsWith(".")){iterator.next();};
            filepath.replace("temp/","");
            addon_list << filepath;
        }
        QFile output_list("uninstall_addon_MCP.txt");
        QString file;
        output_list.open(QIODevice::WriteOnly | QIODevice::Truncate);
        QTextStream out_enc(&output_list);
        addon_list.sort();
        foreach (file, addon_list) {
            out_enc << file << endl;
        }
        output_list.close();
        QFile::remove("checker/uninstall_addon_MCP.txt");
        output_list.rename("checker/uninstall_addon_MCP.txt");

        // Copy files to mod folder
        QDirIterator iterator2("temp/", QDir::Files | QDir::NoDotAndDotDot,  QDirIterator::Subdirectories);
        while (iterator2.hasNext())
        {
            QString filepath;
            iterator2.next();
            filepath = iterator2.filePath();
            //qDebug() << filepath;
            filepath.replace("temp/","");
            QFile::remove(filepath);
            QFile::rename(iterator2.filePath(),filepath);
        }

        QDir temp_dir("temp/");
        temp_dir.removeRecursively();

        // Write text and wait 2s
        addon_setup->appendText("\n\n****************************************\nMega Civ Pack addon installation finished !\n****************************************\n");
        wait_timer.start();
        wait_install.exec();

        QFile::remove("AND2_MCP_BASE.7z");
        QFile::remove("AND2_MCP_FILES.7z");
        check_addon_mcp();

    }

    if(update_addon_moremusic_checkbox->isChecked())
    {
        // Write text and wait 2s
        addon_setup->appendText("\n\n****************************************\nDownloading Music Addon (500MB)\n****************************************\n");
        wait_timer.start();
        wait_install.exec();

        // Download addon
        bool cursor = false;
        QString download_addon_music = "checker/curl.exe -o AND2_MUSIC_ADDON.7z -J -L -C - --retry 10 --insecure " + upd_ini.value("ADDON_MOREMUSIC/Link").toString();
        addon_setup->execute(download_addon_music,cursor);
        wait_install.exec();

        // Write text and wait 2s
        addon_setup->appendText("\n\n****************************************\nExtracting Music Addon\n****************************************\n");
        wait_timer.start();
        wait_install.exec();

        QString extract_addon_music = "checker/7za.exe x -y -otemp/ AND2_MUSIC_ADDON.7z";
        addon_setup->execute(extract_addon_music,cursor);
        wait_install.exec();

        // Scan temp directory and generate a list of files
        QStringList addon_list;
        QDirIterator iterator("temp/", QDir::Files | QDir::NoDotAndDotDot,  QDirIterator::Subdirectories);
        while (iterator.hasNext())
        {
            iterator.next();
            QString filepath;
            filepath = iterator.filePath();
            if (filepath.endsWith(".")){iterator.next();};
            filepath.replace("temp/","");
            addon_list << filepath;
        }
        QFile output_list("uninstall_addon_moremusic.txt");
        QString file;
        output_list.open(QIODevice::WriteOnly | QIODevice::Truncate);
        QTextStream out_enc(&output_list);
        addon_list.sort();
        foreach (file, addon_list) {
            out_enc << file << endl;
        }
        output_list.close();
        QFile::remove("checker/uninstall_addon_moremusic.txt");
        output_list.rename("checker/uninstall_addon_moremusic.txt");

        // Copy files to mod folder
        QDirIterator iterator2("temp/", QDir::Files | QDir::NoDotAndDotDot,  QDirIterator::Subdirectories);
        while (iterator2.hasNext())
        {
            QString filepath;
            iterator2.next();
            filepath = iterator2.filePath();
            //qDebug() << filepath;
            filepath.replace("temp/","");
            QFile::remove(filepath);
            QFile::rename(iterator2.filePath(),filepath);
        }

        QDir temp_dir("temp/");
        temp_dir.removeRecursively();

        // Write text and wait 2s
        addon_setup->appendText("\n\n****************************************\nMore music addon installation finished !\n****************************************\n");
        wait_timer.start();
        wait_install.exec();
        QFile::remove("AND2_MUSIC_ADDON.7z");
        check_addon_more_music();

    }

    if(update_addon_morehandicaps_checkbox->isChecked())
    {
        // Write text and wait 2s
        addon_setup->appendText("\n\n****************************************\nDownloading Handicaps Addon (0.02MB)\n****************************************\n\n");
        wait_timer.start();
        wait_install.exec();

        // Download addon
        QString download_addon_handicaps = "checker/curl.exe -o AND2_HANDICAP_ADDON.7z -J -L -C - -# --retry 10 --insecure " + upd_ini.value("ADDON_MOREHANDICAPS/Link").toString();
        bool cursor = false;
        addon_setup->execute(download_addon_handicaps,cursor);
        wait_install.exec();

        // Write text and wait 2s
        addon_setup->appendText("\n\n****************************************\nExtracting Handicaps Addon\n****************************************\n");
        wait_timer.start();
        wait_install.exec();

        QString extract_addon_music = "checker/7za.exe x -y -otemp/ AND2_HANDICAP_ADDON.7z";
        addon_setup->execute(extract_addon_music,cursor);
        wait_install.exec();

        // Scan temp directory and generate a list of files
        QStringList addon_list;
        QDirIterator iterator("temp/", QDir::Files | QDir::NoDotAndDotDot,  QDirIterator::Subdirectories);
        while (iterator.hasNext())
        {
            iterator.next();
            QString filepath;
            filepath = iterator.filePath();
            if (filepath.endsWith(".")){iterator.next();};
            filepath.replace("temp/","");
            addon_list << filepath;
        }
        QFile output_list("uninstall_addon_morehandicaps.txt");
        QString file;
        output_list.open(QIODevice::WriteOnly | QIODevice::Truncate);
        QTextStream out_enc(&output_list);
        addon_list.sort();
        foreach (file, addon_list) {
            out_enc << file << endl;
        }
        output_list.close();
        QFile::remove("checker/uninstall_addon_morehandicaps.txt");
        output_list.rename("checker/uninstall_addon_morehandicaps.txt");

        // Copy files to mod folder
        QDirIterator iterator2("temp/", QDir::Files | QDir::NoDotAndDotDot,  QDirIterator::Subdirectories);
        while (iterator2.hasNext())
        {
            QString filepath;
            iterator2.next();
            filepath = iterator2.filePath();
            //qDebug() << filepath;
            filepath.replace("temp/","");
            QFile::remove(filepath);
            QFile::rename(iterator2.filePath(),filepath);
        }

        QDir temp_dir("temp/");
        temp_dir.removeRecursively();

        // Write text and wait 2s
        addon_setup->appendText("\n\n****************************************\nMore handicaps addon installation finished !\n****************************************\n\n");
        wait_timer.start();
        wait_install.exec();
        QFile::remove("AND2_HANDICAP_ADDON.7z");
        check_addon_more_handicaps();
    }

    if(update_launcher_checkbox->isChecked())
    {
        addon_setup->appendText("\n\n****************************************\nInstalling launcher update. The program is going to be restarted !\n****************************************\n\n");
        wait_timer.start();
        wait_install.exec();
        launcherUpdate();
    }
}

void updateManager::on_launcher_changelog_clicked()
{
    QDesktopServices::openUrl(QUrl("https://github.com/dbkblk/and2_checker/releases"));
}

void updateManager::on_addon_sogroon_clicked()
{
    QDesktopServices::openUrl(QUrl("http://forums.civfanatics.com/showthread.php?t=523763"));
}

void updateManager::on_addon_megacivpack_clicked()
{
    QDesktopServices::openUrl(QUrl("http://forums.civfanatics.com/showthread.php?t=521289"));
}

void updateManager::on_checkbox_clicked()
{
    QFile update("checker/update.ini");
    if(update.exists())
    {
        if (update_core_checkbox->isChecked() == true || update_launcher_checkbox->isChecked() == true  || update_addon_MCP_checkbox->isChecked() == true  || update_addon_moremusic_checkbox->isChecked() == true  || update_addon_morehandicaps_checkbox->isChecked() == true )
        {
            this->apply->setEnabled(true);
        }
        else
        {
            this->apply->setEnabled(false);
        }
    }
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

void Worker::UMCheckUpdate()
{
    // Wait 5s before to check for update
    QEventLoop loop;
    QTimer::singleShot(10000, &loop, SLOT(quit()));
    loop.exec();

    // Begin processing
    qDebug()<<"Starting worker process in Thread "<<thread()->currentThreadId();
    bool update;
    QProcess download;
    download.start(constants::GLOBAL_UPDATE_URL);

    if (download.waitForFinished(60000))
    {
        QSettings upd_ini("checker/update.ini", QSettings::IniFormat);

        // Reading update info
        setCheckerParam("Update/Changelog",upd_ini.value("VERSION/Changelog").toString());
        setCheckerParam("Update/DistantCheckerMajorVersion",upd_ini.value("VERSION/CheckerMajorVersion").toString());
        setCheckerParam("Update/DistantCheckerMinorVersion",upd_ini.value("VERSION/CheckerMinorVersion").toString());
        setCheckerParam("ADDON_MOREMUSIC/DistantVersion",upd_ini.value("ADDON_MOREMUSIC/Version").toString());
        setCheckerParam("ADDON_MOREHANDICAPS/DistantVersion",upd_ini.value("ADDON_MOREHANDICAPS/Version").toString());
        setCheckerParam("ADDON_MEGACIVPACK/DistantBaseVersion",upd_ini.value("ADDON_MEGACIVPACK/BaseVersion").toString());
        setCheckerParam("ADDON_MEGACIVPACK/DistantBaseVersion",upd_ini.value("ADDON_MEGACIVPACK/FilesVersion").toString());

        if(LauncherVersionCalculation() == true || readCheckerParam("ADDON_MEGACIVPACK/FilesVersion").toFloat() < readCheckerParam("ADDON_MEGACIVPACK/DistantVersion").toFloat() || readCheckerParam("ADDON_MOREHANDICAPS/Version").toFloat() < readCheckerParam("ADDON_MOREHANDICAPS/DistantBaseVersion").toFloat() || readCheckerParam("ADDON_MOREMUSIC/Version").toFloat() < readCheckerParam("ADDON_MOREMUSIC/DistantVersion").toFloat() || svnLocalInfo() < svnDistantInfo()){
            update = true;
            qDebug() << "Update is " << update;
        }

        else
        {
            qDebug() << "No update is required";
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
    QSettings upd_ini("checker/update.ini", QSettings::IniFormat);
    QString downloadlink = upd_ini.value("VERSION/DownloadLink").toString();
    char cmd[512];
    QFile::copy("checker/7za.exe","7za.exe");
    sprintf(cmd, "taskkill /f /im and2_checker.exe && SLEEP 1 && checker\\curl.exe -o AND2_CHECKER_UPDATE.7z -J -L -C - -# --retry 10 --insecure  %s && SLEEP 1 && 7za.exe x -y AND2_CHECKER_UPDATE.7z && SLEEP 1 && del 7za.exe && SLEEP 1 && del checker\\update.ini && SLEEP 1 && del AND2_CHECKER_UPDATE.7z && SLEEP 1 && start and2_checker.exe", downloadlink.toStdString().c_str());
    qDebug() << "Update command : " << cmd;
    system(cmd);
    return 0;
}

bool LauncherVersionCalculation()
{
    if (readCheckerParam("Main/CheckerMajorVersion").toInt() < readCheckerParam("Update/DistantCheckerMajorVersion").toInt())
    {
        return true;
    }
    else if (readCheckerParam("Main/CheckerMajorVersion").toInt() == readCheckerParam("Update/DistantCheckerMajorVersion").toInt() && readCheckerParam("Main/CheckerMinorVersion").toInt() < readCheckerParam("Update/DistantCheckerMinorVersion").toInt())
    {
        return true;
    }
    else
    {
        return false;
    }
}

void restartLauncher()
{
    QProcess::startDetached(QApplication::applicationFilePath());
    exit(12);
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

bool clearGameOptions()
{
    setConfigParam("GameOptions","");
    qDebug() << "Cleared parameters";
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

