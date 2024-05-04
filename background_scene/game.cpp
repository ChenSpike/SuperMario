#include "game.h"
#include "coin.h"
#include "castle.h"
#include "floorbrick.h"
#include "boxbrick.h"
#include "brokenbrick.h"
#include "normalbrick.h"
#include "waterpipe.h"
#include <QBrush>
#include <QLabel>
#include <QPushButton>
#include <QDebug>

Game::Game(QWidget *parent){
    setStart(); // launch the start screen

    //////////////////// create background scene ////////////////////
    // create a scene
    scene = new QGraphicsScene(this);
    scene -> setSceneRect(0, 0, 7000, 619); // scene original point:(0,0); size:7000x619
    // set the background image
    setBackgroundBrush(QBrush(QImage(":/new/dataset/dataset/background_7000pixel.png")));
    setScene(scene);
    // turn off scroll bars
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    // set the view
    resize(1400, 619); // view size:1400x619
    centerOn(0,0); // view original point:(0,0)

    // include the score
    score = new Score;
    scene -> addItem(score);

    // include the health
    health = new Health;
    health -> setPos(health->x() + 200, health->y());
    scene -> addItem(health);
    ///////////////////////////////////////////////////////////

    //////////////////// create the player ////////////////////
    mario = new Player();
    mario -> setPos(250,470); // TODO generalize to always be in the middle bottom of screen
    // make the player focusable and set it to be the current focus
    mario -> setFlag(QGraphicsItem::ItemIsFocusable);
    mario -> setFocus();
    scene -> addItem(mario);
    ///////////////////////////////////////////////////////////

    //////////////////// create items ////////////////////
    Coin::CreateCoins(scene); // coins
    Castle::CreateCastle(scene); // a castle
    FloorBrick::CreateFloorBricks(scene); // floor bricks
    BoxBrick::CreateBoxBricks(scene); // box bricks
    BrokenBrick::CreateBrokenBricks(scene); // broken bricks
    NormalBrick::CreateNormalBricks(scene); // normal bricks w/ and w/o coins
    WaterPipe::CreateWaterPipes(scene); // water pipes
    //////////////////////////////////////////////////////
}

void Game::mousePressEvent(QMouseEvent *event){
    QPointF target = mapToScene(event->pos());
    mario->shoot(target);
    return;
}

void Game::keyPressEvent(QKeyEvent *event){
    QGraphicsView::keyPressEvent(event);
    qreal marioMidPos = mario->x() + (mario->pixmap().width())/2;
    auto rect = scene->sceneRect();
    if (mario->x() < rect.x()){
        mario->setPos(rect.x(), mario->y());
        return;
    }
    if (marioMidPos > 700 && marioMidPos < 6300){
        if (marioMidPos - rect.x() > 700){
            // view shift right
            rect.translate(mario->stepX,0);
            scene->setSceneRect(rect);
            // Score and Health shift right
            score->setPos(rect.x(),0);
            health->setPos(rect.x() + 200,0);
        }
    }
    return;
}

void Game::setStart(){
    //////////////////// create start screen ////////////////////
    // Create start window
    start = new QDialog();
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

    // start button is trigged by mouse click
    QObject::connect(startbutton, &QPushButton::clicked, this, &Game::closeStart);
    start->exec(); // show the start dialog
}

void Game::closeStart(){
    start->close(); // After clicking, close the start screen
}
