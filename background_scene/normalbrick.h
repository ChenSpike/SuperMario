#ifndef NORMALBRICK_H
#define NORMALBRICK_H

#include <QGraphicsPixmapItem>
#include <QObject>
#include <QTimer>
#include "coin.h"

class NormalBrick : public QObject, public QGraphicsPixmapItem{
    Q_OBJECT
public:
    NormalBrick(const QPixmap& pixmap, bool withCoin = false);
    static void CreateNormalBricks(QGraphicsScene* scene);
    void handleCollision();
private:
    Coin *coin;
    int coinCount;
    bool isNormalBrickWCoin; // state of w/ or w/o coins
    QTimer *bounceTimer; // normal brick bouncing timer
    QTimer *coinTimer; // coin flying timer
    qreal bounceStep; // the step when the brick is bouncing
    qreal initialY; // initial y position of the normal brick
    bool isBouncing; // state of bouncing
    void setBounce();
private slots:
    void bounce();
    void coinFly();
};

#endif // NORMALBRICK_H
