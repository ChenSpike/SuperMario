#include "mainwindow.h"
#include "floorbrick.h"
#include "player.h"
#include "game.h"
#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsPixmapItem>
#include <QTimer>
#include <QGraphicsTextItem>
#include <QFont>
#include <QBrush>
#include <QImage>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //create a scene
    QGraphicsScene *scene = new QGraphicsScene();

    //load background image
    QPixmap pixmap("/Users/sophiawannnsmacbookair/Downloads/background_7000pixel");
    //"":insert image's path

    //add the image to the scene
    QGraphicsPixmapItem* item = scene ->addPixmap(pixmap);

    // create the player
    mario = new Player();
    mario->setPos(400,500); // TODO generalize to always be in the middle bottom of screen
    // make the player focusable and set it to be the current focus
    mario->setFlag(QGraphicsItem::ItemIsFocusable);
    mario->setFocus();
    scene ->addItem(mario);

    //add floor brick item
    QPixmap FloorBrickImage("/Users/sophiawannnsmacbookair/Downloads/floor brick.png");
    //floor brick image path
    for (int x=0;x<139;x++){
        if (x == 15||16||45||46||80||81){
            continue;
        }//use "if loop" to make three holes (100 pixels width/hole)
        FloorBrick* brick = new FloorBrick(FloorBrickImage);
        brick -> setPos(x*50,0);//floor brick width = 50 pixel
        scene -> addItem(brick);
    }

    //visualize (view)
    //set the view size
    view -> setFixedSize(1400,620);
    view -> show();


    return a.exec();
}
