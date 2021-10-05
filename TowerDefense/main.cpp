#include "game.h"
#include <QApplication>
#include <QIcon>

// Global game
Game *game;

// Constants
    // Global
int TIMER = 20; // ms
    // Towers
        // Index
int IDX_DEMON = 1;
int IDX_EYE = 2;
int IDX_SWORD = 3;
        // Damage
int DMG_DEMON = 70;
int DMG_EYE = 50;
int DMG_SWORD = 400;
        // Range
int RNG_DEMON = 280;
int RNG_EYE = 400;
int RNG_SWORD = 240;
        // Attack time
int ATM_DEMON = TIMER * 30;
int ATM_EYE = TIMER * 20;
int ATM_SWORD = TIMER * 50;
        // Bullet speed
int BSP_DEMON = 30;
int BSP_EYE = 40;
int BSP_SWORD = 30;
        // Cost
int CST_DEMON = 40;
int CST_EYE = 60;
int CST_SWORD = 90;
        // Image path
QString IMG_DEMON = ":/img/Images/tower1.png";
QString IMG_EYE = ":/img/Images/tower2.png";
QString IMG_SWORD = ":/img/Images/tower3.png";
    // Enemies
int SPD_ENEMY = 3;


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    a.setApplicationDisplayName("Monster Defense");
    a.setApplicationName("Monster Defense");
    a.setWindowIcon(QIcon(":/img/Images/icon1.ico"));

    game = new Game();
    game->show();
    game->start();

    return a.exec();
}
