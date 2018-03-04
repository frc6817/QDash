#include "client.h"

#include <string>


Client::Client(QObject *parent) : QObject(parent)
{
    m_sentThisHandshake = false;
    m_receivedThisHandshake = false;
}


void Client::Connect()
{
    /*
     * This is needed because every time this function is called without deleting the pointer,
     * it somehow connects multiple instances of the same socket and it just gets messy.
     */
    delete mp_socket;
    mp_socket = new QTcpSocket(this);


    // Connect signals and slots
    connect(mp_socket , SIGNAL(connected()) , this , SLOT(Connected()));
    connect(mp_socket , SIGNAL(disconnected()) , this , SLOT(Disconnected()));
    connect(mp_socket , SIGNAL(readyRead()) , this , SLOT(ReadyRead()));

    // DON'T CHANGE THIS
//    mp_socket->connectToHost("10.68.17.2" , 1560);
//    mp_socket->connectToHost("google.com" , 443);
    mp_socket->connectToHost("localhost" , 6817);
}


void Client::AddMessage(const RioMessage MSG)
{
    m_messageList.push_back(MSG);
}


bool Client::SentThisHandshake()
{
    return m_sentThisHandshake;
}


bool Client::ReceivedThisHandshake()
{
    return m_receivedThisHandshake;
}


void Client::Connected()
{
    qDebug() << "Connected to rio!" << endl;
    emit ClientConnected();
}


void Client::Disconnected()
{
    qDebug() << "Disconnected!" << endl;
    mp_socket->close();
    emit ClientDisconnected();
}


void Client::ReadyRead()
{
    if(!m_receivedThisHandshake)
    {
        emit MessageReceived(mp_socket->readLine().toStdString());

        m_receivedThisHandshake = true;
    }
}


void Client::Tick()
{
    if(mp_socket->state() == QTcpSocket::UnconnectedState)
    {
        qDebug() << "Trying to connect" << endl;

        Connect();
    }
    else if(mp_socket->state() == QTcpSocket::ConnectedState && !m_sentThisHandshake)
    {
        std::string finalMessage = "";

        for(int i = 0; i < m_messageList.size(); i ++)
        {
            finalMessage += m_messageList[i].Message();
        }

        finalMessage += "\n";

        m_messageList.clear();

        mp_socket->write(finalMessage.c_str());

        mp_socket->waitForBytesWritten();

        m_sentThisHandshake = true;
    }


    if(m_sentThisHandshake && m_receivedThisHandshake)
    {
        m_sentThisHandshake = false;
        m_receivedThisHandshake = false;
    }
}












//mp_socket->write("Hello from C++! This is an especially long message because I need to test some things. "
//                 "Here, let me tell you a story. Once upon a time... ah whatever. This "
//                 "message is plenty long. Or maybe not? Here let's keep going. So once upon a "
//                 "time there were two penguins. One of them is called Matt. He's just a kid "
//                 "in high school, looking to make his life out of something. He likes noodles,"
//                 "robotics (that's why he's programming this!), UC Berkeley (PLEASE ACCEPT ME), "
//                 "and another penguin. This penguin is very special- the best that there is, "
//                 "smart, loving, caring, supportive, and absolutely adorable. Her name is Kassi "
//                 "(but who's Kassandra again?). Together, the two penguins work together to "
//                 "support each other, defeat AP Lit work, and make life so much better.\n");
