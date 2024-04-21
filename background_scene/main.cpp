#include "mainwindow.h"
#include "floorbrick.h"
#include "stonebrick.h"
#include "boxbrick.h"
#include "player.h"
#include "game.h"
#include "boxbrick.h"
#include "coin.h"
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

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

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
    startbutton.setIconSize(startbuttonimage.size());//icon 和 screen的照片設置方法不一樣
    startbutton.setGeometry(435,455,startbuttonimage.width(),startbuttonimage.height());
    //設置start button的觸發方式是用鼠標click
    QObject::connect(&startbutton, &QPushButton::clicked, [&](){
        //觸發完click後，關閉start screen
        start.close();

        //create a scene
        QGraphicsScene *scene = new QGraphicsScene();

        // load background image
        QPixmap pixmap(":/new/dataset/dataset/background_7000pixel.png");
        //"":insert image's path

        // add the image to the scene
        QGraphicsPixmapItem* background = scene ->addPixmap(pixmap);
        background -> setPos(0,0);

        //////////////////// create the player ////////////////////
        Player *mario = new Player();
        mario->setPos(200,450); // TODO generalize to always be in the middle bottom of screen
        // make the player focusable and set it to be the current focus
        mario->setFlag(QGraphicsItem::ItemIsFocusable);
        mario->setFocus();
        scene ->addItem(mario);
        ///////////////////////////////////////////////////////////

        // create floor bricks
        FloorBrick::CreateFloorBricks(scene);

        //////////////////// create box bricks ////////////////////
    //    BoxBrick *boxBrick = new BoxBrick(scene);
    //    boxBrick->setPos(500, 350); // Set position of the box brick
    //    scene->addItem(boxBrick);

        // connect collision handling signal for player
    //    QObject::connect(mario, &Player::collidedWithBoxBrick, boxBrick, &BoxBrick::handleCollision);

        //add box brick item (要再加collide())
        BoxBrick::CreateBoxBricks(scene);
        // 遍历场景中的所有项目
        for (auto item : scene->items()) {
            // 检查是否是 BoxBrick 类型的项目
            if (auto boxBrick = dynamic_cast<BoxBrick*>(item)) {
                // 检查是否已经连接过信号
                if (!boxBrick->isSignalConnected()) {
                    // 连接 mario 的 collidedWithBoxBrick 信号到 box brick 的 handleCollision 槽函数
                    QObject::connect(mario, &Player::collidedWithBoxBrick, boxBrick, &BoxBrick::handleCollision);
                    // 标记为已连接信号
                    boxBrick->setSignalConnected(true);
                }
            }
        }
        //QObject::connect(mario, &Player::collidedWithBoxBrick, BoxBrick::handleCollision);

        //////////////////////////////////////////////////////////

        //add broken brick item
        BrokenBrick::CreateBrokenBricks(scene);

        // visualize (view)
        QGraphicsView *view = new QGraphicsView(scene);

        // set the view size
        view -> setFixedSize(1400,620);
        view -> show();
    });

    start.exec(); //show the start dialog

    return a.exec();
}
