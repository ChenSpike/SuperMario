#ifndef COIN_H
#define COIN_H

#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QObject>
#include <QTimer>

class Coin : public QObject, public QGraphicsPixmapItem{
    Q_OBJECT
public:
    Coin(QGraphicsItem *parent = nullptr);
    static QVector<Coin*> vCoin;
    static void CreateCoins(QGraphicsScene* scene);
    static int numberCoin;
    void setFly();
private:
    qreal initialY; // initial Y position
    QTimer *flyTimer;
private slots:
    void fly(); // The coin flies up and then disappears
};

#endif // COIN_H
