#include <QPolygonF>
#include "bullet.h"
#include "enemy.h"
#include "tower.h"
#include <QPixmap>
#include <QVector>
#include <QPointF>
#include <game.h>

extern Game *game;
extern int TIMER;

Tower::Tower(QPixmap pix, int range, QGraphicsItem *parent): QObject(), BaseItem(parent)
{
    // set attack
    m_speed = 0;
    reloadTime = 0;
    m_range = range;

    // set graphics
    setPixmap(pix);
    setZValue(1);

    // set geometry transform
    setTransformOriginPoint(getXc(), getYc());
    mirror.scale(-1,1);
    mirror.translate(-2*getXc(),0);

    // set attack circle area
    attack_area = setAttackArea(this, m_range);
    attack_area->setVisible(false);

    // set shot sound
    towerShot_ = new QMediaPlayer(this);
    towerShot_->setMedia(QUrl("qrc:/snd/Sounds/TowerShot.wav"));

    // connect to game update
    connect(game, SIGNAL(towersFire()), this, SLOT(acquire_target()));
}

double Tower::distanceTo(QGraphicsItem *item){
    QLineF ln(pos(), item->pos());
    return ln.length();
}

QGraphicsEllipseItem *Tower::setAttackArea(BaseItem *item, int range, QColor color){
    QPointF point = item->getCenter();
    QGraphicsEllipseItem *circle = new QGraphicsEllipseItem(point.x()-range/2, point.y()-range/2, range, range, item);
    QPen pen;
    pen.setColor(color);
    pen.setStyle(Qt::DotLine);
    pen.setWidth(2);
    circle->setPen(pen);
    return circle;
}

void Tower::rotateToPoint(QPointF point)
{
    QLineF ln(mapToScene(getCenter()), point);
    qreal angle = ln.angle();
    int lim = 30;

    if (angle < 90 || angle > 270){
        if (angle > 90-lim && angle < 90){
            angle = 90-lim;}

        else if (angle > 270 && angle < 270+lim){
            angle = 270+lim;}

        resetTransform();
        setRotation(-angle);
    }
    else {
        if (angle > 90 && angle < 90+lim){
            angle = 90+lim;}

        else if (angle > 270-lim && angle < 270){
            angle = 270-lim;}

        setTransform(mirror);
        setRotation(angle-180);
    }
}

void Tower::mousePressEvent(QGraphicsSceneMouseEvent *event){
    attack_area->setVisible(!attack_area->isVisible());
    game->sounds->clickTower();
}

void Tower::fire(){
    return;
}

void Tower::acquire_target(){
    // get all items colliding with attack_area
    QList<QGraphicsItem *> collision_items = attack_area->collidingItems();

    // look for a target
    hasTarget = false;
    int first_numero = 300;
    QPointF first_pt = QPointF(0,0);
    for (int i(0); i < collision_items.size(); i++){
        Enemy *enemy = dynamic_cast<Enemy *>(collision_items[i]);
        if (enemy){
            if (!enemy->isDead()){
                int this_numero = enemy->getNumero();
                if (this_numero < first_numero){
                    first_numero = this_numero;
                    first_pt = enemy->getSceneCenter();
                    hasTarget = true;}}}}

    // shot if it got a tartget
    if (hasTarget){
        attack_dest = first_pt;
        rotateToPoint(attack_dest);

        // shot if it has reloaded
        if (reloadTime <= 0){
            game->sounds->play(towerShot_);
            fire();
            reloadTime = m_speed;}}

   reloadTime -= TIMER;}

