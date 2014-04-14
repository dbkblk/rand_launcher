/* Download and extract the base package
bool downloadBase()
{
    system("bin\\wget -c --no-check-certificate -O base.exe http://www.atmoburn.com/upload/RoM-AnD_repo.exe");
    system("bin\\7za.exe e base.exe");
    // DeleteFile(L"base.exe");
    return 0;
}
*/


                /* Dev tests
                case 6:
                    {
                    downloadBase();
                    break;
                    }*/