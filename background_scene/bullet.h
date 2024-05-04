#ifndef BULLET_H
#define BULLET_H

#include <QGraphicsPixmapItem>
#include <QObject>
//#include <QTimer>
#include <QPointF>

class Bullet : public QObject, public QGraphicsPixmapItem {
    Q_OBJECT
public:
    Bullet(QGraphicsItem *parent = nullptr);
    void setAngle(QPointF start, QPointF target);
public slots:
    void move();
private:
    QPointF startPos;
    QPointF targetPos;
    qreal step;
};

#endif // BULLET_H
