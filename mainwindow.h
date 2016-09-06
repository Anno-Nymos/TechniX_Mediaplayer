#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QDebug>
#include <QFileDialog>
#include <QProgressBar>
#include <QSlider>
#include <QMessageBox>
#include <QWinTaskbarButton>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    QString nextTitle = "";

    QString version = "v2";

    qint64 positionInPlaylist = 0;

private slots:

    void on_actionPlay_triggered();

    void on_actionStop_triggered();

    void on_sliderProgress_sliderMoved(int);

    void on_positionChanged(qint64 position);

    void on_durationChanged(qint64 position);

    void on_actionNewFile_triggered();

    void on_actionNext_triggered();

    void on_listWidget_doubleClicked();

    void on_currentMediaChanged();

    void on_actionPrevious_triggered();

    void on_mediaplayerStateChanged();

    void on_actionAbout_triggered();

private:
    Ui::MainWindow *ui;
    //items for mediaplayer
    QMediaPlayer* player;
    QMediaPlaylist* playlist;
    //items in progressbar
    QProgressBar* progressBar;
    QSlider* sliderVolume;
    QLabel* labelForVolumeSlider;
};

#endif // MAINWINDOW_H
