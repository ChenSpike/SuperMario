#include "bullet.h"
#include "boxbrick.h"
#include "brokenbrick.h"
#include "normalbrick.h"
#include "floorbrick.h"
#include "waterpipe.h"
#include "toxicmushroom.h"
#include <QGraphicsScene>
#include <QTimer>
#include <QList>
#include <qmath.h>

Bullet::Bullet(QGraphicsItem *parent) :
    QGraphicsPixmapItem(parent),
    step(15),
    trajectory(0)
{
    setPixmap(QPixmap(":/new/dataset/dataset/bullet.png")); // Set bullet image

    // connect timer to move()
    QTimer *moveTimer = new QTimer(this);
    connect(moveTimer, &QTimer::timeout, this, &Bullet::move);
    moveTimer->start(30);
}

void Bullet::move() {
    qreal theta = rotation(); // degrees

    // Calculate new position based on current position and angle
    qreal dy = step * qSin(qDegreesToRadians(theta));
    qreal dx = step * qCos(qDegreesToRadians(theta));
    setPos(x() + dx, y() + dy);

    QList<QGraphicsItem* > colliding_items = collidingItems();
    for (int i=0; i < colliding_items.size(); i++){
        if ((typeid(*(colliding_items[i])) == typeid(BoxBrick)) ||
            (typeid(*(colliding_items[i])) == typeid(BrokenBrick)) ||
            (typeid(*(colliding_items[i])) == typeid(FloorBrick)) ||
            (typeid(*(colliding_items[i])) == typeid(NormalBrick)) ||
            (typeid(*(colliding_items[i])) == typeid(WaterPipe))){
            scene()->removeItem(this);
            delete this;
            return;
        }
        else if (typeid(*(colliding_items[i])) == typeid(ToxicMushroom)){
            ToxicMushroom *toxicmushroom = dynamic_cast<ToxicMushroom *>(colliding_items[i]);
            toxicmushroom->breakToxicMushroom();
            scene()->removeItem(this);
            delete this;
            return;
        }
    }

    trajectory = trajectory + step; // accumulate the distance
    if ((y() + pixmap().height() < 0) ||
        (trajectory > 1400)){
        scene()->removeItem(this);
        delete this;
        qDebug()<<"delete bullet";
        return;
    }
    return;
}
