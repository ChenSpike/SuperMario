#include "boxbrick.h"
#include "coin.h"
#include "score.h"
#include <QGraphicsScene>
#include <QPixmap>
#include <QTimer>

BoxBrick::BoxBrick() : isBoxBrick(true){
    // Set box brick image
    setPixmap(QPixmap(":/new/dataset/dataset/box brick.png"));
    // connect coin timer to coinFly
    coinTimer = new QTimer(this);
    connect(coinTimer, &QTimer::timeout, this, &BoxBrick::coinFly);
}

void BoxBrick::CreateBoxBricks(QGraphicsScene* scene){
    // create box bricks at different position
    QVector<BoxBrick*> vboxBrick;
    int position[] = {8, 15, 35, 65, 70, 90};
    for(int i=0; i<6; i++){
        BoxBrick* newBoxBrick = new BoxBrick();
        newBoxBrick -> setPos(position[i] * 50, 400);
        scene -> addItem(newBoxBrick);
        vboxBrick.append(newBoxBrick);
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
    // Create a coin and increase the score
    coin = new Coin();
    scene() -> addItem(coin);
    coin->setPos(this->x(), this->y() - coin->boundingRect().height()); // Set position above the stone brick
    Score::getInstance()->increase();  // Increase the score

    // Start a timer for the coin to fly up and then disappear
    coinTimer->start(20);
}

void BoxBrick::coinFly(){
    if (coin) {
        coin->setPos(coin->x(), coin->y() - 10); // coin goes up
        if (coin->y() <= this->y() - 100) { // height limit: 100px
            coinTimer->stop();
            scene()->removeItem(coin);
            delete coin;
            coin = nullptr;
        }
    }
}
