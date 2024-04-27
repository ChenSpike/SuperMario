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

public slots:
    void move();

protected:
    void advance(int phase);

private:
    qreal initialY; // initial Y position
    qreal finalY; // landing Y position
    qreal bounceHeight; // bounce height limit
    qreal bounceStep;
    QTimer *bounceTimer;
    QTimer *moveTimer;
    int direction = 1;  // 1 表示向右移動，-1 表示向左移動

private slots:
    void bounce();
};


#endif // SUPERMUSHROOM_H
