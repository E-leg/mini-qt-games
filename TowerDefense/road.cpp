#include "road.h"
#include <QPixmap>

Road::Road(QGraphicsItem *parent): QGraphicsPixmapItem(parent)
{
    setPixmap(QPixmap(":/img/Images/road.png"));
    points << QPointF(785,0) << QPointF(785,12) << QPointF(785,75) << QPointF(635,75) << QPointF(635,225) << QPointF(485,225)
           << QPointF(485,375) << QPointF(185,375) << QPointF(185,555) << QPointF(15,555) << QPointF(15,590);
}

QList<QPointF> Road::getPoints(){
    return points;
}
