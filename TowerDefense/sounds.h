#ifndef SOUNDS_H
#define SOUNDS_H

#include <QMediaPlayer>

class Sounds
{
public:
    Sounds();
    void play(QMediaPlayer *sound);

    void clickTower();
    void clickNotAllowed();
    void buildTower();
    void buildingTower();

    void goldEndWave();
    void clockStartWave();
    void lifeLost();

    void enemyDie();
    void enemyDamaged();
    void towerShot();

    void backgroundMusics();
    void gameOverLose();
    void gameOverWin();


protected:
    QMediaPlayer *clickTower_;
    QMediaPlayer *clickNotAllowed_;
    QMediaPlayer *buildTower_;
    QMediaPlayer *buildingTower_;

    QMediaPlayer *goldEndWave_;
    QMediaPlayer *clockStartWave_;
    QMediaPlayer *lifeLost_;

    QMediaPlayer *enemyDie_;
    QMediaPlayer *enemyDamaged_;
    QMediaPlayer *towerShot_;

    QMediaPlayer *backgroundMusics_;
    QMediaPlayer *gameOverLose_;
    QMediaPlayer *gameOverWin_;
};

#endif // SOUNDS_H
