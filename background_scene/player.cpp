#include "player.h"
#include "brokenbrick.h"
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
    // move the player left and right
    if (event->key() == Qt::Key_Left){
        if (pos().x() > 0)
            setPos(x()-50,y());
        setPixmap(QPixmap(":/new/dataset/dataset/s_mario_run1_L.png"));
    }
    else if (event->key() == Qt::Key_Right){
        if (pos().x() + 100 < 7000)
            setPos(x()+50,y());
        setPixmap(QPixmap(":/new/dataset/dataset/s_mario_run1_R.png"));
    }
    if (event->key() == Qt::Key_Space && !isJumping) {
        isJumping = true; // 开始跳跃
        velocity = -15; // 设置一个初始向上的速度
        jumpTimer->start(20); // 每20毫秒更新一次位置
    }
}

void Player::jumpStep() {
    setPos(x(), y() + velocity);
    velocity += 1;

    QList<QGraphicsItem *> colliding_items = collidingItems();
    for (int i = 0; i < colliding_items.size(); ++i) {
        if (typeid(*(colliding_items[i])) == typeid(BrokenBrick)) {
            BrokenBrick *brokenbrick = dynamic_cast<BrokenBrick *>(colliding_items[i]);

            // Check if hit from the bottom
            if (velocity < 0 && y() > brokenbrick->y()) {
                brokenbrick->breakBrick();
                break;
            }

            // Check if landing on top of the brick
            if (velocity > 0 && y() + pixmap().height() < brokenbrick->y() + brokenbrick->pixmap().height()) {
                setPos(x(), brokenbrick->y() - pixmap().height());
                velocity = 0;
                isJumping = false;
                jumpTimer->stop();
                break;
            }

            // Check for side collisions
            if (x() < brokenbrick->x() + brokenbrick->pixmap().width() && x() + pixmap().width() > brokenbrick->x()) {
                if (x() < brokenbrick->x()) {
                    setPos(brokenbrick->x() - pixmap().width(), y());
                } else {
                    setPos(brokenbrick->x() + brokenbrick->pixmap().width(), y());
                }
            }
        }
    }

    if (pos().y() > 500) { // Assuming 500 is ground level
        jumpTimer->stop();
        setPos(x(), 500);
        isJumping = false;
        velocity = 0;
    }


}


