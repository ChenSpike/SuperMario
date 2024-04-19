#include "boxbrick.h"
#include "stonebrick.h"
#include <QGraphicsScene>

BoxBrick::BoxBrick(const QPixmap& pixmap){
    setPixmap(pixmap);
}

void BoxBrick::CreateBoxBricks(QGraphicsScene *scene){
    QPixmap BoxBrickImage(":/new/dataset/dataset/box brick.png");
    BoxBrick *boxbrick = new BoxBrick(BoxBrickImage);
    for (int i = 0; i < 140;i++){
        if (i == 8||i==15||i==35||i==65||i==70||i==90){
            boxbrick -> setPos(i*50, 400);
            scene ->addItem(boxbrick);
        }
        continue;
    }

}
