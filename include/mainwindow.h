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
#include "matchtimer.h"


namespace Ui
{
    class MainWindow;
}


/**
 * @brief Most directly manages the UI elements- with the exception of the
 * indicator, all UI elements are manipulated by this class. Also acts as
 * a central "hub" that connects all the required classes and signals/slots
 * together. This should be the only class accessed in main().
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT


public:
    /**
     * @brief Sets up UI, connects signals and slots, starts the scheduler.
     *
     * @param parent Parent QObject, should the MainWindow be imbedded/subclassed
     * in some other QObject. In our application, this will never be the case.
     */
    explicit MainWindow(QWidget *parent = 0);


    ~MainWindow();


private slots:
    /**
     * @brief Attempts to refresh the camera view by reloading the URL
     */
    void on_refreshButton_clicked();


    /**
     * @brief Changes the value of the drivetrain normal throttle slider.
     * Adjusts the value of the corresponding text edit. If the slider is
     * moved such that it is less than the drivetrain precision throttle slider,
     * the drivetrain precision throttle decreases with this. The drivetrain precision
     * throttle can never be greater than normal drivetrain throttle.
     *
     * @param value Value to set normal throttle to- this is a percent value between
     * 0 and 100
     */
    void on_drivetrainSlider_valueChanged(int value);


    /**
     * @brief Changes the value of the drivetrain normal throttle text edit.
     * Also adjusts the value of the corresponding slider to match the value
     * of the text edit. If the value is adjusted to a lower value than that
     * of the precision throttle, then the precision throttle is lowered until
     * it matches. The precision throttle can never be greater than normal
     * drivetrain throttle.
     */
    void on_drivetrainEdit_editingFinished();


    /**
     * @brief Changes the value of the drivetrain precision throttle slider.
     * Adjusts the value of the corresponding text edit. If the slider is
     * moved such that it is greater than the drivetrain throttle slider, the
     * drivetrain throttle increases with this. The drivetrain throttle can never
     * be lower than precision throttle.
     *
     * @param value Value to set precision throttle to- this is a percent
     * value between 0 and 100
     */
    void on_drivetrainPrecisionSlider_valueChanged(int value);


    /**
     * @brief Changes the value of the drivetrain precision throttle text edit.
     * Also adjusts the value of the corresponding slider to match the value
     * of the text edit. If the value is adjusted to a higher value than that
     * of the normal throttle, then the normal throttle is increased until
     * it matches. The normal throttle can never be less than precision
     * drivetrain throttle.
     */
    void on_drivetrainPrecisionEdit_editingFinished();


    /**
     * @brief Changes the value of the flipper throttle slider. Adjusts the
     * value of the corresponding text edit to match the slider value.
     *
     * @param value Value to set throttle to- this is a percent value between
     * 0 and 100
     */
    void on_flipperSlider_valueChanged(int value);


    /**
     * @brief Changes the value of the flipper throttle text edit.
     * Also adjusts the value of the corresponding slider to match the value
     * of the text edit.
     */
    void on_flipperEdit_editingFinished();


    /**
     * @brief Changes the value of the flywheel throttle slider. Adjusts the
     * value of the corresponding text edit to match the slider value.
     *
     * @param value Value to set throttle to- this is a percent value between
     * 0 and 100
     */
    void on_flywheelThrottle_valueChanged(int value);


    /**
     * @brief Changes the value of the flywheel throttle text edit.
     * Also adjusts the value of the corresponding slider to match the value
     * of the text edit.
     */
    void on_flywheelEdit_editingFinished();


    /**
     * @brief Sends messages to the TCP client. These messages update the server
     * (RoboRio) about notable changes in UI. Note that this method DOES NOT actually
     * send the messages over TCP- it instead sends a list of messages to the client,
     * where further processing is done before the messages are sent. Messages are
     * instructed to send only once per handshake- that is, once per send/receive cycle.
     * For example, the client cannot send two messages in a row without receiving, and
     * the client cannot receive two messages in a row without sending.
     */
    void UpdateServerFromUi();


    /**
     * @brief Updates all elements pertaining to the left drivetrain encoder. Currently,
     * this is merely a label that displays the current count of the left
     * drivetrain encoder. Note that this number is probably not perfectly accurate- TCP
     * communication takes time.
     *
     * @param encoderCount Count of the left drivetrain encoder
     */
    void UpdateLeftEncoder(int encoderCount);


    /**
     * @brief Updates all elements pertaining to the right drivetrain encoder. Currently,
     * this is merely a label that displays the current count of the right
     * drivetrain encoder. Note that this number is probably not perfectly accurate- TCP
     * communication takes time.
     *
     * @param encoderCount Count of the right drivetrain encoder
     */
    void UpdateRightEncoder(int encoderCount);


    /**
     * @brief Updates all elements pertaining to the flipper encoder. Currently,
     * this is merely a label that displays the current count of the flipper
     * encoder. Note that this number is probably not perfectly accurate- TCP
     * communication takes time.
     *
     * @param encoderCount Count of the flipper encoder
     */
    void UpdateFlipEncoder(int encoderCount);


    /**
     * @brief Updates all elements pertaining to the yaw of the robot. Currently,
     * this is merely a label that displays the current yaw of the robot. Note
     * that this number is probably not perfectly accurate- TCP communication
     * takes time.
     *
     * This is probably the most useful angular measurement for our purposes.
     * For example, if you wish to write a "TurnRobotToAngle" method, yaw would
     * be the way to go.
     *
     * @param yaw Yaw of the robot.
     */
    void UpdateYaw(double yaw);


    /**
     * @brief Updates all elements pertaining to the roll of the robot. Currently,
     * this is merely a label that displays the current roll of the robot. Note
     * that this number is probably not perfectly accurate- TCP communication
     * takes time.
     *
     * @param roll Roll of the robot.
     */
    void UpdateRoll(double roll);


    /**
     * @brief Updates all elements pertaining to the pitch of the robot. Currently,
     * this is merely a label that displays the current pitch of the robot. Note
     * that this number is probably not perfectly accurate- TCP communication
     * takes time.
     *
     * @param pitch Pitch of the robot.
     */
    void UpdatePitch(double pitch);


    /**
     * @brief Updates the telemetry log box- this is the place for all messages sent by
     * the server (RoboRio) that don't have a specific UI element associated with them here.
     * Subsequent message updates do not clear the log box- they are appended with a line break
     * in between.
     *
     * For example, if the server were to issue a countdown over TCP, then it would show
     * up in the log box.
     *
     * @param message Message to be shown in the log box. For better readability, it is
     * recommended that the original message tag prepend the message.
     */
    void UpdateLogBox(std::string message);


private:
    const QUrl m_CAMERA_URL;

    Ui::MainWindow *ui;

    Scheduler *mp_scheduler;
    Client *mp_client;
    Notifier *mp_notifier;


    /**
     * @brief Connects the signals and slots needed for operation. These include setting up
     * the scheduler, indicator, and other UI elements.
     */
    void ConnectSignalsAndSlots();


    /**
     * @brief Sets up the camera view- connecting to the HTML stream, resizing, and displaying
     */
    void SetupCameraView();


    /**
     * @brief Sets up input validators to prevent bad input
     */
    void SetValidators();
};


#endif // MAINWINDOW_H
