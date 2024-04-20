#include "player.h"
#include "boxbrick.h"
#include <QGraphicsScene>
#include <QKeyEvent>


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
    // 更新位置
    setPos(x(), y() + velocity);
    jumpTimer->start(20);
    velocity += 1; // 模拟重力影响

    // get the item collided with the player
    QList<QGraphicsItem* > colliding_items = collidingItems();
    for (int i=0; i < colliding_items.size(); i++){

        // check whether the player collided with BoxBrick
        if(typeid(*(colliding_items[i])) == typeid(BoxBrick)){
            BoxBrick *brick = dynamic_cast<BoxBrick *>(colliding_items[i]);
            QRectF brickRect = brick->boundingRect();

            // check if hit from the bottom
            if(velocity < 0 && y() + pixmap().height() > brick->y() + brickRect.height()){
                velocity = 0;
                setPos(x(), y());
                isJumping = false;
                jumpTimer->stop();
                emit collidedWithBoxBrick(); // emit collision signal

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
            if (velocity > 0 && y() + pixmap().height() < brick->y() + brick->pixmap().height()) {
                setPos(x(), brick->y() - pixmap().height());
                velocity = 0;
                isJumping = false;
                jumpTimer->stop();
                break;
            }

            // Check for side collisions
            if (x() < brick->x() + brick->pixmap().width() && x() + pixmap().width() > brick->x()) {
                if (x() < brick->x()) {
                    setPos(brick->x() - pixmap().width(), y());
                }
                else {
                    setPos(brick->x() + brick->pixmap().width(), y());
                }
            }
        }
    }

    // 检查是否完成跳跃（是否回到了初始高度或更低）
    if (pos().y() > 450) {
        jumpTimer->stop();
        setPos(x(), 450); // 重置到地面
        isJumping = false; // 结束跳跃
        velocity = 0; // 重置速度
    }
}


