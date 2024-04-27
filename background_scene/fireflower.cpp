#include "fireflower.h"

FireFlower::FireFlower(QGraphicsItem *parent):
    QGraphicsPixmapItem(parent),
    initialY(0),
    finalY(0),
    bounceHeight(30),
    bounceStep(-10),
    bounceTimer(new QTimer(this))
{
    // Set the pixmap to fire flower image
    setPixmap(QPixmap(":/new/dataset/dataset/Fire Flower.png"));
    connect(bounceTimer, &QTimer::timeout, this, &FireFlower::bounce);
}

void FireFlower::setBounce(qreal boxBrickY) {
    initialY = y(); // set initial y position
    finalY = boxBrickY; // set landing Y position
    bounceTimer->start(20); // start bounce timer
    return;
}

void FireFlower::bounce() {
    setPos(x(), y() + bounceStep);
    if (bounceStep < 0 && y() <= initialY - bounceHeight) {
        bounceStep = 10; // change direction after reaching height limit
    }
    else if (bounceStep > 0 && y() >= finalY) {
        // stop timer when landing on final y position
        bounceTimer->stop();
        bounceStep = -10;
        setPos(x(), finalY);
    }
    return;
}
