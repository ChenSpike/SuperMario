#include "floorbrick.h"

FloorBrick::FloorBrick(const QPixmap& pixmap){
    setPixmap(pixmap);
}

void FloorBrick::CreateFloorBricks(QGraphicsScene *scene){
    QPixmap FloorBrickImage(":/new/dataset/dataset/floor brick.png");
    //floor brick image path
    for (int j=0;j<140;j++){
        if (j == 15||j==16||j==45||j==46||j==80||j==81){
            continue;
        }//use "if loop" to make three holes (100 pixels width/hole)
        FloorBrick *brick = new FloorBrick(FloorBrickImage);
        brick -> setPos(j*50,520);//floor brick width = 50 pixel
        scene -> addItem(brick);
    }
}
