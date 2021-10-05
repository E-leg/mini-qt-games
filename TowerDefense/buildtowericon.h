#ifndef BUILDTOWERICON_H
#define BUILDTOWERICON_H

#include <QGraphicsSceneMouseEvent>
#include <QGraphicsPixmapItem>
#include <QGraphicsItem>
#include <QObject>

class BuildTowerIcon : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    // constructor
    BuildTowerIcon(int index=0, QGraphicsItem *parent=0);

    // methods
    void setInScene(int x=0, int y=0);

    // events
    void mousePressEvent(QGraphicsSceneMouseEvent *event);

    // getters
    int getCost();

protected:
    int m_index;
    int cost;
};

#endif // BUILDTOWERICON_H
