; Installation script
;--------------------------------

; Modern UI
;--------------------------------

  !include "MUI.nsh"


; General information
;--------------------------------

; The name of the installer
Name "Civilization IV: A New Dawn 2"

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


; Pages
;--------------------------------

!insertmacro MUI_PAGE_WELCOME
;!insertmacro MUI_PAGE_LICENSE "License.txt"
;!insertmacro MUI_PAGE_DIRECTORY

!define MUI_FINISHPAGE_TITLE "Civilization IV - A New Dawn 2"
!define MUI_FINISHPAGE_TEXT "The launcher is now installed. On the first launch, it will detect if the mod is present in the directory. If it's not, just follow the installation procedure."
!define MUI_FINISHPAGE_NOAUTOCLOSE

!define MUI_FINISHPAGE_RUN_CHECKED
!define MUI_FINISHPAGE_RUN "$INSTDIR\and2_checker.exe"
!define MUI_FINISHPAGE_RUN_TEXT "Start the mod launcher"

!define MUI_FINISHPAGE_SHOWREADME ""
!define MUI_FINISHPAGE_SHOWREADME_CHECKED
!define MUI_FINISHPAGE_SHOWREADME_TEXT "Create Desktop Shortcut"
!define MUI_FINISHPAGE_SHOWREADME_FUNCTION DesktopShortcut

!define MUI_STARTMENUPAGE_DEFAULTFOLDER "Civilization IV - A New Dawn 2"
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

function .onInit

        !insertmacro MUI_LANGDLL_DISPLAY

functionEnd


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
CreateShortCut "$SMPROGRAMS\$StartMenuFolder\Civilization IV - A New Dawn 2.lnk" "$INSTDIR\and2_checker.exe"
  
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
Delete "$SMPROGRAMS\$StartMenuFolder\Civilization IV - A New Dawn 2.lnk"
  RMDir "$SMPROGRAMS\$StartMenuFolder"

SectionEnd

