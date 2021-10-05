#include "finalshow.h"

#include <QTimer>
#include "game.h"

extern Game *game;

FinalShow::FinalShow() : QObject(), QGraphicsPixmapItem()
{
    // draw graphics
    setPixmap(QPixmap(":/img/images/finalshow.png"));

    // connect
    QTimer *timer = new QTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(move()));
    timer->start(60);
}


void FinalShow::move()
{
    // move up
    setPos(x(), y() - game->speed_finalshow);
    if (pos().y() > game->sceneRect().height()){
        game->removeItem(this);
        delete this;
    }
}
