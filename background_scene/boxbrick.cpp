#include "boxbrick.h"
#include "stonebrick.h"
#include <QGraphicsScene>

BoxBrick::BoxBrick(const QPixmap& pixmap){
    setPixmap(pixmap);
}

void BoxBrick::CreateBoxBricks(QGraphicsScene *scene){
    BoxBrick *boxbrick = new BoxBrick(QPixmap(":/new/dataset/dataset/box brick.png"));
    for (int i = 0; i < 140;i++){
        if (i == 8||i==15||i==35||i==65||i==70||i==90){
            boxbrick -> setPos(i*50, 400);
            scene ->addItem(boxbrick);
        }
        continue;
    }

}

void BoxBrick::collide(){
    QList<QGraphicsItem*> collidingItemsList = collidingItems();
    foreach(QGraphicsItem* item, collidingItemsList) {
        if (dynamic_cast<BoxBrick*>(item)) {
            // Replace box brick to stone brick
            StoneBrick* stoneBrick = new StoneBrick(QPixmap(":/new/dataset/dataset/stone brick.png"));
            stoneBrick->setPos(pos());
            scene()->addItem(stoneBrick);

            // Remove BoxBrick from scene
            scene()->removeItem(this);
            delete this;

            return; // No need to continue searching for collisions
        }
    }
}
