#include <iostream>
#include <fstream>
#include <windows.h>
#include <string>
#include <shlobj.h>
#include <wchar.h>
#include <civ_functions.h>
#include <lib\tinyxml2.h>
#include <QDir>
#include <QDebug>

using namespace std;

// Check for a directory

bool dirExists(const std::string& dirName_in)
{
  DWORD ftyp = GetFileAttributesA(dirName_in.c_str());
  if (ftyp == INVALID_FILE_ATTRIBUTES)
    return false;  // Wrong path

  if (ftyp & FILE_ATTRIBUTE_DIRECTORY)
    return true;   // Correct path

  return false;    // There is no directory
}

// Clear the cache folder

bool clearCache()
{
	// Getting the cache path
    string cacheDir;
    string delCmd = "DEL /Q ";
    string quote = "\"";
    string finalDir = "\\My Games\\Beyond the Sword\\cache\\";
    string dat = "*";
    char* Appdata = getenv("LOCALAPPDATA");
    cacheDir = delCmd + quote + Appdata + finalDir + dat + quote;
    // cout << cacheDir << endl;

    // Remove .dat files
//	if (QDir::remove(cacheDir.c_str())) {
//		return 0;
//	}
//	else {
//		return 1;
//	}
    return 0;
}

// Set the mod to start by default
bool setStartup()
{
    // Make a backup
    DeleteFile(L"..//..//CivilizationIV.bak");
    CopyFileW(L"..//..//CivilizationIV.ini", L"..//..//CivilizationIV.bak",0);

    /* Look for the file and replace the string
     * Help : https://stackoverflow.com/questions/4499095/replace-line-in-a-file-c */

    string search_string = "Mod = 0";
    string replace_string = "Mod = Mods\\Rise of Mankind - A New Dawn";
    string inbuf;

    fstream input_file("..//..//CivilizationIV.ini", ios::in);
    ofstream output_file("..//..//temp.txt");

    // Look line by line the file
    while (!input_file.eof())
    {
       getline(input_file, inbuf);

       // Register the number of the line where "search string" is found
       size_t foundpos = inbuf.find(search_string);

       // While the eof is not reached, try to replace the string when search_string is found
       if(foundpos != std::string::npos)
       {
          replaceAll(inbuf, search_string, replace_string);
       }
       output_file << inbuf << endl;
    }

    // Close the files
    output_file.close();
    input_file.close();

    // Replace config file
    DeleteFile(L"..//..//CivilizationIV.ini");
    MoveFileW(L"..//..//temp.txt", L"..//..//CivilizationIV.ini");
    return 0;
}

// Replace a string by another
void replaceAll(std::string& str, const std::string& from, const std::string& to)
{
    size_t start_pos = 0;
    while((start_pos = str.find(from, start_pos)) != std::string::npos)
    {
        size_t end_pos = start_pos + from.length();
        str.replace(start_pos, end_pos, to);
        start_pos += to.length(); // In case 'to' contains 'from', like replacing 'x' with 'yx'
    }
}

bool restoreBackup()
{
	DeleteFile(L"..//..//CivilizationIV.ini");
	CopyFileW(L"..//..//CivilizationIV.bak", L"..//..//CivilizationIV.ini", 0);
	return 0;
}

bool checkUpdate()
{
    cout << "Checking for update..." << endl;
    Sleep(1500);
    system("bin\\svn.exe update && echo The cache will now be cleared && TIMEOUT 3");
    clearCache();
    return 0;
}

bool rollBack()
{
    system("bin\\svn.exe update -r PREV --accept theirs-full && echo The cache will now be cleared && TIMEOUT 3");
    clearCache();
    return 0;
}

bool cleanUp()
{
    cout << "Cleaning up..." << endl;
    Sleep(1500);
    system("bin\\svn.exe cleanup");
    clearCache();
    cout << "The mod is reverted to the last working version." << endl;
    return 0;
}

bool installMod()
{
    system("\"\"bin\\svn.exe\" checkout \"svn://svn.code.sf.net/p/anewdawn/code/Trunk/Rise of Mankind - A New Dawn\"\" .");
    return 0;
}

const char* readXML(const char* file, const char* tag)
{
    tinyxml2::XMLDocument read;
    read.LoadFile(file);
    const char* value = read.FirstChildElement("versions")->FirstChildElement(tag)->GetText();
    qDebug() << "The value is " << value;
    return value;
}

