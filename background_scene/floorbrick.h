#ifndef FLOORBRICK_H
#define FLOORBRICK_H
#include <QGraphicsPixmapItem>>

class FloorBrick: public QGraphicsPixmapItem {
    public:
      FloorBrick (const QPixmap &pixmap, QGraphicsItem *parent = 0);
};
#endif // FLOORBRICK_H
