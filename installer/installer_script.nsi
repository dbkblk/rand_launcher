; Installation script
;--------------------------------

SetCompressor /SOLID LZMA

; Modern UI
;--------------------------------

  !include "MUI.nsh"
  !define VERSION "1.04"

; General information
;--------------------------------

; The name of the installer
Name "Civilization IV: A New Dawn"

; The file to write
OutFile "AND2_installer.exe"

; The default installation directory
InstallDir "$DOCUMENTS\My Games\Beyond the sword\Mods\"

; Request application privileges
RequestExecutionLevel user

;Variables
;--------------------------------
  Var StartMenuFolder

; Layout
;--------------------------------
!define MUI_ICON "AND_icon.ico"
!define MUI_WELCOMEFINISHPAGE_BITMAP "left_image.bmp"

; Page definition
;--------------------------------
!define MUI_WELCOMEPAGE_TITLE $(WELCOME_TITLE)
!define MUI_WELCOMEPAGE_TEXT $(WELCOME)

!define MUI_DIRECTORYPAGE_TEXT_TOP $(DIRECTORY)

;!define MUI_FINISHPAGE_RUN "$INSTDIR\and2_checker.exe"

!define MUI_STARTMENUPAGE_DEFAULTFOLDER "Civilization IV - A New Dawn"

!insertmacro MUI_PAGE_WELCOME
!insertmacro MUI_PAGE_COMPONENTS
!insertmacro MUI_PAGE_DIRECTORY
RequestExecutionLevel admin
!insertmacro MUI_PAGE_STARTMENU 0 $StartMenuFolder
!insertmacro MUI_PAGE_INSTFILES
;!insertmacro MUI_PAGE_FINISH
!insertmacro MUI_UNPAGE_WELCOME
!insertmacro MUI_UNPAGE_CONFIRM
!insertmacro MUI_UNPAGE_INSTFILES
;!insertmacro MUI_UNPAGE_FINISH

; Language
;--------------------------------
!insertmacro MUI_LANGUAGE "English"
!insertmacro MUI_LANGUAGE "French"
!insertmacro MUI_LANGUAGE "German"
!insertmacro MUI_LANGUAGE "Italian"
!insertmacro MUI_LANGUAGE "Polish"
!insertmacro MUI_LANGUAGE "Spanish"

Function .onInit
        !insertmacro MUI_LANGDLL_DISPLAY
FunctionEnd

Function .onInstSuccess
SetOutPath "$INSTDIR\Rise of Mankind - A New Dawn\"
Exec "$INSTDIR\Rise of Mankind - A New Dawn\and2_checker.exe"
SetOutPath "$INSTDIR"
FunctionEnd

AutoCloseWindow true 

; Translations
;--------------------------------

; English

LangString WELCOME_TITLE ${LANG_ENGLISH} "Civilization IV: A New Dawn Expansion pack"
LangString WELCOME ${LANG_ENGLISH} "Launcher version: ${VERSION}\n\nThis setup wizard will guide you through the installation of Civilization IV: A New Dawn.\n\nThe mod will be installed in 'My Documents\My Games\Beyond the Sword\Mods\' by default. \nIt will create a shortcut (optional) to the mod launcher, which will be used to easily download, update or configure the mod installation.\n\nWARNING : Any existing mod installation is compatible. However, if you have modded files, it could be overwritten on mod update."
LangString REQUIRED ${LANG_ENGLISH} "required"
LangString DIRECTORY ${LANG_ENGLISH} "Setup will install the expansion pack in the following folder.$\nTo install it in a different folder, click on 'Browse...' and select another folder.$\n$\nNOTA: It is highly recommended to use the default folder selected below. However, you can choose to install the mod directly into the game folder ('Sid Meier's Civilization IV Beyond the Sword\Beyond the Sword\Mods\')."
LangString FINISH ${LANG_ENGLISH} "The launcher is now installed. On the first launch, it will detect if the mod is present in the directory. If it's not, just follow the installation procedure."
LangString RUN ${LANG_ENGLISH} "Start the mod launcher"
LangString SHORTCUT ${LANG_ENGLISH} "Create Desktop Shortcut"
LangString MSVC10 ${LANG_ENGLISH} "Microsoft Visual C++ 2010 Redist is not installed. Downloading and installing now. Please wait..."
LangString MSVC13 ${LANG_ENGLISH} "Microsoft Visual C++ 2013 Redist is not installed. Downloading and installing now. Please wait..."

