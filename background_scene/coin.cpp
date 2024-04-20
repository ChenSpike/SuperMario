#include "coin.h"
#include <QPixmap>
#include <QTimer>

//Coin* Coin::instance = nullptr;

Coin::Coin() {
    // Set the pixmap to coin image
    QPixmap pixmap(":/new/dataset/dataset/coin.png");
    setPixmap(pixmap);
}

/*
Coin* Coin::getInstance()
{
    if (!instance)
        instance = new Coin();
    return instance;
}

void Coin::create()
{
    // Create a new coin at a random position
    Coin *coin = new Coin();
    coin->setPos(500, 200); // You can set the position as you like
    scene()->addItem(coin);
}*/
