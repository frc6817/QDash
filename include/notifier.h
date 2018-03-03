#ifndef NOTIFIER_H
#define NOTIFIER_H

#include <QObject>


class Notifier: public QObject
{
    Q_OBJECT

public:
    Notifier() = default;


signals:
    /**
     * @brief Notifies the UI of the current left encoder count
     *
     * @param encoderCount Current encoder count of the left drivetrain encoder
     */
    void NotifyLeftEncoder(int encoderCount);


    /**
     * @brief Notifies the UI of the current right encoder count
     *
     * @param encoderCount Current encoder count of the right drivetrain encoder
     */
    void NotifyRightEncoder(int encoderCount);


    /**
     * @brief Notifies the UI of the current flipper encoder count
     *
     * @param encoderCount Current encoder count of the flipper
     */
    void NotifyFlipperEncoder(int encoderCount);


    /**
     * @brief Notifies the UI of the current robot yaw
     *
     * @param yaw Yaw of the robot
     */
    void NotifyYaw(double yaw);


    /**
     * @brief Notifies the UI of the current robot pitch
     *
     * @param pitch Pitch of the robot
     */
    void NotifyPitch(double pitch);


    /**
     * @brief Notifies the UI of the current robot roll
     *
     * @param roll Roll of the robot
     */
    void NotifyRoll(double roll);


    /**
     * @brief Notifies the UI of any log messages (messages not given a specific
     * UI element)
     *
     * @param message Message to sent to the log box
     */
    void NotifyLog(std::string message);


public slots:
    /**
     * @brief Notifies (updates) UI based on message received via the Client
     *
     * @param message Raw message to be interpreted and notify from
     */
    void NotifyUI(std::string message);
};

#endif // NOTIFIER_H
