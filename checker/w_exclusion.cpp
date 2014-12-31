#include "w_exclusion.h"
#include "ui_w_exclusion.h"
#include "QtCore"
#include <QtXml>

w_exclusion::w_exclusion(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::w_exclusion)
{
    ui->setupUi(this);

    // List files in tree widget
    ui->treeWidget->setColumnCount(1);
    ui->treeWidget->setHeaderLabels(QStringList() << "File");

    // Read XML exclusion
    QStringList checked_list;
    checked_list << ReadExcludedList("checker/exclusions.default.xml");
    checked_list << ReadExcludedList("checker/exclusions.custom.xml");

    // Test
    treeWidget = new QTreeWidget;
    QStringList list = ListFiles();
    PopulateList(ui->treeWidget, list, checked_list);

    // Connect checkboxes
    connect(ui->treeWidget, SIGNAL(itemClicked(QTreeWidgetItem *,int)), this, SLOT(modeItemChecked(QTreeWidgetItem *,int)));
    connect(ui->buttonBox,SIGNAL(accepted()),this,SLOT(GetOutputList()));
}

void w_exclusion::AddItem(QTreeWidget *treeWidget, QTreeWidgetItem *itm, QString string)
{
    itm->setText(0,string);
    itm->setFlags(itm->flags() | Qt::ItemIsUserCheckable);
    itm->setCheckState(0,Qt::Checked);
    ui->treeWidget->insertTopLevelItem(0,itm);
    treeWidget->addTopLevelItem(itm);
}

QStringList w_exclusion::ListFiles()
{
    // List all files
    QStringList files;

    QDirIterator iterator(".", QDir::Files | QDir::NoDotAndDotDot, QDirIterator::Subdirectories);
    do{
        QString path = iterator.filePath();
        path.remove(0,2);
        if (!path.isEmpty()){
            files << path;
        }
        iterator.next();
    } while (iterator.hasNext());

    files.sort(Qt::CaseInsensitive);

    return files;
}

void w_exclusion::PopulateList(QTreeWidget *treeWidget, QStringList file_list, QStringList exclusion_list){
    // Code borrowed from https://stackoverflow.com/questions/10348801/populate-qtreewidget-with-hierarchic-structure-from-absolute-filepaths
    foreach (QString fileName, file_list)
            {
                bool checked = 0;
                QStringList splitFileName = fileName.split("/");
                foreach(QString path, exclusion_list){
                    if(path == fileName){
                        checked = 1;
                        //qDebug() << "File found";
                    }
                }

                // add root folder as top level item if treeWidget doesn't already have it
                if (treeWidget->findItems(splitFileName[0], Qt::MatchFixedString).isEmpty())
                {
                    topLevelItem = new QTreeWidgetItem;
                    topLevelItem->setText(0,splitFileName[0]);
                    topLevelItem->setFlags(topLevelItem->flags() | Qt::ItemIsUserCheckable);
                    if(checked == 1){
                        topLevelItem->setCheckState(0,Qt::Checked);
                    }
                    else{
                        topLevelItem->setCheckState(0,Qt::Unchecked);
                    }

                    treeWidget->addTopLevelItem(topLevelItem);
                }

                QTreeWidgetItem *parentItem = topLevelItem;

                // iterate through non-root directories (file name comes after)
                //qDebug() << splitFileName.size();
                for (int i = 1; i < (splitFileName.size() - 1); ++i)
                {
                    //qDebug() << "here";
                    // iterate through children of parentItem to see if this directory exists
                    bool thisDirectoryExists = false;
                    for (int j = 0; j < parentItem->childCount(); ++j)
                    {
                        if (splitFileName[i] == parentItem->child(j)->text(0))
                        {
                            thisDirectoryExists = true;
                            parentItem = parentItem->child(j);
                            break;
                        }
                    }

                    if (!thisDirectoryExists)
                    {
                        // Add directory
                        parentItem = new QTreeWidgetItem(parentItem);
                        parentItem->setFlags(parentItem->flags() | Qt::ItemIsUserCheckable);
                        if(checked == 1){
                            parentItem->setCheckState(0,Qt::Checked);
                        }
                        else{
                            parentItem->setCheckState(0,Qt::Unchecked);
                        }
                        parentItem->setText(0, splitFileName[i]);
                    }

                }
                if(splitFileName.size() > 1){
                    QTreeWidgetItem *childItem = new QTreeWidgetItem(parentItem);
                    childItem->setText(0, splitFileName.last());
                    childItem->setFlags(childItem->flags() | Qt::ItemIsUserCheckable);
                    if(checked == 1){
                        childItem->setCheckState(0,Qt::Checked);
                    }
                    else{
                        childItem->setCheckState(0,Qt::Unchecked);
                    }
                }

    }
}

void w_exclusion::CheckChildState(QTreeWidgetItem* item, enum Qt::CheckState eCheckState){
    //qDebug("Check child state");
       if(item)
       {
           int nChildCount = item->childCount();
           for (int i = 0; i < nChildCount; i++)
           {
                item->child(i)->setCheckState(0,eCheckState);
           }
       }
}

