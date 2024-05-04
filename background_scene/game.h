#ifndef GAME_H
#define GAME_H

#include "player.h"
#include "score.h"
#include <QWidget>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QMouseEvent>
#include <QKeyEvent>
#include <QDialog>
#include <QGraphicsPixmapItem>

class Game: public QGraphicsView{
public:
    Game(QWidget *parent = nullptr);
    QGraphicsScene *scene;
    Player *mario;
    Score *score;
    void mousePressEvent(QMouseEvent *event);
    void keyPressEvent(QKeyEvent *event);
private:
    QDialog* start;
    void setStart();
private slots:
    void closeStart();
};

#endif // GAME_H
