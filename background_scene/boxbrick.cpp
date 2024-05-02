#include "boxbrick.h"
#include "score.h"
#include "coin.h"
#include "fireflower.h"
#include "supermushroom.h"

QVector<BoxBrick*> BoxBrick::BoxBricks;

BoxBrick::BoxBrick(ItemType type, QGraphicsItem *parent):
    QGraphicsPixmapItem(parent),
    itemType(type),
    isBoxBrick(true),
    bounceTimer(new QTimer(this)),
    bounceStep(-10), // bounce upward (-10px)
    initialY(0)
{
    setPixmap(QPixmap(":/new/dataset/dataset/box brick.png")); // Set box brick image
    // create a rectangle of size 50x50
    boxbrickRect = QRect(0, 0, pixmap().width(), pixmap().height());
    setPos(boxbrickRect.center() - QPointF(pixmap().width() / 2, pixmap().height() / 2));

    connect(bounceTimer, &QTimer::timeout, this, &BoxBrick::bounce); // connect bounce timer to bounce
}

void BoxBrick::CreateBoxBricks(QGraphicsScene* scene){
    // create box bricks at different position and store the positions in a vector
    BoxBrick *newBoxBrick;
    for(int i=0;i<8;i++){
        //Frame 1 Box Bricks
        if(i==0){
            newBoxBrick = new BoxBrick(SUPERMUSHROOM);
            //newBoxBrick -> setPos(850, 320);
            newBoxBrick -> setPos(850, 400);
        }
        if(i==1){
            newBoxBrick = new BoxBrick(FIREFLOWER);
            newBoxBrick -> setPos(1100,320);
        }
        //Frame 2 Box Bricks
        if(i==2){
            newBoxBrick = new BoxBrick();
            newBoxBrick -> setPos(2150,320);
        }
        //Frame 3 Box Bricks
        if(i==3){
            newBoxBrick = new BoxBrick();
            newBoxBrick -> setPos(3200,300);
        }
        if(i==4){
            newBoxBrick = new BoxBrick();
            newBoxBrick -> setPos(3900,320);
        }
        //Frame 4 Box Bricks
        if(i==5){
            newBoxBrick = new BoxBrick();
            newBoxBrick -> setPos(4700,150);
        }
        if(i==6){
            newBoxBrick = new BoxBrick();
            newBoxBrick -> setPos(5450,220);
        }
        //Frame 5 Box Bricks
        if(i==7){
            newBoxBrick = new BoxBrick();
            newBoxBrick -> setPos(5800,320);
        }
        scene -> addItem(newBoxBrick);
        BoxBricks.append(newBoxBrick);
    }
    // test for mushroom falling
    // newBoxBrick = new BoxBrick();
    // newBoxBrick -> setPos(950,470);
    // scene -> addItem(newBoxBrick);
    // BoxBricks.append(newBoxBrick);
    return;
}

void BoxBrick::handleCollision(){
    // Change the pixmap to stone brick after collision
    if (isBoxBrick) {
        isBoxBrick = false; // set as stone brick state
        setBounce();
    }
    return;
}

void BoxBrick::setBounce(){
    initialY = y(); // set initial y position
    bounceTimer->start(20); // start bounce timer
}

void BoxBrick::bounce() {
    setPos(x(), y() + bounceStep);
    if (bounceStep < 0 && y() <= initialY - 30) { // bounce height limit 30px
        bounceStep = 10; // change direction after reaching height limit
        setPixmap(QPixmap(":/new/dataset/dataset/stone brick.png"));
        createItem(); // create an item
    }
    else if (bounceStep > 0 && y() >= initialY) {
        // stop timer when bouncing back to initial y
        bounceTimer->stop();
        bounceStep = -10;
        setPos(x(), initialY);
    }
    return;
}

// Create an item above a box brick
void BoxBrick::createItem(){
    switch (itemType) {
    case COIN: {
        Score::getInstance()->increase(); // Increase the score
        // create a coin and the coin will fly
        Coin *coin = new Coin();
        coin->setPos(this->x(), this->y() - coin->boundingRect().height());
        scene() -> addItem(coin);
        coin->setFly();
        break;
    }
    case SUPERMUSHROOM: {
        SuperMushroom *superMushroom = new SuperMushroom();
        qreal bounceStartY = this->y() - superMushroom->boundingRect().height();
        qreal bounceEndY = initialY - superMushroom->boundingRect().height();
        superMushroom->setPos(this->x(), bounceStartY);
        scene()->addItem(superMushroom);
        superMushroom->setBounce(bounceEndY);
        break;
    }
    case FIREFLOWER: {
        FireFlower *fireFlower = new FireFlower();
        qreal bounceStartY = this->y() - fireFlower->boundingRect().height();
        qreal bounceEndY = initialY - fireFlower->boundingRect().height();
        fireFlower->setPos(this->x(), bounceStartY);
        scene()->addItem(fireFlower);
        fireFlower->setBounce(bounceEndY);
        break;
    }
    }
    return;
}
