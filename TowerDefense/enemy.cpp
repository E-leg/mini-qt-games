#include "enemy.h"
#include "game.h"
#include <QPixmap>
#include <QTimer>
#include <qmath.h>
#include <QDebug>

extern Game *game;

Enemy::Enemy(Wave *wave, QList<QPointF> pointsToFollow, int num, int speed, int health, int type, QGraphicsItem *parent): QObject(), BaseItem(parent)
{
    // set characteristics
    wave_ = wave;
    m_numero = num;
    m_health = health;
    m_speed = speed;
    setScoreAndGold(type);

    // set points to follow
    points = pointsToFollow;
    point_index = 1;
    dest = points[point_index];

    // set pixmap
    setPixmap(QPixmap(QString(":/img/Images/enemy%1.png").arg(type)));

    // set position and rotation
    setPos(points[0]-getCenter());
    rotateToPoint(dest);

    // set lifebar
    lifeBar = new LifeBar(QPointF(0,0), m_health);
    game->scene->addItem(lifeBar);

    // initialize param for dying effect
    opacity = 1;

    // connect to game update
    connect(game, SIGNAL(moveEnemies()), this, SLOT(move_forward()));
}

void Enemy::decreaseHealth(int damage){
    if (!isDead()){
        m_health -= damage;
        lifeBar->decreaseLife(damage);}
}

bool Enemy::isDead(){
    return (m_health <= 0);
}

void Enemy::hideLifeBar(){
    lifeBar->setVisible(false);
}

void Enemy::setScoreAndGold(int type)
{
    if (type == 1){
        goldGain = 1;
        scoreGain = 10;
    }
    else if (type == 2){
        goldGain = 10;
        scoreGain = 100;
    }
    else if (type == 3){
        goldGain = 100;
        int n = game->numWave->getValue();
        scoreGain = 100*n;
    }
}

int Enemy::getNumero()
{
    return m_numero;
}

void Enemy::move_forward()
{
    if (!isDead()) {
        // if close to dest, rotate to next dest
        QLineF ln(mapToScene(getCenter()), dest);
        if (ln.length() < 10){
            setPos(dest-getCenter());
            point_index++;

            // if it reached the last points
            if (point_index == points.length()){
                wave_->enemyLess();
                game->destroyItem(lifeBar);
                game->destroyItem(this);
                game->decreaseLife();
                return;}

            else { // set the new direction
                dest = points[point_index];
                rotateToPoint(dest);
                setPos(points[point_index-1]-getCenter());
                lifeBar->setPos(pos());
                return;}
        }

        // move enemy forward at current angle
        double dx = m_speed * qCos(orientation());
        double dy = m_speed * qSin(orientation());
        setPos(x()+dx, y()+dy);
        lifeBar->setPos(pos());}

    else { // it dies
        // disconnect move
        disconnect(game, SIGNAL(moveEnemies()), this, SLOT(move_forward()));

        // update
        wave_->enemyLess();
        game->destroyItem(lifeBar);
        game->gold->increase(goldGain);
        game->score->increase(scoreGain);

        // change pixmap to death image
        setPixmap(QPixmap(":/img/Images/death.png"));
        setPos(x(), y()-10);
        setRotation(0);

        // dying animation
        QTimer *dying_timer = new QTimer(this);
        connect(dying_timer, SIGNAL(timeout()), this, SLOT(dying()));
        dying_timer->start(200);

        // delete enemy
        QTimer *death_timer = new QTimer(this);
        connect(death_timer, SIGNAL(timeout()), this, SLOT(die()));
        death_timer->start(2000);}
}

void Enemy::dying()
{
    // Slowly reduce opacity
    opacity -= 0.1;
    QPixmap alpha(pixmap().size());
    alpha.fill(Qt::transparent);
    QPainter painter(&alpha);
    painter.setOpacity(opacity);
    painter.drawPixmap(0, 0, pixmap());
    painter.end();
    setPixmap(alpha);

    // move up
    setPos(x(), y()-1);
}

void Enemy::die()
{
    game->destroyItem(this);
}


