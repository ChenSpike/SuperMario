#ifndef SUPERMUSHROOM_H
#define SUPERMUSHROOM_H

#include <QObject>
#include <QGraphicsPixmapItem>

class SuperMushroom : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    explicit SuperMushroom(QGraphicsItem *parent = nullptr);

public slots:
    void move();

protected:
    void advance(int phase);

private:
    int direction = 1;  // 1 表示向右移動，-1 表示向左移動
};


#endif // SUPERMUSHROOM_H
