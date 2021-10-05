#include "eyetower.h"
#include "bullet.h"
#include "game.h"

extern Game *game;

extern int IDX_EYE;
extern int DMG_EYE;
extern int RNG_EYE;
extern int ATM_EYE;
extern int BSP_EYE;
extern QString IMG_EYE;

EyeTower::EyeTower(QGraphicsItem *parent): Tower(QPixmap(IMG_EYE), RNG_EYE, parent)
{
    // set attack speed
    m_speed = ATM_EYE;
}

void EyeTower::fire()
{
    // create a bullet
    Bullet *bullet = new Bullet(IDX_EYE, DMG_EYE, BSP_EYE);
    bullet->setPos(getSceneCenter());

    // set direction
    QLineF ln(getSceneCenter(), attack_dest);
    double angle = -1 * ln.angle();
    bullet->setRotation(angle);

    // add to scene
    game->scene->addItem(bullet);
}

