#ifndef INTDISPLAYTEXT_H
#define INTDISPLAYTEXT_H

#include <QGraphicsItemGroup>

class IntDisplayText : public QGraphicsTextItem
{
public:
    IntDisplayText(QPointF pos, int val=0, QString str="", QGraphicsItem *parent=0);

    int getValue();
    void setValue(int val);

    void decrease(int n=1);
    void increase(int n=1);

protected:
    int value;
    QString title;
};

#endif // INTDISPLAYTEXT_H
