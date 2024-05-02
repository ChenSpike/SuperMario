#ifndef SUPERMUSHROOM_H
#define SUPERMUSHROOM_H

#include <QGraphicsPixmapItem>
#include <QObject>
#include <QTimer>

class SuperMushroom : public QObject, public QGraphicsPixmapItem{
    Q_OBJECT
public:
    explicit SuperMushroom(QGraphicsItem *parent = nullptr);
    void setBounce(qreal boxBrickY);
    QRectF boundingRect() const override;
    QRectF getMushroomRect() const;

public slots:
    void move();

private:
    qreal initialY; // initial Y position
    qreal finalY; // landing Y position
    qreal bounceHeight; // bounce height limit
    qreal bounceStep;
    qreal velocityX; // 3(default): move right 3px; -3: move left 3px
    qreal velocityY;
    bool onBrick; // true(default): mushroom is on bricks
    QTimer *bounceTimer;
    QTimer *moveTimer;
private slots:
    void bounce();
};


#endif // SUPERMUSHROOM_H
