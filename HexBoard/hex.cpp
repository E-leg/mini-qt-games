#include "hex.h"
#include "game.h"
#include <QBrush>
#include <QDebug>

extern Game *game;

Hex::Hex(QGraphicsItem *parent): QGraphicsPolygonItem(parent)
{
    // draw the hexagon
    QVector<QPointF> hexPoints;
    hexPoints << QPointF(1,0) << QPointF(2,0) << QPointF(3,1)
              << QPointF(2,2) << QPointF(1,2) << QPointF(0,1);
    int SCALE_BY = 40;
    for (int i=0; i<hexPoints.size(); i++) {
        hexPoints[i] *= SCALE_BY;
    }

    // create a hexagon with the scaled points
    QPolygonF hexagon(hexPoints);

    // draw the poly
    setPolygon(hexagon);

    // initialized as not placed
    placed = false;

    // initialize side attacks and item
    QVector<QPointF> itemPos;
    itemPos << QPointF(50,0) << QPointF(20,15) << QPointF(20,40)
            << QPointF(50,55) << QPointF(80,40) << QPointF(80,15);
    for (int i=0; i<6; i++){
        QGraphicsTextItem *text = new QGraphicsTextItem(QString::number(0), this);
        text->setPos(itemPos[i]);
        text->setVisible(false);
        attackItem.append(text);
        sideAttack.append(0);}

    // initialize neighborhood lines
    createLines();
}

void Hex::displaySideAttacks(){
    for (int i=0; i<6; i++){
        attackItem[i]->setVisible(true);}
}

void Hex::fightNeighbords(){
    for (int j=0; j<neighborLines.size(); j++){
        QList<QGraphicsItem*> items = neighborLines[j]->collidingItems();
        for (int i=0; i<items.size(); i++){
            Hex* hex = dynamic_cast<Hex*>(items[i]);
            if (hex && items[i] != this){
                if (hex->isPlaced()){
                    int defenseSide = (j + 3) % 6;
                    if (hex->getAttackOf(defenseSide) < sideAttack[j]){
                        hex->setOwner(game->getWhosTurn());
                    }
                }
            }
        }
    }
}

int Hex::getAttackOf(int side)
{
    return sideAttack[side];
}

void Hex::setAttackOf(int side, int attack){
    sideAttack[side] = attack;
    attackItem[side]->setPlainText(QString::number(attack));
}

QString Hex::getOwner()
{
    return owner;
}

void Hex::setOwner(QString player){
    // set the owner
    owner = player;

    // change the color
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    if (player == game->player1){
        brush.setColor(Qt::blue);
    }
    else if (player == game->player2){
        brush.setColor(Qt::red);
    }
    else if (player == game->playerNone){
        brush.setColor(Qt::lightGray);
    }
    setBrush(brush);
}

bool Hex::isPlaced()
{
    return placed;
}

void Hex::setPLaced(bool b){
    placed = b;
}

void Hex::mousePressEvent(QGraphicsSceneMouseEvent *event){
    // if hex NOT placed and belong to the current player, pick it up
    if (!placed && owner == game->getWhosTurn()){
        game->pickUpCard(this);}

    // if hex IS placed, then replace it
    else if (game->cardToPlace && owner == game->playerNone) {
        game->placeCard(this);}
}

void Hex::createLines(){
    QPointF center(x()+60, y()+40);
    QPointF finalPt(center.x(), center.y()-65);
    QLineF ln(center, finalPt);

    for (int i=0; i<6; i++){
        QLineF lnCopy(ln);
        lnCopy.setAngle(90+60*i);
        QGraphicsLineItem* line = new QGraphicsLineItem(lnCopy, this);
        line->setVisible(false);
        neighborLines.append(line);
    }
}
