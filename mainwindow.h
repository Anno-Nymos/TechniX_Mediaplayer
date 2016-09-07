#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtMultimedia/QMediaPlayer>
#include "settings.h"
#include <QStringList>
#include <QDir>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    QStringList library;
    QStringList pathlist;

private slots:

    void on_actionStop_triggered();

    void on_actionPause_triggered();

    void on_actionPlay_triggered();

    void on_actionBack_triggered();

    void on_actionSkip_triggered();

    void on_durationChanged(qint64 position);

    void on_positionChanged(qint64 position);

    void on_volume_valueChanged(int position);

    void on_progress_sliderReleased();

    void on_progress_sliderMoved(int position);

    void on_actionSettings_triggered();

    void updateLibrary();

    void on_actionSpace_triggered();

private:
    Ui::MainWindow *ui;
    QMediaPlayer* player;
    // QDir mDir;
};

#endif // MAINWINDOW_H
