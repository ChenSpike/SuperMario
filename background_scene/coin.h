#ifndef COIN_H
#define COIN_H

#include <QGraphicsScene>

#include <QObject>
#include <QGraphicsPixmapItem>

class Coin : public QObject, public QGraphicsPixmapItem{
    Q_OBJECT
public:
    Coin();
    static void CreateCoins(QGraphicsScene* scene);
    static int numberCoin;
};

#endif // COIN_H
