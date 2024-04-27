#ifndef CASTLE_H
#define CASTLE_H
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>


class Castle: public QGraphicsPixmapItem
{
public:
    Castle(const QPixmap& pixmap);
    static void CreateCastle(QGraphicsScene* scene);
};

#endif // CASTLE_H

