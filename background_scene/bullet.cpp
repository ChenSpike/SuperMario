#include "bullet.h"
#include <QGraphicsScene>
#include <QTimer>
#include <qmath.h>

Bullet::Bullet(QGraphicsItem *parent) :
    QGraphicsPixmapItem(parent),
    startPos(0,0),
    targetPos(0,0),
    step(30)
{
    setPixmap(QPixmap(":/new/dataset/dataset/bullet.png")); // Set bullet image

    // connect timer to move()
    QTimer *moveTimer = new QTimer(this);
    connect(moveTimer, &QTimer::timeout, this, &Bullet::move);
    moveTimer->start(50);
}

void Bullet::setAngle(QPointF start, QPointF target){
    // Calculate angle towards the target
    startPos = start;
    targetPos = target;
    qreal angle = qAtan2(targetPos.y() - start.y(), targetPos.x() - start.x());
    setRotation(qRadiansToDegrees(angle)); // Set bullet direction
    //moveTimer->start(50); // Start a timer to shoot the bullet
    return;
}

void Bullet::move() {
    qreal theta = rotation(); // degrees

    // Calculate new position based on current position and angle
    qreal dy = step * qSin(qDegreesToRadians(theta));
    qreal dx = step * qCos(qDegreesToRadians(theta));
    setPos(x() + dx, y() + dy);

    // // Remove bullet if it's out of scene
    // if (!scene()->sceneRect().contains(pos())) {
    //     scene()->removeItem(this);
    //     delete this;
    //     qDebug()<<"success delete";
    //     return;
    // }
    return;
}
