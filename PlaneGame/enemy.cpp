#include "enemy.h"
#include <QTimer>
#include "game.h"
#include <QDebug>
#include <QList>
#include "bullet.h"
#include "player.h"
#include <stdlib.h> // rand() -> really large int

extern Game *game;

Enemy::Enemy(): QObject(), QGraphicsPixmapItem()
{   
    // draw graphics
    setPixmap(QPixmap(":/img/images/enemy.png"));

    // set random position
    int x_max = (int) (game->sceneRect().width() - pixmap().width());
    int random_x = rand() % x_max;
    setPos(random_x,0);

    // connect
    QTimer *timer = new QTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(move()));
    timer->start(50);


    // Set explosion sound
    explosionSound = new QMediaPlayer();
    explosionSound->setMedia(QUrl("qrc:/sounds/sounds/explosion.wav"));
}

void Enemy::move()
{
    // if collides with enemy, destroy both
    QList<QGraphicsItem *> collinding_items = collidingItems();
    for (int i(0); i<collinding_items.size(); i++){

        if (typeid(*(collinding_items[i])) == typeid(Bullet)){

            // remove them both
            game->removeItem(collinding_items[i]);
            game->removeItem(this);

            // delete them both
            delete collinding_items[i];
            delete this;

            // play explosion sound
            if (explosionSound->state() == QMediaPlayer::PlayingState){
                explosionSound->setPosition(0);
            }
            else if (explosionSound->state() == QMediaPlayer::StoppedState){
                explosionSound->play();
            }

            //increase the score
            game->increaseScore();

            return;
        }
        else if (typeid(*(collinding_items[i])) == typeid(Player)){

            // play explosion sound
            if (explosionSound->state() == QMediaPlayer::PlayingState){
                explosionSound->setPosition(0);
            }
            else if (explosionSound->state() == QMediaPlayer::StoppedState){
                explosionSound->play();
            }

            // remove them both
            game->removeItem(collinding_items[i]);
            game->removeItem(this);

            // delete them both
            delete this;

            // game over
            game->over();

            qDebug() << "GAME OVER";
            return;
        }
    }

    // move down
    setPos(x(), y() + game->speed_enemy);
    if (pos().y() > game->sceneRect().height()){
        game->removeItem(this);
        delete this;

        // decrease score
        game->decreaseHealth();

    }
}
