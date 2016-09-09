#include "mainwindow.h"
#include "about.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
                                                        //setting up the player
    player = new QMediaPlayer(this);

    playlist = new QMediaPlaylist(player);
    player->setPlaylist(playlist);
                                                        //define items in statusbar
    sliderVolume = new QSlider(this);
    labelForVolumeSlider = new QLabel(this);
    labelBuffer = new QLabel(this);
                                                        //set window title
    this->setWindowTitle("TX mp " + version);
                                                        //style volume slider
    sliderVolume->setOrientation(Qt::Horizontal);
    sliderVolume->setValue(100);
    sliderVolume->setFixedWidth(110);

    labelForVolumeSlider->setText("Volume:");

    labelBuffer->setText("Buffer health");

    ui->statusBar->addPermanentWidget(labelForVolumeSlider);
    ui->statusBar->addPermanentWidget(sliderVolume);
    ui->statusBar->addPermanentWidget(labelBuffer);


    //connect signals and slots
    connect(player, &QMediaPlayer::positionChanged, this, &MainWindow::on_positionChanged);
    connect(player, &QMediaPlayer::durationChanged, this, &MainWindow::on_durationChanged);

    connect(playlist, &QMediaPlaylist::currentIndexChanged, this, &MainWindow::on_currentMediaChanged);

    connect(player, &QMediaPlayer::stateChanged, this,&MainWindow::on_mediaplayerStateChanged);

    connect(player, &QMediaPlayer::bufferStatusChanged, this, &MainWindow::bla);

    connect(sliderVolume, &QSlider::valueChanged, player, &QMediaPlayer::setVolume);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_sliderProgress_sliderMoved(int position)
{
    player->setPosition(position);
}

void MainWindow::on_positionChanged(qint64 position)
{
    ui->sliderProgress->setValue(position);
    QString positionMinStr = "";
    QString positionSecStr = "";
    qint64 min = (player->duration() / 1000 / 60 - position / 1000 / 60);
    qint64 sec = ((player->duration() / 1000 - position / 1000 ) - min * 60);
    positionSecStr.setNum(sec);
    positionMinStr.setNum(min);
    ui->label_2->setText(positionMinStr + ":" + positionSecStr);
    qint64 buffer = player->bufferStatus();
    QString bufferstr = "";
    bufferstr.setNum(buffer);
    labelBuffer->setText("Buffer: " + bufferstr);
}

void MainWindow::on_durationChanged(qint64 position)
{
    ui->sliderProgress->setMaximum(position);
    QString positionMinStr = "";
    QString positionSecStr = "";
    qint64 min = (position / 1000 / 60);
    qint64 sec = (position / 1000 - min * 60);
    positionMinStr.setNum(min);
    positionSecStr.setNum(sec);
    ui->label->setText(positionMinStr + ":" + positionSecStr);
}

void MainWindow::on_actionPlay_triggered()
{
    // definig wheather to play or pause
    if (player->state() == 1) {
        player->pause();
        qDebug() << "paused";
        ui->actionPlay->setIcon(QIcon(":/images/icons/play1-150x150.png"));
    }
    else {

        player->play();
        ui->actionPlay->setIcon(QIcon(":/images/icons/pause1-150x150.png"));
        qDebug() << "playing";
    }

}

void MainWindow::on_actionStop_triggered()
{
    player->stop();
    ui->actionPlay->setIcon(QIcon(":/images/icons/play1-150x150.png"));
}

void MainWindow::on_actionNewFile_triggered()
{
    /*  nextTitle = QFileDialog::getOpenFileName(this, "Open a File","C:/Users/XD/Music/","Mediafile (*.wav *mp3)");
      player->setMedia(QUrl::fromLocalFile(nextTitle));
      qDebug() << "open file";
  */
      qDebug() << "open file1";
      QString directory = QFileDialog::getExistingDirectory(this,"Select dir for files to import","C:/Users/Public/Music/");
      qDebug() << "QFileDialog triggerd";
      if(directory.isEmpty())
          return;
      QDir dir(directory);
      QStringList files = dir.entryList(QStringList() << "*.mp3",QDir::Files);
      QList<QMediaContent> content;
      for(const QString& f:files)
      {
          content.push_back(QUrl::fromLocalFile(dir.path()+"/" + f));
          QFileInfo fi(f);
          ui->listWidget->addItem(fi.fileName());
      }
      playlist->addMedia(content);
      playlist->setCurrentIndex(positionInPlaylist);
}
/*
void MainWindow::dropEvent(QDropEvent* event)
{
  const QMimeData* mimeData = event->mimeData();

  // check for our needed mime type, here a file or a list of files
  if (mimeData->hasUrls())
  {
    QStringList pathList;
    QList<QUrl> urlList = mimeData->urls();

    // extract the local paths of the files
    for (int i = 0; i < urlList.size() && i < 32; +i)
    {
      pathList.append(urlList.at(i).toLocalFile());
    }

    // call a function to open the files
    qDebug() << "hi";
  }
}
*/
void MainWindow::on_actionNext_triggered()
{
    ui->actionPlay->setIcon(QIcon(":/images/icons/play1-150x150.png"));
    positionInPlaylist = positionInPlaylist + 1;
    playlist->setCurrentIndex(positionInPlaylist);
    ui->listWidget->setCurrentRow(positionInPlaylist);
}

void MainWindow::on_actionPrevious_triggered()
{
    ui->actionPlay->setIcon(QIcon(":/images/icons/play1-150x150.png"));
    positionInPlaylist = positionInPlaylist - 1;
    playlist->setCurrentIndex(positionInPlaylist);
    ui->listWidget->setCurrentRow(positionInPlaylist);
}

void MainWindow::on_mediaplayerStateChanged()
{
    if (player->state() == 2) {

        ui->statusBar->showMessage("Paused");
        this->setWindowTitle("TX mp " + version + " | paused");


    } else if (player->state() == 1) {

        ui->statusBar->showMessage("Playing");
        this->setWindowTitle("TX mp " + version + " | playing");


    } else{

        ui->statusBar->showMessage("Stopped");
        this->setWindowTitle("TX mp " + version + " | stopped");


    }
}

void MainWindow::on_listWidget_doubleClicked()
{
    ui->actionPlay->setIcon(QIcon(":/images/icons/play1-150x150.png"));
    positionInPlaylist = ui->listWidget->row(ui->listWidget->currentItem());
    playlist->setCurrentIndex(positionInPlaylist);
    qDebug() << "double clicked on list";
}

void MainWindow::on_currentMediaChanged()
{
    ui->actionPlay->setIcon(QIcon(":/images/icons/play1-150x150.png"));
    player->stop();
}

void MainWindow::on_actionAbout_triggered()
{
    about mDialog;
    mDialog.setModal(true);
    mDialog.exec();
}

void MainWindow::bla()
{
    qDebug() << "percentFilled";
}
