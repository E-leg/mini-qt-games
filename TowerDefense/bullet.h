#ifndef BULLET_H
#define BULLET_H

#include "baseitem.h"
#include <QGraphicsItem>
#include <QMediaPlayer>
#include <QObject>

class Bullet : public QObject, public BaseItem
{
    Q_OBJECT
public:
    // constructor
    Bullet(int index, int dmg, int spd, QGraphicsItem *parent=0);

public slots:
    void move();
    void verifyIfHitEnemy();

protected:
    // attributes
    int damage;
    int speed;
    QMediaPlayer *hitEnemy;

    // methods
    void explode();
};

#endif // BULLET_H
