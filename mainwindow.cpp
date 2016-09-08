#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "settings.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    player = new QMediaPlayer(this);

    connect(player, &QMediaPlayer::positionChanged, this, &MainWindow::on_positionChanged);
    connect(player, &QMediaPlayer::durationChanged, this, &MainWindow::on_durationChanged);

    player->setMedia(QUrl::fromLocalFile("F:/Users/Maximilian/Documents/Music/Mine/DimitriVegas&LikeMike/Dimitri Vegas & Like Mike vs DVBBS & Borgeous - STAMPEDE ( Original Mix ).mp3"));

    pathlist << "C:/Users/Maximilian/Music/";
    QStringList filters;
    filters << "*.mp3" << "*.wav" << "*.m4a";
    //mDir.setNameFilters(filters);
    QDir mDir(pathlist[0]);
    //qDebug() << mDir.dirName() << mDir.entryList();
}

MainWindow::~MainWindow()
{
    qDebug() << "gnarf";
    delete ui;
}

void MainWindow::updateLibrary()
{


    qDebug() << library;
}

void MainWindow::on_actionStop_triggered()
{
    player->stop();
}

void MainWindow::on_actionPause_triggered()
{
    if(player->state() == 1)
    {
        player->pause();
    }
    else if(player->state() == 2)
    {
        player->play();
    }

}

void MainWindow::on_actionPlay_triggered()
{
    player->play();
}

void MainWindow::on_actionBack_triggered()
{

}

void MainWindow::on_actionSkip_triggered()
{

}

void MainWindow::on_durationChanged(qint64 position)
{
    ui->progress->setMaximum(position);
}

void MainWindow::on_positionChanged(qint64 position)
{
    ui->progress->setValue(position);
}

void MainWindow::on_volume_valueChanged(int position)
{
    player->setVolume(position);
}

void MainWindow::on_progress_sliderMoved(int position)
{
    player->setPosition(position);
}

void MainWindow::on_progress_sliderReleased()
{

}

void MainWindow::on_actionSettings_triggered()
{
    Settings sets;
    sets.setModal(true);
    sets.exec();
    pathlist = sets.pathlist;
    sets.pathlist = pathlist;
}

void MainWindow::on_actionSpace_triggered()
{
    if(player->state() == 0)
    {
        player->play();
    }
    else if(player->state() == 1)
    {
        player->pause();
    }
    else
    {
        player->play();
    }
}
