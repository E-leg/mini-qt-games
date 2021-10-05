#include "swordtower.h"
#include "bullet.h"
#include "game.h"

extern Game *game;

extern int IDX_SWORD;
extern int DMG_SWORD;
extern int RNG_SWORD;
extern int ATM_SWORD;
extern int BSP_SWORD;
extern QString IMG_SWORD;

SwordTower::SwordTower(QGraphicsItem *parent): Tower(QPixmap(IMG_SWORD), RNG_SWORD, parent)
{
    // set attack speed
    m_speed = ATM_SWORD;
}

void SwordTower::fire()
{
    // create a bullet
    Bullet *bullet = new Bullet(IDX_SWORD, DMG_SWORD, BSP_SWORD);
    bullet->setPos(getSceneCenter());

    // set direction
    QLineF ln(getSceneCenter(), attack_dest);
    double angle = -1 * ln.angle();
    bullet->setRotation(angle);

    // set to scene
    game->scene->addItem(bullet);
}
