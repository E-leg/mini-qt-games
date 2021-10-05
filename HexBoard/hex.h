#ifndef HEX_H
#define HEX_H

#include <QGraphicsPolygonItem>
#include <QGraphicsSceneMouseEvent>

class Hex : public QGraphicsPolygonItem
{
public:
    // constructor
    Hex(QGraphicsItem *parent=NULL);

    // methods
    void displaySideAttacks();
    void fightNeighbords();

    // getters
    int getAttackOf(int side);
    QString getOwner();
    bool isPlaced();

    // setters
    void setAttackOf(int side, int attack);
    void setOwner(QString player);
    void setPLaced(bool b);

    // events
    void mousePressEvent(QGraphicsSceneMouseEvent *event);

private:
    QString owner;
    QList<int> sideAttack;
    QList<QGraphicsTextItem*> attackItem;
    QList<QGraphicsLineItem*> neighborLines;
    bool placed;

    // methods
    void createLines();
};

#endif // HEX_H
