#ifndef INDICATOR_H
#define INDICATOR_H


#include <QMainWindow>
#include <QGraphicsView>
#include <QGraphicsRectItem>


class Indicator: public QGraphicsView
{
    Q_OBJECT

public:
    Indicator(QWidget *parent = 0);


private:
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
