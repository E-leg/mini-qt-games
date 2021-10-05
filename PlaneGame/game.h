#ifndef GAME_H
#define GAME_H

#include <QGraphicsScene>
#include <QGraphicsView>
#include <QMediaPlayer>
#include <QTimer>
#include <QObject>
#include "player.h"
#include "score.h"
#include "health.h"

class Game : public QGraphicsScene
{
    Q_OBJECT
public:
    Game();
    void increaseScore();
    void decreaseHealth();
    void over();

    int speed_player;
    double speed_enemy;
    int speed_bullet;
    int respawn_time;
    double speed_finalshow;

public slots:
    void spawn();

protected:
    int m_width;
    int m_height;
    int m_pl_size;

    QGraphicsView *m_view;
    Player *m_player;
    Score *m_score;
    Health *m_health;

    QTimer *timer;
    QMediaPlayer *music;


};

#endif // GAME_H
