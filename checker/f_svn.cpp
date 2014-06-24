#include "f_svn.h"
#include "f_civ.h"
#include <QtCore>
#include <QtXml>

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
    }
    else {
        QFile::remove("checker/changelog.xml");
        QProcess svn_changelog;
        svn_changelog.setStandardOutputFile("checker/changelog.xml");
        svn_changelog.start(QString("checker/svn.exe log -l %1 -r HEAD:0 --xml").arg(revisions));
        svn_changelog.waitForFinished(-1);
    }

    QString result;

    // Open the output file
    QFile svn_changelog_file("checker/changelog.xml");
    QDomDocument xml;
    svn_changelog_file.open(QIODevice::ReadOnly);
    xml.setContent(&svn_changelog_file);
    svn_changelog_file.close();
    QDomElement revision = xml.firstChildElement().firstChildElement();

    for(revision;!revision.isNull();revision = revision.nextSiblingElement())
    {
        QString text_rev = revision.attribute("revision");
        QString text_value = revision.firstChildElement("msg").text();
        text_value.replace("\n","<br>");
        result = result + "\n <html><head/><body><p><span style=\" font-size:10pt; font-weight:600;\">Revision " + text_rev + ":</span></p></body></html>\n" + text_value;
    }
    return result;
}
