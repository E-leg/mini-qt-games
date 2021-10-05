#include "baseitem.h"

BaseItem::BaseItem(QGraphicsItem *parent): QGraphicsPixmapItem(parent)
{
    angle_move = 0;
}

double BaseItem::getXc()
{
    return pixmap().width() / 2;
}

double BaseItem::getYc()
{
    return pixmap().height() / 2;
}

QPointF BaseItem::getCenter()
{
    return QPointF(getXc(), getYc());
}

QPointF BaseItem::getSceneCenter()
{
    return mapToScene(getCenter());
}

void BaseItem::rotateToPoint(QPointF point)
{
    setTransformOriginPoint(getXc(), getYc());
    QLineF ln(mapToScene(getCenter()), point);
    setRotation((-1 * ln.angle()));
    angle_move = -1 * ln.angle();
}

qreal BaseItem::orientation()
{
    if (-angle_move < 45){
        return 0;
    }
    else if (-angle_move < 135){
        return -M_PI_2;
    }
    else if (-angle_move < 225){
        return -M_PI;
    }
    else {
        return -3*M_PI_2;
    }
}
