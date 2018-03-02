#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QUrl>

#include "scheduler.h"
#include "indicator.h"
#include "client.h"


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

    void UpdateServerFromUi();

    void on_drivetrainSlider_valueChanged(int value);

private:
    const QUrl _cameraUrl;

    Ui::MainWindow *ui;
    QGraphicsScene *mp_scene;

    Scheduler *mp_scheduler;
    Indicator *mp_ind;
    Client *mp_client;
};


#endif // MAINWINDOW_H
