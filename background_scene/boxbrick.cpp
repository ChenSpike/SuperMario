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
    // create box bricks at different position and store the positions in a vector
    QVector <BoxBrick*> BoxBricks;
    for(int i=0; i<8; i++){
        //Frame 1 Box Bricks
        if(i==0){
            BoxBrick *boxBrick0 = new BoxBrick();
            boxBrick0 -> setPos(850, 320);
            scene -> addItem(boxBrick0);
            BoxBricks.append(boxBrick0);
        }
        if(i==1){
            BoxBrick *boxBrick1 = new BoxBrick();
            boxBrick1 -> setPos(1100,320);
            scene -> addItem(boxBrick1);
            BoxBricks.append(boxBrick1);
        }
        //Frame 2 Box Brick
        if(i==2){
            BoxBrick *boxBrick2 = new BoxBrick();
            boxBrick2 -> setPos(2150,320);
            scene -> addItem(boxBrick2);
            BoxBricks.append(boxBrick2);
        }
        //Frame 3 Box Bricks
        if(i==3){
            BoxBrick *boxBrick3 = new BoxBrick();
            boxBrick3 -> setPos(3200,300);
            scene -> addItem(boxBrick3);
            BoxBricks.append(boxBrick3);
        }
        if(i==4){
            BoxBrick *boxBrick4 = new BoxBrick();
            boxBrick4 -> setPos(3900,320);
            scene -> addItem(boxBrick4);
            BoxBricks.append(boxBrick4);
        }
        //Frame 4 Box Bricks
        if(i==5){
            BoxBrick *boxBrick5 = new BoxBrick();
            boxBrick5 -> setPos(4700,150);
            scene -> addItem(boxBrick5);
            BoxBricks.append(boxBrick5);
        }
        if(i==6){
            BoxBrick *boxBrick6 = new BoxBrick();
            boxBrick6 -> setPos(5450,220);
            scene -> addItem(boxBrick6);
            BoxBricks.append(boxBrick6);
        }
        //Frame 5 Box Brick
        if(i==7){
            BoxBrick *boxBrick7 = new BoxBrick();
            boxBrick7 -> setPos(5800,320);
            scene -> addItem(boxBrick7);
            BoxBricks.append(boxBrick7);
        }
        else{
            continue;
        }
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
