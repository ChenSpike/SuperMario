#include "score.h"
#include <QFont>
#include <QGraphicsView>

Score* Score::instance = nullptr;

Score::Score(QGraphicsItem *parent) : QGraphicsTextItem(parent), score(0){
    setPlainText(QString("Score: ") + QString::number(score)); // Score: 0
    setDefaultTextColor(Qt::white);
    setFont(QFont("times", 16));
    instance = this;
}

Score* Score::getInstance() {
    if (!instance)
        instance = new Score();
    return instance;
}

void Score::increase(){
    qDebug()<<"increase";
    score++;
    setPlainText(QString("Score: ") + QString::number(score));
    return;
}

int Score::getScore() const{
    return score;
}
