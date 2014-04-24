#include "updatemanager.h"
#include "ui_updatemanager.h"

updateManager::updateManager(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::updateManager)
{
    ui->setupUi(this);
}

updateManager::~updateManager()
{
    delete ui;
}
