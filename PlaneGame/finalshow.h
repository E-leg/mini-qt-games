#ifndef FINALSHOW_H
#define FINALSHOW_H

#include <QGraphicsPixmapItem>
#include <QObject>

class FinalShow : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    FinalShow();

public slots:
    void move();
};

#endif // FINALSHOW_H

