#ifndef COIN_H
#define COIN_H

#include <QObject>
#include <QGraphicsPixmapItem>

class Coin : public QObject, public QGraphicsPixmapItem{
    Q_OBJECT
public:
    Coin();
};

#endif // COIN_H
