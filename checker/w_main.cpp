#include "w_main.h"
#include "f_civ.h"
#include "f_lang.h"
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

    /* Language routine : Get language parameter, else if OS language, then wait to fully initialize the GUI.
     * See f_lang.cpp for details */
    // Get OS language
    QString loc = QLocale::system().name().section('_', 0, 0);

    translator = new QTranslator(this);

    if(readCheckerParam("Main/Lang") == "error")
    {
        if(isLanguageSupported(loc)){
            setCheckerParam("Main/Lang",loc);
        }
        else {
            setCheckerParam("Main/Lang","en");
            loc = "en";
        }
    }
    else
    {
        loc = readCheckerParam("Main/Lang");
    }
    qDebug() << "Language used: " << getLanguageNameFromCode(loc);

    // Initialize sub-windows
    modules = new w_modules(this);
    modules->UpdateWindow();
    connect(modules, SIGNAL(exit()), this, SLOT(stopLauncher()));

    // Setup translator
    translator->load(QString("launcher_" + loc + ".qm"),"checker/lang/");
    qApp->installTranslator(translator);

    // GUI : Set menu icons
    ui->actionOpen_mod_folder->setIcon(QIcon("checker/icons/open.png"));
    ui->actionExit->setIcon(QIcon("checker/icons/exit.png"));
    ui->actionForum->setIcon(QIcon("checker/icons/forum.png"));
    ui->actionBugreport->setIcon(QIcon("checker/icons/bugs.png"));
    ui->actionAbout_AND_Resurrection_team_forum->setIcon(QIcon("checker/icons/about.png"));
    ui->actionAddon_Mega_Civ_Pack->setIcon(QIcon("checker/icons/mcp.png"));
    ui->actionAddon_More_music_forum->setIcon(QIcon("checker/icons/music.png"));
    ui->actionHelp_translate_the_mod->setIcon(QIcon("checker/icons/translate.png"));
    ui->actionTranslate_the_civilopedia->setIcon(QIcon("checker/icons/translate.png"));
    ui->actionTranslate_the_mod_help->setIcon(QIcon("checker/icons/help.png"));
    ui->actionWebsite->setIcon(QIcon("checker/icons/blue_marble.png"));
    ui->menuAddons->setIcon(QIcon("checker/icons/addons.png"));
    ui->menuFix_installation->setIcon(QIcon("checker/icons/fix.png"));
    ui->actionClean_up->setIcon(QIcon("checker/icons/clean.png"));
    ui->actionClear_cache->setIcon(QIcon("checker/icons/clear.png"));
    ui->actionReset->setIcon(QIcon("checker/icons/reset.png"));

    // GUI : Set title and background

    this->setWindowTitle("Civilization IV: A New Dawn");
    this->setStyleSheet("w_main { background-image: url(checker/and2_background.jpg); background-position: bottom }");

    // Update : Prepare a background task to check for update without slowing down the GUI
    /*  Thread code, imported from https://github.com/fabienpn/simple-qt-thread-example */
    thread = new QThread();
    worker = new f_check();

    worker->moveToThread(thread);
    connect(worker, SIGNAL(workRequested()), thread, SLOT(start()));
    connect(thread, SIGNAL(started()), worker, SLOT(CheckForUpdate()));
    connect(worker, SIGNAL(finished(bool)), thread, SLOT(quit()), Qt::DirectConnection);
    connect(worker, SIGNAL(finished(bool)), this, SLOT(UpdateWindowInfos()), Qt::DirectConnection);
    connect(worker, SIGNAL(finished(bool)), this, SLOT(UpdateAvailable(bool)));
    connect(worker, SIGNAL(finished(bool)), modules, SLOT(UpdateWindow()));

    // Update : Kill the previous background task if any, then start the task
    worker->abort();
    thread->wait(); // If the thread is not running, this will immediately return.
    worker->requestWork();

    // GUI : Update the local version and font color
    UpdateWindowInfos();

    // Translations : Reload the GUI with the correct translation
    ui->retranslateUi(this);
    clear_language_state();
    populate_language_menu(loc);
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
    // GUI : Set versions label on the main Window
    QString vers = "Launcher rev. " + versions::CHECKER_VERSION + "\nMod rev. " + readCheckerParam("Main/LocalRev");
    QPalette lb_palette;
    lb_palette.setColor(QPalette::WindowText, Qt::black);
    ui->lb_versions->setPalette(lb_palette);
    QFont f( "Arial", 8);
    ui->lb_versions->setFont(f);
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


