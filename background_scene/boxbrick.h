#ifndef BOXBRICK_H
#define BOXBRICK_H

#include <QGraphicsPixmapItem>
#include <QObject>

class BoxBrick: public QObject, public QGraphicsPixmapItem{
    Q_OBJECT
public:
    BoxBrick();
    static void CreateBoxBricks(QGraphicsScene* scene);
    void handleCollision(); // Slot to handle collision
    void createCoin(); // Slot to create a coin
private:
    bool isBoxBrick; // An indicator to determine whether it is a box brick or not.
};

#endif // BOXBRICK_H
