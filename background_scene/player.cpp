#include "player.h"
#include "boxbrick.h"
#include "brokenbrick.h"
#include "normalbrick.h"
#include "coin.h"
#include "score.h"
#include "toxicmushroom.h"
#include "fireflower.h"
#include "bullet.h"
#include "waterpipe.h"
#include <QGraphicsScene>
#include <QList>
#include <qmath.h>
#include <QDebug>

Player::Player(QGraphicsItem *parent):
    QGraphicsPixmapItem(parent),
    isJumping(false),
    stepX(25),
    groundLevel(470),
    jumpTimer(new QTimer(this)),
    velocity(0), // initial velocity
    isBig(false),
    bullet(0)
{
    setPixmap(QPixmap(":/new/dataset/dataset/s_mario_run1_R.png")); // set initial mario pose
    connect(jumpTimer, &QTimer::timeout, this, &Player::jumpStep);
}

void Player::grow() {
    ////new for health////
    //Health::increasement();
    //////////////////////
    if (!isBig) {
        if(!isJumping){
            setPos(x(), y()-35); // reset player's position so that not to be in ground
        }
        setPixmap(QPixmap(":/new/dataset/dataset/mario_R_run1.png"));
        isBig = true;
    }
}

void Player::shrink() {
    if (isBig) {
        if(!isJumping){
            //setting player's position so that not to be in air
            setPos(x(), y()+35);
        }
        setPixmap(QPixmap(":/new/dataset/dataset/s_mario_run1_R.png"));
        isBig = false;
    }
    return;
}

void Player::keyPressEvent(QKeyEvent *event){
    if (event->key() == Qt::Key_Left){
        if(isBig)
            setPixmap(QPixmap(":/new/dataset/dataset/mario_L_run1.png"));
        else
            setPixmap(QPixmap(":/new/dataset/dataset/s_mario_run1_L.png"));
        setPos(x()-stepX, y());
        if (!isJumping) {
            jumpStep();  // Trigger gravity check after movement
        }
    }
    else if (event->key() == Qt::Key_Right){
        if(isBig)
            setPixmap(QPixmap(":/new/dataset/dataset/mario_R_run1.png"));
        else
            setPixmap(QPixmap(":/new/dataset/dataset/s_mario_run1_R.png"));
        setPos(x()+stepX, y());
        if (!isJumping) {
            jumpStep();  // Trigger gravity check after movement
        }
    }
    else if (event->key() == Qt::Key_Space && !isJumping) {
        if(isBig)
            velocity = -20;  // initial jump velocity = -20px
        else
            velocity = -15;  // initial jump velocity = -15px
        isJumping = true;
        jumpTimer->start(20);
    }
    return;
}

void Player::mousePressEvent(QGraphicsSceneMouseEvent *event){
    shoot(event->pos());
}

void Player::shoot(QPointF targetPos) {
    QPointF target = targetPos;
    QPointF start = mapToScene(boundingRect().center());
    qDebug()<<"click pos:("<<target.x()<<","<<target.y()<<")"<<"mario center:("<<start.x()<<","<<start.y()<<")";
    if (bullet > 0) {
        Bullet *fireball = new Bullet();
        fireball->setPos(start); // Start from player's center
        // use a line to calculate degrees to fire
        QLineF ln(start, target);
        int angle = ln.angle(); // angle() defines counter-clockwise is +deg
        fireball->setRotation(-angle); // setRotation(-deg): counter-clockwise deg
        scene()->addItem(fireball);
        bullet--;
        qDebug()<<"remaining bullet:"<<bullet;
    }
    return;
}


