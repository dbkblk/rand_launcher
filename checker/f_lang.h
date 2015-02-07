#ifndef F_LANG_H
#define F_LANG_H

#include <QString>

QString getGameLanguage();
bool setGameLanguage(QString language);
bool isLanguageDefault(QString language);
bool isLanguageSupported(QString code);
QString getLanguageNameFromCode(QString code);
QString getLanguageGameNumberFromCode(QString code);
QString getLanguageProgressFromCode(QString code);
QString getLanguageCodeFromGameNumber(QString number);
bool getFScale();
void setFScale(bool enable);
QString getLanguageRecommendedFont(QString code);
QString getLanguageCurrentFont(QString code);
void setLanguageFont(QString font);
#endif // F_LANG_H