bool writeXML(const char* file, const char* tag, const char* newValue)
{
    tinyxml2::XMLDocument read;
    read.LoadFile(file);
    read.FirstChildElement("versions")->FirstChildElement(tag)->SetText(newValue);
    read.SaveFile(file);
    return 0;
}

//bool download(string link, string outputfile)
//{
//    getLink = "bin\\wget -c --no-check-certificate -O ";
//    getLink += outputfile + " " + link;
//    system(getlink);
//}

//system("bin\\wget -c --no-check-certificate -O devel.zip https://github.com/dbkblk/and2_checker/archive/devel.zip");
//system("bin\\7za.exe e devel.zip");

const char* readColors()
{
    // Open the file
    tinyxml2::XMLDocument read;
    const char* file = "Assets/Modules/Interface Colors/MLF_CIV4ModularLoadingControls.xml";
    read.LoadFile(file);
    if (!read.ErrorID() == 0){
        cout << "The file couldn't be read : " << read.ErrorID()<< endl;
        return 0;
    }

    // Go to color level
    tinyxml2::XMLElement* value_el = read.FirstChildElement("Civ4ModularLoadControls")->FirstChildElement("ConfigurationInfos")->FirstChildElement("ConfigurationInfo")->FirstChildElement("Modules")->FirstChildElement("Module")->ToElement();

    // Loop
    for(;; value_el=value_el->NextSiblingElement() ) {
        const char* value = value_el->FirstChildElement("Directory")->GetText();
        const char* bLoad = value_el->FirstChildElement("bLoad")->GetText();

        if (!strcmp(bLoad, "1")) {
            return value;
        }

    }
    return 0;
}

int readColorsCounter()
{
    // Open the file
    tinyxml2::XMLDocument read;
    const char* file = "Assets/Modules/Interface Colors/MLF_CIV4ModularLoadingControls.xml";
    read.LoadFile(file);
    if (!read.ErrorID() == 0){
        cout << "The file couldn't be read : " << read.ErrorID()<< endl;
        return 0;
    }

    // Go to color level
    tinyxml2::XMLElement* value_el = read.FirstChildElement("Civ4ModularLoadControls")->FirstChildElement("ConfigurationInfos")->FirstChildElement("ConfigurationInfo")->FirstChildElement("Modules")->FirstChildElement("Module")->ToElement();

    // Loop
    int counter = -1;
    for(;; value_el=value_el->NextSiblingElement() ) {

        const char* value = value_el->FirstChildElement("Directory")->GetText();
        const char* bLoad = value_el->FirstChildElement("bLoad")->GetText();
        counter++;
        if (!strcmp(bLoad, "1")) {
            return counter;
        }

    }
    return 0;
}

bool setColors(const char* color)
{
    // Open the file
    tinyxml2::XMLDocument read;
    const char* file = "Assets/Modules/Interface Colors/MLF_CIV4ModularLoadingControls.xml";
    read.LoadFile(file);
    const char* resetValue = "0";
    if (!read.ErrorID() == 0){
        cout << "The file couldn't be read : " << read.ErrorID()<< endl;
        return 1;
    }


    // Go to color level
    tinyxml2::XMLElement* value_el = read.FirstChildElement("Civ4ModularLoadControls")->FirstChildElement("ConfigurationInfos")->FirstChildElement("ConfigurationInfo")->FirstChildElement("Modules")->FirstChildElement("Module")->ToElement();

    // Reset all values
    for(value_el; value_el; value_el=value_el->NextSiblingElement() ) {
        value_el->FirstChildElement("bLoad")->SetText(resetValue);
    }

    tinyxml2::XMLElement* valueSet_el = read.FirstChildElement("Civ4ModularLoadControls")->FirstChildElement("ConfigurationInfos")->FirstChildElement("ConfigurationInfo")->FirstChildElement("Modules")->FirstChildElement("Module")->ToElement();

    for(valueSet_el; valueSet_el; valueSet_el=valueSet_el->NextSiblingElement() ) {
        const char* txtValue = valueSet_el->FirstChildElement("Directory")->GetText();
        if (strcmp(txtValue ,color) == 0) {
            valueSet_el->FirstChildElement("bLoad")->SetText("1");
        }
    }
    read.SaveFile(file);
    return 0;
}
