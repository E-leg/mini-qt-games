#ifndef BASEITEM_H
#define BASEITEM_H

#include <QGraphicsPixmapItem>
#include <QGraphicsItem>
#include "qmath.h"

class BaseItem : public QGraphicsPixmapItem
{
public:
    // constructor
    BaseItem(QGraphicsItem *parent=0);

    // methods
    double getXc();
    double getYc();
    QPointF getCenter();
    QPointF getSceneCenter();
    void rotateToPoint(QPointF point);
    qreal orientation();

protected:
    qreal angle_move;
};

#endif // BASEITEM_H
