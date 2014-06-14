; Installation script
;--------------------------------

SetCompressor /SOLID LZMA

; Modern UI
;--------------------------------

  !include "MUI.nsh"
  !define VERSION "0.11"

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
!define MUI_ICON "rom-and.ico"
!define MUI_WELCOMEFINISHPAGE_BITMAP "left_image.bmp"

; Page definition
;--------------------------------
!define MUI_WELCOMEPAGE_TITLE $(WELCOME_TITLE)
!define MUI_WELCOMEPAGE_TEXT $(WELCOME)

!define MUI_DIRECTORYPAGE_TEXT_TOP $(DIRECTORY)

!define MUI_FINISHPAGE_TITLE "Civilization IV - A New Dawn"
!define MUI_FINISHPAGE_TEXT $(FINISH)
!define MUI_FINISHPAGE_NOAUTOCLOSE
!define MUI_PAGE_CUSTOMFUNCTION_PRE MSVC
!define MUI_FINISHPAGE_RUN_CHECKED
!define MUI_FINISHPAGE_RUN "$INSTDIR\and2_checker.exe"
!define MUI_FINISHPAGE_RUN_TEXT $(RUN)
!define MUI_FINISHPAGE_SHOWREADME ""
!define MUI_FINISHPAGE_SHOWREADME_CHECKED
!define MUI_FINISHPAGE_SHOWREADME_TEXT $(SHORTCUT)
!define MUI_FINISHPAGE_SHOWREADME_FUNCTION DesktopShortcut

!define MUI_STARTMENUPAGE_DEFAULTFOLDER "Civilization IV - A New Dawn"

!insertmacro MUI_PAGE_WELCOME
!insertmacro MUI_PAGE_DIRECTORY
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

; French

LangString WELCOME_TITLE ${LANG_FRENCH} "Civilization IV: A New Dawn pack d'expansion"
LangString WELCOME ${LANG_FRENCH} "Version du lanceur: ${VERSION}\n\nCet assistant d'installation va vous guider pour l'installer de Civilization IV: A New Dawn.\nLe mod sera install� dans 'My Documents\My Games\Beyond the Sword\Mods\' par d�faut. \nIl va cr�er un raccourcis (option) vers le lanceur, qui sera utilis� pour t�l�charger, mettre � jour ou configurer l'installation du mod.\n\nATTENTION : Si le mod est d�j� install�, le lanceur pourrait remplacer certains de vos fichiers pendant les mises � jour."
LangString DIRECTORY ${LANG_FRENCH} "L'installateur va installer le pack d'expansion dans le dossier suivant.$\nPour l'installer dans un dossier diff�rent, cliquez sur 'Parcourir...' et s�lectionnez un autre dossier.$\n$\nNOTE: Il est hautement recommand� d'utiliser le dossier par d�faut s�lectionn� ci-dessous. Cependant, vous pouvez choisir d'installer le mod directement dans le dossier du jeu ('Sid Meier's Civilization IV Beyond the Sword\Beyond the Sword\Mods\')."
LangString FINISH ${LANG_FRENCH} "Le lanceur est maintenant install�. Au premier lancement, il va essayer de d�tecter si le mod est pr�sent dans le r�pertoire. Si ce n'est pas le cas, il suffit de suivre la proc�dure d'installation."
LangString RUN ${LANG_FRENCH} "D�marrer le lanceur"
LangString SHORTCUT ${LANG_FRENCH} "Cr�er un raccourci sur le bureau"
LangString MSVC10 ${LANG_FRENCH} "Microsoft Visual C++ 2013 Redist n'est pas install�. T�l�chargement et installation en cours. Veuillez patienter..."
LangString MSVC13 ${LANG_FRENCH} "Microsoft Visual C++ 2010 Redist n'est pas install�. T�l�chargement et installation en cours. Veuillez patienter..."

; Installation
;--------------------------------

Section "instfiles" ;No components page, name is not important

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

; Uninstallation
;--------------------------------


Section "Uninstall"

; Delete files

Delete "$INSTDIR\Uninstall.exe"
Delete "$INSTDIR\and2_checker.exe"
Delete "$INSTDIR\*.dll"
RMDir /r "$INSTDIR\checker\"
RMDir /r "$INSTDIR\platforms\"

  
  !insertmacro MUI_STARTMENU_GETFOLDER 0 $StartMenuFolder
    
  Delete "$SMPROGRAMS\$StartMenuFolder\Uninstall.lnk"
Delete "$SMPROGRAMS\$StartMenuFolder\Civilization IV - A New Dawn.lnk"
  RMDir "$SMPROGRAMS\$StartMenuFolder"

SectionEnd

Function MSVC

; Check for MSVC2013
install_msvc2013:
IfFileExists "$SYSDIR\msvcp120.dll" not_install_msvc2013 install_msvc2013

MessageBox MB_OK $(MSVC13)
NSISdl::download https://dl.dropboxusercontent.com/u/369241/vcredist_x86_2013.exe vcredist_x86_2013.exe
Pop $R0 ;Get the return value
  StrCmp $R0 "success" +3
    MessageBox MB_OK "Download failed: $R0"
    Quit   
StrCpy $1 "/q"
StrCpy $2 "/norestart"
ExecWait 'vcredist_x86_2013.exe $1 $2'

not_install_msvc2013:

; Check for MSVC2010
IfFileExists "$SYSDIR\msvcr100.dll" not_install_msvc2010 install_msvc2010

install_msvc2010:
MessageBox MB_OK $(MSVC10)
NSISdl::download http://download.microsoft.com/download/5/B/C/5BC5DBB3-652D-4DCE-B14A-475AB85EEF6E/vcredist_x86.exe vcredist_x86_2010.exe
Pop $R0 ;Get the return value
  StrCmp $R0 "success" +3
    MessageBox MB_OK "Download failed: $R0"
    Quit   
StrCpy $1 "/q"
StrCpy $2 "/norestart"
ExecWait 'vcredist_x86_2010.exe $1 $2'

not_install_msvc2010:

FunctionEnd


