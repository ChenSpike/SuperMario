#include "normalbrick.h"
#include "score.h"
#include "coin.h"
#include <QPixmap>

QVector<NormalBrick*> NormalBrick::NormalBricks;

NormalBrick::NormalBrick(const QPixmap& pixmap, bool withCoin):
    coinCount(0),
    isNormalBrickWCoin(withCoin),
    isBouncing(false),
    bounceTimer(new QTimer(this)),
    initialY(0)
{
    setPixmap(pixmap); // Set normal brick image
    connect(bounceTimer, &QTimer::timeout, this, &NormalBrick::bounce); // connect bounce timer to bounce
}

void NormalBrick::CreateNormalBricks(QGraphicsScene* scene){
    QPixmap NormalBrickImage(":/new/dataset/dataset/normal brick.png");
    NormalBrick *newNormalBrick;
    // create no-coin normal bricks
    for(int i=0;i<19;i++){
        //Frame 1 Normal Bricks
        if(i==0||i==1){
            newNormalBrick = new NormalBrick(NormalBrickImage);
            newNormalBrick -> setPos((1050+(i*200)),320);
        }
        //Frame 2 Normal Bricks
        if(i==2||i==3){
            newNormalBrick = new NormalBrick(NormalBrickImage);
            newNormalBrick -> setPos((2100+(i*50)),320);
        }
        if(i==4||i==5){
            newNormalBrick = new NormalBrick(NormalBrickImage);
            newNormalBrick -> setPos((2000+(i*50)),150);
        }
        //Frame 3 and 4 Normal Bricks
        if(i>5 && i<14){
            newNormalBrick = new NormalBrick(NormalBrickImage);
            newNormalBrick -> setPos((3700+(i*50)),150);
        }
        if(i==14||i==15||i==16){
            newNormalBrick = new NormalBrick(NormalBrickImage);
            newNormalBrick -> setPos((3850+(i*50)),150);
        }
        //Frame 5 Normal Bricks
        if(i==17||i==18){
            newNormalBrick = new NormalBrick(NormalBrickImage);
            newNormalBrick -> setPos((5150+(i*50)),150);
        }
        scene ->addItem(newNormalBrick);
        NormalBricks.append(newNormalBrick);
    }
    // create coin normal bricks
    for(int i=0;i<3;i++){
        //Frame 1 Normal Bricks
        if(i==19){
            newNormalBrick = new NormalBrick(NormalBrickImage, true);
            newNormalBrick -> setPos(1150,320);
        }
        //Frame 2 Normal Bricks
        if(i==1){
            newNormalBrick = new NormalBrick(NormalBrickImage, true);
            newNormalBrick -> setPos(4700,320);
        }
        if(i==2){
            newNormalBrick = new NormalBrick(NormalBrickImage, true);
            newNormalBrick -> setPos(6050,150);
        }
        scene ->addItem(newNormalBrick);
        NormalBricks.append(newNormalBrick);
    }
}

void NormalBrick::handleCollision(){
    // Check whether the collided normal brick contains coins
    // coins within a normal brick
    if (isNormalBrickWCoin) {
        if (coinCount < 5) {
            coinCount++; // coin count + 1
            Score::getInstance()->increase(); // score + 1
            // create a coin and fly above the brick
            Coin *coin = new Coin();
            coin->setPos(this->x(), this->y() - coin->boundingRect().height());
            scene()->addItem(coin);
            coin->setFly();
            // Brick will bouncing again until it changs into a stone brick.
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
    return;
}

void NormalBrick::setBounce(){
    initialY = y(); // set initial y position
    bounceStep = -10; // bounce upward (-10px)
    isBouncing = true; // set bouncing state
    bounceTimer->start(20); // start bounce timer
    return;
}

void NormalBrick::bounce() {
    // 跳躍步驟為負數，向上跳躍，直到達到一定高度後再改變方向
    setPos(x(), y() + bounceStep);
    if (bounceStep < 0 && y() <= initialY - 30) {
        // 到達一定高度後，改變方向
        bounceStep = 10; // 設置跳躍步驟為正數，向下跳躍
    }
    else if (bounceStep > 0 && y() >= initialY) {
        // stop timer when bouncing back to initial y
        bounceTimer->stop();
        bounceStep = 0;
        setPos(x(), initialY);
        isBouncing = false;
    }
    return;
}
