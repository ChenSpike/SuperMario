#include "supermushroom.h"
#include "waterpipe.h"
#include "player.h"
#include <QTimer>
#include <QGraphicsScene>
#include <QList>

SuperMushroom::SuperMushroom(QGraphicsItem *parent) : QGraphicsPixmapItem(parent)
{
    setPixmap(QPixmap(":/new/dataset/dataset/super mushroom.png"));  // 設置蘑菇的圖片
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(move()));
    timer->start(50);  // 每50毫秒移動一次
}

void SuperMushroom::move()
{
    // 檢查撞擊
    QList<QGraphicsItem *> colliding_item = collidingItems();
    for (int i = 0, n = colliding_item.size(); i < n; ++i) {
        if (typeid(*(colliding_item[i])) == typeid(WaterPipe)) {
            direction = -direction;  // 改變方向
        } else if (typeid(*(colliding_item[i])) == typeid(Player)) {
            Player *player = dynamic_cast<Player *>(colliding_item[i]);
            player->grow();
            scene()->removeItem(this);
            delete this;
            return;
        }
    }

    setPos(x() + 5 * direction, y());
}

void SuperMushroom::advance(int phase)
{
    if (!phase) return;
    move();
}
