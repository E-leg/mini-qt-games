#ifndef EYETOWER_H
#define EYETOWER_H

#include "tower.h"

class EyeTower : public Tower
{
public:
    // constructor
    EyeTower(QGraphicsItem *parent=0);

    // implement fire from Tower
    void fire();
};

#endif // EYETOWER_H
