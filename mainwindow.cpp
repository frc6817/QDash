#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow) ,
    _cameraUrl(QUrl("http://roborio-6817-frc.local:1181/?action=stream"))
{
    ui->setupUi(this);

    mp_scene = new QGraphicsScene(this);
    mp_ind = new Indicator(ui->indicator , mp_scene);
    mp_client = new Client(nullptr , mp_ind);
    mp_scheduler = new Scheduler();


    connect(mp_client , SIGNAL(ClientConnected()) , mp_ind , SLOT(SetConnected()));
    connect(mp_client , SIGNAL(ClientDisconnected()) , mp_ind , SLOT(SetDisconnected()));
    connect(mp_scheduler , SIGNAL(tick()) , mp_client , SLOT(Tick()));


    mp_scheduler->start();


    ui->cameraView->load(_cameraUrl);
    ui->cameraView->show();
    ui->cameraView->setZoomFactor(5);


    mp_ind->SetDisconnected();
//    mp_ind->SetConnected();

    mp_client->Connect();
}


MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_refreshButton_clicked()
{
    ui->cameraView->load(_cameraUrl);
    mp_client->Connect();
}


void MainWindow::on_drivetrainPrecisionSlider_valueChanged(int value)
{
    ui->drivetrainPrecisionLabel->setText(QString::number(value) + "%");
}
