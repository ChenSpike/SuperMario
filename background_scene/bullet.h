#ifndef BULLET_H
#define BULLET_H

#include <QGraphicsPixmapItem>
#include <QObject>
#include <QTimer>
#include <QPointF>

class Bullet : public QObject, public QGraphicsPixmapItem {
    Q_OBJECT
public:
    Bullet(QGraphicsItem *parent = nullptr);
    void setAngle(QPointF start, QPointF target);
public slots:
    void shoot();
private:
    QPointF startPos;
    QPointF targetPos;
    QTimer *shootTimer;
    qreal speed;
};

#endif // BULLET_H
