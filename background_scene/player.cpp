#include "player.h"
#include "boxbrick.h"
#include "brokenbrick.h"
#include "coin.h"
#include "score.h"
#include <QGraphicsScene>
#include <QKeyEvent>
#include <QList>

//extern Score * score;

Player::Player(QGraphicsItem *parent): QGraphicsPixmapItem(parent){

    // set graphic
    setPixmap(QPixmap(":/new/dataset/dataset/s_mario_run1_R.png"));
    jumpTimer = new QTimer(this);
    connect(jumpTimer, &QTimer::timeout, this, &Player::jumpStep);
    velocity = 0; // 初始速度
}

void Player::keyPressEvent(QKeyEvent *event){
    if (event->key() == Qt::Key_Left){
        setPixmap(QPixmap(":/new/dataset/dataset/s_mario_run1_L.png"));
        setPos(x()-25, y());
        if (!isJumping) {
            jumpStep();  // Trigger gravity check after movement
        }
    }
    else if (event->key() == Qt::Key_Right){
        setPixmap(QPixmap(":/new/dataset/dataset/s_mario_run1_R.png"));
        setPos(x()+25, y());
        if (!isJumping) {
            jumpStep();  // Trigger gravity check after movement
        }
    }
    else if (event->key() == Qt::Key_Space && !isJumping) {
        isJumping = true;
        velocity = -15;  // Adjust the initial jump velocity as needed
        jumpTimer->start(20);
    }

}

void Player::jumpStep() {
    setPos(x(), y() + velocity);
    jumpTimer->start(20);
    velocity += 1; // 模拟重力影响

    // get the item collided with the player
    QList<QGraphicsItem* > colliding_items = collidingItems();
    for (int i=0; i < colliding_items.size(); i++){

        // check whether the player collided with BoxBrick
        if(typeid(*(colliding_items[i])) == typeid(BoxBrick)){
            BoxBrick *boxbrick = dynamic_cast<BoxBrick *>(colliding_items[i]);

            // check if hit from the bottom
            if(velocity < 0 && pos().y() + pixmap().height() > boxbrick->y() + boxbrick->pixmap().height()){
                // stop the jumpTimer and set the starting point for falling down
                velocity = 0;
                setPos(x(), y());
                isJumping = false;
                jumpTimer->stop();

                boxbrick->handleCollision(); // change to the block brick

                // mario fall to ground
                QTimer *fallTimer = new QTimer(this);
                // lambda 函数由 timeout 信號每 20 毫秒觸發，因為 start(20) 決定 timeout 的時間間隔為 20 毫秒
                connect(fallTimer, &QTimer::timeout, [=]() {
                    velocity += 1;
                    if (y() <= 450) { // 检查是否达到地面
                        setPos(x(), y() + velocity); // gradually drop to the ground
                    }
                    else {
                        velocity = 0;
                        fallTimer->stop(); // 停止落地动画
                        delete fallTimer;
                    }
                });
                fallTimer->start(20); // 每 20 毫秒更新位置
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
        
        // check whether the player collided with BrokenBrick
        if (typeid(*(colliding_items[i])) == typeid(BrokenBrick)) {
            BrokenBrick *brokenbrick = dynamic_cast<BrokenBrick *>(colliding_items[i]);

            // Check if hit from the bottom
            if (velocity < 0 && y() > brokenbrick->y()) {
                brokenbrick->breakBrick();
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
                } else {
                    setPos(brokenbrick->x() + brokenbrick->pixmap().width(), y());
                }
            }            
        }

        // collided with coin
        if (typeid(*(colliding_items[i])) == typeid(Coin)) {
            Coin *coin = dynamic_cast<Coin*>(colliding_items[i]);
            scene()->removeItem(coin); // 移除coin
            delete coin; // 释放内存
            //score->increase();
            emit increaseScore(); // Emit a signal to score.cpp: score + 1
        }
    }

    // 检查是否完成跳跃（是否回到了初始高度或更低）
    if (y() > 450) {
        jumpTimer->stop();
        setPos(x(), 450); // 重置到地面
        isJumping = false; // 结束跳跃
        velocity = 0; // 重置速度            
    }
}


