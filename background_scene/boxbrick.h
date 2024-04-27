#ifndef BOXBRICK_H
#define BOXBRICK_H

#include <QGraphicsPixmapItem>
#include <QObject>
#include <QTimer>

class BoxBrick: public QObject, public QGraphicsPixmapItem{
    Q_OBJECT
public:
    enum ItemType {
        COIN,
        SUPERMUSHROOM,
        FIREFLOWER
    };

    BoxBrick(ItemType type = COIN, QGraphicsItem *parent = nullptr);
    static void CreateBoxBricks(QGraphicsScene* scene);
    static QVector<BoxBrick*> BoxBricks;
    void handleCollision(); // handle collision
private:
    ItemType itemType;
    bool isBoxBrick; // State of being a stone brick
    QTimer *bounceTimer; // box brick bouncing timer
    qreal bounceStep; // the step when the brick is bouncing
    qreal initialY; // initial y position of the normal brick
    void setBounce();
    void createItem(); // Create an item above a box brick
private slots:
    void bounce();
};

#endif // BOXBRICK_H
