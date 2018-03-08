#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QIntValidator>
#include <QDoubleValidator>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow) ,
    m_CAMERA_URL(QUrl("http://roborio-6817-frc.local:1181/?action=stream")) ,
    m_SAVE_FILE(QString("save.txt"))
{
    ui->setupUi(this);

    mp_client = new Client();
    mp_scheduler = new Scheduler();
    mp_notifier = new Notifier;

    mp_scheduler->start();
    ui->indicator->SetDisconnected();

    mp_client->Connect();

    ui->matchTimer->DisplayTime(2 , 30);

    ConnectSignalsAndSlots();
    SetupCameraView();
    SetValidators();

    ReadFromFile();
}


MainWindow::~MainWindow()
{
    delete ui;
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


void MainWindow::on_saveButton_clicked()
{
    SaveToFile();
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
        mp_client->AddMessage(RioMessage("TurnP" , ui->turnPEdit->text().toStdString()));
        mp_client->AddMessage(RioMessage("TurnI" , ui->turnIEdit->text().toStdString()));
        mp_client->AddMessage(RioMessage("TurnD" , ui->turnDEdit->text().toStdString()));
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
    connect(mp_client , SIGNAL(ClientConnected()) , ui->indicator , SLOT(SetConnected()));
    connect(mp_client , SIGNAL(ClientDisconnected()) , ui->indicator , SLOT(SetDisconnected()));

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


void MainWindow::SetValidators()
{
    QIntValidator *delayValidator = new QIntValidator();
    delayValidator->setBottom(0);
    ui->delayEdit->setValidator(delayValidator);

    ui->drivetrainEdit->setValidator(new QIntValidator(0 , 100));
    ui->drivetrainPrecisionEdit->setValidator(new QIntValidator(0 , 100));
    ui->flipperEdit->setValidator(new QIntValidator(0 , 100));
    ui->flywheelEdit->setValidator(new QIntValidator(0 , 100));


    QDoubleValidator *pidValidator = new QDoubleValidator();
    pidValidator->setBottom(0);

    ui->turnPEdit->setValidator(pidValidator);
    ui->turnIEdit->setValidator(pidValidator);
    ui->turnDEdit->setValidator(pidValidator);
}


void MainWindow::SaveToFile()
{
    QFile saveFile(m_SAVE_FILE);

    if(!saveFile.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        qDebug() << "Saving failed" << endl;
        return;
    }

    QTextStream out(&saveFile);

    out << ui->startPosBox->currentText() << endl;
    out << ui->delayEdit->text() << endl;
    out << ui->drivetrainEdit->text() << endl;
    out << ui->drivetrainPrecisionEdit->text() << endl;
    out << ui->flipperEdit->text() << endl;
    out << ui->flywheelEdit->text() << endl;
    out << ui->turnPEdit->text() << endl;
    out << ui->turnIEdit->text() << endl;
    out << ui->turnDEdit->text() << endl;

    saveFile.close();
}


void MainWindow::ReadFromFile()
{
    QFile saveFile(m_SAVE_FILE);

    if(!saveFile.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug() << "Failed to read from file. Does it exist yet? Try saving it" << endl;
        return;
    }


    for(int i = 0; !saveFile.atEnd(); i ++)
    {
        QString currentLine = saveFile.readLine();
        currentLine = currentLine.section("" , 0 , -3);

        switch(i)
        {
        case 0:
            if(currentLine == "Left")
            {
                ui->startPosBox->setCurrentIndex(0);
            }
            else if(currentLine == "Center")
            {
                ui->startPosBox->setCurrentIndex(1);
            }
            else if(currentLine == "Right")
            {
                ui->startPosBox->setCurrentIndex(2);
            }
            break;

        case 1:
            ui->delayEdit->setText(currentLine);
            break;

        case 2:
            ui->drivetrainEdit->setText(currentLine);
            ui->drivetrainSlider->setValue(currentLine.toInt());
            break;

        case 3:
            ui->drivetrainPrecisionEdit->setText(currentLine);
            ui->drivetrainPrecisionSlider->setValue(currentLine.toInt());
            break;

        case 4:
            ui->flipperEdit->setText(currentLine);
            ui->flipperSlider->setValue(currentLine.toInt());
            break;

        case 5:
            ui->flywheelEdit->setText(currentLine);
            ui->flywheelThrottle->setValue(currentLine.toInt());
            break;

        case 6:
            ui->turnPEdit->setText(currentLine);
            break;

        case 7:
            ui->turnIEdit->setText(currentLine);
            break;

        case 8:
            ui->turnDEdit->setText(currentLine);
            break;

        default:
            break;
        }
    }
}
