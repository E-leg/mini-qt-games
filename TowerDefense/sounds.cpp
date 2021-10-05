#include "sounds.h"
#include <QMediaPlaylist>

Sounds::Sounds()
{
    clickTower_ = new QMediaPlayer;
    clickTower_->setMedia(QUrl("qrc:/snd/Sounds/TowerClick.wav"));
    clickNotAllowed_ = new QMediaPlayer;
    clickNotAllowed_->setMedia(QUrl("qrc:/snd/Sounds/CantClick.wav"));
    buildTower_ = new QMediaPlayer;
    buildTower_->setMedia(QUrl("qrc:/snd/Sounds/BuildTower.wav"));
    buildingTower_ = new QMediaPlayer;
    buildingTower_->setMedia(QUrl("qrc:/snd/Sounds/BuildingTower.wav"));

    goldEndWave_ = new QMediaPlayer;
    goldEndWave_->setMedia(QUrl("qrc:/snd/Sounds/gold.wav"));
    clockStartWave_ = new QMediaPlayer;
    clockStartWave_->setMedia(QUrl("qrc:/snd/Sounds/Clock.wav"));
    lifeLost_ = new QMediaPlayer;
    lifeLost_->setMedia(QUrl("qrc:/snd/Sounds/lifeLost.wav"));

    enemyDie_ = new QMediaPlayer;
    enemyDie_->setMedia(QUrl("qrc:/snd/Sounds/enemyDie.wav"));
    enemyDamaged_ = new QMediaPlayer;
    enemyDamaged_->setMedia(QUrl("qrc:/snd/Sounds/enemyDamaged.wav"));
    towerShot_ = new QMediaPlayer;
    towerShot_->setMedia(QUrl("qrc:/snd/Sounds/TowerShot.wav"));

    QMediaPlaylist *playlist = new QMediaPlaylist();
    playlist->addMedia(QUrl("qrc:/snd/Sounds/Music2.wav"));
    playlist->addMedia(QUrl("qrc:/snd/Sounds/Music1.wav"));
    playlist->setPlaybackMode(QMediaPlaylist::Loop);
    backgroundMusics_ = new QMediaPlayer;
    backgroundMusics_->setPlaylist(playlist);
    gameOverLose_ = new QMediaPlayer;
    gameOverLose_->setMedia(QUrl("qrc:/snd/Sounds/Music3.wav"));
    gameOverWin_ = new QMediaPlayer;
    gameOverWin_->setMedia(QUrl("qrc:/snd/Sounds/Music4.wav"));
}

void Sounds::play(QMediaPlayer *sound)
{
    if (sound->state() == QMediaPlayer::PlayingState){
        sound->setPosition(0);
    }
    else if (sound->state() == QMediaPlayer::StoppedState){
        sound->play();
    }
}

void Sounds::clickTower()
{
    return play(clickTower_);
}

void Sounds::clickNotAllowed()
{
    return play(clickNotAllowed_);
}

void Sounds::buildTower()
{
    return play(buildTower_);
}

void Sounds::buildingTower()
{
    return play(buildingTower_);
}

void Sounds::goldEndWave()
{
    return play(goldEndWave_);
}

void Sounds::clockStartWave()
{
    return play(clockStartWave_);
}

void Sounds::lifeLost()
{
    return play(lifeLost_);
}

void Sounds::enemyDie()
{
    return play(enemyDie_);
}

void Sounds::enemyDamaged()
{
    return play(enemyDamaged_);
}

void Sounds::towerShot()
{
    return play(towerShot_);
}

void Sounds::backgroundMusics()
{
    return play(backgroundMusics_);
}

void Sounds::gameOverLose()
{
    backgroundMusics_->stop();
    return play(gameOverLose_);
}

void Sounds::gameOverWin()
{
    backgroundMusics_->stop();
    return play(gameOverWin_);
}

