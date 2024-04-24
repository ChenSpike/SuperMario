#ifndef BOXBRICK_H
#define BOXBRICK_H

#include <QGraphicsPixmapItem>
#include <QObject>

class BoxBrick: public QObject, public QGraphicsPixmapItem{
    Q_OBJECT
public:
    BoxBrick();
    static void CreateBoxBricks(QGraphicsScene* scene);
    void handleCollision(); // handle collision
private:
    void createCoin(); // create a coin
    bool isBoxBrick; // An indicator to determine whether it is a box brick or not.
};

#endif // BOXBRICK_H