; German

LangString WELCOME_TITLE ${LANG_GERMAN} "Civilization IV: A New Dawn Expansionserweiterung"
LangString WELCOME ${LANG_GERMAN} "Launcher-Version: ${VERSION}\n\nDieser Installationsassistent wird Sie durch die Installation von 'Civilization IV: A New Dawn' führen.\n\nDie Mod wird standardmäßig in das Verzeichnis 'Dokumente\My Games\Beyond the Sword\Mods\' installiert.\n\nEs kann eine Verknüpfung zum Launcher erstellt werden (optional). Dieser kann zum einfach Download, Update und Konfiguration der Mod-Installation verwendet werden.\n\nWARNUNG: Alle existierenden Mod-Installationen sind kompatibel. Teilweise können jedoch veränderte Dateien beim Update überschrieben werden."
LangString REQUIRED ${LANG_GERMAN} "benötigt"
LangString DIRECTORY ${LANG_GERMAN} "Das Setupprogramm wird das Expansionspack in das folgende Verzeichnis kopieren.$\nUm einen anderen Installationsort zu wählen, klicken Sie bitte 'Durchsuchen...' und wählen ein anderes Verzeichnis.$\nAchtung: Das unten angegebene Standardverzeichnis sollte verwendet werden. Andererseits kann die Mod auch direkt in das Spielverzeichnis ('Sid Meier's Civilization IV Beyond the Sword\Beyond the Sword\Mods\') installiert werden."
LangString FINISH ${LANG_GERMAN} "Der Launcher ist jetzt installiert. Beim ersten Start wird überprüft, ob die Mod im Verzeichnis vorhanden ist. Sollte dies nicht der Fall sein, so folgen Sie bitte der Installationsroutine."
LangString RUN ${LANG_GERMAN} "Den Mod-Launcher starten"
LangString SHORTCUT ${LANG_GERMAN} "Desktopverknüpfung erstellen"
LangString MSVC10 ${LANG_GERMAN} "Microsoft Visual C++ 2010 Redist ist nicht installiert. Das Paket wird jetzt heruntergeladen und installiert. Bitte warten..."
LangString MSVC13 ${LANG_GERMAN} "Microsoft Visual C++ 2013 Redist ist nicht installiert. Das Paket wird jetzt heruntergeladen und installiert. Bitte warten..."

; Italian

LangString WELCOME_TITLE ${LANG_ITALIAN} "Civilization IV: A New Dawn Expansion pack"
LangString WELCOME ${LANG_ITALIAN} "Versione Launcher: ${VERSION}\n\nQuesta configurazione guidata vi guiderà attraverso l'installazione di Civilization IV: A New Dawn.\n\nVerrà installato il mod in 'My Documents\My Games\Beyond the Sword\Mods' di default. \nSi creerà un collegamento (opzionale) per il lanciatore mod, che verrà utilizzato per facilmente scaricare, aggiornare o configurare l'installazione mod.\n\nAttenzione: Qualsiasi installazione esistente mod è compatibile. Tuttavia, se avete i file modded, potrebbe essere sovrascritto su aggiornamento mod."
LangString REQUIRED ${LANG_ITALIAN} "required"
LangString DIRECTORY ${LANG_ITALIAN} "Verrà installato il pacchetto di espansione nella seguente cartella. $\nInstallarlo in una cartella diversa, fare clic su 'Sfoglia...' e selezionare un'altra cartella. $\n$\nNOTA: è consigliabile utilizzare la cartella predefinita selezionata di seguito. Tuttavia, si può scegliere di installare il mod direttamente nella cartella del gioco ('Sid Meier's Civilization IV Beyond the Sword\Beyond the Sword\Mods')."
LangString FINISH ${LANG_ITALIAN} "Il lanciatore è ora installato. Il primo avvio, rileva se la mod è presente nella directory. Se non lo è, basta seguire la procedura di installazione."
LangString RUN ${LANG_ITALIAN} "Avviare il launcher mod"
LangString SHORTCUT ${LANG_ITALIAN} "Creare il collegamento sul Desktop"
LangString MSVC10 ${LANG_ITALIAN} "Non è installato Microsoft Visual C++ 2010 Redist. Scaricare e installare ora. Attendere prego..."
LangString MSVC13 ${LANG_ITALIAN} "Non è installato Microsoft Visual C++ 2013 Redist. Scaricare e installare ora. Attendere prego..."

