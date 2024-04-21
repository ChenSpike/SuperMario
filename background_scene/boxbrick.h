#ifndef BOXBRICK_H
#define BOXBRICK_H

#include <QGraphicsPixmapItem>
#include <QObject>
//#include <QPixmap>

class BoxBrick: public QObject, public QGraphicsPixmapItem{
    Q_OBJECT
public:
    BoxBrick();
//    BoxBrick(QGraphicsScene *scene); // Constructor that takes QGraphicsScene as parameter
    BoxBrick(const QPixmap& pixmap);
    static void CreateBoxBricks(QGraphicsScene* scene);
    bool isSignalConnected() const; // 检查是否已连接信号
    void setSignalConnected(bool connected); // 设置连接信号的标志
    void collide(); // change boxbrick to stonebrick
public slots:
    void handleCollision(); // Slot to handle collision
    void createCoin(); // Slot to create a coin
private:
    //QGraphicsScene *scene; // Pointer to QGraphicsScene
    bool isBoxBrick; // An indicator to determine whether it is a box brick or not.
    bool m_signalConnected; // 用于跟踪是否已连接信号的标志
};

#endif // BOXBRICK_H
