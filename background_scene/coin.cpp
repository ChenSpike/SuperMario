#include "coin.h"
#include <QPixmap>
#include <QTimer>

//Coin* Coin::instance = nullptr;

Coin::Coin() {
    // Set the pixmap to coin image
    QPixmap pixmap(":/new/dataset/dataset/coin.png");
    setPixmap(pixmap);
}

void Coin::CreateCoins(QGraphicsScene* scene){
    // create coins at different position
    QVector<Coin*> vCoin;
    int position[] = {7, 8, 9, 10, 11, 12};
    for(int i=0; i<6; i++){
        Coin* newCoin = new Coin();
        newCoin -> setPos(position[i] * 50, 350);
        scene -> addItem(newCoin);
        vCoin.append(newCoin);
    }
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
