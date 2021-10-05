#include "bullet.h"
#include "demontower.h"
#include "game.h"

extern Game *game;

extern int IDX_DEMON;
extern int DMG_DEMON;
extern int RNG_DEMON;
extern int ATM_DEMON;
extern int BSP_DEMON;
extern QString IMG_DEMON;

DemonTower::DemonTower(QGraphicsItem *parent): Tower(QPixmap(IMG_DEMON), RNG_DEMON, parent)
{   
    // set attack speed
    m_speed = ATM_DEMON;
}

void DemonTower::fire()
{
    // create a bullet
    Bullet *bullet = new Bullet(IDX_DEMON, DMG_DEMON, BSP_DEMON);
    bullet->setPos(getSceneCenter());

    // set the angle
    QLineF ln(getSceneCenter(), attack_dest);
    double angle = -1 * ln.angle();
    bullet->setRotation(angle);

    // add to scene
    game->scene->addItem(bullet);
}
