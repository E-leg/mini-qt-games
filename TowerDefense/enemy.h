#ifndef ENEMY_H
#define ENEMY_H

#include "baseitem.h"
#include "lifebar.h"
#include <QObject>
#include "wave.h"

class Enemy : public QObject, public BaseItem
{
    Q_OBJECT
public:
    // constructor
    Enemy(Wave *wave, QList<QPointF> pointsToFollow, int num, int speed=5, int health=100, int type=1, QGraphicsItem *parent=0);

    // getters
    void hideLifeBar();
    int getNumero();
    bool isDead();

    // methods
    void decreaseHealth(int damage);
    void setScoreAndGold(int type);

public slots:
    void move_forward();
    void dying();
    void die();

protected:
    // points to follow
    QList<QPointF> points;
    int point_index;
    QPointF dest;

    // characteristics
    int m_numero;
    int m_health;
    int m_speed;
    int scoreGain;
    int goldGain;
    Wave *wave_;

    // life bar
    LifeBar *lifeBar;

    // parameter for dying effect
    double opacity;   
};

#endif // ENEMY_H
