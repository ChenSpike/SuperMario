#ifndef BOXBRICK_H
#define BOXBRICK_H

#include <QGraphicsPixmapItem>
#include <QObject>
#include <QGraphicsScene>

class BoxBrick: public QObject, public QGraphicsPixmapItem{
    Q_OBJECT
public:
    BoxBrick(QGraphicsScene *scene); // Constructor that takes QGraphicsScene as parameter
public slots:
    void handleCollision(); // Slot to handle collision
    void createCoin(); // Slot to create a coin
private:
    QGraphicsScene *scene; // Pointer to QGraphicsScene
    bool isBoxBrick; // An indicator to determine whether it is a box brick or not.
};

#endif // BOXBRICK_H
