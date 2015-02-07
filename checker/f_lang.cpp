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

QString getLanguageProgressFromCode(QString code){
    QDomDocument global;
    QFile file("checker/languagesDefine.xml");
    if(!file.open(QIODevice::ReadOnly))
     {
         qDebug() << "Error opening checker/languagesDefine.xml";
         return "err";
     }
    global.setContent(&file);
    file.close();
    QString progress = "err";

    QDomElement element_define = global.firstChildElement("Civ4Defines").firstChildElement("Define").toElement();
    for(;!element_define.isNull();element_define = element_define.nextSiblingElement()){
        if(element_define.firstChildElement("Code").firstChild().nodeValue() == code){
            progress = element_define.firstChildElement("Progress").firstChild().nodeValue();
                        break;
        }
    }
    return progress;
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
    QDomDocument global;
    QFile file("checker/languagesDefine.xml");
    if(!file.open(QIODevice::ReadOnly))
     {
         qDebug() << "Error opening checker/languagesDefine.xml";
         return 0;
     }
    global.setContent(&file);
    file.close();
    QString font;

    QDomElement element_define = global.firstChildElement("Civ4Defines").firstChildElement("Define").toElement();
    for(;!element_define.isNull();element_define = element_define.nextSiblingElement()){
        if(element_define.firstChildElement("Code").firstChild().nodeValue() == code){
            font = element_define.firstChildElement("Font").firstChild().nodeValue();
                        break;
        }
    }
    return font;
}

QString getLanguageCurrentFont(QString code){
    QFile file("Assets/Modules/Interface Colors/Black UI/Resource/Themes/Civ4/Civ4Theme_Common.thm"); // Change for each color UI file.
    QString value = "GFont	.Size0_Normal";

    // Read the file
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream in_enc(&file);
    while(!in_enc.atEnd())
    {
        QString line = in_enc.readLine();
        if(line.contains(value))
        {
            // Isolate each value
            QStringList list = line.split("\"");
            file.close();
            return QString(list[1]);
        }
    }
    return "";
}

void setLanguageFont(QString font){
    // List all interface common theme files
    QStringList xml_filter;
    QStringList color_list;
    xml_filter << "*";
    QDir root("Assets/Modules/Interface Colors/");
    foreach(QFileInfo entry, root.entryInfoList(QDir::Dirs | QDir::NoDotAndDotDot)){
        color_list << entry.fileName();
    }

    // Loop through all interface files
    foreach(QString color_file, color_list){
        QString file_name = "Assets/Modules/Interface Colors/" + color_file + "/Resource/Themes/Civ4/Civ4Theme_Common.thm";
        QString file_name_out = file_name + ".tmp";
        QFile file(file_name);

        // Make a copy
        QFile file_out(file_name_out);
        file_out.remove();
        file.copy(file_name_out);

        // Set the values to look for
        QString value = "GFont	.Size";

        // Read the file
        file.open(QIODevice::ReadOnly | QIODevice::Text);
        QTextStream in_enc(&file);
        file_out.open(QIODevice::WriteOnly | QIODevice::Truncate);
        QTextStream out_enc(&file_out);
        while(!in_enc.atEnd())
        {
            QString line = in_enc.readLine();
            if(line.contains(value))
            {
                // Isolate each value and replace the font value
                QStringList list = line.split("\"");
                list[1] = font;
                line = list.join("\"");
                //qDebug() << line;
            }

            out_enc << line << "\n";
        }
        file.close();
        file_out.close();
        file.remove();
        file_out.rename(file_name);
    }
        return;
}
