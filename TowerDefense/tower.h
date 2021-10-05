#ifndef TOWER_H
#define TOWER_H

#include <QGraphicsSceneMouseEvent>
#include <QGraphicsPolygonItem>
#include "baseitem.h"
#include <QMediaPlayer>
#include <QObject>

class Tower : public QObject, public BaseItem
{
    Q_OBJECT
public:
    // constructor
    Tower(QPixmap pix, int range, QGraphicsItem *parent = nullptr);

    // methods
    double distanceTo(QGraphicsItem *item);
    void rotateToPoint(QPointF point);
    static QGraphicsEllipseItem* setAttackArea(BaseItem *item, int range, QColor color=Qt::lightGray);

    // events
    void mousePressEvent(QGraphicsSceneMouseEvent *event);

public slots:
    virtual void fire();
    void acquire_target();

protected:
    // attack parameters
    QGraphicsEllipseItem *attack_area;
    QPointF attack_dest;
    bool hasTarget;
    int m_range;
    int m_speed;
    int reloadTime;

    // sound
    QMediaPlayer *towerShot_;

    // geometry transform
    QTransform mirror;
};
#endif // TOWER_H
