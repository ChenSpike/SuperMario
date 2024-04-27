#ifndef FIREFLOWER_H
#define FIREFLOWER_H

#include <QGraphicsPixmapItem>
#include <QObject>
#include <QTimer>

class FireFlower : public QObject, public QGraphicsPixmapItem{
    Q_OBJECT
public:
    FireFlower(QGraphicsItem *parent = nullptr);
    void setBounce(qreal boxBrickY);
private:
    qreal initialY; // initial Y position
    qreal finalY; // landing Y position
    qreal bounceHeight; // bounce height limit
    qreal bounceStep;
    QTimer *bounceTimer;
private slots:
    void bounce();
};

#endif // FIREFLOWER_H
