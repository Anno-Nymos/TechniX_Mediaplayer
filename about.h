#ifndef ABOUT_H
#define ABOUT_H

#include <QDialog>
#include <QLabel>

namespace Ui {
class about;
}

class about : public QDialog
{
    Q_OBJECT

public:
    explicit about(QWidget *parent = 0);
    ~about();

private slots:
    void on_OK_clicked();

private:
    Ui::about *ui;

};

#endif // ABOUT_H
