#include "coin.h"
#include <QPixmap>

QVector<Coin*> Coin::Coins;

Coin::Coin(QGraphicsItem *parent):
    QGraphicsPixmapItem(parent),
    initialY(0),
    flyTimer(new QTimer(this))
{
    // Set the pixmap to coin image
    setPixmap(QPixmap(":/new/dataset/dataset/coin.png"));
    connect(flyTimer, &QTimer::timeout, this, &Coin::fly);
}

void Coin::CreateCoins(QGraphicsScene* scene){
    // create coins at different position
    int position[] = {7, 8, 9, 10, 11, 12};
    for(int i=0; i<6; i++){
        Coin* newCoin = new Coin();
        newCoin -> setPos(position[i] * 50, 350);
        scene -> addItem(newCoin);
        Coins.append(newCoin);
    }
    return;
}

void Coin::deleteCoin(Coin *coin){
    // delete the coin
    scene()->removeItem(coin);
    QVector<Coin*>::iterator i = Coins.begin();
    while(i != Coins.end()){
        if(*i == coin){
            qDebug()<<"found the coin";
            i = Coins.erase(i);
        }
        else{
            i++;
        }
    }
    qDebug()<<"coins length:"<<Coins.length();
    delete coin;
    return;
}

void Coin::setFly(){
    initialY = y(); // set initial y position
    flyTimer->start(20); // start bounce timer
    return;
}

void Coin::fly(){
    setPos(x(), y() - 10); // coin goes up
    if (y() <= initialY - 100) { // height limit: 100px
        flyTimer->stop();
        scene()->removeItem(this);
        delete this;
    }
    return;
}
