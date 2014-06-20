#include "f_svn.h"
#include "f_civ.h"
#include <QtCore>

int svnLocalInfo(){
    // Get the info from the distant server
    QProcess svn_loc;
    svn_loc.setStandardOutputFile("svn.txt");
    svn_loc.start("checker\\svn.exe", QStringList() << "info");
    svn_loc.waitForFinished(-1);

    // Open the output file
    QFile svn_out_loc("svn.txt");
    QString svn;
    QString rev;

    // Find the local revision
    if(svn_out_loc.open(QFile::ReadWrite  |QFile::Text))
    {
        while(!svn_out_loc.atEnd())
        {
            svn += svn_out_loc.readLine();
        }
        int j = 0;
        while ((j = svn.indexOf("Revision: ", j)) != -1) {
             rev = svn.mid(j+10,3);
             ++j;
         }
        qDebug() << "Local revision : " << rev;
    setCheckerParam("Main/LocalRev",rev);
    svn_out_loc.close();
    QFile::remove("svn.txt");
    return rev.toInt();
    }

    return 0;
}

int svnDistantInfo()
{
        // Get the info from the distant server
        QProcess svn_dist;
        svn_dist.setStandardOutputFile("svn_dist.txt");
        svn_dist.start("checker/svn.exe", QStringList() << "info" << "-r" << "HEAD");
        svn_dist.waitForFinished(-1);

        // Open the output file
        QFile svn_out_dist("svn_dist.txt");
        QString svn_str_dist;
        QString rev_dist;

        // Find the local revision
        if(svn_out_dist.open(QFile::ReadWrite  |QFile::Text))
        {
            while(!svn_out_dist.atEnd())
            {
                svn_str_dist += svn_out_dist.readLine();
            }
            int j = 0;
            while ((j = svn_str_dist.indexOf("Revision: ", j)) != -1) {
                 rev_dist = svn_str_dist.mid(j+10,3);
                 ++j;
             }
            qDebug() << "Distant revision : " << rev_dist;
        setCheckerParam("Update/DistantRev",rev_dist);
        svn_out_dist.close();
        QFile::remove("svn_dist.txt");
        }
        return rev_dist.toInt();
}

QString svnGetChangelog(int revisions)
{
    // Avoid to redownload if the changelog has already been grabbed
    if(readCheckerParam("Changelog/LastCheckedRevision") == QString::number(svnLocalInfo()))
    {
        qDebug() << "Changelog already exists";
        return readCheckerParam("Changelog/Value");
    }

    QFile::remove("svn_changelog.txt");
    QProcess svn_changelog;
    svn_changelog.setStandardOutputFile("svn_changelog.txt");
    svn_changelog.start(QString("checker/svn.exe log -l %1 -r HEAD:0").arg(revisions));
    svn_changelog.waitForFinished(-1);
    QString result;


    // Open the output file
    QFile svn_changelog_file("svn_changelog.txt");
    if(svn_changelog_file.open(QFile::ReadWrite  |QFile::Text))
    {
        result = svn_changelog_file.readAll();
        svn_changelog_file.close();
        svn_changelog_file.remove();
        setCheckerParam("Changelog/LastCheckedRevision",QString::number(svnDistantInfo()));
        setCheckerParam("Changelog/Value",result);
        return result;
    }
    return "Can't read changelog";
}
