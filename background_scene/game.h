#ifndef GAME_H
#define GAME_H

#include <QWidget>
#include <QGraphicsView>
#include <QGraphicsScene>
#include "player.h"
#include "score.h"
#include <QMouseEvent>

class Game: public QGraphicsView{
public:
    Game(QWidget *parent = nullptr);
    QGraphicsScene *scene;
    //QGraphicsView *view = nullptr;
    Player *mario;
    Score *score;
    void mousePressEvent(QMouseEvent *event);
    void keyPressEvent(QKeyEvent *event);
    QTimer *timer;
    int c=0;
public slots:
    void ScrollEvent();
};

#endif // GAME_H
