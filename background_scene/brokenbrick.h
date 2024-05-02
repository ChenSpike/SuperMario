#ifndef BROKENBRICK_H
#define BROKENBRICK_H

#include <QGraphicsItem>
#include <QGraphicsPixmapItem>
#include <QObject>
#include <QVector>

class BrokenBrick: public QObject, public QGraphicsPixmapItem{
    Q_OBJECT
public:
    BrokenBrick(const QPixmap& pixmap);
    static void CreateBrokenBricks(QGraphicsScene* scene);
    static QVector<BrokenBrick*> BrokenBricks;
    void breakBrick(BrokenBrick *brokenbrick); // breaking the collided brick
};

#endif // BROKENBRICK_H
