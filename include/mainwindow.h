#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QUrl>

#include "scheduler.h"
#include "indicator.h"
#include "client.h"
#include "notifier.h"


namespace Ui
{
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_refreshButton_clicked();

    void on_drivetrainPrecisionSlider_valueChanged(int value);

    void on_drivetrainSlider_valueChanged(int value);

    void UpdateServerFromUi();


    void UpdateLeftEncoder(int encoderCount);


    void UpdateRightEncoder(int encoderCount);


    void UpdateFlipEncoder(int encoderCount);


    void UpdateYaw(double yaw);


    void UpdateRoll(double roll);


    void UpdatePitch(double pitch);


    void UpdateLogBox(std::string message);


private:
    const QUrl _cameraUrl;

    Ui::MainWindow *ui;
    QGraphicsScene *mp_scene;

    Scheduler *mp_scheduler;
    Indicator *mp_ind;
    Client *mp_client;
    Notifier *mp_notifier;
};


#endif // MAINWINDOW_H
