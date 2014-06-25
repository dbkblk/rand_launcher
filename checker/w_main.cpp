#include "w_main.h"
#include "f_civ.h"
#include "f_svn.h"
#include "f_check.h"
#include "w_options.h"
#include "updatebox.h"
#include "ui_w_main.h"
#include "ui_w_install.h"
#include "ui_w_options.h"
#include <lib/f_binaries.h>
#include <w_modules.h>

#include <QtCore>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QtGui>
#include <QtWidgets>
#include <QMessageBox>

w_main::w_main(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::w_main)
{
    ui->setupUi(this);

    // Translations
    translator = new QTranslator(this);
    QString loc;
    if(readCheckerParam("Main/Lang") == "error")
    {
        loc = QLocale::system().name().section('_', 0, 0);
    }
    else
    {
        loc = readCheckerParam("Main/Lang");
    }
    qDebug() << "Language used: " << loc;
    translator->load(QString("launcher_" + loc + ".qm"),"checker/lang/");
    qApp->installTranslator(translator);

    // Menu icons
    ui->languageEnglish->setIcon(QIcon("checker/icons/en.png"));
    ui->languageFinnish->setIcon(QIcon("checker/icons/fi.png"));
    ui->languageFrench->setIcon(QIcon("checker/icons/fr.png"));
    ui->languageGerman->setIcon(QIcon("checker/icons/de.png"));
    ui->languageHungarian->setIcon(QIcon("checker/icons/hu.png"));
    ui->languageItalian->setIcon(QIcon("checker/icons/it.png"));
    ui->languagePolish->setIcon(QIcon("checker/icons/pl.png"));
    ui->languageRussian->setIcon(QIcon("checker/icons/ru.png"));
    ui->languageSinhala->setIcon(QIcon("checker/icons/si.png"));
    ui->languageSpanish->setIcon(QIcon("checker/icons/es.png"));
    ui->actionOpen_mod_folder->setIcon(QIcon("checker/icons/open.png"));
    ui->actionExit->setIcon(QIcon("checker/icons/exit.png"));
    ui->actionForum->setIcon(QIcon("checker/icons/forum.png"));
    ui->actionBugreport->setIcon(QIcon("checker/icons/bugs.png"));
    ui->actionAbout_AND_Resurrection_team_forum->setIcon(QIcon("checker/icons/about.png"));
    ui->actionAddon_Mega_Civ_Pack->setIcon(QIcon("checker/icons/mcp.png"));
    ui->actionAddon_More_music_forum->setIcon(QIcon("checker/icons/music.png"));
    ui->actionHelp_translate_the_mod->setIcon(QIcon("checker/icons/translate.png"));
    ui->actionTranslate_the_launcher->setIcon(QIcon("checker/icons/translate.png"));
    ui->actionTranslate_the_mod_help->setIcon(QIcon("checker/icons/help.png"));
    ui->actionAddon_Blue_marble->setIcon(QIcon("checker/icons/blue_marble.png"));
    ui->actionClean_up->setIcon(QIcon("checker/icons/clean.png"));
    ui->actionRevert_to_an_older_revision->setIcon(QIcon("checker/icons/revert.png"));
    ui->menuFix_installation->setIcon(QIcon("checker/icons/fix.png"));
    ui->actionClear_cache->setIcon(QIcon("checker/icons/clear.png"));

    // Checker version
    setCheckerParam("Main/CheckerMajorVersion",QString::number(constants::MAJOR_CHECKER_VERSION));
    setCheckerParam("Main/CheckerMinorVersion",QString::number(constants::MINOR_CHECKER_VERSION));

    // Creation of widgets
    ubox = new updatebox(this);
    modules = new w_modules(this);

    // Main window shape

    this->setWindowTitle("Civilization IV: A New Dawn");
    this->setStyleSheet("w_main { background-image: url(checker/and2_background.jpg); background-position: bottom }");

    /*  Thread code, imported from https://github.com/fabienpn/simple-qt-thread-example */
    thread = new QThread();
    worker = new f_check();

    worker->moveToThread(thread);
    connect(worker, SIGNAL(workRequested()), thread, SLOT(start()));
    connect(thread, SIGNAL(started()), worker, SLOT(UMCheckUpdate()));
    connect(worker, SIGNAL(finished(bool)), thread, SLOT(quit()), Qt::DirectConnection);
    connect(worker, SIGNAL(finished(bool)), this, SLOT(UpdateWindowInfos()), Qt::DirectConnection);
    connect(worker, SIGNAL(finished(bool)), this, SLOT(UpdateAvailable(bool)));

    // Check launcher update in background (to avoid having two threads running simultaneously, the previous thread is aborted).
    worker->abort();
    thread->wait(); // If the thread is not running, this will immediately return.
    worker->requestWork();

    // Update labels and buttons
    UpdateWindowInfos();

    // Check for addons
    check_addon_mcp();
    check_addon_more_handicaps();
    check_addon_more_music();

    ui->retranslateUi(this);
}

