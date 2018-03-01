#include "indicator.h"

#include <QtCore>

Indicator::Indicator(QGraphicsView *view , QGraphicsScene *scene) :
    mp_view(view) ,
    mp_scene(scene)
{

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
    mp_view->setScene(mp_scene);
}
