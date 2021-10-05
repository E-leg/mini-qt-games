#include "buildtowericon.h"
#include "demontower.h"
#include "eyetower.h"
#include "swordtower.h"
#include <QPixmap>
#include "game.h"

extern Game *game;

extern int RNG_DEMON;
extern int RNG_EYE;
extern int RNG_SWORD;

extern int CST_DEMON;
extern int CST_EYE;
extern int CST_SWORD;

BuildTowerIcon::BuildTowerIcon(int index, QGraphicsItem *parent): QObject(), QGraphicsPixmapItem(parent)
{
    // set index
    m_index = index;

    // set pixmap
    setPixmap(QPixmap(QString(":/img/Images/tower%1.png").arg(m_index+1)));

    // set cost
    QList<int> costs;
    costs.append(CST_DEMON);
    costs.append(CST_EYE);
    costs.append(CST_SWORD);
    cost = costs[index];
}

void BuildTowerIcon::setInScene(int x, int y)
{
    // initialize the border and cost items
    QGraphicsPixmapItem *border = new QGraphicsPixmapItem(QPixmap(QString(":/img/Images/buildTower_back.png")), this);
    IntDisplayIcon *costItem = new IntDisplayIcon(QPointF(0,0), cost, QString(":/img/Images/gold.png"), border);

    // set the build icon position
    setPos(x + (border->pixmap().width()-pixmap().width())/2, y+7);

    // set their positions
    border->setPos(mapFromScene(QPointF(x,y)));
    costItem->setPos(QPointF(35, border->pixmap().height()-35));
}

void BuildTowerIcon::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if (!game->build && game->gold->getValue() >= cost){
        game->sounds->buildingTower();

        if (m_index == 0){
            game->setBuildingCursor(QString(":/img/Images/tower%1.png").arg(m_index+1), RNG_DEMON, mapToScene(event->pos()));
            game->build = new DemonTower();
        }
        else if (m_index == 1){
            game->setBuildingCursor(QString(":/img/Images/tower%1.png").arg(m_index+1), RNG_EYE, mapToScene(event->pos()));
            game->build = new EyeTower();
        }
        else if (m_index == 2){
            game->setBuildingCursor(QString(":/img/Images/tower%1.png").arg(m_index+1), RNG_SWORD, mapToScene(event->pos()));
            game->build = new SwordTower();
        }
        game->setCursor(Qt::ClosedHandCursor);
        game->buildCost = cost;
    }

    else {game->sounds->clickNotAllowed();}
}

int BuildTowerIcon::getCost(){
    return cost;
}


