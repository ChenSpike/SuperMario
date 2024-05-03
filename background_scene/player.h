#ifndef PLAYER_H
#define PLAYER_H

#include <QGraphicsPixmapItem>
#include <QGraphicsItem>
#include <QKeyEvent>
#include <QMouseEvent>
#include <QObject>
#include <QTimer>

class Player:public QObject, public QGraphicsPixmapItem{
    Q_OBJECT
public:
    Player(QGraphicsItem * parent=0);
    void keyPressEvent(QKeyEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void grow();
    void shrink();
    bool isJumping; // state of jumping
    void shoot(QPointF targetPos);
    qreal stepX;
    qreal groundLevel;
    int t=0;
private:
    QTimer* jumpTimer;
    int velocity; // initial velocity
    bool isBig; //  true:big ; false:small(default)
    int bullet; // 0(default)
private slots:
    void jumpStep();
};


#endif // PLAYER_H
