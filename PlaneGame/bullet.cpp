#include "bullet.h"
#include <QTimer>
#include <QDebug>
#include "game.h"

extern Game * game; // extern global variable

Bullet::Bullet(): QObject(), QGraphicsPixmapItem()
{
    // draw graphics
    setPixmap(QPixmap(":/img/images/rocket.png"));

    // connect
    QTimer *timer = new QTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(move()));
    timer->start(50);
}

void Bullet::move()
{
    // move up
    setPos(x(), y() - game->speed_bullet);

    if (pos().y() + pixmap().height() < 0){
        scene()->removeItem(this);
        delete this;
    }
}

