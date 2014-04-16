#include <iostream>
#include <fstream>
#include <windows.h>
#include <string>
#include <shlobj.h>
#include <wchar.h>
#include <civ_functions.h>
#include <lib\tinyxml2.h>

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
    cout << "Clearing cache folder..." << endl;
    Sleep(1500);

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
    system(cacheDir.c_str());
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

bool restoreBackup()
{
    DeleteFile(L"..//..//CivilizationIV.ini");
    CopyFileW(L"..//..//CivilizationIV.bak", L"..//..//CivilizationIV.ini",0);
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

bool checkUpdate()
{
    cout << "Checking for update..." << endl;
    Sleep(1500);
    system("bin\\svn.exe update && echo The cache will now be cleared && TIMEOUT 5");
    clearCache();
    return 0;
}

bool rollBack()
{
    system("bin\\svn.exe update -r PREV --accept theirs-full && echo The cache will now be cleared && TIMEOUT 5");
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

bool checkInstall()
{
    cout << "Civilization IV: Rise of Mankind - A New Dawn 2" << endl << "-----------------------------------------------" << endl << endl << "Checking for existing installation..." << endl;
    bool check = dirExists(".svn");

    if(check == 0) {
        cout << "The mod is not installed." << endl << "Do you want to download and install it (Y/N) ?" << endl;
        string answer;
        cin >> answer;
        if(answer == "Y") {
            cout << "The mod will be downloaded. It might take a while !" << endl;
            system("\"\"bin\\svn.exe\" checkout \"svn://svn.code.sf.net/p/anewdawn/code/Trunk/Rise of Mankind - A New Dawn\"\" .");
            cout << "The mod has been installed" << endl;
            system("PAUSE");
            return 0;
         }
    }
    else {
        cout << "The mod have been detected" << endl;
        return 1;
    }
    return 1;
}

//const char* getInterfaceColor()
//{
//    tinyxml2::XMLDocument read;
//    read.LoadFile("test.xml");
//    colors = read.FirstChildElement("Civ4ModularLoadControls")->FirstChildElement("ConfigurationInfos")->FirstChildElement("ConfigurationInfo")->FirstChildElement("Modules")->
//    for ()
//}

//bool readXML(const char* file, const char* tag)
//{
//    tinyxml2::XMLDocument read;
//    read.LoadFile(file);
//    const char* value = read.FirstChildElement(tag)->GetText();
//    cout << "The value is : " << value << endl;
//    return 0;
//}

//bool writeXML(const char* file, const char* tag, const char* newValue)
//{
//    tinyxml2::XMLDocument read;
//    read.LoadFile(file);
//    read.FirstChildElement(tag)->SetText(newValue);
//    read.SaveFile(file);
//    return 0;
//}

//bool download(string link, string outputfile)
//{
//    getLink = "bin\\wget -c --no-check-certificate -O ";
//    getLink += outputfile + " " + link;
//    system(getlink);
//}

//system("bin\\wget -c --no-check-certificate -O devel.zip https://github.com/dbkblk/and2_checker/archive/devel.zip");
//system("bin\\7za.exe e devel.zip");
