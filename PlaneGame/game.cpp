#include "game.h"
#include "enemy.h"
#include "finalshow.h"
#include <QDebug>
#include <QImage>
#include <QFont>
#include <QList>
#include <QMediaPlaylist>

Game::Game(): QGraphicsScene()
{
    // set parameters
    speed_player = 15;
    speed_enemy = 5;
    speed_bullet = 10;
    respawn_time = 1500;
    speed_finalshow = 1;

    // set size
    m_width = 800;
    m_height = 600;
    setSceneRect(0, 0, m_width, m_height);

    // set background
    setBackgroundBrush(QBrush(QImage(":/img/images/sky.png")));

    // add a view
    m_view = new QGraphicsView(this);
    m_view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_view->setFixedSize(m_width, m_height);

    // add the player
    m_pl_size = 100;
    m_player = new Player();
    m_player->setPos((m_width-m_pl_size)/2, m_height-m_pl_size);
    m_player->setZValue(1); // Put player in the foreground
    addItem(m_player);

    // focus on the player
    m_player->setFlag(QGraphicsItem::ItemIsFocusable);
    m_player->setFocus();

    // create the score
    m_score = new Score();
    m_score->setZValue(1); // Foreground
    addItem(m_score);

    // create the score
    m_health = new Health();
    m_health->setPos(0,35);
    m_health->setZValue(1); // Foreground
    addItem(m_health);

    // spawn enemies
    timer = new QTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(spawn()));
    timer->start(respawn_time);

    // play background music
    QMediaPlaylist *playlist = new QMediaPlaylist();
    playlist->addMedia(QUrl("qrc:/sounds/sounds/musicTheme.wav"));
    playlist->setPlaybackMode(QMediaPlaylist::Loop);

    music = new QMediaPlayer();
    music->setPlaylist(playlist);
    music->play();

    // show
    m_view->show();
}

void Game::increaseScore()
{
    m_score->increase();
}

void Game::decreaseHealth()
{
    m_health->decrease();
    if (m_health->getHealth() == 0){
        qDebug() << "NO MORE LIVES";
        over();
    }
}

void Game::over()
{
    timer->stop();
    music->setMedia(QUrl("qrc:/sounds/sounds/GameOver.wav"));
    music->play();

    // Remove all enemies
    QList<QGraphicsItem *> all_items = items();
    for (int i(0); i<all_items.size(); i++){
        if (typeid(*(all_items[i])) == typeid(Enemy)){
            removeItem(all_items[i]);
            delete all_items[i];
        }
    }

    // display the score
    m_score->setFont(QFont("times", 42));
    m_score->setPos(m_width/2 - 150, m_height/2 - 60);

    // set final show
    FinalShow *show = new FinalShow();
    show->setPos((m_width-show->pixmap().width())/2, m_height);
    addItem(show);

}

void Game::spawn()
{
    // create an enemy
    Enemy *enemy = new Enemy();
    addItem(enemy);

    // update enemy parameters
    speed_enemy += 0.2;
    respawn_time -= 10;
    timer->start(respawn_time);

    qDebug() << QString("Speed : %2").arg(speed_enemy);
    qDebug() << QString("Respawn : %2 ms").arg(respawn_time);
    qDebug() << "";
}

