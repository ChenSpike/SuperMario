#include "brokenbrick.h"
#include <QGraphicsScene>

BrokenBrick::BrokenBrick(const QPixmap& pixmap){
    setPixmap(pixmap);
}
void BrokenBrick::CreateBrokenBricks(QGraphicsScene *scene){
    QPixmap BrokenBrickImage(":/new/dataset/dataset/broken brick.png");
    BrokenBrick *brokenbrick1 = new BrokenBrick(BrokenBrickImage);
    brokenbrick1 -> setPos(350,400);
    scene ->addItem(brokenbrick1);
}

void BrokenBrick::breakBrick(){
    // 從場景中移除磚塊
    scene()->removeItem(this);
    // 刪除磚塊以釋放內存
    delete this;
}
