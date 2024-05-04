#include "brokenbrick.h"
#include <QGraphicsScene>

QVector<BrokenBrick*> BrokenBrick::BrokenBricks;

BrokenBrick::BrokenBrick(const QPixmap& pixmap){
    setPixmap(pixmap);
}

void BrokenBrick::CreateBrokenBricks(QGraphicsScene *scene){
    QPixmap BrokenBrickImage(":/new/dataset/dataset/broken brick.png");
    BrokenBrick *newBrokenBrick;
    for(int i=0;i<9;i++){
        //Frame 3 Broken Bricks
        if (i<=1){
            newBrokenBrick = new BrokenBrick(BrokenBrickImage);
            newBrokenBrick -> setPos((3850+(i*100)),320);
        }
        //Frame 4 Broken Bricks
        else if (i>=2 && i<=5){
            newBrokenBrick = new BrokenBrick(BrokenBrickImage);
            newBrokenBrick -> setPos((4900+(i*50)),320);
        }
        //Frame 5 Broken Bricks
        else{
            newBrokenBrick = new BrokenBrick(BrokenBrickImage);
            newBrokenBrick -> setPos((5300+(100*i)),320);
        }
        scene -> addItem(newBrokenBrick);
        BrokenBricks.append(newBrokenBrick);
    }

    // test for mushroom
    // newBrokenBrick = new BrokenBrick(BrokenBrickImage);
    // newBrokenBrick -> setPos(950,470);
    // scene -> addItem(newBrokenBrick);
    // BrokenBricks.append(newBrokenBrick);

    return;
}

void BrokenBrick::breakBrick(BrokenBrick *brokenbrick){
    // delete the break brick
    scene()->removeItem(brokenbrick);
    QVector<BrokenBrick*>::iterator i = BrokenBricks.begin();
    while(i != BrokenBricks.end()){
        if(*i == brokenbrick){
            i = BrokenBricks.erase(i);
        }
        else{
            i++;
        }
    }
    delete brokenbrick;
    return;
}
