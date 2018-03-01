#ifndef CLIENT_H
#define CLIENT_H


#include <QObject>
#include <QTcpSocket>
#include <thread>
#include <chrono>

#include "indicator.h"
#include "riomessage.h"


class Client : public QObject
{
    Q_OBJECT
public:
    explicit Client(QObject *parent = nullptr , Indicator *indicator = nullptr);


    /**
     * @brief Connects the QDashboard to the Rio
     */
    void Connect();


    /**
     * @brief Runs the client, refreshes, sends, and updates continuously.
     */
//    void Run();


    /**
     * @brief Queues up a RioMessage for sending
     *
     * @param MSG Message to send
     */
    void AddMessage(const RioMessage MSG);


private:
    QTcpSocket *mp_socket = nullptr;
    QString m_socketData;

    Indicator *mp_indicator;
    std::vector<RioMessage> m_messageList;


signals:
    /**
     * @brief Emitted whenever the client is connected to the Rio
     */
    void ClientConnected();


    /**
     * @brief Emitted whenever the client is disconnected from the Rio
     */
    void ClientDisconnected();


public slots:
    void Connected();

    void Disconnected();

    void ReadyRead();

    void Tick();
};

#endif // CLIENT_H
