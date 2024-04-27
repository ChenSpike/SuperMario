#include "castle.h"
#include <QGraphicsScene>
#include <QPixmap>

Castle::Castle(const QPixmap& pixmap) {
    setPixmap(pixmap);
}
void Castle::CreateCastle(QGraphicsScene* scene){
    QPixmap CastleImage(":/new/dataset/castle.png");
    Castle *castle = new Castle(CastleImage);
    castle -> setPos(6800,370);
    scene ->addItem(castle);
}
