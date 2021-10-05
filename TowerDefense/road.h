#ifndef ROAD_H
#define ROAD_H

#include <QGraphicsPixmapItem>
#include <QGraphicsItem>

class Road : public QGraphicsPixmapItem
{
public:
    Road(QGraphicsItem *parent=0);
    QList<QPointF> getPoints();

protected:
    QList<QPointF> points;
};

#endif // ROAD_H
