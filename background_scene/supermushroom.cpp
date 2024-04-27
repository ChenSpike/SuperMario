#include "supermushroom.h"
#include "waterpipe.h"
#include "player.h"
#include <QGraphicsScene>
#include <QList>

SuperMushroom::SuperMushroom(QGraphicsItem *parent):
    QGraphicsPixmapItem(parent),
    initialY(0),
    finalY(0),
    bounceHeight(30),
    bounceStep(-10),
    bounceTimer(new QTimer(this)),
    moveTimer(new QTimer(this))
{
    // Set the pixmap to super mushroom image
    setPixmap(QPixmap(":/new/dataset/dataset/super mushroom.png"));
    connect(bounceTimer, &QTimer::timeout, this, &SuperMushroom::bounce);
    connect(moveTimer, SIGNAL(timeout()), this, SLOT(move()));
}

void SuperMushroom::setBounce(qreal boxBrickY) {
    initialY = y(); // set initial y position
    finalY = boxBrickY; // set landing Y position
    bounceTimer->start(20); // start bounce timer
    return;
}

void SuperMushroom::bounce() {
    setPos(x(), y() + bounceStep);
    if (bounceStep < 0 && y() <= initialY - bounceHeight) {
        bounceStep = 10; // change direction after reaching height limit
    }
    else if (bounceStep > 0 && y() >= finalY) {
        // stop timer when landing on final y position
        bounceTimer->stop();
        bounceStep = -10;
        setPos(x(), finalY);
        moveTimer->start(20);
    }
    return;
}

void SuperMushroom::move(){
    // 檢查撞擊
    QList<QGraphicsItem *> colliding_item = collidingItems();
    for (int i = 0, n = colliding_item.size(); i < n; ++i) {
        if (typeid(*(colliding_item[i])) == typeid(WaterPipe)) {
            direction = -direction;  // 改變方向
        }
        else if (typeid(*(colliding_item[i])) == typeid(Player)) {
            Player *player = dynamic_cast<Player *>(colliding_item[i]);
            player->grow();
            scene()->removeItem(this);
            delete this;
            return;
        }
    }

    setPos(x() + 3 * direction, y());
    return;
}

void SuperMushroom::advance(int phase){
    if (!phase) return;
    move();
}
