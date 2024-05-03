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
    Player *mario;
    Score *score;
    void mousePressEvent(QMouseEvent *event);
    void keyPressEvent(QKeyEvent *event);
};

#endif // GAME_H
