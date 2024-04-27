#ifndef PLAYER_H
#define PLAYER_H

#include <QGraphicsPixmapItem>
#include <QObject>
#include <QGraphicsItem>
#include <QTimer>

class Player:public QObject, public QGraphicsPixmapItem{
    Q_OBJECT
public:
    Player(QGraphicsItem * parent=0);
    void keyPressEvent(QKeyEvent * event);
    void jumpStep();
    void grow();
private:
    QTimer* jumpTimer;
    int velocity;
    int maxHeight = 100; // 跳躍高度
    bool isJumping = false; // 跳躍狀態
    bool isBig = false;

};


#endif // PLAYER_H
