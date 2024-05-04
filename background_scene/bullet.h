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
public slots:
    void move();
private:
    qreal step; // moving step 15px
    qreal trajectory; // the total distance of trajectory
};

#endif // BULLET_H
