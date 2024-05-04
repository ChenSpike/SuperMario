#ifndef TOXICMUSHROOM_H
#define TOXICMUSHROOM_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QTimer>
#include <QList>

class ToxicMushroom: public QObject, public QGraphicsPixmapItem{
    Q_OBJECT
public:
    explicit ToxicMushroom(QGraphicsItem *parent = nullptr);
    void breakToxicMushroom();
    void checkCollisions();
    void startCooldown();
    void endCooldown();
    bool isCooldownActive = false;

public slots:
    void move();

protected:
    void advance(int phase);

private:
    int direction = 1;  // 1 表示向右移動，-1 表示向左移動
    int velocity = 0;
    bool onBrick;
    QTimer *cooldownTimer;
};

#endif // TOXICMUSHROOM_H
