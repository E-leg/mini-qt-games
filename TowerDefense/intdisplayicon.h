#ifndef INTDISPLAYICON_H
#define INTDISPLAYICON_H

#include <QGraphicsItemGroup>

class IntDisplayIcon : public QGraphicsTextItem
{
public:
    // constructor
    IntDisplayIcon(QPointF pos, int val=0, QString path="", QGraphicsItem *parent=0);

    // methods
    int getValue();
    void setValue(int val);
    void decrease(int n=1);
    void increase(int n=1);

protected:
    int value;
};

#endif // INTDISPLAYICON_H
