#ifndef WAVE_H
#define WAVE_H

#include "road.h"
#include <QObject>
#include <QTimer>

class Wave : public QObject
{
    Q_OBJECT
public:
    // constructor
    Wave(Road *road);

    // methods
    void setEnemy();
    void enemyLess();
    int getTimeNextWave();
    void createEnemies(int number);
    void start();
    void stop();
    void gameOver();

public slots:
    void waitNextWave();
    void spawnEnemy();

protected:
    Road *road_;
    int health_;
    qreal velocity_;
    int type_;
    int number_;
    bool on;
    int numWave;

    int timeNextWave;
    QTimer *nextWaveTimer;

    int enemiesSpawned;
    QTimer *spawnTimer;

    int maxNumberEnemies;
    int remainingEnemies;
};

#endif // WAVE_H
