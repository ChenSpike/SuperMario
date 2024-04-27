#ifndef WATERPIPE_H
#define WATERPIPE_H
#include <QGraphicsPixmapItem>
#include <QObject>
#include <QGraphicsItem>
#include <QVector>

class WaterPipe: public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    WaterPipe(const QPixmap& pixmap);
    static void CreateWaterPipes(QGraphicsScene* scene);
};

#endif // WATERPIPE_H
