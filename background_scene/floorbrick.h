#ifndef FLOORBRICK_H
#define FLOORBRICK_H

#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QObject>

class FloorBrick: public QObject, public QGraphicsPixmapItem {
    Q_OBJECT
public:
    FloorBrick(const QPixmap& pixmap);
    static void CreateFloorBricks(QGraphicsScene* scene);
    static QVector<FloorBrick*> FloorBricks; //floor brick pointer vector
private:
    QRectF floorbrickRect;
};
#endif // FLOORBRICK_H
