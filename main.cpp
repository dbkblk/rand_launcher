#include <iostream>
#include <windows.h>
#include <string>

using namespace std;

bool dirExists(const string &dirName_in);

int main()
{
    cout << "Checking for existing installation..." << endl;
    bool check = dirExists(".svn");

    if(check == 0)
    {
         cout << "The mod is not installed. Press a key to download. It might take a while..." << endl;
         system("PAUSE");
         system("\"\"bin\\svn.exe\" checkout \"http://svn.code.sf.net/p/anewdawn/code/Trunk/Rise of Mankind - A New Dawn\"\" .");
         cout << "The mod has been installed" << endl;
         system("PAUSE");
    }
    else
    {
        cout << "A mod installation has been detected. Now checking for update..." << endl;
        system("PAUSE");
        system("bin\\svn.exe update");
        system("PAUSE");
    }

    return 0;
}


bool dirExists(const std::string& dirName_in)
{
  DWORD ftyp = GetFileAttributesA(dirName_in.c_str());
  if (ftyp == INVALID_FILE_ATTRIBUTES)
    return false;  // Wrong path

  if (ftyp & FILE_ATTRIBUTE_DIRECTORY)
    return true;   // Correct path

  return false;    // There is no directory
}
