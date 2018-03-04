#ifndef MATCHTIMER_H
#define MATCHTIMER_H


#include <QLCDNumber>
#include <QTimer>


class MatchTimer: public QLCDNumber
{
    Q_OBJECT


public:
    MatchTimer(QWidget *parent = 0);


    /**
     * @brief Displays the given time as a digital clock would.
     * Minutes and seconds are divided with a colon (:)
     *
     * @param minutes Minutes to set to the match timer
     * @param seconds Seconds to set to the match timer
     */
    void DisplayTime(int minutes , int seconds);


    /**
     * @brief Initiates the autonomous period countdown. The timer is
     * first set to 2:30 and counts down to 2:15
     */
    void AutoCountdown();


    /**
     * @brief Initiates the teleoperated period countdown. The timer is
     * first set to 2:15 and counts down to 0:00
     */
    void TeleOpCountdown();


private:
    QTimer *mp_timer;

    int m_currentMinutes;
    int m_currentSeconds;
    int m_secondsLeftToCountdown;


private slots:
    /**
     * @brief Called once per second- manages the actual updating of the timer.
     * Counts down on the timer for a specified number of seconds stored in
     * an internal variable.
     */
    void Tick();
};


#endif // MATCHTIMER_H
