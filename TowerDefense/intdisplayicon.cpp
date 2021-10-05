#include "intdisplayicon.h"
#include <QFont>

IntDisplayIcon::IntDisplayIcon(QPointF pos, int val, QString path, QGraphicsItem *parent): QGraphicsTextItem(parent)
{
    // retrieve value
    value = val;

    // create icon
    QGraphicsPixmapItem *icon = new QGraphicsPixmapItem(QPixmap(path), this);

    // set text
    setPlainText(QString("%1").arg(value));
    setFont(QFont("times", 14));
    setDefaultTextColor(Qt::lightGray);
    setPos(pos.x()+icon->pixmap().width()+5, pos.y());

    // set icon pos
    icon->setPos(-icon->pixmap().width(), (boundingRect().height()-icon->pixmap().height())/2);

    // set in the foreground
    setZValue(2);
}

int IntDisplayIcon::getValue(){
    return value;
}

void IntDisplayIcon::setValue(int val){
    value = val;
    setPlainText(QString("%1").arg(value));
}

void IntDisplayIcon::increase(int n){
    value += n;
    setPlainText(QString("%1").arg(value));
}

void IntDisplayIcon::decrease(int n){
    value -= n;
    setPlainText(QString("%1").arg(value));
}
