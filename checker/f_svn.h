#ifndef SVN_FUNCTIONS_H
#include <QtCore>
#define SVN_FUNCTIONS_H

int svnLocalInfo();
int svnDistantInfo();
QString svnGetChangelog(int revisions);

#endif // SVN_FUNCTIONS_H
