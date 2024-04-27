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
    void grow();
private:
    QTimer* jumpTimer;
    int velocity; // initial velocity
    int maxHeight; // maximum jumping height
    bool isJumping; // state of jumping
    bool isBig; // state of big or small
private slots:
    void jumpStep();
};


#endif // PLAYER_H
