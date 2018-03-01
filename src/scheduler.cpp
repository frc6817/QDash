#include "scheduler.h"


Scheduler::Scheduler(QObject *parent, int tickRate)
{
    m_tickRate = tickRate;
}


void Scheduler::run()
{
    using namespace std::chrono;

    long long startPauseTime = duration_cast <milliseconds> (system_clock::now().time_since_epoch()).count();

    for(;;)
    {
        if(duration_cast <milliseconds> (system_clock::now().time_since_epoch()).count() -
                startPauseTime >= m_tickRate)
        {
            emit tick();
            startPauseTime = duration_cast <milliseconds> (system_clock::now().time_since_epoch()).count();
        }
    }
}
