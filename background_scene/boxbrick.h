#ifndef BOXBRICK_H
#define BOXBRICK_H

#include <QGraphicsPixmapItem>
#include <QObject>
#include <QTimer>
#include "coin.h"

class BoxBrick: public QObject, public QGraphicsPixmapItem{
    Q_OBJECT
public:
    BoxBrick();
    static void CreateBoxBricks(QGraphicsScene* scene);
    void handleCollision(); // handle collision
private:
    Coin *coin;
    void createCoin(); // create a coin
    bool isBoxBrick; // State of being a stone brick
    QTimer *jumpTimer; // 用於跳躍的計時器
    QTimer *coinTimer; // coin flying timer
    qreal jumpStep; // 跳躍的步驟大小
private slots:
    void coinFly();
};

#endif // BOXBRICK_H