w_main::~w_main()
{
    // Abort threads and close the ui
    worker->abort();
    thread->wait();
    qDebug() << "Deleting thread and worker in Thread " << this->QObject::thread()->currentThreadId();
    QFile::remove("checker/update.ini");
    QProcess::execute("taskkill /f /im curl.exe");
    delete thread;
    delete worker;
    delete ui;

}

void w_main::UpdateWindowInfos()
{
    // Versions label on the main Window

    QString vers = "Launcher rev. " + readCheckerParam("Main/CheckerMajorVersion") + "." + readCheckerParam("Main/CheckerMinorVersion") + "\nMod rev. " + readCheckerParam("Main/LocalRev");
    QPalette lb_palette;
    lb_palette.setColor(QPalette::WindowText, Qt::black);
    ui->lb_versions->setPalette(lb_palette);
    ui->lb_versions->setText(vers);
}

void w_main::RestoreButtonState()
{
    ui->bt_components->setStyleSheet("");
    ui->bt_components->setText(tr("Check for update"));
    return;
}

void w_main::UpdateAvailable(bool update)
{
    // Detect if it's a launcher update or another type
    if(update)
    {
        ui->bt_components->setStyleSheet("background-color: yellow");
        ui->bt_components->setText(tr("Update available !"));
    }
    return;
}

// Menu actions

void w_main::on_actionForum_triggered()
{
    QDesktopServices::openUrl(QUrl("http://forums.civfanatics.com/forumdisplay.php?f=369"));
}

void w_main::on_actionAddon_Mega_Civ_Pack_triggered()
{
    QDesktopServices::openUrl(QUrl("http://forums.civfanatics.com/showthread.php?t=521289"));
}

void w_main::on_actionBugreport_triggered()
{
    QDesktopServices::openUrl(QUrl("http://forums.civfanatics.com/showthread.php?t=474185"));
}

void w_main::on_actionAbout_AND_Resurrection_team_forum_triggered()
{
    QDesktopServices::openUrl(QUrl("http://forums.civfanatics.com/showthread.php?t=471460"));
}

void w_main::on_actionAddon_More_music_forum_triggered()
{
    QDesktopServices::openUrl(QUrl("http://forums.civfanatics.com/showthread.php?t=523763"));
}

void w_main::on_actionAddon_Blue_marble_triggered()
{
    QDesktopServices::openUrl(QUrl("http://www.civfanatics.net/bluemarble/content/index.php"));
}

void w_main::on_actionExit_triggered()
{
    QApplication::quit();
}

void w_main::on_actionOpen_mod_folder_triggered()
{
    QDesktopServices::openUrl(QUrl::fromLocalFile(QDir::currentPath()));
}

void w_main::on_actionHelp_translate_the_mod_triggered()
{
    QDesktopServices::openUrl(QUrl("https://www.transifex.com/projects/p/main-mod/"));
}

void w_main::on_actionTranslate_the_launcher_triggered()
{
    QDesktopServices::openUrl(QUrl("https://www.transifex.com/projects/p/launcher/"));
}

void w_main::on_actionTranslate_the_mod_help_triggered()
{
    QDesktopServices::openUrl(QUrl("http://forums.civfanatics.com/showthread.php?t=526671"));
}


// Menu buttons

void w_main::on_bt_launch_clicked()
{
    // Check if the game path is known

    if(readCheckerParam("Main/ExecutablePath") == "error") {
        QMessageBox::information(0, "Information", tr("To be able to launch the game from the launcher, you need to set the game path in the options window. (Options > Select game path)"));
        return;
    }
    else {
        launchGame();
    }

    // Check if the launcher should quit

    if(readCheckerParam("Main/QuitLauncher") == "1") {
        qApp->exit();
    }
    else {
        this->setWindowState(Qt::WindowMinimized);
    }
}

void w_main::on_bt_option_clicked()
{
    // Invoke the option window
    options = new w_options(this);
    options->show();
}



void w_main::on_bt_components_clicked()
{
    modules->show();
}

