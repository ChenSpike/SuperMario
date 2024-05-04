#ifndef PLAYER_H
#define PLAYER_H

#include <QGraphicsPixmapItem>
#include <QGraphicsItem>
#include <QKeyEvent>
#include <QGraphicsSceneMouseEvent>
#include <QObject>
#include <QTimer>

class Player:public QObject, public QGraphicsPixmapItem{
    Q_OBJECT
public:
    Player(QGraphicsItem * parent=0);
    bool isJumping; // ture:jumping ; false:standing(default)
    qreal stepX;
    qreal groundLevel;
    void grow();
    void shrink();
    void keyPressEvent(QKeyEvent *event);
    void setBullet(int bulletNum);
    void shoot(QPointF targetPos);
    //int t=0; // test for counting death
private:
    QTimer* jumpTimer;
    int velocity; // initial velocity
    bool isBig; //  true:big ; false:small(default)
    int bullet; // 0(default)
private slots:
    void jumpStep();
};


#endif // PLAYER_H
