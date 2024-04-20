#ifndef STONEBRICK_H
#define STONEBRICK_H
#include <QGraphicsPixmapItem>
#include <QPixmap>

class StoneBrick:public QGraphicsPixmapItem{
public:
    StoneBrick(const QPixmap& pixmap);
};

#endif // STONEBRICK_H
