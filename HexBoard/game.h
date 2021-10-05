#ifndef GAME_H
#define GAME_H

#include <QGraphicsView>
#include <QMouseEvent>
#include <QObject>
#include "hexboard.h"

class Game : public QGraphicsView
{
    Q_OBJECT
public:
    // constructors
    Game(QWidget *parent=NULL);

    // public methods
    void displayMenu();
    QString getWhosTurn();
    void setWhosTurn(QString player);
    void pickUpCard(Hex *card);
    void placeCard(Hex *hexToReplace);
    void gameOver();
    void displayGameOverWindow(QString msg);

    // events
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);

    // public attributes
    QGraphicsScene *scene;
    HexBoard *hexboard;
    Hex *cardToPlace;
    QPointF originalPos;

    int width_;
    int height_;

    QString player1;
    QString player2;
    QString playerNone;

    int numCardsPlaced;

public slots:
    void start();
    void restart();

private:
    void drawPanel(int x, int y, int width, int height, QColor color, double opacity);
    void drawGUI();
    void createNewCard(QString player);
    void createInitialCards();
    void drawCards();
    void removeFromDeck(Hex *card, QString player);
    void nextPlayerTurn();

    QString whosTurn_;
    QGraphicsTextItem *whosTurnText;
    QList<Hex*> player1Cards;
    QList<Hex*> player2Cards;
};

#endif // GAME_H
