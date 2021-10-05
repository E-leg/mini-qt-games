#include "intdisplaytext.h"

#include <QFont>

IntDisplayText::IntDisplayText(QPointF pos, int val, QString str, QGraphicsItem *parent): QGraphicsTextItem(parent)
{
    // set title and value
    value = val;
    title = str;

    // set graphics
    setPlainText(title + QString(" : %1").arg(value));
    setFont(QFont("times", 14));
    setDefaultTextColor(Qt::lightGray);
    setPos(pos.x(), pos.y());

    // set in the foreground
    setZValue(2);
}

int IntDisplayText::getValue(){
    return value;
}

void IntDisplayText::setValue(int val){
    value = val;
    setPlainText(title + QString(" : %1").arg(value));
}

void IntDisplayText::increase(int n){
    value += n;
    setPlainText(title + QString(" : %1").arg(value));
}

void IntDisplayText::decrease(int n){
    value -= n;
    setPlainText(title + QString(" : %1").arg(value));
}
