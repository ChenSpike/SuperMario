#include "normalbrick.h"
#include "score.h"
#include <QPixmap>

NormalBrick::NormalBrick(bool withCoin) :
    coinCount(0), isNormalBrickWCoin(withCoin), initialY(0), isBouncing(false){
    setPixmap(QPixmap(":/new/dataset/dataset/normal brick.png"));
    bounceTimer = new QTimer(this);
    coinTimer = new QTimer(this);
    connect(bounceTimer, &QTimer::timeout, this, &NormalBrick::bounce);
    connect(coinTimer, &QTimer::timeout, this, &NormalBrick::coinFly);
}

void NormalBrick::CreateNormalBricks(QGraphicsScene* scene){
    QVector<NormalBrick*> vNormalBrick;
    int position[] = {10, 11}; // create normal bricks at different position
    for(int i=0; i<2; i++){
        NormalBrick* noCoinNormalBrick = new NormalBrick();
        noCoinNormalBrick -> setPos(position[i] * 50, 400);
        scene -> addItem(noCoinNormalBrick);
        vNormalBrick.append(noCoinNormalBrick);
    }
    position[0] = 13;
    position[1] = 14;// create normal bricks at different position
    for(int i=0; i<2; i++){
        NormalBrick* coinNormalBrick = new NormalBrick(true);
        coinNormalBrick -> setPos(position[i] * 50, 400);
        scene -> addItem(coinNormalBrick);
        vNormalBrick.append(coinNormalBrick);
    }
}

void NormalBrick::handleCollision(){
    // Check whether the collided normal brick contains coins
    // coins within a normal brick
    if (isNormalBrickWCoin) {
        if (coinCount < 5) {
            // Increase coin count and score
            coinCount++;
            Score::getInstance()->increase();

            // create a coin
            coin = new Coin();
            scene()->addItem(coin);
            coin->setPos(this->x(), this->y() - coin->boundingRect().height()); // Set position above the brick
            coinTimer->start(20); // Start a timer for the coin to fly up and then disappear

            // Brick will keep bouncing until it changs into a stone brick.
            if(coinCount == 5)
                setPixmap(QPixmap(":/new/dataset/dataset/stone brick.png"));
            else{
                if(!isBouncing) setBounce();
            }
        }
    }
    // no coin within a normal brick
    else {
        if(!isBouncing) setBounce();
    }
}

void NormalBrick::setBounce(){
    initialY = y(); // set initial y position
    bounceStep = -10; // bounce upward (-10px)
    isBouncing = true; // set bouncing state
    bounceTimer->start(20); // start bounce timer
}

void NormalBrick::bounce() {
    // 跳躍步驟為負數，向上跳躍，直到達到一定高度後再改變方向
    setPos(x(), y() + bounceStep);
    if (bounceStep < 0 && y() <= initialY - 30) {
        // 到達一定高度後，改變方向
        bounceStep = 10; // 設置跳躍步驟為正數，向下跳躍
    } else if (bounceStep > 0 && y() >= initialY) {
        // stop timer when bouncing back to initial y
        bounceTimer->stop();
        bounceStep = 0;
        setPos(x(), initialY);
        isBouncing = false;
    }
}


void NormalBrick::coinFly(){
    if (coin) {
        coin->setPos(coin->x(), coin->y() - 10); // coin goes up
        if (coin->y() <= initialY - 100) { // height limit: 100px
            coinTimer->stop();
            scene()->removeItem(coin);
            delete coin;
            coin = nullptr;
        }
    }
}
