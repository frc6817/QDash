#ifndef SCHEDULER_H
#define SCHEDULER_H


#include <QThread>


class Scheduler : public QThread
{
    Q_OBJECT


public:
    explicit Scheduler(QObject *parent = nullptr , int tickRate = 100);


    /**
     * @brief Runs the scheduler at the tickrate specified- this is executed on a
     * separate thread. At each tick, the tick signal is emitted. This method
     * DOES NOT emit immediately- the first tick occurs after the specified tickrate
     * has elapsed.
     */
    void run();


private:
    int m_tickRate;


signals:
    /**
     * @brief Emitted whenever the scheduler ticks- this is however long is specified
     * in the constructor
     */
    void tick();


};


#endif // SCHEDULER_H
