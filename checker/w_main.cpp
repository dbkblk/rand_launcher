#include "w_main.h"
#include "f_civ.h"
#include "f_svn.h"
#include "f_check.h"
#include "w_options.h"
#include "ui_w_main.h"
#include "ui_w_install.h"
#include "ui_w_options.h"
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

    // Translations : Get language parameter, else if OS language, then wait to fully initialize the GUI.
    translator = new QTranslator(this);
    QString loc;
    if(readCheckerParam("Main/Lang") == "error")
    {
        loc = QLocale::system().name().section('_', 0, 0);
        setCheckerParam("Main/Lang",loc);
    }
    else
    {
        loc = readCheckerParam("Main/Lang");
    }
    qDebug() << "Language used: " << loc;
    translator->load(QString("launcher_" + loc + ".qm"),"checker/lang/");

    qApp->installTranslator(translator);

    // GUI : Fix language menu selector
    clear_language_state();
    if(loc=="en"){ui->language_en->setChecked(1);}
    if(loc=="fr"){ui->language_fr->setChecked(1);}
    if(loc=="si"){ui->language_si->setChecked(1);}
    if(loc=="hu"){ui->language_hu->setChecked(1);}
    if(loc=="fi"){ui->language_fi->setChecked(1);}
    if(loc=="it"){ui->language_it->setChecked(1);}
    if(loc=="de"){ui->language_de->setChecked(1);}
    if(loc=="pl"){ui->language_pl->setChecked(1);}
    if(loc=="es"){ui->language_es->setChecked(1);}
    if(loc=="ru"){ui->language_ru->setChecked(1);}

    // GUI : Set menu icons
    ui->language_en->setIcon(QIcon("checker/icons/en.png"));
    ui->language_fi->setIcon(QIcon("checker/icons/fi.png"));
    ui->language_fr->setIcon(QIcon("checker/icons/fr.png"));
    ui->language_de->setIcon(QIcon("checker/icons/de.png"));
    ui->language_hu->setIcon(QIcon("checker/icons/hu.png"));
    ui->language_it->setIcon(QIcon("checker/icons/it.png"));
    ui->language_pl->setIcon(QIcon("checker/icons/pl.png"));
    ui->language_ru->setIcon(QIcon("checker/icons/ru.png"));
    ui->language_si->setIcon(QIcon("checker/icons/si.png"));
    ui->language_es->setIcon(QIcon("checker/icons/es.png"));
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
    ui->actionEnter_SVN_command->setIcon(QIcon("checker/icons/svn.png"));

    // Internal : Set internal checker version as parameter in the ini file
    setCheckerParam("Main/CheckerMajorVersion",QString::number(constants::MAJOR_CHECKER_VERSION));
    setCheckerParam("Main/CheckerMinorVersion",QString::number(constants::MINOR_CHECKER_VERSION));

    // Update : SVN behavior fix on update (erase my files by default)
    if(readCheckerParam("Main/UpdateBehavior") == "error"){
        setCheckerParam("Main/UpdateBehavior","theirs-full");
    }

    // GUI : Set title and background

    this->setWindowTitle("Civilization IV: A New Dawn");
    this->setStyleSheet("w_main { background-image: url(checker/and2_background.jpg); background-position: bottom }");

    // Update : Prepare a background task to check for update without slowing down the GUI
    /*  Thread code, imported from https://github.com/fabienpn/simple-qt-thread-example */
    thread = new QThread();
    worker = new f_check();

    worker->moveToThread(thread);
    connect(worker, SIGNAL(workRequested()), thread, SLOT(start()));
    connect(thread, SIGNAL(started()), worker, SLOT(UMCheckUpdate()));
    connect(worker, SIGNAL(finished(bool)), thread, SLOT(quit()), Qt::DirectConnection);
    connect(worker, SIGNAL(finished(bool)), this, SLOT(UpdateWindowInfos()), Qt::DirectConnection);
    connect(worker, SIGNAL(finished(bool)), this, SLOT(UpdateAvailable(bool)));

    // Update : Kill the previous background task if any, then start the task
    worker->abort();
    thread->wait(); // If the thread is not running, this will immediately return.
    worker->requestWork();

    // GUI : Update the SVN local version and font color
    UpdateWindowInfos();

    // Translations : Reload the GUI with the correct translation
    ui->retranslateUi(this);
}

