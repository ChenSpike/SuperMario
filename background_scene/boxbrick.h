#ifndef BOXBRICK_H
#define BOXBRICK_H
#include <QGraphicsPixmapItem>
#include <QPixmap>

class BoxBrick : public QGraphicsPixmapItem {
public:
    BoxBrick(const QPixmap& pixmap);
    static void CreateBoxBricks(QGraphicsScene* scene);
    void collide(); // change boxbrick to stonebrick
};
#endif // BOXBRICK_H
