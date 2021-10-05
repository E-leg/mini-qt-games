#include "lifebar.h"
#include <QPen>

LifeBar::LifeBar(QPointF point, int health, QGraphicsItem *parent): QGraphicsRectItem(parent)
{
    // set size and space
    width = 30;
    height = 5;
    space = -15;

    // set position and size
    setRect(point.x(), point.y()+space, width, height);
    setPen(QPen(Qt::black));

    // set the color bar
    colorBar = new QGraphicsRectItem(0, space, width, height, this);
    colorBar->setBrush(QBrush(getColor(health)));

    // set life
    max_life = health;
    life = health;
}

void LifeBar::decreaseLife(int n){
    life -= n;
    colorBar->setRect(0, space, width*life/max_life, height);
}

void LifeBar::setPos(QPointF pos){
    QGraphicsRectItem::setPos(pos.x(), pos.y());
}

QColor LifeBar::getColor(int health)
{
    qreal h = (qreal) health;
    QColor col;
    if (health <= 450) {
        qreal r = 0.5 + h/900;
        col.setRgbF(r, 1, 0);
    }
    else if (health <= 900) {
        qreal g = 1-(h-450)/900;
        col.setRgbF(1, g, 0);
    }
    else if (health <= 5000) {
        qreal r = 1-h/10000;
        qreal g = 0.5-h/10000;
        col.setRgbF(r, g, 0);
    }
    else if (health == 5001) {
        col.setRgbF(0.5, 0, 0);
    }
    else if (health == 15001) {
        col.setRgbF(0, 0, 0);
    }
    else {
        col.setRgbF(1, 1, 1);
    }
    return col;
}
