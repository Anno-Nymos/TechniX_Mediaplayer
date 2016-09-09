#include "about.h"
#include "ui_about.h"

about::about(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::about)
{
    ui->setupUi(this);
    QPixmap image(":/images/icons/Technix_favicon.jpg");
    ui->imageLabel->setPixmap(image);
}

about::~about()
{
    delete ui;
}

void about::on_OK_clicked()
{
  about::close();
}
