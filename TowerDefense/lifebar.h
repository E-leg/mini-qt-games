#ifndef LIFEBAR_H
#define LIFEBAR_H

#include <QGraphicsRectItem>

class LifeBar : public QGraphicsRectItem
{
public:
    // constructor
    LifeBar(QPointF point, int health=100, QGraphicsItem *parent=0);

    // methods
    QColor getColor(int health);
    void decreaseLife(int n);
    void setPos(QPointF pos);

protected:
    QGraphicsRectItem *colorBar;
    int width;
    int height;
    int space;
    int max_life;
    int life;

};

#endif // LIFEBAR_H