void Player::jumpStep() {
    //qDebug()<<t++;
    setPos(x(), y() + velocity);
    jumpTimer->start(20);
    velocity += 1; // 模拟重力影响

    // no jumping during falling
    if (velocity > 0 && !isJumping){
        isJumping = true;
    }

    // get the item collided with the player
    QList<QGraphicsItem* > colliding_items = collidingItems();
    for (int i=0; i < colliding_items.size(); i++){

        // collided with BoxBrick
        if(typeid(*(colliding_items[i])) == typeid(BoxBrick)){
            BoxBrick *boxbrick = dynamic_cast<BoxBrick *>(colliding_items[i]);

            qreal buttomBrick = boxbrick->y() + boxbrick->pixmap().height();
            // check if hit from the bottom
            if(velocity < 0 && y() > boxbrick->y()){
                // stop jumping and start to fall down
                velocity = 0;
                setPos(x(), buttomBrick);
                jumpTimer->stop(); // stop jumping
                boxbrick->handleCollision(); // change to the block brick
                jumpStep(); // start to fall
                break;
            }

            // Check if landing on top of the brick
            if (velocity > 0 && pos().y() + pixmap().height() < boxbrick->y() + boxbrick->pixmap().height()) {
                setPos(x(), boxbrick->y() - pixmap().height());
                velocity = 0;
                isJumping = false;
                jumpTimer->stop();
                break;
            }

            // Check for side collisions
            if (x() < boxbrick->x() + boxbrick->pixmap().width() && x() + pixmap().width() > boxbrick->x()) {
                if (x() < boxbrick->x()) {
                    setPos(boxbrick->x() - pixmap().width(), y());
                    // qDebug()<<"hit left";
                }
                else {
                    setPos(boxbrick->x() + boxbrick->pixmap().width(), y());
                    // qDebug()<<"hit right";
                }
            }
        }
        
        // collided with BrokenBrick
        if (typeid(*(colliding_items[i])) == typeid(BrokenBrick)) {
            BrokenBrick *brokenbrick = dynamic_cast<BrokenBrick *>(colliding_items[i]);

            qreal buttomBrick = brokenbrick->y() + brokenbrick->pixmap().height();
            // Check if hit from the bottom
            if (velocity < 0 && y() > brokenbrick->y()) {
                // stop jumping and start to fall down
                velocity = 0;
                setPos(x(), buttomBrick);
                jumpTimer->stop(); // stop jumping
                brokenbrick->breakBrick(brokenbrick); // broken brick disappear
                jumpStep(); // start to fall
                break;
            }

            if (velocity > 0 && y() + pixmap().height() < brokenbrick->y() + brokenbrick->pixmap().height()) {
                setPos(x(), brokenbrick->y() - pixmap().height());
                velocity = 0;
                isJumping = false;
                jumpTimer->stop();
                break;
            }

            if (x() < brokenbrick->x() + brokenbrick->pixmap().width() && x() + pixmap().width() > brokenbrick->x()) {
                if (x() < brokenbrick->x()) {
                    setPos(brokenbrick->x() - pixmap().width(), y());
                }
                else {
                    setPos(brokenbrick->x() + brokenbrick->pixmap().width(), y());
                }
            }
        }

        // collided with NormalBrick
        if(typeid(*(colliding_items[i])) == typeid(NormalBrick)){
            NormalBrick *normalbrick = dynamic_cast<NormalBrick *>(colliding_items[i]);

            qreal buttomBrick = normalbrick->y() + normalbrick->pixmap().height();
            // check if hit from the bottom
            if(velocity < 0 && y() > normalbrick->y()){
                // stop jumping and start to fall down
                velocity = 0;
                setPos(x(), buttomBrick);
                jumpTimer->stop(); // stop jumping
                normalbrick->handleCollision(); // change to the block brick
                jumpStep(); // start to fall
                break;
            }

            // Check if landing on top of the brick
            if (velocity > 0 && pos().y() + pixmap().height() < normalbrick->y() + normalbrick->pixmap().height()) {
                setPos(x(), normalbrick->y() - pixmap().height());
                velocity = 0;
                isJumping = false;
                jumpTimer->stop();
                break;
            }

            // Check for side collisions
            if (x() < normalbrick->x() + normalbrick->pixmap().width() && x() + pixmap().width() > normalbrick->x()) {
                if (x() < normalbrick->x()) {
                    setPos(normalbrick->x() - pixmap().width(), y());
                }
                else {
                    setPos(normalbrick->x() + normalbrick->pixmap().width(), y());
                }
            }
        }

        // collided with Water Pipe
        if(typeid(*(colliding_items[i])) == typeid(WaterPipe)){
            WaterPipe *waterpipe = dynamic_cast<WaterPipe *>(colliding_items[i]);

            // landing on the top
            if (velocity > 0 && pos().y() + pixmap().height() < waterpipe->y() + waterpipe->pixmap().height()) {
                setPos(x(), waterpipe->y() - pixmap().height());
                velocity = 0;
                isJumping = false;
                jumpTimer->stop();
                break;
            }

            // side collisions
            if (x() < waterpipe->x() + waterpipe->pixmap().width() && x() + pixmap().width() > waterpipe->x()) {
                if (x() < waterpipe->x()) {
                    setPos(waterpipe->x() - pixmap().width(), y());
                    qDebug()<<"hit left";
                }
                else {
                    setPos(waterpipe->x() + waterpipe->pixmap().width(), y());
                    qDebug()<<"hit right";
                }
            }
        }

        // collided with Coin
        if (typeid(*(colliding_items[i])) == typeid(Coin)) {
            Coin *coin = dynamic_cast<Coin*>(colliding_items[i]);
            Score::getInstance()->increase(); // score + 1
            qDebug()<<"a coin";
            coin->deleteCoin(coin);
        }

        // collided with toxic mushroom
        if (typeid(*(colliding_items[i])) == typeid(ToxicMushroom)) {
            ToxicMushroom *toxicmushroom = dynamic_cast<ToxicMushroom *>(colliding_items[i]);
            // jump onto toxic mushroom
            if (isJumping && y() + pixmap().height() > toxicmushroom->y()) {
                toxicmushroom->breakToxicMushroom();
                break;
            }

        }

        // collided with fire flower
        if(typeid(*(colliding_items[i])) == typeid(FireFlower)) {
            FireFlower *fireflower = dynamic_cast<FireFlower*>(colliding_items[i]);
            scene()->removeItem(fireflower); // delete the fire flower
            delete fireflower;

            grow();
            groundLevel = 435;
            bullet = 999; // reset player with 3 ammos
            qDebug()<<"bullet"<<bullet;
        }
    }

    // fall on the ground
    if (y() > groundLevel) {
        if ((x() < 2450 || x() > 2500) &&
            (x() < 3450 || x() > 3500) &&
            (x() < 4300 || x() > 4350) ){
            setPos(x(), groundLevel);
            jumpTimer->stop();
            isJumping = false;
            velocity = 0;
        }
        else if (y() > groundLevel+pixmap().height()){
            qDebug()<<"Die"<<t++;
            setPos(x(), groundLevel+pixmap().height());
            jumpTimer->stop();
            isJumping = false;
            velocity = 0;
        }
    }
    return;
}


