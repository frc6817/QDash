#ifndef SCHEDULER_H
#define SCHEDULER_H


#include <QThread>


class Scheduler : public QThread
{
    Q_OBJECT

public:
    explicit Scheduler(QObject *parent = nullptr , int tickRate = 2000);


    void run();


private:
    int m_tickRate;


signals:
    /**
     * @brief Emitted whenever the scheduler ticks- this is however long is specified
     * in the constructor
     */
    void tick();

public slots:
};


#endif // SCHEDULER_H
