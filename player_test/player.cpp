#include "player.h"
#include <QGraphicsScene>
#include <QKeyEvent>


Player::Player(QGraphicsItem *parent): QGraphicsPixmapItem(parent){

    // set graphic
    setPixmap(QPixmap(":/image/s_mario_run1_R.png"));
}

void Player::keyPressEvent(QKeyEvent *event){
    // move the player left and right
    if (event->key() == Qt::Key_Left){
        if (pos().x() > 0)
        setPos(x()-10,y());
        setPixmap(QPixmap(":/image/s_mario_run1_L.png"));
    }
    else if (event->key() == Qt::Key_Right){
        if (pos().x() + 100 < 800)
        setPos(x()+10,y());
        setPixmap(QPixmap(":/image/s_mario_run1_R.png"));
    }
}
