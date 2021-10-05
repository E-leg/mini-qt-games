#ifndef ENEMY_H
#define ENEMY_H

#include <QGraphicsPixmapItem>
#include <QObject>
#include <QMediaPlayer>

class Enemy : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    Enemy();

public slots:
    void move();

protected:
    QMediaPlayer *explosionSound;
};

#endif // ENEMY_H
