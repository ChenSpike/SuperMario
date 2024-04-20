#include "boxbrick.h"
#include "coin.h"
#include <QPixmap>
#include <QTimer>

BoxBrick::BoxBrick(QGraphicsScene *scene) : scene(scene), isBoxBrick(true){
    // Set the pixmap to box brick image
    QPixmap pixmap(":/new/dataset/dataset/box brick.png");
    setPixmap(pixmap);

    // connect to collision handling funciton
    connect(this, SIGNAL(collided()), this, SLOT(handleCollision()));
}

void BoxBrick::handleCollision(){
    // Change the pixmap to stone brick after collision
    if (isBoxBrick) {
        QPixmap pixmap(":/new/dataset/dataset/stone brick.png");
        setPixmap(pixmap);
        isBoxBrick = false; // set as stone brick state
        createCoin(); // create a coin
    }
}

void BoxBrick::createCoin(){
    // Create a coin at the position above the stone brick
    Coin *coin = new Coin();
    scene->addItem(coin);
    coin->setPos(this->x(), this->y() - coin->boundingRect().height()); // Set position above the stone brick

    // Start a timer to remove the coin after 0.5 seconds
    QTimer::singleShot(500, coin, SLOT(deleteLater()));
}
