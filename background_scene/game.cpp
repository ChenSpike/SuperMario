#include "game.h"
#include "coin.h"
#include "castle.h"
#include "floorbrick.h"
#include "boxbrick.h"
#include "brokenbrick.h"
#include "normalbrick.h"
#include "waterpipe.h"
#include <iostream>
#include <QTimer>
#include <QObject>
#include <QScrollArea>
#include <QScrollBar>
#include <QBrush>

using namespace std;

Game::Game(QWidget *parent){
    //////////////////// create background scene ////////////////////
    //create a scene
    scene = new QGraphicsScene();
    scene -> setSceneRect(0, 0, 7000, 619);
    setBackgroundBrush(QBrush(QImage(":/new/dataset/dataset/background_7000pixel.png")));
    setScene(scene);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    resize(1400, 619);
    centerOn(0,0);


    /// concise codes ///
    // set the background image
    // QPixmap backgroundImage(":/new/dataset/dataset/background_7000pixel.png");
    // scene -> addPixmap(backgroundImage);
    /////////////////////

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
    mario -> setPos(250,470); // TODO generalize to always be in the middle bottom of screen
    // make the player focusable and set it to be the current focus
    mario -> setFlag(QGraphicsItem::ItemIsFocusable);
    mario -> setFocus();
    scene -> addItem(mario);
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
    // view = new QGraphicsView(scene);
    // Disable scroll bars
    // view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    // view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    // set the view size and initial position: (0,0)
    // view->setFixedSize(1400,619);
    // view->setSceneRect(scene->sceneRect());
    // view->horizontalScrollBar()->setValue(0);
    // view->viewport()->scroll(-2000,0);
    // qDebug()<<"moving back";
    // // view->viewport()->setX(0);
    // // view->viewport()->setY(0);
    // // Track player's position and scroll the view
    timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()), this, SLOT(ScrollEvent()));
    timer->start(100);

    // view -> show();
    // ////////////////////////////////////////////////////////////
    int sceneX = x();
    QPointF marioX;
    qDebug()<<"view :"<<this->size()<<"mario x:"<<mario->x();

    show();
}

void Game::ScrollEvent() {
    // int leftValue = view->horizontalScrollBar()->value();
    // int viewWidth = view->viewport()->width();
    // int viewCenterX = leftValue + viewWidth / 2;
    // QRectF marioRect = mario->boundingRect();
    // int playerCenterX = mario->pos().x() + marioRect.width() / 2;
    // int scrollThreshold = viewWidth / 18; // 讓mario維持在畫面中間
    // int scrollSpeed = 50; // 捲軸移動速度

    // if ((playerCenterX < viewCenterX - scrollThreshold) && (leftValue > 0)) {
    //     // Mario is too far left, scroll right
    //     int autoScrollPosition = leftValue - scrollSpeed;
    //     cout << "autoScroll " << autoScrollPosition << endl;
    //     view->horizontalScrollBar()->setValue(autoScrollPosition);
    //     qDebug()<<"moving right";
    // }

    // else if (playerCenterX > viewCenterX + scrollThreshold) {
    //     //Mario is too far right, scroll left
    //     int autoScrollPosition = leftValue + scrollSpeed;
    //     cout << "autoScroll " << autoScrollPosition << endl;
    //     view->horizontalScrollBar()->setValue(autoScrollPosition);
    //     qDebug()<<"moving left";

    // }

    qDebug()<<"view x:"<<this->x()<<"mario x:"<<mario->x();

}


void Game::mousePressEvent(QMouseEvent *event){
    qDebug()<<"click"<<c++;
    mario->mousePressEvent(event);
}

void Game::keyPressEvent(QKeyEvent *event){
    mario->keyPressEvent(event);
    qDebug()<<"mario x:"<<mario->x();
    auto rect = scene->sceneRect();
    if (mario->x() < rect.x()){
        qDebug()<<"set mario"<<rect.x();
        mario->setPos(rect.x(), mario->y());
        return;
    }
    if (mario->x() > 700 && mario->x() < 6300){
        if (mario->x() - rect.x() > 700){
            qDebug()<<"view x:"<<rect.x();
            rect.translate(mario->stepX,0);
            scene->setSceneRect(rect);
        }
    }
    return;
}
