#include "mainwindow.h"
#include "score.h"
#include "floorbrick.h"
#include "normalbrick.h"
#include "game.h"
#include "boxbrick.h"
#include "coin.h"
#include "waterpipe.h"
#include "castle.h"
#include "player.h"
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
#include <QLabel>
#include <QMouseEvent>
#include <QDebug>

void mousePressEvent(QMouseEvent *event);

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
     //////////////////// create start screen ////////////////////
    //create start window
    QDialog start;
    start.setWindowTitle("Start the Game");
    //Add Start Screen Image
    QPixmap startscreenimage(":/new/dataset/dataset/start_screen.png");
    QLabel startlabel(&start);
    startlabel.setPixmap(startscreenimage);
    startlabel.setGeometry(0,0,startscreenimage.width(),startscreenimage.height());

    //push button to start the game
    QPushButton startbutton("", &start);
    QPixmap startbuttonimage(":/new/dataset/dataset/start_btn.png");
    startbutton.setIcon(QIcon(startbuttonimage));
    startbutton.setIconSize(startbuttonimage.size()); //icon 和 screen的照片設置方法不一樣
    startbutton.setGeometry(435,455,startbuttonimage.width(),startbuttonimage.height());
    //設置start button的觸發方式是用鼠標click
    QObject::connect(&startbutton, &QPushButton::clicked, [&](){
    //觸發完click後，關閉start screen
    start.close();
    ///////////////////////////////////////////////////////////

        //////////////////// create background scene ////////////////////
        //create a scene
        QGraphicsScene *scene = new QGraphicsScene();

        // load background image
        QPixmap pixmap(":/new/dataset/dataset/background_7000pixel.png");
        //"":insert image's path

        // add the image to the scene
        QGraphicsPixmapItem* background = scene ->addPixmap(pixmap);
        background -> setPos(0,0);

        // create coins
        Coin::CreateCoins(scene);

        // create the score
        Score *score = new Score;
        scene -> addItem(score);
        //add castle
        Castle::CreateCastle(scene);
        ///////////////////////////////////////////////////////////

        //////////////////// create the player ////////////////////
        Player *mario = new Player();
        mario->setPos(250,470); // TODO generalize to always be in the middle bottom of screen
        // make the player focusable and set it to be the current focus
        mario->setFlag(QGraphicsItem::ItemIsFocusable);
        mario->setFocus();
        scene ->addItem(mario);
        ///////////////////////////////////////////////////////////

        //////////////////// create bricks and pipes ////////////////////
        FloorBrick::CreateFloorBricks(scene); // floor bricks
        BoxBrick::CreateBoxBricks(scene); // box bricks
        BrokenBrick::CreateBrokenBricks(scene); // broken bricks
        NormalBrick::CreateNormalBricks(scene); //normal bricks without coins
        WaterPipe::CreateWaterPipes(scene); // water pipes
        /////////////////////////////////////////////////////////////////

        //////////////////// view //////////////////////////////////
        // visualize (view)
        QGraphicsView *view = new QGraphicsView(scene);
        // set the view size and initial position: (0,0)
        view -> setFixedSize(1400,619);
        view -> move(0,0); // view position
        view -> show();
        ////////////////////////////////////////////////////////////

    });

    start.exec(); //show the start dialog

    return a.exec();
}

void mousePressEvent(QMouseEvent *event){
    qDebug()<<"left click";
}
