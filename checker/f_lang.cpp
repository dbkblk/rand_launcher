#include "f_lang.h"

#include <QtCore>
#include <QtNetwork>
#include <QtGui>
#include <QtWidgets>
#include <QDebug>
#include <QtXml/QtXml>

/* Language logic:
 * Detect language at start reading settings. If none has been defined, use the OS language. Otherwise, use the settings.
 * If the language OS not supported, fallback to english.
 * Check the ini file for language. If language is different from settings, set the new language.
 * Check if language is default. If not, set recommended font and fscale if the language is not the same as in Global Define.
 */

bool isLanguageDefault(QString language){
    QStringList list;
    list << "Default" << "English" << "French" << "German" << "Italian" << "Spanish";
    if(list.contains(language)){return true;}
    return false;
}

bool isLanguageSupported(QString code){
    QStringList list;

    QDomDocument global;
    QFile file("checker/languagesDefine.xml");
    if(!file.open(QIODevice::ReadOnly))
     {
         qDebug() << "Error opening checker/languagesDefine.xml";
         return 0;
     }
    global.setContent(&file);
    file.close();

    QDomElement element_define = global.firstChildElement("Civ4Defines").firstChildElement("Define").toElement();
    for(;!element_define.isNull();element_define = element_define.nextSiblingElement()){
        list << element_define.firstChildElement("Code").firstChild().nodeValue();
        }

    if(list.contains(code)){return true;}
    else{return false;}
}

QString getLanguageNameFromCode(QString code){
    QDomDocument global;
    QFile file("checker/languagesDefine.xml");
    if(!file.open(QIODevice::ReadOnly))
     {
         qDebug() << "Error opening checker/languagesDefine.xml";
         return 0;
     }
    global.setContent(&file);
    file.close();
    QString language = "English"; // Fallback to English

    QDomElement element_define = global.firstChildElement("Civ4Defines").firstChildElement("Define").toElement();
    for(;!element_define.isNull();element_define = element_define.nextSiblingElement()){
        if(element_define.firstChildElement("Code").firstChild().nodeValue() == code){
            language = element_define.firstChildElement("Language").firstChild().nodeValue();
                        break;
        }
    }
    return language;
}

QString getLanguageGameNumberFromCode(QString code){
    QDomDocument global;
    QFile file("checker/languagesDefine.xml");
    if(!file.open(QIODevice::ReadOnly))
     {
         qDebug() << "Error opening checker/languagesDefine.xml";
         return 0;
     }
    global.setContent(&file);
    file.close();
    QString language = "0"; // Fallback to English

    QDomElement element_define = global.firstChildElement("Civ4Defines").firstChildElement("Define").toElement();
    for(;!element_define.isNull();element_define = element_define.nextSiblingElement()){
        if(element_define.firstChildElement("Code").firstChild().nodeValue() == code){
            language = element_define.firstChildElement("Number").firstChild().nodeValue();
                        break;
        }
    }
    return language;
}

QString getLanguageCodeFromGameNumber(QString number){
    QDomDocument global;
    QFile file("checker/languagesDefine.xml");
    if(!file.open(QIODevice::ReadOnly))
     {
         qDebug() << "Error opening checker/languagesDefine.xml";
         return 0;
     }
    global.setContent(&file);
    file.close();
    QString language = "en"; // Fallback to English

    QDomElement element_define = global.firstChildElement("Civ4Defines").firstChildElement("Define").toElement();
    for(;!element_define.isNull();element_define = element_define.nextSiblingElement()){
        if(element_define.firstChildElement("Number").firstChild().nodeValue() == number){
            language = element_define.firstChildElement("Code").firstChild().nodeValue();
                        break;
        }
    }
    return language;
}

bool getFScale(){
    QDomDocument global;
    QFile file("Assets/XML/Art/CIV4ArtDefines_Misc.xml");
    if(!file.open(QIODevice::ReadOnly))
     {
         qDebug() << "Error opening CIV4ArtDefines_Misc.xml";
         return 0;
     }
    global.setContent(&file);
    file.close();
    float value;

    QDomElement element_define = global.firstChildElement("Civ4ArtDefines").firstChildElement("MiscArtInfos").firstChildElement("MiscArtInfo").toElement();
    for(;!element_define.isNull();element_define = element_define.nextSiblingElement()){
        if(element_define.firstChildElement("Type").firstChild().nodeValue() == "CITY_BILLBOARDS"){
            value = element_define.firstChildElement("fScale").firstChild().nodeValue().toFloat();
                        break;
        }
    }
    if(value >= 0){ return true; }
    else{ return false; }
}

void setFScale(bool enable){
    QDomDocument global;
    QFile file("Assets/XML/Art/CIV4ArtDefines_Misc.xml");
    if(!file.open(QIODevice::ReadOnly))
     {
         qDebug() << "Error opening CIV4ArtDefines_Misc.xml";
         return;
     }
    global.setContent(&file);
    file.close();
    QString value;
    if(enable){ value = "1.0"; }
    else{ value = "-1.0"; }

    QDomElement element_define = global.firstChildElement("Civ4ArtDefines").firstChildElement("MiscArtInfos").firstChildElement("MiscArtInfo").toElement();
    for(;!element_define.isNull();element_define = element_define.nextSiblingElement()){
        if(element_define.firstChildElement("Type").firstChild().nodeValue() == "CITY_BILLBOARDS"){
            element_define.firstChildElement("fScale").firstChild().setNodeValue(value);
                        break;
        }
    }

    // Save content back to the file
    if (!file.open(QIODevice::Truncate | QIODevice::WriteOnly)) {
        return;
    }
    QTextStream ts(&file);
    global.save(ts, 4);
    file.close();
    return;
}

QString getLanguageRecommendedFont(QString code){
    return "";
}

QString getLanguageCurrentFont(QString code){
    return "";
}

QString setLanguageFont(QString font){
    return "";
}
