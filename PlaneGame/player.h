#ifndef PLAYER_H
#define PLAYER_H

#include <QGraphicsPixmapItem>
#include <QKeyEvent>
#include <QMediaPlayer>

class Player :  public QGraphicsPixmapItem
{
public:
    Player(QGraphicsItem *parent=0);
    void keyPressEvent(QKeyEvent *event);

protected:
    QMediaPlayer *bulletsound;
};

#endif // PLAYER_H
