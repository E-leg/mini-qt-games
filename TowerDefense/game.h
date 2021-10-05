#ifndef GAME_H
#define GAME_H

#include "intdisplayicon.h"
#include "intdisplaytext.h"
#include "baseitem.h"
#include <QGraphicsView>
#include <QMouseEvent>
#include <QKeyEvent>
#include "sounds.h"
#include <QObject>
#include "tower.h"
#include <QTimer>
#include "road.h"
#include "wave.h"

class Game: public QGraphicsView
{
    Q_OBJECT
public:
    Game();

    // methods
    void setBuildingCursor(QString filename, int range, QPointF pos);
    void destroyItem(QGraphicsItem *item);
    void setBuildingTowers();
    void gameOver(bool win);
    bool notColliding();
    void decreaseLife();
    void setInfos();
    void start();

    // events
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void keyPressEvent(QKeyEvent *event);

    // scene
    QGraphicsScene *scene;

    // build attributes
    QGraphicsEllipseItem *cursor_area;
    BaseItem *cursor;
    int buildCost;
    Tower *build;

    // display item attributes
    IntDisplayIcon *lives;
    IntDisplayIcon *gold;
    IntDisplayIcon *nextWave;
    IntDisplayText *numWave;
    IntDisplayText *score;

    // other attributes
    Sounds *sounds;
    Road *road;
    Wave *wave;

public slots:
    void update();

signals:
    void moveBullets();
    void moveEnemies();
    void checkHits();
    void towersFire();

private:
    QTimer *updateTimer;
};

#endif // GAME_H
