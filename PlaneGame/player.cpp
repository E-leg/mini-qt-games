#include "player.h"
#include <QDebug>
#include "bullet.h"
#include "game.h"

extern Game *game;

Player::Player(QGraphicsItem *parent): QGraphicsPixmapItem(parent)
{
    // draw graphics
    setPixmap(QPixmap(":/img/images/player.png"));

    // set bullet sound
    bulletsound = new QMediaPlayer();
    bulletsound->setMedia(QUrl("qrc:/sounds/sounds/shotNoise.wav"));
}

void Player::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Left && pos().x() >= 0)
    {
        setPos(x()-game->speed_player, y());
    }
    else if (event->key() == Qt::Key_Right && pos().x() + pixmap().width() < scene()->sceneRect().width())
    {
        setPos(x()+game->speed_player, y());
    }
    else if (event->key() == Qt::Key_Space)
    {
        // Create a bullet
        Bullet *bullet = new Bullet();
        bullet->setPos(x()+(pixmap().width()-bullet->pixmap().width())/2, y());
        game->addItem(bullet);

        // play bullet sound
        if (bulletsound->state() == QMediaPlayer::PlayingState){
            bulletsound->setPosition(0);
        }
        else if (bulletsound->state() == QMediaPlayer::StoppedState){
            bulletsound->play();
        }
    }
}
