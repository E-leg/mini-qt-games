#include "bullet.h"
#include "enemy.h"
#include "game.h"
#include <QTimer>
#include <qmath.h>

extern Game *game;
extern int TIMER;

Bullet::Bullet(int index, int dmg, int spd, QGraphicsItem *parent): QObject(), BaseItem(parent)
{
    // set graphics
    setPixmap(QPixmap(QString(":/img/Images/bullet%1.png").arg(index)));

    // initialze values
    damage = dmg;
    speed = spd;

    // set hit sound
    hitEnemy = new QMediaPlayer(this);
    hitEnemy->setMedia(QUrl("qrc:/snd/Sounds/enemyDamaged.wav"));

    // connect to game update
    connect(game, SIGNAL(moveBullets()), this, SLOT(move()));
    connect(game, SIGNAL(checkHits()), this, SLOT(verifyIfHitEnemy()));
}

void Bullet::move() {
    // compute displacement parameters
    double theta = rotation(); //degree
    double dx = speed * qCos(qDegreesToRadians(theta));
    double dy = speed * qSin(qDegreesToRadians(theta));

    // set position
    setPos(x() + dx, y() + dy);

    // destroy if it quits the scene
    if (x()+dx<0 || x()+dx>game->scene->width() || y()+dy<0 || y()+dy>game->scene->height()){
        game->destroyItem(this);}
}

void Bullet::verifyIfHitEnemy()
{
    // look if it hits an enemy
    QList<QGraphicsItem *> cItems = collidingItems();
    for (int i(0); i < cItems.size(); i++){
        Enemy *enemy = dynamic_cast<Enemy *>(cItems[i]);
        if (enemy){
            enemy->decreaseHealth(damage);
            explode();
            return;}
    }
}

void Bullet::explode(){
    game->sounds->play(hitEnemy);
    game->destroyItem(this);
}

