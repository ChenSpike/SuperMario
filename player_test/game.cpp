#include "game.h"
#include <QTimer>
#include <QGraphicsTextItem>
#include <QFont>
#include <QBrush>
#include <QImage>

Game::Game(QWidget *parent){
    // create the scene
    scene = new QGraphicsScene();
    scene->setSceneRect(0,0,800,600); // make the scene 800x600 instead of infinity by infinity (default)
    setBackgroundBrush(QBrush(QImage(":/images/bg.png")));

    //load background image
    QPixmap pixmap("/Users/sophiawannnsmacbookair/Downloads/background_7000pixel");
    //"":insert image's path

    //add the image to the scene
    QGraphicsPixmapItem* item = scene ->addPixmap(pixmap);
    //visualize (view)
    QGraphicsView* view = new QGraphicsView(scene);

    // make the newly created scene the scene to visualize (since Game is a QGraphicsView Widget,
    // it can be used to visualize scenes)
    setScene(scene);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    // create the player
    mario = new Player();
    mario->setPos(400,500); // TODO generalize to always be in the middle bottom of screen
    // make the player focusable and set it to be the current focus
    mario->setFlag(QGraphicsItem::ItemIsFocusable);
    mario->setFocus();

    //set the view size
    view -> setFixedSize(1400,620);
    // add the player to the scene
    scene->addItem(mario);

    show();
}
