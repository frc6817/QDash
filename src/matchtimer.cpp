#include "matchtimer.h"


MatchTimer::MatchTimer(QWidget *parent)
{
    mp_timer = new QTimer();
    mp_timer->setInterval(1000);

    connect(mp_timer , SIGNAL(timeout()) , this , SLOT(Tick()));
}


void MatchTimer::DisplayTime(int minutes, int seconds)
{
    QString minuteString = QString::number(minutes);
    QString secondString = QString::number(seconds);

    m_currentMinutes = minutes;
    m_currentSeconds = seconds;

    if(secondString.length() == 1)
    {
        secondString = "0" + secondString;
    }

    display(minuteString + ":" + secondString);
}


void MatchTimer::AutoCountdown()
{
    DisplayTime(2 , 30);

    m_secondsLeftToCountdown = 15;
    mp_timer->start();
}


void MatchTimer::TeleOpCountdown()
{
    DisplayTime(2 , 15);

    m_secondsLeftToCountdown = 135;
    mp_timer->start();
}


void MatchTimer::Tick()
{
    m_currentSeconds --;

    if(m_currentSeconds < 0)
    {
        m_currentSeconds = 59;
        m_currentMinutes --;
    }

    DisplayTime(m_currentMinutes , m_currentSeconds);

    m_secondsLeftToCountdown --;

    if(m_secondsLeftToCountdown == 0)
    {
        mp_timer->stop();
    }
}


