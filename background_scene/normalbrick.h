#ifndef NORMALBRICK_H
#define NORMALBRICK_H

#include <QGraphicsPixmapItem>
#include <QObject>
#include <QTimer>

class NormalBrick : public QObject, public QGraphicsPixmapItem{
    Q_OBJECT
public:
    NormalBrick(const QPixmap& pixmap, bool withCoin = false);
    static void CreateNormalBricks(QGraphicsScene* scene);
    static QVector<NormalBrick*> NormalBricks;
    void handleCollision();
private:
    int coinCount;
    bool isNormalBrickWCoin; // state of w/ or w/o coins
    bool isBouncing; // state of bouncing
    QTimer *bounceTimer; // normal brick bouncing timer
    qreal bounceStep; // the step when the brick is bouncing
    qreal initialY; // initial y position of the normal brick
    void setBounce();
private slots:
    void bounce();
};

#endif // NORMALBRICK_H
