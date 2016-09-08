#include "settings.h"
#include "ui_settings.h"
#include <QFileDialog>
#include <QDebug>
#include "mainwindow.h"

Settings::Settings(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Settings)
{
    ui->setupUi(this);
    MainWindow mWin;

    pathlist = mWin.pathlist;

    qDebug() << mWin.pathlist.count();

    for(int i = 0;i < pathlist.count();i++)
    {
        ui->paths->addItem(pathlist[i]);
    }
}

Settings::~Settings()
{
    delete ui;
}

void Settings::on_add_clicked()
{
    QString path;
    path = ui->path->text();
    ui->paths->addItem(path);
    pathlist.append(path);
    ui->path->clear();
}

void Settings::on_Delete_clicked()
{
    pathlist.removeAt(ui->paths->currentRow());
    delete ui->paths->currentItem();
}

void Settings::on_search_clicked()
{
    QString path = "";
    path = QFileDialog::getExistingDirectory(this, tr("Select Directory"), "C://");
    ui->paths->addItem(path);
    pathlist.append(path);
    qDebug() << pathlist.count();
}
