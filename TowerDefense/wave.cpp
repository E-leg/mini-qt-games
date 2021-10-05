#include "enemy.h"
#include "game.h"
#include "wave.h"

extern Game *game;

Wave::Wave(Road *road): QObject()
{
    // set road
    road_ = road;

    // set parameters
    health_ = 100;
    velocity_ = 5;
    type_ = 1;
    number_ = 10;
    numWave = 1;
    on = true;

    // set waves
    timeNextWave = 10;
    nextWaveTimer = new QTimer;
    nextWaveTimer->start(1000);

    // set spawning
    enemiesSpawned = 0;
    spawnTimer = new QTimer;
    spawnTimer->start(1000);

    // set enemy number
    maxNumberEnemies = 0;
    remainingEnemies = 0;
}

void Wave::enemyLess()
{
    // decrease the number of enemies
    remainingEnemies--;

    // if game reach final wave
    if (numWave == 30){
        game->gameOver(true);}

    else if (remainingEnemies == 0 && on){
        // Add end wave gold
        int factorGain = numWave/10;
        game->gold->increase(10+5*factorGain);
        game->sounds->goldEndWave();

        // set next time timer
        timeNextWave = 5;
        connect(nextWaveTimer, SIGNAL(timeout()), this, SLOT(waitNextWave()));
        game->sounds->clockStartWave();
        game->nextWave->setValue(timeNextWave);}
}

void Wave::waitNextWave()
{
    // decrement next wave timer and display
    timeNextWave--;
    game->nextWave->decrease();

    // launch the wave
    if (timeNextWave == 0 && on){
        nextWaveTimer->disconnect();
        game->numWave->increase();
        numWave = game->numWave->getValue();
        setEnemy();
        createEnemies(number_);}
}

void Wave::createEnemies(int number){
    enemiesSpawned = 0;
    maxNumberEnemies = number;
    remainingEnemies = number;
    connect(spawnTimer, SIGNAL(timeout()), this, SLOT(spawnEnemy()));
}

int Wave::getTimeNextWave(){
    return timeNextWave;
}

void Wave::start(){
    on = true;
    timeNextWave = 10;
    connect(nextWaveTimer, SIGNAL(timeout()), this, SLOT(waitNextWave()));
}

void Wave::stop(){
    on = false;
    nextWaveTimer->disconnect();
    spawnTimer->disconnect();
}

void Wave::gameOver(){
    stop();
    numWave = 0;
    setEnemy();
    createEnemies(number_);
}

void Wave::spawnEnemy(){
    // create an enemy
    Enemy *enemy = new Enemy(this, road_->getPoints(), enemiesSpawned, velocity_, health_, type_);
    enemiesSpawned ++;

    // special game over case
    if (numWave == 0){
        enemy->hideLifeBar();}

    // add the enemy to the scene
    game->scene->addItem(enemy);

    // all enemies have spawned
    if (enemiesSpawned >= maxNumberEnemies){
        spawnTimer->disconnect();}
}

void Wave::setEnemy()
{
    if (numWave == 0) {
        health_ = 100;
        velocity_ = 3;
        number_ = 1000;
        spawnTimer->setInterval(1000);}

    else if (numWave%10 == 0) {
        if (numWave == 10) {health_ = 5001;}
        if (numWave == 20) {health_ = 15001;}
        if (numWave == 30) {health_ = 30001;}
        velocity_ = 1;
        type_ = 3;
        number_ = 1;}

    else if (numWave%5 == 0) {
        health_ = numWave*150;
        velocity_ = 3;
        type_ = 2;
        number_ = 5;
        spawnTimer->start(2000);}

    else {
        health_ = 100 + numWave*30;
        velocity_ = 3 + ((qreal)numWave-1)/4;
        type_ = 1;
        number_ = 10;
        spawnTimer->setInterval(1000);}
}
