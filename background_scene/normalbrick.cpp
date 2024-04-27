#include "normalbrick.h"
#include "score.h"
#include <QPixmap>

NormalBrick::NormalBrick(const QPixmap& pixmap, bool withCoin) :
    coinCount(0), isNormalBrickWCoin(withCoin), initialY(0), isBouncing(false){
    // Set normal brick image
    setPixmap(pixmap);
    // connect bounce timer and coin timer
    bounceTimer = new QTimer(this);
    coinTimer = new QTimer(this);
    connect(bounceTimer, &QTimer::timeout, this, &NormalBrick::bounce);
    connect(coinTimer, &QTimer::timeout, this, &NormalBrick::coinFly);
}

void NormalBrick::CreateNormalBricks(QGraphicsScene* scene){
    QPixmap NormalBrickImage(":/new/dataset/dataset/normal brick.png");
    QVector<NormalBrick*> NormalBricks;
    // create no-coin normal bricks at different position
    for(int i=0;i<19;i++){
        //Frame 1 Normal Bricks
        if(i==0||i==1){
            NormalBrick *normalbrick0 = new NormalBrick(NormalBrickImage);
            normalbrick0 -> setPos((1050+(i*200)),320);
            scene ->addItem(normalbrick0);
            NormalBricks.append(normalbrick0);
        }
        //Frame 2 Normal Bricks
        if(i==2||i==3){
            NormalBrick *normalbrick1 = new NormalBrick(NormalBrickImage);
            normalbrick1 -> setPos((2100+(i*50)),320);
            scene ->addItem(normalbrick1);
            NormalBricks.append(normalbrick1);
        }
        if(i==4||i==5){
            NormalBrick *normalbrick2 = new NormalBrick(NormalBrickImage);
            normalbrick2 -> setPos((2000+(i*50)),150);
            scene ->addItem(normalbrick2);
            NormalBricks.append(normalbrick2);
        }
        //Frame 3 and 4 Normal Bricks
        if(i>5&&i<14){
            NormalBrick *normalbrick3 = new NormalBrick(NormalBrickImage);
            normalbrick3 -> setPos((3700+(i*50)),150);
            scene ->addItem(normalbrick3);
            NormalBricks.append(normalbrick3);
        }
        if(i==14||i==15||i==16){
            NormalBrick *normalbrick4 = new NormalBrick(NormalBrickImage);
            normalbrick4 -> setPos((3850+(i*50)),150);
            scene ->addItem(normalbrick4);
            NormalBricks.append(normalbrick4);
        }
        //Frame 5 Normal Bricks
        if(i==17||i==18){
            NormalBrick *normalbrick5 = new NormalBrick(NormalBrickImage);
            normalbrick5 -> setPos((5150+(i*50)),150);
            scene ->addItem(normalbrick5);
            NormalBricks.append(normalbrick5);
        }
        else{
            continue;
        }
    }
    for(int i=0;i<3;i++){
        //Frame 1 Normal Bricks
        if(i==0){
            NormalBrick *normalbrickc0 = new NormalBrick(NormalBrickImage,true);
            normalbrickc0 -> setPos(1150,320);
            scene ->addItem(normalbrickc0);
            NormalBricks.append(normalbrickc0);
        }
        //Frame 2 Normal Bricks
        if(i==1){
            NormalBrick *normalbrickc1 = new NormalBrick(NormalBrickImage,true);
            normalbrickc1 -> setPos(4700,320);
            scene ->addItem(normalbrickc1);
            NormalBricks.append(normalbrickc1);
        }
        if(i==2){
            NormalBrick *normalbrickc2 = new NormalBrick(NormalBrickImage,true);
            normalbrickc2 -> setPos(6050,150);
            scene ->addItem(normalbrickc2);
            NormalBricks.append(normalbrickc2);
        }
        else{
            continue;
        }
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
        if (coin->y() <= this->y() - 100) { // height limit: 100px
            coinTimer->stop();
            scene()->removeItem(coin);
            delete coin;
            coin = nullptr;}
    }

}