void w_main::on_actionGit_Pack_binaries_triggered()
{
    // Preparing signals
    QTimer wait_timer;
    QEventLoop wait_install;
    wait_timer.setInterval(1000);
    wait_timer.setSingleShot(true);
    connect(&wait_timer,SIGNAL(timeout()),&wait_install,SLOT(quit()));

    // Window layout
    QWidget *window = new QWidget();
    window->setGeometry(0,0,250,250);
    window->setWindowTitle(tr("Pack base binaries"));
    const QRect screen = QApplication::desktop()->screenGeometry();
    window->setFixedSize(250,250);
    window->move(screen.center());
    QLabel *label = new QLabel(window);
    label->setGeometry(20,20,210,210);
    label->setAlignment(Qt::AlignLeft | Qt::AlignTop);
    label->setWordWrap(true);

    // Process
    wait_timer.start();
    QString label_value;
    label_value = tr("Packing base files") + "\n(" + tr("this might take up to 10 min") + ":\n\n" + tr("Listing files") + "... ";
    label->setText(label_value);
    wait_install.exec();
    window->show();
    PackBinaries pack;
    QStringList file_list;
    file_list = pack.ListBinaries();
    wait_timer.start();
    label_value = label_value + tr("OK") + "\n" + tr("Generating hash file") + "... ";
    label->setText(label_value);
    wait_install.exec();
    pack.GenerateHashFile(file_list, "AND2_BASE_FILES.xml");
    wait_timer.start();
    label_value = label_value + tr("OK") + "\n" + tr("Gathering files") + "... ";
    label->setText(label_value);
    wait_install.exec();
    pack.CopyToTempFolder(file_list);
    wait_timer.start();
    label_value = label_value + tr("OK") + "\n" + tr("Compressing files") + "... ";
    label->setText(label_value);
    wait_install.exec();
    pack.CompressTempFolder("AND2_BASE_FILES.7z");
    QDir temp("temp/");
    temp.removeRecursively();
    wait_timer.start();
    label_value = label_value + tr("OK") + "\n" + tr("Cleaning folder") + "... " + tr("OK") + "\n\n" + QString(tr("Operation finished. The binaries have been packed in %1 and their checksums are listed in %2")).arg("\"AND2_BASE_FILES.7z\"").arg("\"AND2_BASE_FILES.xml\"");
    label->setText(label_value);
    wait_install.exec();
}

void w_main::on_actionGit_Create_update_binary_pack_triggered()
{
    // Preparing signals
    QTimer wait_timer;
    QEventLoop wait_install;
    wait_timer.setInterval(1000);
    wait_timer.setSingleShot(true);
    connect(&wait_timer,SIGNAL(timeout()),&wait_install,SLOT(quit()));

    // Window layout
    QWidget *window = new QWidget();
    window->setGeometry(0,0,250,250);
    window->setWindowTitle(tr("Pack update binaries"));
    const QRect screen = QApplication::desktop()->screenGeometry();
    window->setFixedSize(250,250);
    window->move(screen.center());
    QLabel *label = new QLabel(window);
    label->setGeometry(20,20,210,210);
    label->setAlignment(Qt::AlignLeft | Qt::AlignTop);
    label->setWordWrap(true);

    // Process
    wait_timer.start();
    QString label_value;
    label_value = QString(tr("Packing update files")) + QString("\n(") + QString(tr("this might take up to 10 min")) + QString(":\n\n") + QString("Downloading base signatures (NB: For testing purpose, the signature must already be in the folder)") + QString("...");
    label->setText(label_value);

    wait_timer.start();
    label_value = label_value + " " + tr("OK") + "\n" + tr("Listing files") + "...";
    label->setText(label_value);
    wait_install.exec();
    window->show();
    PackBinaries pack;
    QStringList existing_files;
    existing_files = pack.ListBinaries();

    wait_timer.start();
    label_value = label_value + " " + tr("OK") + "\n" + tr("Generating hash file") + "...";
    label->setText(label_value);
    wait_install.exec();
    //pack.GenerateHashFile(existing_files, "AND2_UPDATE_FILES.xml");

    wait_timer.start();
    label_value = label_value + " " + tr("OK") + "\n" + tr("Comparing base and update hashs") + "...";
    label->setText(label_value);
    wait_install.exec();
    QStringList updated_files;
    updated_files = pack.CompareHashs("AND2_BASE_FILES.xml","AND2_UPDATE_FILES.xml");

    qDebug() << "Pack files";
    wait_timer.start();
    label_value = label_value + " " + tr("OK") + "\n" + tr("Checking for new files") + "...";
    label->setText(label_value);
    wait_install.exec();
    QStringList new_files;
    new_files = pack.CheckNewFiles("AND2_BASE_FILES.xml",existing_files);

    wait_timer.start();
    label_value = label_value + " " + tr("OK") + "\n" + tr("Checking for missing files") + "...";
    label->setText(label_value);
    wait_install.exec();
    QStringList missing_files;
    missing_files = pack.CheckMissingFiles("AND2_BASE_FILES.xml",existing_files);

    wait_timer.start();
    label_value = label_value + " " + tr("OK") + "\n" + tr("Gathering files") + "...";
    label->setText(label_value);
    wait_install.exec();
    pack.CopyToTempFolder(updated_files);
    pack.CopyToTempFolder(new_files);

    wait_timer.start();
    label_value = label_value + " " + tr("OK") + "\n" + tr("Compressing files") + "...";
    label->setText(label_value);
    wait_install.exec();
    pack.CompressTempFolder("AND2_UPDATE_FILES.7z");
    QDir temp("temp/");
    temp.removeRecursively();

    wait_timer.start();
    label_value = label_value + " " + tr("OK") + "\n" + tr("Cleaning folder") + "..." + " " + tr("OK") + "\n\n" + QString(tr("Operation finished. The updated binaries have been packed in %1 and their checksums are listed in %2")).arg("\"AND2_UPDATE_FILES.7z\"").arg("\"AND2_UPDATE_FILES.xml\"");
    label->setText(label_value);
    wait_install.exec();
}

