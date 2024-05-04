#include "supermushroom.h"
#include "waterpipe.h"
#include "player.h"
#include "boxbrick.h"
#include "brokenbrick.h"
#include "floorbrick.h"
#include "normalbrick.h"
#include <QGraphicsScene>
#include <QList>
#include <QDebug>
#include <QPainter>
#include <QGraphicsRectItem>

SuperMushroom::SuperMushroom(QGraphicsItem *parent):
    QGraphicsPixmapItem(parent),
    initialY(0),
    finalY(0),
    bounceHeight(30),
    bounceStep(-10),
    velocityX(5),
    velocityY(0),
    onBrick(true),
    bounceTimer(new QTimer(this)),
    moveTimer(new QTimer(this))
{
    // Set the pixmap to super mushroom image
    setPixmap(QPixmap(":/new/dataset/dataset/super mushroom.png"));
    connect(bounceTimer, &QTimer::timeout, this, &SuperMushroom::bounce);
    connect(moveTimer, SIGNAL(timeout()), this, SLOT(move()));
}

QRectF SuperMushroom::boundingRect() const {
    return QRectF(0, 0, pixmap().width(), pixmap().height());
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
        bounceStep = 5; // change direction after reaching height limit
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

int t=0;
void SuperMushroom::move(){
    onBrick = false;

    // check collision
    QList<QGraphicsItem *> colliding_items = collidingItems();
    for (int i = 0, n = colliding_items.size(); i < n; ++i) {
        // collide with player
        if (typeid(*(colliding_items[i])) == typeid(Player)) {
            Player *player = dynamic_cast<Player *>(colliding_items[i]);
            scene()->removeItem(this);
            moveTimer->stop();
            player->grow();
            player->groundLevel = 435;
            delete this;
            return;
        }

        // collide with bricks or pipes
        if (typeid(*(colliding_items[i])) == typeid(WaterPipe)){
            WaterPipe *ordinaryItem = dynamic_cast<WaterPipe *>(colliding_items[i]);
            qreal rightMushroom = x() + pixmap().width();
            qreal bottomMushroom = y() + pixmap().height();
            qreal rightItem = ordinaryItem->x() + ordinaryItem->pixmap().width();
            qreal bottomItem = ordinaryItem->y() + ordinaryItem->pixmap().height();
            // top collsion
            if (velocityY > 0 && bottomMushroom < bottomItem){
                setPos(x(), ordinaryItem->y() - pixmap().height());
                velocityY = 0;
                onBrick = true;
                break;
            }
            // side collision
            if (x() < rightItem || rightMushroom > ordinaryItem->x()){
                velocityX = -velocityX; // change direction
            }
        }
        if (typeid(*(colliding_items[i])) == typeid(BoxBrick)) {
            BoxBrick *ordinaryItem = dynamic_cast<BoxBrick *>(colliding_items[i]);
            qreal rightMushroom = x() + pixmap().width();
            qreal bottomMushroom = y() + pixmap().height();
            qreal rightItem = ordinaryItem->x() + ordinaryItem->pixmap().width();
            qreal bottomItem = ordinaryItem->y() + ordinaryItem->pixmap().height();
            // top collsion
            if (velocityY > 0 && bottomMushroom < bottomItem){
                setPos(x(), ordinaryItem->y() - pixmap().height());
                velocityY = 0;
                onBrick = true;
                break;
            }

            if (x() < rightItem || rightMushroom > ordinaryItem->x()){
                velocityX = -velocityX; // change direction
            }
        }
        if (typeid(*(colliding_items[i])) == typeid(BrokenBrick)) {
            BrokenBrick *ordinaryItem = dynamic_cast<BrokenBrick *>(colliding_items[i]);
            qreal rightMushroom = x() + pixmap().width();
            qreal bottomMushroom = y() + pixmap().height();
            qreal rightItem = ordinaryItem->x() + ordinaryItem->pixmap().width();
            qreal bottomItem = ordinaryItem->y() + ordinaryItem->pixmap().height();
            // top collsion
            if (velocityY > 0 && bottomMushroom < bottomItem){
                setPos(x(), ordinaryItem->y() - pixmap().height());
                velocityY = 0;
                onBrick = true;
                break;
            }
            // side collision
            if (x() < rightItem || rightMushroom > ordinaryItem->x()){
                velocityX = -velocityX; // change direction
            }
        }
        if (typeid(*(colliding_items[i])) == typeid(NormalBrick)) {
            NormalBrick *ordinaryItem = dynamic_cast<NormalBrick *>(colliding_items[i]);
            qreal rightMushroom = x() + pixmap().width();
            qreal bottomMushroom = y() + pixmap().height();
            qreal rightItem = ordinaryItem->x() + ordinaryItem->pixmap().width();
            qreal bottomItem = ordinaryItem->y() + ordinaryItem->pixmap().height();
            // top collsion
            if (velocityY > 0 && bottomMushroom < bottomItem){
                setPos(x(), ordinaryItem->y() - pixmap().height());
                velocityY = 0;
                onBrick = true;
                break;
            }
            // side collision
            if (x() < rightItem || rightMushroom > ordinaryItem->x()){
                velocityX = -velocityX; // change direction
            }
        }
        if (typeid(*(colliding_items[i])) == typeid(FloorBrick)) {
            FloorBrick *ordinaryItem = dynamic_cast<FloorBrick *>(colliding_items[i]);
            qreal rightMushroom = x() + pixmap().width();
            qreal bottomMushroom = y() + pixmap().height();
            qreal rightItem = ordinaryItem->x() + ordinaryItem->pixmap().width();
            qreal bottomItem = ordinaryItem->y() + ordinaryItem->pixmap().height();
            // top collsion
            if (velocityY > 0 && bottomMushroom < bottomItem){
                setPos(x(), ordinaryItem->y() - pixmap().height());
                velocityY = 0;
                onBrick = true;
                break;
            }
            // side collision
            if (x() < rightItem || rightMushroom > ordinaryItem->x()){
                velocityX = -velocityX; // change direction
            }
        }
    }

    if (y() >= 519){
        if ((x() >= 2450 && x() <= 2500) ||
            (x() >= 3450 && x() <= 3500) ||
            (x() >= 4300 && x() <= 4350) ){
            scene()->removeItem(this);
            moveTimer->stop();
            delete this;
            return;
        }
    }

    if (!onBrick) {
        velocityY += 1;  // 增加垂直速度
    }

    setPos(x() + velocityX, y() + velocityY);
    return;
}
