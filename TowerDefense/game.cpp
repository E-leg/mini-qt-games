#include "game.h"
#include <QGraphicsScene>
#include <QGraphicsLineItem>
#include "buildtowericon.h"
#include "demontower.h"
#include "eyetower.h"
#include "swordtower.h"
#include "bullet.h"
#include "enemy.h"

extern int TIMER;

Game::Game(): QGraphicsView()
{
    // create a scene
    scene = new QGraphicsScene(this);
    scene->setSceneRect(0, 0, 800, 600);

    // set the scene
    setScene(scene);
    setBackgroundBrush(QBrush(QImage(":/img/Images/background.png")));

    // set cursor
    cursor = nullptr;
    build = nullptr;
    buildCost = 0;
    setMouseTracking(true);

    // set size
    setFixedSize(800,600);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    // create road
    road = new Road;
    scene->addItem(road);

    // create enemy waves
    wave = new Wave(road);
}

void Game::start(){
    // set sounds & music
    sounds = new Sounds;
    sounds->backgroundMusics();

   // set display infos
   setInfos();

   // set building towers
   setBuildingTowers();

   // launch waves
   wave->start();

   // start update the movements
   updateTimer = new QTimer;
   connect(updateTimer, SIGNAL(timeout()), this, SLOT(update()));
   updateTimer->start(TIMER);
}

void Game::setBuildingCursor(QString filename, int range, QPointF pos)
{
    if (cursor){
        destroyItem(cursor);}

    cursor = new BaseItem();
    cursor->setPixmap(QPixmap(filename));
    cursor_area = Tower::setAttackArea(cursor, range, Qt::green);
    cursor->setPos(pos-cursor->getCenter());
    scene->addItem(cursor);
}

void Game::mouseMoveEvent(QMouseEvent *event)
{
    if (cursor){
        cursor->setPos(event->pos()-cursor->getCenter());

        QPen pen;
        pen.setStyle(Qt::DotLine);
        pen.setWidth(2);
        if (notColliding()) {
            pen.setColor(Qt::green);} 

        else {
            pen.setColor(Qt::red);}

        cursor_area->setPen(pen);
    }
}

void Game::mousePressEvent(QMouseEvent *event)
{
    if (build){
        if (event->button() == Qt::LeftButton) {
            if (notColliding()){
                sounds->buildTower();
                build->setPos(event->pos()-cursor->getCenter());
                scene->addItem(build);
                scene->removeItem(cursor);
                cursor = nullptr;
                build = nullptr;

                // decrease gold
                gold->decrease(buildCost);

                this->setCursor(Qt::ArrowCursor);
            }
            else {
                sounds->clickNotAllowed();
            }
        }
        else {
            destroyItem(cursor);
            cursor = nullptr;
            build = nullptr;
            this->setCursor(Qt::ArrowCursor);
        }
    }
    else {
        QGraphicsView::mousePressEvent(event);
    }
}

void Game::keyPressEvent(QKeyEvent *event){
    if (event->key() == Qt::Key_G && lives->getValue() > 0)
        {gold->increase();}

    else if (event->key() == Qt::Key_L && lives->getValue() > 0)
        {lives->increase();}
}

void Game::destroyItem(QGraphicsItem *item)
{
    scene->removeItem(item);
    delete item;
}

bool Game::notColliding()
{
    // the item must not overlap towers or the road
    QList<QGraphicsItem *> collision_items = cursor->collidingItems();
    for (int i(0); i < collision_items.size(); i++){
        Road *test = dynamic_cast<Road *>(collision_items[i]);
        if (test){
            return false;
        }
        DemonTower *test2 = dynamic_cast<DemonTower *>(collision_items[i]);
        if (test2){
            return false;
        }
        EyeTower *test3 = dynamic_cast<EyeTower *>(collision_items[i]);
        if (test3){
            return false;
        }
        SwordTower *test4 = dynamic_cast<SwordTower *>(collision_items[i]);
        if (test4){
            return false;
        }
        BuildTowerIcon *test5 = dynamic_cast<BuildTowerIcon *>(collision_items[i]);
        if (test5){
            return false;
        }
    }
    return true;
}

void Game::decreaseLife()
{
    if (lives->getValue() > 0){
        sounds->lifeLost();
        lives->decrease();
        if (lives->getValue() == 0){
            gameOver(false);
        }
    }
}

void Game::gameOver(bool win)
{
    updateTimer->stop();
    wave->stop();
    nextWave->setValue(0);

    QGraphicsTextItem *gameOverText = new QGraphicsTextItem;

    if (!win){
        wave->gameOver();
        sounds->gameOverLose();
        QList<QGraphicsItem *> items = scene->items();
        for (int i(0); i < items.size(); i++){
            DemonTower *test2 = dynamic_cast<DemonTower *>(items[i]);
            if (test2){
                destroyItem(test2);
            }
            EyeTower *test3 = dynamic_cast<EyeTower *>(items[i]);
            if (test3){
                destroyItem(test3);
            }
            SwordTower *test4 = dynamic_cast<SwordTower *>(items[i]);
            if (test4){
                destroyItem(test4);
            }
            BuildTowerIcon *test5 = dynamic_cast<BuildTowerIcon *>(items[i]);
            if (test5){
                test5->setEnabled(false);
            }
        }

        gameOverText->setPlainText(QString("GAME OVER"));
        gameOverText->setDefaultTextColor(Qt::red);
    }
    else {
        sounds->gameOverWin();
        gameOverText->setPlainText(QString("YOU WON !"));
        gameOverText->setDefaultTextColor(Qt::yellow);
    }

    gameOverText->setFont(QFont("times", 40));
    gameOverText->setPos(scene->width()/2-170, scene->height()/2-70);
    gameOverText->setZValue(2);
    scene->addItem(gameOverText);

    score->setFont(QFont("times", 20));
    score->setPos(scene->width()/2-80, scene->height()/2+10);
}

void Game::setBuildingTowers()
{
    // set demon building tower
    BuildTowerIcon *demon = new BuildTowerIcon(0);
    demon->setInScene(10,10);
    scene->addItem(demon);

    // set eye building tower
    BuildTowerIcon *eye = new BuildTowerIcon(1);
    eye->setInScene(10,120);
    scene->addItem(eye);

    // set sword building tower
    BuildTowerIcon *sword = new BuildTowerIcon(2);
    sword->setInScene(10,230);
    scene->addItem(sword);
}

void Game::setInfos()
{
    score = new IntDisplayText(QPointF(100, 5), 0, QString("Score"));
    scene->addItem(score);

    lives = new IntDisplayIcon(QPointF(100, 45), 10, QString(":/img/Images/life.png"));
    scene->addItem(lives);

    gold = new IntDisplayIcon(QPointF(100, 85), 100, QString(":/img/Images/gold.png"));
    scene->addItem(gold);

    nextWave = new IntDisplayIcon(QPointF(590, 565), wave->getTimeNextWave(), QString(":/img/Images/time.png"));
    scene->addItem(nextWave);

    numWave = new IntDisplayText(QPointF(660, 565), 0, QString("Wave"));
    scene->addItem(numWave);

}

void Game::update(){
    emit moveBullets();
    emit moveEnemies();
    emit checkHits();
    emit towersFire();
}



