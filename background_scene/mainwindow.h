#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsView>
#include "player.h"
#include "score.h"
#include <QMouseEvent>

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    Player *mario = nullptr;
    QGraphicsView *view = nullptr;
    QGraphicsScene *scene = nullptr;
    Score *score = nullptr;
    MainWindow(QWidget *parent = nullptr);
    void CreateElements();
    static void GameOver();
    bool isMarioMoving;
    void mousePressEvent(QMouseEvent *event);
    // void SetScrollEvent();
    ~MainWindow();
public slots:
    void ScrollEvent();

private:

};
#endif // MAINWINDOW_H
