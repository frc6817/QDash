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
    mp_notifier = new Notifier;


    connect(mp_client , SIGNAL(ClientConnected()) , mp_ind , SLOT(SetConnected()));
    connect(mp_client , SIGNAL(ClientDisconnected()) , mp_ind , SLOT(SetDisconnected()));
    connect(mp_scheduler , SIGNAL(tick()) , mp_client , SLOT(Tick()));
    connect(mp_scheduler , SIGNAL(tick()) , this , SLOT(UpdateServerFromUi()));

    connect(mp_notifier , SIGNAL(NotifyLeftEncoder(int)) , this , SLOT(UpdateLeftEncoder(int)));
    connect(mp_notifier , SIGNAL(NotifyRightEncoder(int)) , this , SLOT(UpdateRightEncoder(int)));
    connect(mp_notifier , SIGNAL(NotifyFlipperEncoder(int)) , this , SLOT(UpdateFlipEncoder(int)));
    connect(mp_notifier , SIGNAL(NotifyYaw(double)) , this , SLOT(UpdateYaw(double)));
    connect(mp_notifier , SIGNAL(NotifyRoll(double)) , this , SLOT(UpdateRoll(double)));
    connect(mp_notifier , SIGNAL(NotifyPitch(double)) , this , SLOT(UpdatePitch(double)));
    connect(mp_notifier , SIGNAL(NotifyLog(std::string)) , this , SLOT(UpdateLogBox(std::string)));

    mp_scheduler->start();


    ui->cameraView->load(_cameraUrl);
    ui->cameraView->show();
    ui->cameraView->setZoomFactor(5);


    mp_ind->SetDisconnected();
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

    if(value > ui->drivetrainSlider->value())
    {
        ui->drivetrainSlider->setValue(value);
    }
}


void MainWindow::on_drivetrainSlider_valueChanged(int value)
{
    ui->drivetrainThrottleLabel->setText(QString::number(value) + "%");

    if(ui->drivetrainPrecisionSlider->value() > value)
    {
        ui->drivetrainPrecisionSlider->setValue(value);
    }
}


void MainWindow::UpdateServerFromUi()
{
    if(!mp_client->SentThisHandshake())
    {
        mp_client->AddMessage(RioMessage("Drive" , std::to_string(ui->drivetrainSlider->value())));
        mp_client->AddMessage(RioMessage("PDrive" , std::to_string(ui->drivetrainPrecisionSlider->value())));
    }
}


void MainWindow::UpdateLeftEncoder(int encoderCount)
{
    ui->leftEncValue->setText(QString::number(encoderCount));
}


void MainWindow::UpdateRightEncoder(int encoderCount)
{
    ui->rightEncValue->setText(QString::number(encoderCount));
}


void MainWindow::UpdateFlipEncoder(int encoderCount)
{
    ui->flipEncValue->setText(QString::number(encoderCount));
}


void MainWindow::UpdateYaw(double yaw)
{
    ui->yawValue->setText(QString::number(yaw));
}


void MainWindow::UpdateRoll(double roll)
{
    ui->rollValue->setText(QString::number(roll));
}


void MainWindow::UpdatePitch(double pitch)
{
    ui->pitchValue->setText(QString::number(pitch));
}


void MainWindow::UpdateLogBox(std::string message)
{
    ui->log->appendPlainText(QString::fromStdString(message));
}
