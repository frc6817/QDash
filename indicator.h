#ifndef INDICATOR_H
#define INDICATOR_H


#include <QMainWindow>
#include <QGraphicsView>
#include <QGraphicsRectItem>


class Indicator: public QObject
{
    Q_OBJECT

public:
    Indicator(QGraphicsView *view , QGraphicsScene *scene);


private:
    QGraphicsView *mp_view;
    QGraphicsScene *mp_scene;


    /**
     * @brief Sets the indicator to the specified color
     *
     * @param Color to set the indicator to
     */
    void SetIndicatorColor(QColor color);


public slots:
    /**
     * @brief Sets the indicator to green upon connection to RoboRio
     */
    void SetConnected();


    /**
     * @brief Sets the indicator to red upon connection to RoboRio
     */
    void SetDisconnected();
};

#endif // INDICATOR_H
