; Installation script
;--------------------------------

SetCompressor /SOLID LZMA

; Modern UI
;--------------------------------

  !include "MUI.nsh"
  !define VERSION "0.12"

; General information
;--------------------------------

; The name of the installer
Name "Civilization IV: A New Dawn"

; The file to write
OutFile "AND2_installer.exe"

; The default installation directory
InstallDir "$DOCUMENTS\My Games\Beyond the sword\Mods\Rise of Mankind - A New Dawn\"

; Request application privileges
RequestExecutionLevel user

; Shortcut creation
;--------------------------------

Function DesktopShortcut
CreateShortcut "$desktop\Civilization IV - A New Dawn.lnk" "$instdir\and2_checker.exe"
FunctionEnd


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

!define MUI_FINISHPAGE_TITLE "Civilization IV - A New Dawn"
!define MUI_FINISHPAGE_TEXT $(FINISH)
!define MUI_FINISHPAGE_NOAUTOCLOSE
!define MUI_FINISHPAGE_RUN_CHECKED
!define MUI_FINISHPAGE_RUN "$INSTDIR\and2_checker.exe"
!define MUI_FINISHPAGE_RUN_TEXT $(RUN)
!define MUI_FINISHPAGE_SHOWREADME ""
!define MUI_FINISHPAGE_SHOWREADME_CHECKED
!define MUI_FINISHPAGE_SHOWREADME_TEXT $(SHORTCUT)
!define MUI_FINISHPAGE_SHOWREADME_FUNCTION DesktopShortcut

!define MUI_STARTMENUPAGE_DEFAULTFOLDER "Civilization IV - A New Dawn"

!insertmacro MUI_PAGE_WELCOME
!insertmacro MUI_PAGE_COMPONENTS
!insertmacro MUI_PAGE_DIRECTORY
RequestExecutionLevel admin
!insertmacro MUI_PAGE_STARTMENU 0 $StartMenuFolder
!insertmacro MUI_PAGE_INSTFILES
!insertmacro MUI_PAGE_FINISH
!insertmacro MUI_UNPAGE_WELCOME
!insertmacro MUI_UNPAGE_CONFIRM
!insertmacro MUI_UNPAGE_INSTFILES
!insertmacro MUI_UNPAGE_FINISH

; Language
;--------------------------------
!insertmacro MUI_LANGUAGE "English"
!insertmacro MUI_LANGUAGE "French"
!insertmacro MUI_LANGUAGE "Italian"
!insertmacro MUI_LANGUAGE "Sinhala"
!insertmacro MUI_LANGUAGE "Spanish"

function .onInit
        !insertmacro MUI_LANGDLL_DISPLAY
functionEnd

; Translations
;--------------------------------

; English

LangString WELCOME_TITLE ${LANG_ENGLISH} "Civilization IV: A New Dawn Expansion pack"
LangString WELCOME ${LANG_ENGLISH} "Launcher version: ${VERSION}\n\nThis setup wizard will guide you through the installation of Civilization IV: A New Dawn.\n\nThe mod will be installed in 'My Documents\My Games\Beyond the Sword\Mods\' by default. \nIt will create a shortcut (optional) to the mod launcher, which will be used to easily download, update or configure the mod installation.\n\nWARNING : Any existing mod installation is compatible. However, if you have modded files, it could be overwritten on mod update."
LangString DIRECTORY ${LANG_ENGLISH} "Setup will install the expansion pack in the following folder.$\nTo install it in a different folder, click on 'Browse...' and select another folder.$\n$\nNOTA: It is highly recommended to use the default folder selected below. However, you can choose to install the mod directly into the game folder ('Sid Meier's Civilization IV Beyond the Sword\Beyond the Sword\Mods\')."
LangString FINISH ${LANG_ENGLISH} "The launcher is now installed. On the first launch, it will detect if the mod is present in the directory. If it's not, just follow the installation procedure."
LangString RUN ${LANG_ENGLISH} "Start the mod launcher"
LangString SHORTCUT ${LANG_ENGLISH} "Create Desktop Shortcut"
LangString MSVC10 ${LANG_ENGLISH} "Microsoft Visual C++ 2013 Redist is not installed. Downloading and installing now. Please wait..."
LangString MSVC13 ${LANG_ENGLISH} "Microsoft Visual C++ 2010 Redist is not installed. Downloading and installing now. Please wait..."

; Italian

