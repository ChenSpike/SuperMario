#include "health.h"
#include <QFont>
#include <QGraphicsView>
#include <QDebug>

Health* Health::instance = nullptr;

Health::Health(QGraphicsItem *parent):
    QGraphicsTextItem(parent),
    hp(3)
{
    setPlainText(QString("HP: ") + QString::number(hp)); // HP: 3
    setDefaultTextColor(Qt::white);
    setFont(QFont("times", 16));
    instance = this;
}

Health* Health::getInstance() {
    if (!instance)
        instance = new Health();
    return instance;
}

void Health::decrease(){
    hp--;
    setPlainText(QString("HP: ") + QString::number(hp)); // HP: 2
    return;
}

void Health::increase(){
    hp++;
    if(hp > 3){
        hp = 3;
    }
    setPlainText(QString("HP: ") + QString::number(hp)); // HP: 3
    return;
}

int Health::getHealth() const{
    return hp;
}
