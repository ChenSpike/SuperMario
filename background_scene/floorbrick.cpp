#include "floorbrick.h"

QVector<FloorBrick*> FloorBrick::FloorBricks;

FloorBrick::FloorBrick(const QPixmap& pixmap){
    setPixmap(pixmap);
    // create a rectangle of size 50x50
    floorbrickRect = QRect(0, 0, pixmap.width(), pixmap.height());
    setPos(floorbrickRect.center() - QPointF(pixmap.width() / 2, pixmap.height() / 2));

}

void FloorBrick::CreateFloorBricks(QGraphicsScene *scene){
    //floor brick image path
    QPixmap FloorBrickImage(":/new/dataset/dataset/floor brick.png");
    FloorBrick *newFloorBrick;
    for (int j=0;j<140;j++){
        if (j == 49||j==50||j==69||j==70||j==86||j==87){
            continue;
        }//use "if loop" to make three holes (100 pixels width/hole)
        newFloorBrick = new FloorBrick(FloorBrickImage);
        newFloorBrick -> setPos(j*50,519);//floor brick width = 50 pixel
        scene -> addItem(newFloorBrick);
        FloorBricks.append(newFloorBrick);
    }
    return;
}