LangString WELCOME_TITLE ${LANG_ITALIAN} "Civilization IV: A New Dawn Expansion pack"
LangString WELCOME ${LANG_ITALIAN} "Versione Launcher: ${VERSION}\n\nQuesta configurazione guidata vi guiderà attraverso l'installazione di Civilization IV: A New Dawn.\n\nVerrà installato il mod in 'My Documents\My Games\Beyond the Sword\Mods' di default. \nSi creerà un collegamento (opzionale) per il lanciatore mod, che verrà utilizzato per facilmente scaricare, aggiornare o configurare l'installazione mod.\n\nAttenzione: Qualsiasi installazione esistente mod è compatibile. Tuttavia, se avete i file modded, potrebbe essere sovrascritto su aggiornamento mod."
LangString DIRECTORY ${LANG_ITALIAN} "Verrà installato il pacchetto di espansione nella seguente cartella. $\nInstallarlo in una cartella diversa, fare clic su 'Sfoglia...' e selezionare un'altra cartella. $\n$\nNOTA: è consigliabile utilizzare la cartella predefinita selezionata di seguito. Tuttavia, si può scegliere di installare il mod direttamente nella cartella del gioco ('Sid Meier\'s Civilization IV Beyond the Sword\Beyond the Sword\Mods')."
LangString FINISH ${LANG_ITALIAN} "Il lanciatore è ora installato. Il primo avvio, rileva se la mod è presente nella directory. Se non lo è, basta seguire la procedura di installazione."
LangString RUN ${LANG_ITALIAN} "Avviare il launcher mod"
LangString SHORTCUT ${LANG_ITALIAN} "Creare il collegamento sul Desktop"
LangString MSVC10 ${LANG_ITALIAN} "Non è installato Microsoft Visual C++ 2013 Redist. Scaricare e installare ora. Attendere prego..."
LangString MSVC13 ${LANG_ITALIAN} "Non è installato Microsoft Visual C++ 2010 Redist. Scaricare e installare ora. Attendere prego..."

; French

LangString WELCOME_TITLE ${LANG_FRENCH} "Civilization IV: A New Dawn pack d'expansion"
LangString WELCOME ${LANG_FRENCH} "Version du lanceur: ${VERSION}\n\nCet assistant d'installation va vous guider pour l'installer de Civilization IV: A New Dawn.\nLe mod sera installé dans 'My Documents\My Games\Beyond the Sword\Mods\' par défaut. \nIl va créer un raccourcis (option) vers le lanceur, qui sera utilisé pour télécharger, mettre à jour ou configurer l'installation du mod.\n\nATTENTION : Si le mod est déjà installé, le lanceur pourrait remplacer certains de vos fichiers pendant les mises à jour."
LangString DIRECTORY ${LANG_FRENCH} "L'installateur va installer le pack d'expansion dans le dossier suivant.$\nPour l'installer dans un dossier différent, cliquez sur 'Parcourir...' et sélectionnez un autre dossier.$\n$\nNOTE: Il est hautement recommandé d'utiliser le dossier par défaut sélectionné ci-dessous. Cependant, vous pouvez choisir d'installer le mod directement dans le dossier du jeu ('Sid Meier's Civilization IV Beyond the Sword\Beyond the Sword\Mods\')."
LangString FINISH ${LANG_FRENCH} "Le lanceur est maintenant installé. Au premier lancement, il va essayer de détecter si le mod est présent dans le répertoire. Si ce n'est pas le cas, il suffit de suivre la procédure d'installation."
LangString RUN ${LANG_FRENCH} "Démarrer le lanceur"
LangString SHORTCUT ${LANG_FRENCH} "Créer un raccourci sur le bureau"
LangString MSVC10 ${LANG_FRENCH} "Microsoft Visual C++ 2013 Redist n'est pas installé. Téléchargement et installation en cours. Veuillez patienter..."
LangString MSVC13 ${LANG_FRENCH} "Microsoft Visual C++ 2010 Redist n'est pas installé. Téléchargement et installation en cours. Veuillez patienter..."

; Sinhala

