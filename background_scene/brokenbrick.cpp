#include "brokenbrick.h"
#include <QGraphicsScene>
#include <vector>

BrokenBrick::BrokenBrick(const QPixmap& pixmap){
    setPixmap(pixmap);
}
void BrokenBrick::CreateBrokenBricks(QGraphicsScene *scene){
    QVector <BrokenBrick*> BrokenBricks;
    QPixmap BrokenBrickImage(":/new/dataset/dataset/broken brick.png");
    for(int i=0;i<17;i++){
        //Frame 3 Broken Bricks
        if (i==0||i==1){
            BrokenBrick *brokenbrick0 = new BrokenBrick(BrokenBrickImage);
            brokenbrick0 -> setPos((3850+(i*100)),320);
            scene ->addItem(brokenbrick0);
            BrokenBricks.append(brokenbrick0);
        }
        //Frame 4 Broken Bricks
        if (i==2||i==3||i==4||i==5){
            BrokenBrick *brokenbrick1 = new BrokenBrick(BrokenBrickImage);
            brokenbrick1 -> setPos((4900+(i*50)),320);
            scene ->addItem(brokenbrick1);
            BrokenBricks.append(brokenbrick1);
        }
        //Frame 5 Broken Bricks
        if (i==6||i==7||i==8){
            BrokenBrick *brokenbrick2 = new BrokenBrick(BrokenBrickImage);
            brokenbrick2 -> setPos((5300+(100*i)),320);
            scene ->addItem(brokenbrick2);
            BrokenBricks.append(brokenbrick2);
        }
        else{
            continue;
        }
    }
}

void BrokenBrick::breakBrick(){
    // 從場景中移除磚塊
    scene()->removeItem(this);
    // 刪除磚塊以釋放內存
    delete this;
}
