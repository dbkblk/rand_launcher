#include <iostream>
#include <fstream>
#include <windows.h>
#include <string>
#include <shlobj.h>
#include <wchar.h>
#include <lib\tinyxml2.h>

using namespace std;

// Prototypes
bool dirExists(const string &dirName_in);
bool clearCache();
bool setStartup();
void replaceAll(std::string& str, const std::string& from, const std::string& to);
bool currentVersion();

int main()
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
		 }
		 else
		 {
		 	cout << "Aborting the installation." << endl;
            Sleep(3000);
		 }
    }
	else
	{
        cout << "The mod is installed." << endl;
        int menu;

        do
        {
            cout << endl << "What do you want to do ?" << endl;
            cout << "1) Check for update" << endl << "2) Revert to the previous version" << endl << "3) Clean up the installation (fix installation problems)" << endl << "4) Set the mod to autostart with Civ. IV" << endl << "5) Exit program" << endl;

            cin >> menu;
			switch(menu)
			{
				// Check for update
				case 1:
                    cout << "Checking for update..." << endl;
                    Sleep(1500);
                    system("bin\\svn.exe update");
                    clearCache();
                    cout << "The mod is now up-to-date !" << endl;
                    system("PAUSE");
                    break;
				
				// Rollback to head-1
				case 2:
                    cout << "Rolling back to the previous version..." << endl;
                    Sleep(1500);
                    system("bin\\svn.exe update -r PREV --accept theirs-full");
                    Sleep(1500);
                    clearCache();
                    cout << "Done." << endl;
                    Sleep(1500);
                    break;
				
				// Clean up the folder
				case 3:
                    cout << "Cleaning up..." << endl;
                    Sleep(1500);
                    system("bin\\svn.exe cleanup");
                    clearCache();
                    cout << "The mod is reverted to the last working version." << endl;
                    break;
				
                // Set the mod at startup
                case 4:
                    {
                    cout << "Setting the mod to autostart..." << endl;
                    Sleep(1500);
                    setStartup();
                    cout << "Done." << endl;
                    break;
                    }

                // Exit the launcher
                case 5:
                    {
                    cout << "Exiting..." << endl;
                    break;
                    }

                case 6:
                    {
                    currentVersion();
                    }
            }
        } while(menu !=5);
	}
	
    return 0;
}

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

bool currentVersion()
{
    // Reading version XML
    tinyxml2::XMLDocument doc;
    doc.LoadFile( "version.xml" );

    // Read the base version
    const char* title = doc.FirstChildElement("versions")->FirstChildElement("baselink")->GetText();
    cout << "The base version is : " << title << endl;
}