// Language support
void w_main::on_languageEnglish_triggered()
{
    translator->load(QString("launcher.qm"),"checker/lang/");
    setCheckerParam("Main/Lang","en");
    ui->retranslateUi(this);
}

void w_main::on_languageFrench_triggered()
{
    translator->load(QString("launcher_fr.qm"),"checker/lang/");
    setCheckerParam("Main/Lang","fr");
    ui->retranslateUi(this);
}

void w_main::on_languageSinhala_triggered()
{
    translator->load(QString("launcher_si.qm"),"checker/lang/");
    setCheckerParam("Main/Lang","si");
    ui->retranslateUi(this);
}

void w_main::on_languageHungarian_triggered()
{
    translator->load(QString("launcher_hu.qm"),"checker/lang/");
    setCheckerParam("Main/Lang","hu");
    ui->retranslateUi(this);
}

void w_main::on_languageFinnish_triggered()
{
    translator->load(QString("launcher_fi.qm"),"checker/lang/");
    setCheckerParam("Main/Lang","fi");
    ui->retranslateUi(this);
}

void w_main::on_languageItalian_triggered()
{
    translator->load(QString("launcher_it.qm"),"checker/lang/");
    setCheckerParam("Main/Lang","it");
    ui->retranslateUi(this);
}

void w_main::on_languageSpanish_triggered()
{
    translator->load(QString("launcher_es.qm"),"checker/lang/");
    setCheckerParam("Main/Lang","es");
    ui->retranslateUi(this);
}

void w_main::on_languageGerman_triggered()
{
    translator->load(QString("launcher_de.qm"),"checker/lang/");
    setCheckerParam("Main/Lang","de");
    ui->retranslateUi(this);
}

void w_main::on_languagePolish_triggered()
{
    translator->load(QString("launcher_pl.qm"),"checker/lang/");
    setCheckerParam("Main/Lang","pl");
    ui->retranslateUi(this);
}

void w_main::on_languageRussian_triggered()
{
    translator->load(QString("launcher_ru.qm"),"checker/lang/");
    setCheckerParam("Main/Lang","ru");
    ui->retranslateUi(this);
}

void w_main::on_actionClean_up_triggered()
{
    QProcess clean;
    clean.execute("checker/svn.exe cleanup");
    QMessageBox::information(this,"Mod cleaned","The mod has been cleaned.");
}

void w_main::on_actionRevert_to_an_older_revision_triggered()
{
    QString dial_rev = QInputDialog::getText(this, tr("Revision selector"), tr("Please enter the revision you want to revert to :"), QLineEdit::Normal);
    if(dial_rev.toInt() > 0)
    {
        if(dial_rev.toInt() < 737)
        {
            QMessageBox::critical(this,tr("Warning"),tr("The launcher has been introduced in revision 737. If you revert to an older revision, it will removed (you can reinstall it with the install link on the forum)."));
        }
        QFile::copy("checker/upd_proc.exe","upd_proc.exe");
        QProcess updater;
        updater.startDetached(QString("upd_proc.exe update %1 %2").arg(readCheckerParam("Main/LocalRev").toInt()).arg(dial_rev));
        QApplication::quit();
    }
}

void w_main::on_actionClear_cache_triggered()
{
    clearCache();
    QMessageBox::information(this,tr("Cache"),tr("The cache is now cleared. NOTE: It is already automatically cleared on update."));
}
