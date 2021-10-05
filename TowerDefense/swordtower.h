#ifndef SWORDTOWER_H
#define SWORDTOWER_H

#include "tower.h"

class SwordTower : public Tower
{
public:
    // constructor
    SwordTower(QGraphicsItem *parent=0);

    // implements fire from Tower
    void fire();
};

#endif // SWORDTOWER_H