w_main::~w_main()
{
    // Abort threads and close the ui
    worker->abort();
    thread->wait();
    qDebug() << "Deleting thread and worker in Thread " << this->QObject::thread()->currentThreadId();
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
    // GUI : Restore the standard aspect
    ui->bt_components->setStyleSheet("");
    ui->bt_components->setText(tr("Check for update"));
    return;
}

void w_main::UpdateAvailable(bool update)
{
    // GUID : Detect if it's a launcher update or another type then turn the update button to yellow
    if(update)
    {
        ui->bt_components->setStyleSheet("background-color: yellow");
        ui->bt_components->setText(tr("Update available !"));
    }
    return;
}

// GUI : Menu actions

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


void w_main::on_bt_launch_clicked()
// GUI : Launch game button
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
// GUI : Invoke the option window
{
        options = new w_options(this);
    options->show();
}



void w_main::on_bt_components_clicked()
// GUI : Modules button
{
    modules = new w_modules(this);
    modules->show();
}

// GUI : Set all language selector to 0 before to check the correct one
void w_main::clear_language_state()
{
    ui->language_en->setChecked(0);
    ui->language_fr->setChecked(0);
    ui->language_si->setChecked(0);
    ui->language_hu->setChecked(0);
    ui->language_fi->setChecked(0);
    ui->language_it->setChecked(0);
    ui->language_de->setChecked(0);
    ui->language_pl->setChecked(0);
    ui->language_es->setChecked(0);
    ui->language_ru->setChecked(0);
}

// GUI : Individual translations selectors
void w_main::on_language_en_triggered()
{
    translator->load(QString("launcher.qm"),"checker/lang/");
    setCheckerParam("Main/Lang","en");
    ui->retranslateUi(this);
    clear_language_state();
    ui->language_en->setChecked(1);
}

void w_main::on_language_fr_triggered()
{
    translator->load(QString("launcher_fr.qm"),"checker/lang/");
    setCheckerParam("Main/Lang","fr");
    ui->retranslateUi(this);
    clear_language_state();
    ui->language_fr->setChecked(1);
}

void w_main::on_language_si_triggered()
{
    translator->load(QString("launcher_si.qm"),"checker/lang/");
    setCheckerParam("Main/Lang","si");
    ui->retranslateUi(this);
    clear_language_state();
    ui->language_si->setChecked(1);
}

void w_main::on_language_hu_triggered()
{
    translator->load(QString("launcher_hu.qm"),"checker/lang/");
    setCheckerParam("Main/Lang","hu");
    ui->retranslateUi(this);
    clear_language_state();
    ui->language_hu->setChecked(1);
}

void w_main::on_language_fi_triggered()
{
    translator->load(QString("launcher_fi.qm"),"checker/lang/");
    setCheckerParam("Main/Lang","fi");
    ui->retranslateUi(this);
    clear_language_state();
    ui->language_fi->setChecked(1);
}

void w_main::on_language_it_triggered()
{
    translator->load(QString("launcher_it.qm"),"checker/lang/");
    setCheckerParam("Main/Lang","it");
    ui->retranslateUi(this);
    clear_language_state();
    ui->language_it->setChecked(1);
}

void w_main::on_language_es_triggered()
{
    translator->load(QString("launcher_es.qm"),"checker/lang/");
    setCheckerParam("Main/Lang","es");
    ui->retranslateUi(this);
    clear_language_state();
    ui->language_es->setChecked(1);
}

void w_main::on_language_de_triggered()
{
    translator->load(QString("launcher_de.qm"),"checker/lang/");
    setCheckerParam("Main/Lang","de");
    ui->retranslateUi(this);
    clear_language_state();
    ui->language_de->setChecked(1);
}

void w_main::on_language_pl_triggered()
{
    translator->load(QString("launcher_pl.qm"),"checker/lang/");
    setCheckerParam("Main/Lang","pl");
    ui->retranslateUi(this);
    clear_language_state();
    ui->language_pl->setChecked(1);
}

void w_main::on_language_ru_triggered()
{
    translator->load(QString("launcher_ru.qm"),"checker/lang/");
    setCheckerParam("Main/Lang","ru");
    ui->retranslateUi(this);
    clear_language_state();
    ui->language_ru->setChecked(1);
}

// Game : Clear the cache
void w_main::on_actionClear_cache_triggered()
{
    clearCache();
    QMessageBox::information(this,tr("Cache"),tr("The cache is now cleared. NOTE: It is already automatically cleared on update."));
}
