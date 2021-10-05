#ifndef DEMONTOWER_H
#define DEMONTOWER_H

#include "tower.h"
#include <QGraphicsItem>

class DemonTower : public Tower
{
public:
    DemonTower(QGraphicsItem *parent=0);

    // implements fire Tower
    void fire();
};

#endif // DEMONTOWER_H
