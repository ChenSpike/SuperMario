#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsView>
#include "player.h"
#include "score.h"
#include <QMouseEvent>
#include "game.h"

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    //Player *mario = nullptr;
    QGraphicsView *view = nullptr;
    //QGraphicsScene *scene = nullptr;
    //Score *score = nullptr;
    MainWindow(QWidget *parent = nullptr);
    void CreateElements();
    static void GameOver();
    bool isMarioMoving;

    // void SetScrollEvent();
    ~MainWindow();

    Game *game;
    // void mousePressEvent(QMouseEvent *event);
    // void keyPressEvent(QKeyEvent *event);
public slots:
    void ScrollEvent();

private:

};
#endif // MAINWINDOW_H