; French

LangString WELCOME_TITLE ${LANG_FRENCH} "Civilization IV: A New Dawn pack d'expansion"
LangString WELCOME ${LANG_FRENCH} "Version du lanceur: ${VERSION}\n\nCet assistant d'installation va vous guider pour l'installer de Civilization IV: A New Dawn.\nLe mod sera installé dans 'My Documents\My Games\Beyond the Sword\Mods\' par défaut. \nIl va créer un raccourcis (option) vers le lanceur, qui sera utilisé pour télécharger, mettre à jour ou configurer l'installation du mod.\n\nATTENTION : Si le mod est déjà installé, le lanceur pourrait remplacer certains de vos fichiers pendant les mises à jour."
LangString REQUIRED ${LANG_FRENCH} "requis"
LangString DIRECTORY ${LANG_FRENCH} "L'installateur va installer le pack d'expansion dans le dossier suivant.$\nPour l'installer dans un dossier différent, cliquez sur 'Parcourir...' et sélectionnez un autre dossier.$\n$\nNOTE: Il est hautement recommandé d'utiliser le dossier par défaut sélectionné ci-dessous. Cependant, vous pouvez choisir d'installer le mod directement dans le dossier du jeu ('Sid Meier's Civilization IV Beyond the Sword\Beyond the Sword\Mods\')."
LangString FINISH ${LANG_FRENCH} "Le lanceur est maintenant installé. Au premier lancement, il va essayer de détecter si le mod est présent dans le répertoire. Si ce n'est pas le cas, il suffit de suivre la procédure d'installation."
LangString RUN ${LANG_FRENCH} "Démarrer le lanceur"
LangString SHORTCUT ${LANG_FRENCH} "Créer un raccourci sur le bureau"
LangString MSVC10 ${LANG_FRENCH} "Microsoft Visual C++ 2010 Redist n'est pas installé. Téléchargement et installation en cours. Veuillez patienter..."
LangString MSVC13 ${LANG_FRENCH} "Microsoft Visual C++ 2013 Redist n'est pas installé. Téléchargement et installation en cours. Veuillez patienter..."

; Polish

LangString WELCOME_TITLE ${LANG_POLISH} "Modyfikacja Civilization IV: A New Dawn"
LangString WELCOME ${LANG_POLISH} "Wersja launchera: ${VERSION}\n\nInstalatow poprowadzi Cię przez proces instalacji modyfikacji: Civilization IV: A New Dawn.\n\nModyfikacja zostanie zainstalowana w 'My Documents\My Games\Beyond the Sword\Mods\' (domyślnie).\n\nStworzy skrót (opcjonalnie) do launchera modyfikacji, który może zostać użyty do łatwego pobierania, aktualizacji lub konfiguracji modyfikacji.\n\nUWAGA : Jakakolwiek inna instalacja modyfikacja jest kompatybilna. Jednak jeśli masz jakieś zmodyfikowane pliki mogą one zostać nadpisane."
LangString REQUIRED ${LANG_POLISH} "wymagane"
LangString DIRECTORY ${LANG_POLISH} "Instalator zainstaluje modyfikacje w wybranym katalogu.$\nAby zainstalować w innym katalogu kliknij 'Przeglądaj...' i wybierz inny folder.$\n$\nUWAGA: Jest bardzo rekomendowane użycie domyślnej ścieżki. Tak czy inaczej możesz wybrać ścieżkę beżpośrednio do folderu z grą ('Sid Meier's Civilization IV Beyond the Sword\Beyond the Sword\Mods\')."
LangString FINISH ${LANG_POLISH} "Launcher został zainstalowany. Przy pierwszym uruchomieniu, wykryje czy modyfikacja znajduje się w podanym katalogu. Jeśli jej nie znajdzie, instalator przeprowadzi Cię przez proces instalacji."
LangString RUN ${LANG_POLISH} "Uruchom laucher modyfikacji"
LangString SHORTCUT ${LANG_POLISH} "Stwórz skrót na pulpicie"
LangString MSVC10 ${LANG_POLISH} "Microsoft Visual C++ 2010 Redist jest nie zainstalowany. Pobieranie oraz instalacja. Proszę czekać..."
LangString MSVC13 ${LANG_POLISH} "Microsoft Visual C++ 2013 Redist jest nie zainstalowany. Pobieranie oraz instalacja. Proszę czekać..."


