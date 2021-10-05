#include "button.h"
#include "game.h"
#include "hex.h"
#include <stdlib.h>
#include <time.h>
#include <QDebug>


Game::Game(QWidget *parent): QGraphicsView(parent)
{
    // set up the screen
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    width_ = 1024;
    height_ = 768;
    setFixedSize(width_,height_);

    // set up the scene
    scene = new QGraphicsScene;
    scene->setSceneRect(0,0,width_,height_);
    setScene(scene);

    // initialize parameters
    player1 = QString("Player1");
    player2 = QString("Player2");
    playerNone = QString("None");
    whosTurn_ = player1;
    cardToPlace = NULL;
    numCardsPlaced = 0;
}

void Game::start() {
    // clear the scene
    scene->clear();

    // init parameters
    whosTurn_ = player1;
    cardToPlace = NULL;
    numCardsPlaced = 0;

    // test code TODO remove
    hexboard = new HexBoard;
    hexboard->placeHexes(200, 30, 7, 7);

    // draw GUI
    drawGUI();

    // create initial cards
    createInitialCards();
}

void Game::restart(){
    // clear stuff and call start
    player1Cards.clear();
    player2Cards.clear();
    hexboard->getHexes().clear();
    scene->clear();
    start();
}

void Game::drawPanel(int x, int y, int width, int height, QColor color, double opacity) {
    // draw a panel
    QGraphicsRectItem *panel = new QGraphicsRectItem(x,y,width,height);
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(color);
    panel->setBrush(brush);
    panel->setOpacity(opacity);
    scene->addItem(panel);
}

void Game::drawGUI() {
    // draw the left panel
    drawPanel(0,0,150,height_,Qt::darkCyan, 1);

    // draw the right panel
    drawPanel(874,0,150,height_,Qt::darkCyan, 1);

    // place player 1 text
    QGraphicsTextItem *p1 = new QGraphicsTextItem("Player 1's Cards: ");
    p1->setPos(25,0);
    scene->addItem(p1);

    // place player 2 text
    QGraphicsTextItem *p2 = new QGraphicsTextItem("Player 2's Cards: ");
    p2->setPos(874+25,0);
    scene->addItem(p2);

    // place turn text
    whosTurnText = new QGraphicsTextItem;
    setWhosTurn(QString("Player1"));
    whosTurnText->setPos(460,0);
    scene->addItem(whosTurnText);
}

void Game::createNewCard(QString player) {
    // create the card
    Hex *card = new Hex();
    card->setOwner(player);

    // randomize side attacks
    for (int i=0; i<6; i++){
        int randNum = rand() % 6 + 1;
        card->setAttackOf(i, randNum);
    }

    // display side attacks
    card->displaySideAttacks();

    // add it to the proper player list
    if (player == player1){
        player1Cards.append(card);
    }
    else {
        player2Cards.append(card);
    }

    // draw the cards
    drawCards();
}

void Game::createInitialCards() {
    // create player cards
    for (int i=0; i<5; i++){
        createNewCard(player1);
        createNewCard(player2);
    }

    // draw the cards
    drawCards();
}

void Game::drawCards() {
    // remove all of player 1's cards from the scene
    for (int i=0; i<player1Cards.size(); i++) {
        scene->removeItem(player1Cards[i]);}

    // remove all of player 2's cards from the scene
    for (int i=0; i<player2Cards.size(); i++) {
        scene->removeItem(player2Cards[i]);}

    // draw player1's cards
    for (int i=0; i<player1Cards.size(); i++){
        Hex *card = player1Cards[i];
        card->setPos(13,25+85*i);
        scene->addItem(card);}

    // draw player2's cards
    for (int i=0; i<player2Cards.size(); i++){
        Hex *card = player2Cards[i];
        card->setPos(874+13,25+85*i);
        scene->addItem(card);}
}

void Game::removeFromDeck(Hex *card, QString player){
    if (player == player1){
        player1Cards.removeAll(card);}

    else {
        player2Cards.removeAll(card);}
}

void Game::nextPlayerTurn(){
    if (whosTurn_ == player1){
        setWhosTurn(player2);}

    else {
        setWhosTurn(player1);}
}

