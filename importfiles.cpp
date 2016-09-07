#include "importfiles.h"
#include "ui_importfiles.h"

ImportFiles::ImportFiles(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ImportFiles)
{
    ui->setupUi(this);
}

ImportFiles::~ImportFiles()
{
    delete ui;
}
