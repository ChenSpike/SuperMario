#ifndef FLOORBRICK_H
#define FLOORBRICK_H
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>

class FloorBrick: public QGraphicsPixmapItem {
    public:
    FloorBrick(const QPixmap& pixmap);
    static void CreateFloorBricks(QGraphicsScene* scene);
};
#endif // FLOORBRICK_H
