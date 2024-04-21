#include "boxbrick.h"
#include "coin.h"
#include <QGraphicsScene>
#include <QPixmap>
#include <QTimer>

BoxBrick::BoxBrick() : isBoxBrick(true), m_signalConnected(false){
    // Set the pixmap to box brick image
    QPixmap pixmap(":/new/dataset/dataset/box brick.png");
    setPixmap(pixmap);

    // connect to collision handling function
    connect(this, SIGNAL(collided()), this, SLOT(handleCollision()));
}

/*
BoxBrick::BoxBrick(QGraphicsScene *scene) : scene(scene), isBoxBrick(true){
    // Set the pixmap to box brick image
    QPixmap pixmap(":/new/dataset/dataset/box brick.png");
    setPixmap(pixmap);

    // connect to collision handling funciton
    connect(this, SIGNAL(collided()), this, SLOT(handleCollision()));
}*/

BoxBrick::BoxBrick(const QPixmap& pixmap){
    setPixmap(pixmap);
}

void BoxBrick::CreateBoxBricks(QGraphicsScene *scene){
    //QPixmap BoxBrickImage(":/new/dataset/dataset/box brick.png");
    for (int i = 0; i < 140;i++){
        if (i == 8||i==15||i==35||i==65||i==70||i==90){
            //BoxBrick *boxbrick = new BoxBrick(BoxBrickImage);
            BoxBrick *boxbrick = new BoxBrick();
            boxbrick -> setPos(i*50, 400);
            scene -> addItem(boxbrick);
        }
        continue;
    }
}

void BoxBrick::handleCollision(){
    // Change the pixmap to stone brick after collision
    if (isBoxBrick && !isSignalConnected()) {
        QPixmap pixmap(":/new/dataset/dataset/stone brick.png");
        setPixmap(pixmap);
        isBoxBrick = false; // set as stone brick state
        createCoin(); // create a coin

    }
}

void BoxBrick::createCoin(){
    // Create a coin at the position above the stone brick
    Coin *coin = new Coin();
    scene() -> addItem(coin);
    coin->setPos(this->x(), this->y() - coin->boundingRect().height()); // Set position above the stone brick

    // Start a timer to remove the coin after 0.5 seconds
    QTimer::singleShot(500, coin, SLOT(deleteLater()));
}

bool BoxBrick::isSignalConnected() const {
    return m_signalConnected;
}

void BoxBrick::setSignalConnected(bool connected) {
    m_signalConnected = connected;
}
