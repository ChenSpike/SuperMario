#include "boxbrick.h"
#include "coin.h"
#include "score.h"
#include <QGraphicsScene>
#include <QPixmap>
#include <QTimer>

BoxBrick::BoxBrick() : isBoxBrick(true){
    // Set the pixmap to box brick image
    setPixmap(QPixmap(":/new/dataset/dataset/box brick.png"));
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
    // Create a coin at the position above the stone brick
    Coin *coin = new Coin();
    scene() -> addItem(coin);
    coin->setPos(this->x(), this->y() - coin->boundingRect().height()); // Set position above the stone brick
    Score::getInstance()->increase();  // Increase the score

    // Start a timer to remove the coin after 0.5 seconds
    QTimer::singleShot(500, coin, SLOT(deleteLater()));
}