void w_exclusion::modeItemChecked(QTreeWidgetItem * item, int nColumn )
{
    if (item != NULL && nColumn != -1)
    {
        enum Qt::CheckState eCheckState = item->checkState(0);
        CheckChildState(item, eCheckState); // Check Items Children
    }
}

void w_exclusion::ValidateParentState(QTreeWidgetItem* item)
{
    QTreeWidgetItem* parentItem = NULL;
    enum Qt::CheckState eCheckState = Qt::Unchecked;

    if (item != NULL) // Is a valid Item
    {
        parentItem = item->parent();
        if (parentItem != NULL) // Item was a child
        {
            int nChildCount = parentItem->childCount();
            for (int i = 0; i < nChildCount; i++)
            {
                // See if any siblings are checked
                if (parentItem->child(i)->checkState(0) == Qt::Checked)
                {
                    eCheckState = Qt::Checked;
                    break;
                }
            }
            parentItem->setCheckState(0, eCheckState); // Set parent according to children status
        }
    }
}

QStringList w_exclusion::ReadExcludedList(QString filepath){

    // Open the XML file
    QDomDocument read;
    QFile file(filepath);
    if(!file.open(QIODevice::ReadOnly))
     {
         qDebug() << "Error opening file";
         QStringList error;
         error << "Error opening file";
         return error;
     }
    read.setContent(&file);
    file.close();

    // Read every exclusions
    QStringList exclusions;
    QDomElement entity = read.firstChildElement("exclusions").firstChildElement();

    while(!entity.isNull()){
        exclusions << entity.text();
        //qDebug() << entity.text();
        entity=entity.nextSiblingElement();
    }

    // Split string list into a formatted exclusion list
    /*foreach(QString entry, exclusions){
        qDebug() << entry;
    }*/
    //qDebug() << exclude_list;

    return exclusions;
}

void w_exclusion::GetOutputList(){
    QStringList excluded_list;
    excluded_list = GetCheckedList();
    QList<QStringList> excluded_values;
    excluded_values << ReadExcludedList("checker/exclusions.default.xml");
    //excluded_values << ReadExcludedList("checker/exclusions.custom.xml");
    foreach(QStringList string_list, excluded_values){
        foreach(QString entry1, excluded_list){
            foreach (QString entry2, string_list){
                if(entry1 == entry2){
                    excluded_list.removeAll(entry2);
                }
            }
         }
    }
    WriteToXML(excluded_list);
}

QStringList w_exclusion::GetCheckedList(){
    QTreeWidgetItemIterator it(ui->treeWidget);
    QStringList checked_list;
    // Get file list
    while (*it) {
            if((*it)->checkState(0) == Qt::Checked){
               QStringList filepath;
                filepath << (*it)->text(0);

                // Check if it have parents
                QTreeWidgetItem* parentItem;
                parentItem = (*it)->parent();
                while(parentItem != NULL){
                    filepath << parentItem->text(0);
                    //qDebug() << parentItem->text(0);
                    parentItem = parentItem->parent();
                }

                // Reverse list
                QListIterator<QString> itl(filepath);
                QStringList reverse_list;
                itl.toBack();
                while(itl.hasPrevious()){
                    reverse_list << itl.previous();
                }
                checked_list << reverse_list.join("/");

            }
            ++it;
        }

    return checked_list;
}

void w_exclusion::WriteToXML(QStringList file_list){
    foreach(QString entry, file_list){
        qDebug() << entry;
    }

    // Load the file
    QDomDocument xml;
    QFile file("checker/exclusions.custom.xml");
    if(!file.open(QIODevice::ReadOnly))
     {
         qDebug() << "Error opening custom xml";
         return;
     }
    xml.setContent(&file);
    file.close();

    // Set the correct node
    QDomElement root = xml.firstChildElement().toElement();
    QDomElement entity = xml.firstChildElement("exclusions").firstChildElement("entity").toElement();

    // Check each entity for corresponding file
    QList<QDomNode> nodes_to_remove;
    for(entity;!entity.isNull();entity=entity.nextSiblingElement()){
        QString value = entity.firstChild().nodeValue();
        int counter = 0;
        foreach(QString entry, file_list){
            if(value.compare(entry)){
                counter++;
                file_list.removeAll(entry);
            }
        }

        // Add node in removal list
        if(counter==0){
            nodes_to_remove << entity;
        }
    }

    // Remove unchecked nodes
    foreach(QDomNode node, nodes_to_remove){
        node.parentNode().removeChild(node);
    }

    // Add new nodes
    foreach(QString entry, file_list){
        QDomElement temp_node = xml.createElement("entity");
        root.appendChild(temp_node);
        temp_node.appendChild(xml.createTextNode(entry));
    }

    // Save to file
    file.open(QIODevice::Truncate | QIODevice::WriteOnly);
    file.write(xml.toByteArray());
    file.close();
}

w_exclusion::~w_exclusion()
{
    delete ui;
}
