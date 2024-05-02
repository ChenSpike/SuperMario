#include "toxicmushroom.h"
#include "waterpipe.h"
#include "player.h"
#include "boxbrick.h"
#include "stonebrick.h"
#include "brokenbrick.h"
#include "floorbrick.h"
#include "player.h"
#include "health.h"
#include <iostream>
#include <QTimer>
#include <QGraphicsScene>
#include <QDebug>
#include <QList>


ToxicMushroom::ToxicMushroom(QGraphicsItem *parent) : QGraphicsPixmapItem(parent)
{
    setPixmap(QPixmap(":/new/dataset/dataset/toxic mushroom1.png"));
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(move()));
    timer->start(50);

    cooldownTimer = new QTimer(this);
    cooldownTimer->setInterval(2000); // 2 seconds cooldown
    cooldownTimer->setSingleShot(true); // Only trigger once per activation
    connect(cooldownTimer, &QTimer::timeout, this, &ToxicMushroom::endCooldown);

}

void ToxicMushroom::move()
{
    // 檢查撞擊
    QList<QGraphicsItem *> colliding_item = collidingItems();
    onBrick = false;
    for (int i = 0, n = colliding_item.size(); i < n; ++i) {
        if (typeid(*(colliding_item[i])) == typeid(WaterPipe)) {
            direction = -direction;  // 改變方向
        } else if (typeid(*(colliding_item[i])) == typeid(BoxBrick) ||
                   typeid(*(colliding_item[i])) == typeid(StoneBrick) ||
                   typeid(*(colliding_item[i])) == typeid(BrokenBrick) ||
                   typeid(*(colliding_item[i])) == typeid(FloorBrick)) {
            onBrick = true;
            velocity = 0;  // 停止垂直速度
            setY(colliding_item[i]->y() - pixmap().height());  // 調整位置以站在boxbrick上
            break;
        }else if(typeid(*(colliding_item[i])) == typeid(Player)){
            ///////////////////// new for player shrinking and health decreasement /////////
            Player *player = dynamic_cast<Player *>(colliding_item[i]);
            if(!player->isJumping){
                if (!isCooldownActive) {
                    Health::decreasement();
                    player -> shrink();
                    qDebug() <<"toxicmushroom collids with player. " <<Qt::endl;
                    startCooldown();

                }
            }
            ///////////////////////////////////////////////////////////////////////////////////

        }
    }

    if (!onBrick) {
           velocity += 1;  // 增加垂直速度
       }

    setPos(x() + 2 * direction, y() + velocity);


    //掉到最底刪除
    if(y() > 615){
        scene()->removeItem(this);
        delete this;
    }
}

void ToxicMushroom::breakToxicMushroom(){
    scene()->removeItem(this);
    delete this;
}

void ToxicMushroom::advance(int phase)
{
    if (!phase) return;
    move();
}

///////////handlePlayerCollision()改到move做判斷/////////
void ToxicMushroom::startCooldown() {
    isCooldownActive = true;
    cooldownTimer->start(); // Start or restart the cooldown period
}

void ToxicMushroom::endCooldown() {
    isCooldownActive = false; // Reset the cooldown state after 2 seconds
}

