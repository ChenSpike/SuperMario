#ifndef BROKENBRICK_H
#define BROKENBRICK_H
#include <QGraphicsPixmapItem>
#include <QObject>
#include <QGraphicsItem>

class BrokenBrick:public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
    public:
        BrokenBrick(const QPixmap& pixmap);
        static void CreateBrokenBricks(QGraphicsScene* scene);
        void breakBrick(); // function of breaking the bricks
};

#endif // BROKENBRICK_H
