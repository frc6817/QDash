#ifndef MATCHTIMER_H
#define MATCHTIMER_H


#include <QLCDNumber>


class MatchTimer: public QLCDNumber
{
    Q_OBJECT


public:
    MatchTimer(QWidget *parent = 0);
};


#endif // MATCHTIMER_H
