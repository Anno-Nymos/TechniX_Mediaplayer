#ifndef IMPORTFILES_H
#define IMPORTFILES_H

#include <QDialog>

namespace Ui {
class ImportFiles;
}

class ImportFiles : public QDialog
{
    Q_OBJECT

public:
    explicit ImportFiles(QWidget *parent = 0);
    ~ImportFiles();

private:
    Ui::ImportFiles *ui;
};

#endif // IMPORTFILES_H