void w_main::on_actionWebsite_triggered()
{
    QDesktopServices::openUrl(QUrl("http://anewdawn.sf.net"));
}

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
    QDesktopServices::openUrl(QUrl("http://anewdawn.sf.net/pages/credits/"));
}

void w_main::on_actionAddon_More_music_forum_triggered()
{
    QDesktopServices::openUrl(QUrl("http://forums.civfanatics.com/showthread.php?t=523763"));
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
    QDesktopServices::openUrl(QUrl("https://www.transifex.com/projects/p/and-main-mod/"));
}

void w_main::on_actionTranslate_the_civilopedia_triggered()
{
    QDesktopServices::openUrl(QUrl("https://www.transifex.com/projects/p/and-civilopedia-strings/"));
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
    modules->show();
}

// GUI : Set all language selector to 0 before to check the correct one
void w_main::clear_language_state()
{
    foreach(QAction *action, ui->menuLanguage->actions()){
        action->setChecked(0);
    }
}

// GUI : Individual translations selectors
void w_main::language_select(QString langCode){
    qDebug() << "Language set to" << getLanguageNameFromCode(langCode);
    translator->load(QString("launcher_" + langCode + ".qm"),"checker/lang/");
    setCheckerParam("Main/Lang",langCode);
    ui->retranslateUi(this);
    modules->UpdateWindow();
    clear_language_state();
}

void w_main::populate_language_menu(QString code)
{
    if(code=="en"){ui->language_en->setChecked(1);}
    ui->language_en->setIcon(QIcon("checker/icons/en.png"));
    ui->language_en->setText(tr("English"));
    if(code=="fr"){ui->language_fr->setChecked(1);}
    ui->language_fr->setIcon(QIcon("checker/icons/fr.png"));
    ui->language_fr->setText(tr("French") + " (" + getLanguageProgressFromCode("fr") + "%)");
    if(code=="de"){ui->language_de->setChecked(1);}
    ui->language_de->setIcon(QIcon("checker/icons/de.png"));
    ui->language_de->setText(tr("German") + " (" + getLanguageProgressFromCode("de") + "%)");
    if(code=="it"){ui->language_it->setChecked(1);}
    ui->language_it->setIcon(QIcon("checker/icons/it.png"));
    ui->language_it->setText(tr("Italian") + " (" + getLanguageProgressFromCode("it") + "%)");
    if(code=="es"){ui->language_es->setChecked(1);}
    ui->language_es->setIcon(QIcon("checker/icons/es.png"));
    ui->language_es->setText(tr("Spanish") + " (" + getLanguageProgressFromCode("es") + "%)");
    if(code=="fi"){ui->language_fi->setChecked(1);}
    ui->language_fi->setIcon(QIcon("checker/icons/fi.png"));
    ui->language_fi->setText(tr("Finnish") + " (" + getLanguageProgressFromCode("fi") + "%)");
    if(code=="hu"){ui->language_hu->setChecked(1);}
    ui->language_hu->setIcon(QIcon("checker/icons/hu.png"));
    ui->language_hu->setText(tr("Hungarian") + " (" + getLanguageProgressFromCode("hu") + "%)");
    if(code=="pl"){ui->language_pl->setChecked(1);}
    ui->language_pl->setIcon(QIcon("checker/icons/pl.png"));
    ui->language_pl->setText(tr("Polish") + " (" + getLanguageProgressFromCode("pl") + "%)");
    if(code=="ru"){ui->language_ru->setChecked(1);}
    ui->language_ru->setIcon(QIcon("checker/icons/ru.png"));
    ui->language_ru->setText(tr("Russian") + " (" + getLanguageProgressFromCode("ru") + "%)");
    if(code=="cs"){ui->language_cs->setChecked(1);}
    ui->language_cs->setIcon(QIcon("checker/icons/cs.png"));
    ui->language_cs->setText(tr("Czech") + " (" + getLanguageProgressFromCode("cs") + "%)");
    if(code=="da"){ui->language_da->setChecked(1);}
    ui->language_da->setIcon(QIcon("checker/icons/da.png"));
    ui->language_da->setText(tr("Danish") + " (" + getLanguageProgressFromCode("da") + "%)");
    if(code=="ar"){ui->language_ar->setChecked(1);}
    ui->language_ar->setIcon(QIcon("checker/icons/ar.png"));
    ui->language_ar->setText(tr("Arabic") + " (" + getLanguageProgressFromCode("ar") + "%)");
    if(code=="tr"){ui->language_tr->setChecked(1);}
    ui->language_tr->setIcon(QIcon("checker/icons/tr.png"));
    ui->language_tr->setText(tr("Turkish") + " (" + getLanguageProgressFromCode("tr") + "%)");

    setGameOption("Language", getLanguageGameNumberFromCode(code));
    if(isLanguageSupported(code)){
        ui->flag->setPixmap("checker/icons/" + code + ".png");
    }

    // Compare language OS with game language
    QString gameLanguage = readGameOption("Language");
    if(gameLanguage != getLanguageGameNumberFromCode(code)){
        qDebug() << "Launcher language is" << code << "while game language is" << getLanguageCodeFromGameNumber(gameLanguage) << ". Setting game language.";
        setGameOption("Language", getLanguageGameNumberFromCode(code));
    }

    // If language is not supported and fScale is positive, set it to negative value
    if (getFScale() == true && !isLanguageDefault(code)){
        setFScale(false);
    }
    if(isLanguageDefault(code)){
        setFScale(true);
    }

    // Set recommended game font
    QString recfont = getLanguageRecommendedFont(code);
    if (recfont != getLanguageCurrentFont(code)){
        setLanguageFont(recfont);
    }
}