; Spanish

LangString WELCOME_TITLE ${LANG_SPANISH} "Civilización IV: A New Dawn pack de expansión"
LangString WELCOME ${LANG_SPANISH} "Versión del lanzador: ${VERSION}\n\nEste asistente le guiará a través de la instalación de Civilization IV: A New Dawn.\n\nEl mod se instalará en 'Mis documentos\My Games\Beyond the Sword\Mods\' de forma predeterminada.\nCreará un acceso directo (opcional) al lanzador mod, que se utilizará para descargar fácilmente, actualizar o configurar la mod instalación.\n\nADVERTENCIA: Cualquier instalación existente del mod es compatible. Sin embargo, si tienes archivos modificadas, puede sobrescribirse sobre actualización del mod."
LangString REQUIRED ${LANG_SPANISH} "necesario"
LangString DIRECTORY ${LANG_SPANISH} "Programa de instalación instalará el paquete de expansión en la siguiente carpeta.\nPara instalarlo en una carpeta diferente, haga clic en 'Examinar...' y seleccione otra carpeta.\n\nNOTA: se recomienda encarecidamente utilizar la carpeta predeterminada seleccionada por debajo. Sin embargo, puede instalar el mod directamente en la carpeta del juego (\'Sid Meier\'s Civilization IV Beyond the Sword\Beyond the Sword\Mods\')."
LangString FINISH ${LANG_SPANISH} "El lanzador está instalado. En el primer lanzamiento, detectará si el mod está presente en el directorio. Si no es así, sólo sigue el procedimiento de instalación."
LangString RUN ${LANG_SPANISH} "Iniciar el lanzador mod"
LangString SHORTCUT ${LANG_SPANISH} "Crear acceso directo del escritorio"
LangString MSVC10 ${LANG_SPANISH} "No está instalado Microsoft Visual C++ Redist 2010. Descargar e instalar ahora. Espera..."
LangString MSVC13 ${LANG_SPANISH} "No está instalado Microsoft Visual C++ 2013 Redist. Descargar e instalar ahora. Espera..."

; Installation
;--------------------------------

Section "A New Dawn" ;No components page, name is not important
SectionIn RO
AddSize 1700000

  ; Set output path to the installation directory.
  SetOutPath $INSTDIR
  
  ; Put file there
  File /r "..\release_files\*"

;Create uninstaller
  WriteUninstaller "$INSTDIR\Rise of Mankind - A New Dawn\Uninstall.exe"

  !insertmacro MUI_STARTMENU_WRITE_BEGIN 0
    
    ;Create shortcuts
    CreateDirectory "$SMPROGRAMS\$StartMenuFolder"
	SetOutPath "$INSTDIR\Rise of Mankind - A New Dawn\"
    CreateShortCut "$SMPROGRAMS\$StartMenuFolder\Uninstall.lnk" "$INSTDIR\Rise of Mankind - A New Dawn\Uninstall.exe"
	CreateShortCut "$SMPROGRAMS\$StartMenuFolder\Civilization IV - A New Dawn.lnk" "$INSTDIR\Rise of Mankind - A New Dawn\and2_checker.exe"
	SetOutPath "$INSTDIR"
  
  !insertmacro MUI_STARTMENU_WRITE_END
  
SectionEnd ; end the section

Section "$(SHORTCUT)"
SetOutPath "$INSTDIR\Rise of Mankind - A New Dawn\"
CreateShortcut "$DESKTOP\Civilization IV - A New Dawn.lnk" "$INSTDIR\Rise of Mankind - A New Dawn\and2_checker.exe"
SectionEnd

Section "MSVC 2010 ($(REQUIRED))"
SetOutPath $INSTDIR
ExecWait '"$INSTDIR\Rise of Mankind - A New Dawn\checker\vcredist_x86_2010.exe"  /passive /norestart'

SectionEnd

; Uninstallation
;--------------------------------


Section "Uninstall"

; Delete files

RMDir /r "$INSTDIR"
  
  !insertmacro MUI_STARTMENU_GETFOLDER 0 $StartMenuFolder
    
  Delete "$SMPROGRAMS\$StartMenuFolder\Uninstall.lnk"
Delete "$SMPROGRAMS\$StartMenuFolder\Civilization IV - A New Dawn.lnk"
  RMDir "$SMPROGRAMS\$StartMenuFolder"

SectionEnd


