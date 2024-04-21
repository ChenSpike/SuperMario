#include "boxbrick.h"
#include "coin.h"
#include <QGraphicsScene>
#include <QPixmap>
#include <QTimer>

BoxBrick::BoxBrick() : isBoxBrick(true){
    // Set the pixmap to box brick image
    setPixmap(QPixmap(":/new/dataset/dataset/box brick.png"));
}

void BoxBrick::CreateBoxBricks(QGraphicsScene* scene){
    // create box bricks at different position
    int c=0;
    for(int i=0; i<6; i++){
        if(i==0) c=8;
        if(i==1) c=15;
        if(i==2) c=35;
        if(i==3) c=65;
        if(i==4) c=70;
        if(i==5) c=90;
        BoxBrick *boxBrick = new BoxBrick();
        boxBrick -> setPos(c*50, 400);
        scene -> addItem(boxBrick);
    }
}

void BoxBrick::handleCollision(){
    // Change the pixmap to stone brick after collision
    if (isBoxBrick) {
        setPixmap(QPixmap(":/new/dataset/dataset/stone brick.png"));
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