void w_main::on_language_en_triggered()
{
    QString lang = "en";
    language_select(lang);
    populate_language_menu(lang);
}

void w_main::on_language_fr_triggered()
{
    QString lang = "fr";
    language_select(lang);
    populate_language_menu(lang);
}

void w_main::on_language_hu_triggered()
{
    QString lang = "hu";
    language_select(lang);
    populate_language_menu(lang);
}

void w_main::on_language_fi_triggered()
{
    QString lang = "fi";
    language_select(lang);
    populate_language_menu(lang);
}

void w_main::on_language_it_triggered()
{
    QString lang = "it";
    language_select(lang);
    populate_language_menu(lang);
}

void w_main::on_language_es_triggered()
{
    QString lang = "es";
    language_select(lang);
    populate_language_menu(lang);
}

void w_main::on_language_de_triggered()
{
    QString lang = "de";
    language_select(lang);
    populate_language_menu(lang);
}

void w_main::on_language_pl_triggered()
{
    QString lang = "pl";
    language_select(lang);
    populate_language_menu(lang);
}

void w_main::on_language_ru_triggered()
{
    QString lang = "ru";
    language_select(lang);
    populate_language_menu(lang);
}

void w_main::on_language_cs_triggered()
{
    QString lang = "cs";
    language_select(lang);
    populate_language_menu(lang);
}

void w_main::on_language_da_triggered()
{
    QString lang = "da";
    language_select(lang);
    populate_language_menu(lang);
}

void w_main::on_language_ar_triggered()
{
    QString lang = "ar";
    language_select(lang);
    populate_language_menu(lang);
}

void w_main::on_language_tr_triggered()
{
    QString lang = "tr";
    language_select(lang);
    populate_language_menu(lang);
}


// Game : Clear the cache
void w_main::on_actionClear_cache_triggered()
{
    clearCache();
    QMessageBox::information(this,tr("Cache"),tr("The cache is now cleared. NOTE: It is already automatically cleared on update."));
}

void w_main::on_actionReset_triggered()
{
    f_check *reset = new f_check;
    connect(reset, SIGNAL(exit()), this, SLOT(stopLauncher()));
    QMessageBox msgBox;
    msgBox.setWindowTitle(tr("Reset mod"));
    msgBox.setText(tr("This will reset the mod to the default state. Any modification or launcher preferences will be removed."));
    msgBox.setInformativeText(tr("Are you sure to continue ?"));
    msgBox.setStandardButtons(QMessageBox::Ok |  QMessageBox::Cancel);
    msgBox.setDefaultButton(QMessageBox::Cancel);
    int ret = msgBox.exec();
    switch (ret) {
        case QMessageBox::Ok:
            reset->PrepareUpdate();
            reset->ActionReset();
            break;
        case QMessageBox::Cancel:
            break;
        default:
            break;
    }
}

void w_main::stopLauncher(){
    qDebug("Closing UI");
    this->close();
}
