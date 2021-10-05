#include <QApplication>
#include <QIcon>
#include "game.h"

Game * game;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    a.setApplicationDisplayName("Plane Game");
    a.setWindowIcon(QIcon(":/img/images/icon1.png"));

    game = new Game();

    return a.exec();
}
