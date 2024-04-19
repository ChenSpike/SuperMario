#include "player.h"
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
    // 更新位置
    setPos(x(), y() + velocity);
    velocity += 1; // 模拟重力影响

    // 检查是否完成跳跃（是否回到了初始高度或更低）
    if (pos().y() > 500) {
        jumpTimer->stop();
        setPos(x(), 500); // 重置到地面
        isJumping = false; // 结束跳跃
        velocity = 0; // 重置速度
    }
}


