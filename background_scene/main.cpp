#include "mainwindow.h"
#include "floorbrick.h"
#include "player.h"
#include "game.h"
#include "boxbrick.h"
#include "coin.h"
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
    // create a scene
    QGraphicsScene *scene = new QGraphicsScene();

    // load background image
    QPixmap pixmap(":/new/dataset/dataset/background_7000pixel.png");
    //"":insert image's path

    // add the image to the scene
    QGraphicsPixmapItem* background = scene ->addPixmap(pixmap);
    background -> setPos(0,0);

    // create the player
    Player *mario = new Player();
    mario->setPos(200,450); // TODO generalize to always be in the middle bottom of screen
    // make the player focusable and set it to be the current focus
    mario->setFlag(QGraphicsItem::ItemIsFocusable);
    mario->setFocus();
    scene ->addItem(mario);

    // add floor brick item
    FloorBrick::CreateFloorBricks(scene);

    // Create a BoxBrick
    BoxBrick *boxBrick = new BoxBrick(scene);
    boxBrick->setPos(500, 350); // Set position of the box brick
    scene->addItem(boxBrick);

    // connect collision handling signal for player
    QObject::connect(mario, &Player::collidedWithBoxBrick, boxBrick, &BoxBrick::handleCollision);

    // visualize (view)
    QGraphicsView *view = new QGraphicsView(scene);

    // set the view size
    view -> setFixedSize(1400,620);
    view -> show();


    return a.exec();
}
