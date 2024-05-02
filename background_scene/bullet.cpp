#include "bullet.h"
#include <QGraphicsScene>

Bullet::Bullet(QGraphicsItem *parent) :
    QObject(),
    QGraphicsPixmapItem(parent),
    startPos(0,0),
    targetPos(0,0),
    shootTimer(new QTimer(this)),
    speed(2)
{
    setPixmap(QPixmap(":/new/dataset/dataset/bullet.png")); // Set bullet image

    // Calculate angle towards the target
    // qreal angle = qAtan2(targetPos.y() - start.y(), targetPos.x() - start.x());
    // setRotation(qRadiansToDegrees(angle)); // Set bullet direction

    connect(shootTimer, SIGNAL(timeout()), this, SLOT(shoot()));
}

void Bullet::setAngle(QPointF start, QPointF target){
    // Calculate angle towards the target
    startPos = start;
    targetPos = target;
    qreal angle = qAtan2(targetPos.y() - start.y(), targetPos.x() - start.x());
    setRotation(qRadiansToDegrees(angle)); // Set bullet direction
    shootTimer->start(50); // Start a timer to shoot the bullet
    return;
}

void Bullet::shoot() {
    // Calculate new position based on current position and angle
    qreal dx = cos(rotation() * M_PI / 180);
    qreal dy = sin(rotation() * M_PI / 180);
    setPos(x() + dx * speed, y() + dy * speed); // Adjust speed as needed

    // Remove bullet if it's out of scene
    if (!scene()->sceneRect().contains(pos())) {
        scene()->removeItem(this);
        delete this;
        return;
    }
}
