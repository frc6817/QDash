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
     * @brief Queues up a RioMessage for sending
     *
     * @param MSG Message to send
     */
    void AddMessage(const RioMessage MSG);


    bool SentThisHandshake();


    bool ReceivedThisHandshake();


private:
    QTcpSocket *mp_socket = nullptr;
    QString m_socketData;

    // Handshake refers to a single instance of a message sent and received
    // FROM THIS CLIENT'S PERSPECTIVE
    bool m_sentThisHandshake;
    bool m_receivedThisHandshake;

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


    /**
     * @brief Emitted whenever a message is received from the server
     *
     * @param message Received message
     */
    void MessageReceived(std::string message);


public slots:
    void Connected();

    void Disconnected();

    void ReadyRead();

    void Tick();
};

#endif // CLIENT_H
