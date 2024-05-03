#include "game.h"
#include "coin.h"
#include "castle.h"
#include "floorbrick.h"
#include "boxbrick.h"
#include "brokenbrick.h"
#include "normalbrick.h"
#include "waterpipe.h"
#include <QObject>
#include <QBrush>

using namespace std;

Game::Game(QWidget *parent){
    //////////////////// create background scene ////////////////////
    // create a scene
    scene = new QGraphicsScene();
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

    // create the score
    score = new Score;
    scene -> addItem(score);
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
    /////////////////////////////////////////////////////////////////
}

void Game::mousePressEvent(QMouseEvent *event){
    mario->mousePressEvent(event);
}

void Game::keyPressEvent(QKeyEvent *event){
    mario->keyPressEvent(event);
    qreal marioWidth = mario->pixmap().width();
    auto rect = scene->sceneRect();
    if (mario->x() < rect.x()){
        mario->setPos(rect.x(), mario->y());
        return;
    }
    if (mario->x() + marioWidth/2 > 700 && mario->x() < 6300){
        if (mario->x() - rect.x() > 700){
            // view shift right
            rect.translate(mario->stepX,0);
            scene->setSceneRect(rect);
            // Score shift right
            score->setPos(rect.x(),0);
        }
    }
    return;
}
