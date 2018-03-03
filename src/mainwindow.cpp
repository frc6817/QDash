#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow) ,
    m_CAMERA_URL(QUrl("http://roborio-6817-frc.local:1181/?action=stream"))
{
    ui->setupUi(this);

    mp_scene = new QGraphicsScene(this);
    mp_ind = new Indicator(ui->indicator , mp_scene);
    mp_client = new Client(nullptr , mp_ind);
    mp_scheduler = new Scheduler();
    mp_notifier = new Notifier;

    mp_scheduler->start();
    mp_ind->SetDisconnected();
    mp_client->Connect();

    ConnectSignalsAndSlots();
    SetupCameraView();
}


MainWindow::~MainWindow()
{
    delete ui;
    delete mp_scene;
    delete mp_ind;
    delete mp_scheduler;
    delete mp_notifier;
    delete mp_client;
}


void MainWindow::on_refreshButton_clicked()
{
    ui->cameraView->load(m_CAMERA_URL);
}


void MainWindow::on_drivetrainSlider_valueChanged(int value)
{
    ui->drivetrainEdit->setText(QString::number(value));

    if(ui->drivetrainPrecisionSlider->value() > value)
    {
        ui->drivetrainPrecisionSlider->setValue(value);
    }
}


void MainWindow::on_drivetrainEdit_editingFinished()
{
    ui->drivetrainSlider->setValue(ui->drivetrainEdit->text().toInt());
}


void MainWindow::on_drivetrainPrecisionSlider_valueChanged(int value)
{
    ui->drivetrainPrecisionEdit->setText(QString::number(value));

    if(value > ui->drivetrainSlider->value())
    {
        ui->drivetrainSlider->setValue(value);
    }
}


void MainWindow::on_drivetrainPrecisionEdit_editingFinished()
{
    ui->drivetrainPrecisionSlider->setValue(ui->drivetrainPrecisionEdit->text().toInt());
}


void MainWindow::on_flipperSlider_valueChanged(int value)
{
    ui->flipperEdit->setText(QString::number(value));
}


void MainWindow::on_flipperEdit_editingFinished()
{
    ui->flipperSlider->setValue(ui->flipperEdit->text().toInt());
}


void MainWindow::on_flywheelThrottle_valueChanged(int value)
{
    ui->flywheelEdit->setText(QString::number(value));
}


void MainWindow::on_flywheelEdit_editingFinished()
{
    ui->flywheelThrottle->setValue(ui->flywheelEdit->text().toInt());
}


void MainWindow::UpdateServerFromUi()
{
    if(!mp_client->SentThisHandshake())
    {
        mp_client->AddMessage(RioMessage("Pos" , ui->startPosBox->currentText().toStdString()));
        mp_client->AddMessage(RioMessage("Delay" , ui->delayEdit->text().toStdString()));
        mp_client->AddMessage(RioMessage("Drive" , std::to_string(ui->drivetrainSlider->value())));
        mp_client->AddMessage(RioMessage("PDrive" , std::to_string(ui->drivetrainPrecisionSlider->value())));
        mp_client->AddMessage(RioMessage("Flip" , std::to_string(ui->flipperSlider->value())));
        mp_client->AddMessage(RioMessage("Fly" , std::to_string(ui->flywheelThrottle->value())));
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


void MainWindow::ConnectSignalsAndSlots()
{
    // Indicator
    connect(mp_client , SIGNAL(ClientConnected()) , mp_ind , SLOT(SetConnected()));
    connect(mp_client , SIGNAL(ClientDisconnected()) , mp_ind , SLOT(SetDisconnected()));

    // Scheduler
    connect(mp_scheduler , SIGNAL(tick()) , mp_client , SLOT(Tick()));
    connect(mp_scheduler , SIGNAL(tick()) , this , SLOT(UpdateServerFromUi()));

    // UI Updates
    connect(mp_client , SIGNAL(MessageReceived(std::string)) , mp_notifier , SLOT(NotifyUI(std::string)));

    connect(mp_notifier , SIGNAL(NotifyLeftEncoder(int)) , this , SLOT(UpdateLeftEncoder(int)));
    connect(mp_notifier , SIGNAL(NotifyRightEncoder(int)) , this , SLOT(UpdateRightEncoder(int)));
    connect(mp_notifier , SIGNAL(NotifyFlipperEncoder(int)) , this , SLOT(UpdateFlipEncoder(int)));
    connect(mp_notifier , SIGNAL(NotifyYaw(double)) , this , SLOT(UpdateYaw(double)));
    connect(mp_notifier , SIGNAL(NotifyRoll(double)) , this , SLOT(UpdateRoll(double)));
    connect(mp_notifier , SIGNAL(NotifyPitch(double)) , this , SLOT(UpdatePitch(double)));
    connect(mp_notifier , SIGNAL(NotifyLog(std::string)) , this , SLOT(UpdateLogBox(std::string)));
}


void MainWindow::SetupCameraView()
{
    ui->cameraView->load(m_CAMERA_URL);
    ui->cameraView->show();
    ui->cameraView->setZoomFactor(5);
}
