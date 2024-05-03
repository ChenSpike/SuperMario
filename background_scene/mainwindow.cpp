#include "mainwindow.h"
#include <iostream>
#include <QTimer>
#include <QObject>
#include <QScrollArea>
#include <QScrollBar>
#include <QRectF>
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
#include <QDebug>
#include <QScrollArea>
#include <QRectF>
#include <QScrollBar>

using namespace std;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    //////////////////// create start screen ////////////////////
    // Create start window
    QDialog* start = new QDialog();
    start->setWindowTitle("Start the Game");

    // Add Start Screen Image
    QPixmap startscreenimage(":/new/dataset/dataset/start_screen.png");
    QLabel* startlabel = new QLabel(start);
    startlabel->setPixmap(startscreenimage);
    startlabel->setGeometry(0, 0, startscreenimage.width(), startscreenimage.height());

    // Push button to start the game
    QPushButton* startbutton = new QPushButton("", start);
    QPixmap startbuttonimage(":/new/dataset/dataset/start_btn.png");
    startbutton->setIcon(QIcon(startbuttonimage));
    startbutton->setIconSize(startbuttonimage.size()); // icon 和 screen 的照片設置方法不一樣
    startbutton->setGeometry(435, 455, startbuttonimage.width(), startbuttonimage.height());
    // 設置start button的觸發方式是用鼠標click
    QObject::connect(startbutton, &QPushButton::clicked, [=]() {
        // 觸發完click後，關閉start screen
        start->close();
        CreateElements();
    });

    start->exec(); // show the start dialog
}

void MainWindow::CreateElements() {
    //////////////////// create background scene ////////////////////
    //create a scene
    scene = new QGraphicsScene();
    scene->setSceneRect(0, 0, 7000, 619);
    // StartScreen();
    // load background image
    QPixmap pixmap(":/new/dataset/dataset/background_7000pixel.png");
    //"":insert image's path
    // add the image to the scene
    QGraphicsPixmapItem* background = scene ->addPixmap(pixmap);


    // create coins
    Coin::CreateCoins(scene);
    // create the score
    score = new Score;
    scene -> addItem(score);
    //add castle
    Castle::CreateCastle(scene);
    ///////////////////////////////////////////////////////////

    //////////////////// create the player ////////////////////
    mario = new Player();
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
    view = new QGraphicsView(scene);
    // Disable scroll bars
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    // set the view size and initial position: (0,0)
    view->setFixedSize(1400,619);
    view->setSceneRect(scene->sceneRect());
    view->horizontalScrollBar()->setValue(0);
    view->viewport()->scroll(-2000,0);
    qDebug()<<"moving back";
    // view->viewport()->setX(0);
    // view->viewport()->setY(0);
    // Track player's position and scroll the view
    QTimer *timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()), this, SLOT(ScrollEvent()));
    timer->start(100);

    view -> show();
    ////////////////////////////////////////////////////////////
}

void MainWindow::ScrollEvent() {
    int leftValue = view->horizontalScrollBar()->value();
    int viewWidth = view->viewport()->width();
    int viewCenterX = leftValue + viewWidth / 2;
    QRectF marioRect = mario->boundingRect();
    int playerCenterX = mario->pos().x() + marioRect.width() / 2;
    int scrollThreshold = viewWidth / 18; // 讓mario維持在畫面中間
    int scrollSpeed = 50; // 捲軸移動速度

    if ((playerCenterX < viewCenterX - scrollThreshold) && (leftValue > 0)) {
        // Mario is too far left, scroll right
        int autoScrollPosition = leftValue - scrollSpeed;
        cout << "autoScroll " << autoScrollPosition << endl;
        view->horizontalScrollBar()->setValue(autoScrollPosition);
        qDebug()<<"moving right";
    }

    else if (playerCenterX > viewCenterX + scrollThreshold) {
        //Mario is too far right, scroll left
        int autoScrollPosition = leftValue + scrollSpeed;
        cout << "autoScroll " << autoScrollPosition << endl;
        view->horizontalScrollBar()->setValue(autoScrollPosition);
        qDebug()<<"moving left";

    }
    //hp->setPos(view->horizontalScrollBar()->value()+100,10);
    score->setPos(view->horizontalScrollBar()->value()+50,10);
    // else if (leftValue == 0){
    //     view->setAlignment(Qt::AlignLeft | Qt::AlignTop);
    //     view->horizontalScrollBar()->setValue(0);
    // }
}

void MainWindow::GameOver(){
    // if (mario->pos().y()>600){
    //     Player::MarioDie();
    //     //Gameover Dialog

    // }
    // //else if (hp==0){}
    // //else if (score){}

    // else{
    //     break;
    // }
    return;
}

int c=0;
void MainWindow::mousePressEvent(QMouseEvent *event){
    qDebug()<<"click"<<c++;
}

MainWindow::~MainWindow()
{
}

