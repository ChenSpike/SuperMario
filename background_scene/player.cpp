#include "player.h"
#include "boxbrick.h"
#include "brokenbrick.h"
#include "normalbrick.h"
#include "coin.h"
#include "score.h"
#include "supermushroom.h"
#include <QGraphicsScene>
#include <QKeyEvent>
#include <QList>

Player::Player(QGraphicsItem *parent):
    QGraphicsPixmapItem(parent),
    jumpTimer(new QTimer(this)),
    velocity(0), // initial velocity
    maxHeight(100), // maximum jumping height
    isJumping(false),
    isBig(false)
{
    setPixmap(QPixmap(":/new/dataset/dataset/s_mario_run1_R.png")); // set initial mario pose
    connect(jumpTimer, &QTimer::timeout, this, &Player::jumpStep);
}

void Player::grow() {
    if (!isBig) {
        setPixmap(QPixmap(":/new/dataset/dataset/mario_R_run1.png"));
        isBig = true;
    }
    return;
}

void Player::keyPressEvent(QKeyEvent *event){
    if (event->key() == Qt::Key_Left){
        if(isBig)
            setPixmap(QPixmap(":/new/dataset/dataset/mario_L_run1.png"));
        else
            setPixmap(QPixmap(":/new/dataset/dataset/s_mario_run1_L.png"));
        setPos(x()-25, y());
        if (!isJumping) {
            jumpStep();  // Trigger gravity check after movement
        }
    }
    else if (event->key() == Qt::Key_Right){
        if(isBig)
            setPixmap(QPixmap(":/new/dataset/dataset/mario_R_run1.png"));
        else
            setPixmap(QPixmap(":/new/dataset/dataset/s_mario_run1_R.png"));
        setPos(x()+25, y());
        if (!isJumping) {
            jumpStep();  // Trigger gravity check after movement
        }
    }
    else if (event->key() == Qt::Key_Space && !isJumping) {
        if(isBig)
            velocity = -20;  // initial jump velocity = -20px
        else
            velocity = -15;  // initial jump velocity = -15px
        isJumping = true;
        jumpTimer->start(20);
    }
    return;
}

void Player::jumpStep() {
    setPos(x(), y() + velocity);
    jumpTimer->start(20);
    velocity += 1; // 模拟重力影响

    // get the item collided with the player
    QList<QGraphicsItem* > colliding_items = collidingItems();
    for (int i=0; i < colliding_items.size(); i++){

        // collided with BoxBrick
        if(typeid(*(colliding_items[i])) == typeid(BoxBrick)){
            BoxBrick *boxbrick = dynamic_cast<BoxBrick *>(colliding_items[i]);

            qreal buttomBrick = boxbrick->y() + boxbrick->pixmap().height();
            // check if hit from the bottom
            if(velocity < 0 && y() > boxbrick->y()){
                // stop jumping and start to fall down
                velocity = 0;
                setPos(x(), buttomBrick);
                jumpTimer->stop(); // stop jumping
                boxbrick->handleCollision(); // change to the block brick
                jumpStep(); // start to fall
                break;
            }

            // Check if landing on top of the brick
            if (velocity > 0 && pos().y() + pixmap().height() < boxbrick->y() + boxbrick->pixmap().height()) {
                setPos(x(), boxbrick->y() - pixmap().height());
                velocity = 0;
                isJumping = false;
                jumpTimer->stop();
                break;
            }

            // Check for side collisions
            if (x() < boxbrick->x() + boxbrick->pixmap().width() && x() + pixmap().width() > boxbrick->x()) {
                if (x() < boxbrick->x()) {
                    setPos(boxbrick->x() - pixmap().width(), y());
                }
                else {
                    setPos(boxbrick->x() + boxbrick->pixmap().width(), y());
                }
            }
        }
        
        // collided with BrokenBrick
        if (typeid(*(colliding_items[i])) == typeid(BrokenBrick)) {
            BrokenBrick *brokenbrick = dynamic_cast<BrokenBrick *>(colliding_items[i]);

            qreal buttomBrick = brokenbrick->y() + brokenbrick->pixmap().height();
            // Check if hit from the bottom
            if (velocity < 0 && y() > brokenbrick->y()) {
                // stop jumping and start to fall down
                velocity = 0;
                setPos(x(), buttomBrick);
                jumpTimer->stop(); // stop jumping
                brokenbrick->breakBrick(); // broken brick disappear
                jumpStep(); // start to fall
                break;
            }

            if (velocity > 0 && y() + pixmap().height() < brokenbrick->y() + brokenbrick->pixmap().height()) {
                setPos(x(), brokenbrick->y() - pixmap().height());
                velocity = 0;
                isJumping = false;
                jumpTimer->stop();
                break;
            }

            if (x() < brokenbrick->x() + brokenbrick->pixmap().width() && x() + pixmap().width() > brokenbrick->x()) {
                if (x() < brokenbrick->x()) {
                    setPos(brokenbrick->x() - pixmap().width(), y());
                }
                else {
                    setPos(brokenbrick->x() + brokenbrick->pixmap().width(), y());
                }
            }
        }

        // collided with NormalBrick
        if(typeid(*(colliding_items[i])) == typeid(NormalBrick)){
            NormalBrick *normalbrick = dynamic_cast<NormalBrick *>(colliding_items[i]);

            qreal buttomBrick = normalbrick->y() + normalbrick->pixmap().height();
            // check if hit from the bottom
            if(velocity < 0 && y() > normalbrick->y()){
                // stop jumping and start to fall down
                velocity = 0;
                setPos(x(), buttomBrick);
                jumpTimer->stop(); // stop jumping
                normalbrick->handleCollision(); // change to the block brick
                jumpStep(); // start to fall
                break;
            }

            // Check if landing on top of the brick
            if (velocity > 0 && pos().y() + pixmap().height() < normalbrick->y() + normalbrick->pixmap().height()) {
                setPos(x(), normalbrick->y() - pixmap().height());
                velocity = 0;
                isJumping = false;
                jumpTimer->stop();
                break;
            }

            // Check for side collisions
            if (x() < normalbrick->x() + normalbrick->pixmap().width() && x() + pixmap().width() > normalbrick->x()) {
                if (x() < normalbrick->x()) {
                    setPos(normalbrick->x() - pixmap().width(), y());
                }
                else {
                    setPos(normalbrick->x() + normalbrick->pixmap().width(), y());
                }
            }
        }

        // collided with Coin
        if (typeid(*(colliding_items[i])) == typeid(Coin)) {
            Coin *coin = dynamic_cast<Coin*>(colliding_items[i]);
            scene()->removeItem(coin); // delete the coin
            delete coin; // release memory
            Score::getInstance()->increase(); // score + 1
        }

        // collided with Super Mushroom
        if(typeid(*(colliding_items[i])) == typeid(SuperMushroom)) {
            grow();
        }
    }

    // 检查是否完成跳跃（是否回到了初始高度或更低）
    if (pos().y() > 470) {
        jumpTimer->stop();
        setPos(x(), 470); // 重置到地面
        isJumping = false; // 结束跳跃
        velocity = 0; // 重置速度
    }
    return;
}


