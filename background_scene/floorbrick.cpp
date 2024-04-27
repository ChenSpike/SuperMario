#include "floorbrick.h"
#include <vector>

FloorBrick::FloorBrick(const QPixmap& pixmap){
    setPixmap(pixmap);
}

void FloorBrick::CreateFloorBricks(QGraphicsScene *scene){
    //floor brick image path
    QPixmap FloorBrickImage(":/new/dataset/dataset/floor brick.png");
    //floor brick pointer vector
    QVector <FloorBrick*> floorbricks;
    for (int j=0;j<140;j++){
        if (j == 49||j==50||j==69||j==70||j==86||j==87){
            continue;
        }//use "if loop" to make three holes (100 pixels width/hole)
        FloorBrick *brick = new FloorBrick(FloorBrickImage);
        brick -> setPos(j*50,519);//floor brick width = 50 pixel
        scene -> addItem(brick);
        floorbricks.append(brick);
    }
}
