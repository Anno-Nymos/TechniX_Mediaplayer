#ifndef SETTINGS_H
#define SETTINGS_H

#include <QDialog>
#include <QStringList>
#include "mainwindow.h"

namespace Ui {
class Settings;
}

class Settings : public QDialog
{
    Q_OBJECT

public:
    explicit Settings(QWidget *parent = 0);
    ~Settings();

    QStringList pathlist;

private slots:

    void on_add_clicked();

    void on_Delete_clicked();

    void on_search_clicked();

private:
    Ui::Settings *ui;

};

#endif // SETTINGS_H