LangString WELCOME_TITLE ${LANG_SINHALA} "4 වන ශිෂ්ටාචාරය : නව අවධියක උදාව"
LangString WELCOME ${LANG_SINHALA} "විහිදුවා හරින සංස්කරණය:${VERSION}\nමෙම පිහිටුවීම් ක්‍රමය 4 වන ශිෂ්ධාචාරය ස්ථාපනයට උපදෙස් සපයයි : නව උදාවක් \nමොඩ් ස්ථාපනය කළ යුත්තේ \'මගේ ලියවිලි/මගේ ක්‍රීඩා /කඩු වලට ඔබ්බට ගිය /මොඩ් මුල් ආකාරයෙන් \nඑය මොඩ් දියත් කිරීමට කෙටි මාර්ගයක් සපයයි ,එය පහසුවෙන් භාගත කිරීමට උපකාරී වේ.\nමොඩ් ස්ථානගත කිරීම නවීකරණය හෝ පිළියෙළ කිරීම . \nඅවවාදයයි :පවත්නා ඕනෑම මොඩ් ස්ථාපනයක් අනුකුල වේ .ඔබ සතුව මොඩ් ගොණු තිබේනම් ඒවා නවිකරණ හෝ නැවත ලිවිම කළ යුතුය ."
LangString DIRECTORY ${LANG_SINHALA} "පරිස්ථිතිය පුළුල් ලෙස පවතින ගොනුවෙහි ස්ථාපනය කළ යුතුය.$\nඑය වෙනස් ගොනුවක ස්ථාපනය කිරීමට ,විමසීම ක්ලික් කර වෙනත් ගොනුවක් තොර ගත යුතුය$\n$\nසටහන :එය වෙනත් ගොනුවක තොර ගැනීම ඉහල ලෙස නිර්දේශ කෙරේ .කෙසේ වෙතත් ඔබට මොඩ් ඍජු ලෙසම ක්‍රීඩා ගොනුවෙහි ස්ථානගත කළ හැක.(\'සිඩ් මෙයිරස් 4 වන ශිෂ්ටාචාරය අසිපත් වලින් එපිටට \ සිපත් වලින් එපිටට\මොඩ්ස්\')."
LangString FINISH ${LANG_SINHALA} "දැන් දියත් කිරීම ස්ථාපිතයි .පළමු දියත් කිරීමේදී ,මොඩ් නාමාවලියෙහි පවතින බව මෙහිදී අනාවරණය කරයි , නොඑසේනම් ස්ථානගත කිරිමේ ක්‍රියාමාර්ගය අනුගමනය කළ යුතුය ."
LangString RUN ${LANG_SINHALA} "මොඩ් දියත් කිරීම අරඹන්න"
LangString SHORTCUT ${LANG_SINHALA} "මුහුණත කෙටිමාර්ගය සකස් කරන්න"
LangString MSVC10 ${LANG_SINHALA} "මයික්‍රොසොෆ්ට් විෂුවල් සී ++ 2013 ස්ථානගත කර නොමැත .භාගත කිරීම සහ ස්ථානගත කිරීම සිදු කරන්න . කරුණාකර රැදී සිටින්න ."
LangString MSVC13 ${LANG_SINHALA} "මයික්‍රොසොෆ්ට් විෂුවල් සී ++ 2010 ස්ථානගත කර නොමැත .භාගත කිරීම සහ ස්ථානගත කිරීම සිදු කරන්න . කරුණාකර රැදී සිටින්න ."

; Spanish

LangString WELCOME_TITLE ${LANG_SPANISH} "Civilización IV: A New Dawn pack de expansión"
LangString WELCOME ${LANG_SPANISH} "Versión del lanzador: ${VERSION}\n\nEste asistente le guiará a través de la instalación de Civilization IV: A New Dawn.\n\nEl mod se instalará en 'Mis documentos\My Games\Beyond the Sword\Mods\' de forma predeterminada.\nCreará un acceso directo (opcional) al lanzador mod, que se utilizará para descargar fácilmente, actualizar o configurar la mod instalación.\n\nADVERTENCIA: Cualquier instalación existente del mod es compatible. Sin embargo, si tienes archivos modificadas, puede sobrescribirse sobre actualización del mod."
LangString DIRECTORY ${LANG_SPANISH} "Programa de instalación instalará el paquete de expansión en la siguiente carpeta.\nPara instalarlo en una carpeta diferente, haga clic en 'Examinar...' y seleccione otra carpeta.\n\nNOTA: se recomienda encarecidamente utilizar la carpeta predeterminada seleccionada por debajo. Sin embargo, puede instalar el mod directamente en la carpeta del juego (\'Sid Meier\'s Civilization IV Beyond the Sword\Beyond the Sword\Mods\')."
LangString FINISH ${LANG_SPANISH} "El lanzador está instalado. En el primer lanzamiento, detectará si el mod está presente en el directorio. Si no es así, sólo sigue el procedimiento de instalación."
LangString RUN ${LANG_SPANISH} "Iniciar el lanzador mod"
LangString SHORTCUT ${LANG_SPANISH} "Crear acceso directo del escritorio"
LangString MSVC10 ${LANG_SPANISH} "No está instalado Microsoft Visual C++ Redist 2013. Descargar e instalar ahora. Espera..."
LangString MSVC13 ${LANG_SPANISH} "No está instalado Microsoft Visual C++ 2010 Redist. Descargar e instalar ahora. Espera..."

; Installation
;--------------------------------

Section "A New Dawn" ;No components page, name is not important
SectionIn RO
AddSize 3200000

  ; Set output path to the installation directory.
  SetOutPath $INSTDIR
  
  ; Put file there
  File /r "..\release_files\*"

;Create uninstaller
  WriteUninstaller "$INSTDIR\Uninstall.exe"

  !insertmacro MUI_STARTMENU_WRITE_BEGIN 0
    
    ;Create shortcuts
    CreateDirectory "$SMPROGRAMS\$StartMenuFolder"
    CreateShortCut "$SMPROGRAMS\$StartMenuFolder\Uninstall.lnk" "$INSTDIR\Uninstall.exe"
CreateShortCut "$SMPROGRAMS\$StartMenuFolder\Civilization IV - A New Dawn.lnk" "$INSTDIR\and2_checker.exe"
  
  !insertmacro MUI_STARTMENU_WRITE_END
  
SectionEnd ; end the section

Section "MSVC 2010 (required)"
SetOutPath $INSTDIR
ExecWait '"$INSTDIR\checker\vcredist_x86_2010.exe"  /passive /norestart'

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


