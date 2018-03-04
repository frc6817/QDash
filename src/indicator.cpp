#include "indicator.h"

#include <QtCore>


Indicator::Indicator(QWidget *parent)
{
    mp_scene = new QGraphicsScene(parent);
}


void Indicator::SetConnected()
{
    SetIndicatorColor(Qt::green);
}


void Indicator::SetDisconnected()
{
    SetIndicatorColor(Qt::red);
}


void Indicator::SetIndicatorColor(QColor color)
{
    mp_scene->addRect(0 , 0 , 5000 , 5000 , QPen() , QBrush(color));
    setScene(mp_scene);
}