void Game::displayMenu() {
    // create the title
    QGraphicsTextItem *title = new QGraphicsTextItem(QString("Hex Warz"));
    QFont titleFont("comic sans", 50);
    title->setFont(titleFont);
    int titleXPos = width_/2 - title->boundingRect().width()/2;
    int titleYPos = height_/2 - title->boundingRect().width()/2;
    title->setPos(titleXPos, titleYPos);

    // create the play button
    Button *playButton = new Button(QString("Play"));
    int playXPos = width_/2 - playButton->boundingRect().width()/2;
    int playYPos = 350;
    playButton->setPos(playXPos, playYPos);
    connect(playButton, SIGNAL(clicked()), this, SLOT(start()));

    // create the quit button
    Button *quitButton = new Button(QString("Quit"));
    int quitXPos = width_/2 - quitButton->boundingRect().width()/2;
    int quitYPos = 450;
    quitButton->setPos(quitXPos, quitYPos);
    connect(quitButton, SIGNAL(clicked()), this, SLOT(close()));

    // add them to the scene
    scene->addItem(title);
    scene->addItem(playButton);
    scene->addItem(quitButton);
}

QString Game::getWhosTurn()
{
    return whosTurn_;
}

void Game::setWhosTurn(QString player){
    // change the QString
    whosTurn_ = player;

    // change the QGraphicsTextItem
    whosTurnText->setPlainText(QString("Turn: ")+player);
}

void Game::pickUpCard(Hex *card){
    // picks up the specified card
    qDebug() << whosTurn_ << cardToPlace << card->getOwner();
    if (card->getOwner() == whosTurn_ && cardToPlace == NULL){
        cardToPlace = card;
        originalPos = card->pos();}
}

void Game::placeCard(Hex *hexToReplace){
    // replaces the specified hex with the cardToPlace //

    // set the cardToPlace
    cardToPlace->setPos(hexToReplace->pos());
    hexboard->getHexes().append(cardToPlace);
    removeFromDeck(cardToPlace, whosTurn_);
    cardToPlace->setPLaced(true);

    // remove the previous hex
    hexboard->getHexes().removeAll(hexToReplace);
    scene->removeItem(hexToReplace);

    // replace the placed card with a new one
    createNewCard(whosTurn_);

    // find neighbors
    cardToPlace->fightNeighbords();

    // reinitialize cardToPlace
    cardToPlace = NULL;

    // switch turn
    nextPlayerTurn();

    // increase the number of cards places
    numCardsPlaced++;
    if (numCardsPlaced >= hexboard->getHexes().size()){
        gameOver();}
}

void Game::gameOver(){
    // count who as more hexes placed
    int p1hexes(0);
    int p2hexes(0);
    int boardSize = hexboard->getHexes().size();
    for (int i(0); i<boardSize; i++){
        if (hexboard->getHexes()[i]->getOwner() == player1){
            p1hexes++;}
        else {
            p2hexes++;}
    }

    QString message;
    if (p1hexes > p2hexes){
        message = "Player 1 has won!";}

    else if (p2hexes > p1hexes){
        message = "Player 2 has won!";}

    else {
        message = "Tie game!";}

    displayGameOverWindow(message);

}

void Game::displayGameOverWindow(QString msg){
    // disable all scene items
    for (int i(0); i<scene->items().size(); i++){
        scene->items()[i]->setEnabled(false);}

    // pop up semi-transparent window
    drawPanel(0,0,width_,height_,Qt::black,0.65);

    // draw panel
    drawPanel(312,184,400,400,Qt::lightGray,0.95);

    // create playAgain button
    Button *playAgain = new Button(QString("Play Again"));
    playAgain->setPos(410,300);
    scene->addItem(playAgain);
    connect(playAgain, SIGNAL(clicked()), this, SLOT(restart()));

    // create quit button
    Button *quit = new Button(QString("Quit"));
    quit->setPos(410,375);
    scene->addItem(quit);
    connect(quit, SIGNAL(clicked()), this, SLOT(close()));

    // display text
    QGraphicsTextItem *text = new QGraphicsTextItem(msg);
    text->setPos(440,225);
    scene->addItem(text);
}

void Game::mouseMoveEvent(QMouseEvent *event){
    // if there is a card to place, then make it follow the mouse
    if (cardToPlace){
        cardToPlace->setPos(event->x(), event->y());}

    QGraphicsView::mousePressEvent(event);
}

void Game::mousePressEvent(QMouseEvent *event)
{
    // make right click return cardToPlace to originalPos
    if (cardToPlace && event->button() == Qt::RightButton){
        cardToPlace->setPos(originalPos);
        cardToPlace = NULL;
        return;}
    QGraphicsView::mousePressEvent(event);
}
