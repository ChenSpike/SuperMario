#include "mainwindow.h"
#include "floorbrick.h"
#include "stonebrick.h"
#include "boxbrick.h"
#include "player.h"
#include "game.h"
#include "brokenbrick.h"
#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsPixmapItem>
#include <QTimer>
#include <QGraphicsTextItem>
#include <QDialog>
#include <QPushButton>
#include <QFont>
#include <QBrush>
#include <QImage>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //create start window
    QDialog start;
    start.setWindowTitle("Start the Game");
    //push button to start the game
    QPushButton startbutton("Start Game", &start);
    startbutton.setGeometry(50,50,200,50);
    //connect button click signal to start the game
    QObject::connect(&startbutton, &QPushButton::clicked, [&](){
    start.close();
    //create a scene
    QGraphicsScene *scene = new QGraphicsScene();

    //load background image
    QPixmap pixmap(":/new/dataset/dataset/background_7000pixel.png");
    //"":insert image's path

    //add the image to the scene
    QGraphicsPixmapItem* background = scene ->addPixmap(pixmap);
    background -> setPos(0,0);

    // create the player
    Player *mario = new Player();
    mario->setPos(200,450); // TODO generalize to always be in the middle bottom of screen
    // make the player focusable and set it to be the current focus
    mario->setFlag(QGraphicsItem::ItemIsFocusable);
    mario->setFocus();
    scene ->addItem(mario);

    //add floor brick item
    FloorBrick::CreateFloorBricks(scene);

    //add box brick item (要再加collide())
    BoxBrick::CreateBoxBricks(scene);

    //add broken brick item
    BrokenBrick::CreateBrokenBricks(scene);

    //visualize (view)
    QGraphicsView *view = new QGraphicsView(scene);

    //set the view size
    view -> setFixedSize(1400,620);
    view -> show();
    });

    start.exec(); //show the start dialog

    return a.exec();
}
