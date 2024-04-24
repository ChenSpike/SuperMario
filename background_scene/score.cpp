#include "score.h"
#include <QFont>
#include <QGraphicsView>

int Score::currentScore = 0;

Score::Score(QGraphicsItem *parent) : QGraphicsTextItem(parent){
    setPlainText(QString("Score: ") + QString::number(currentScore)); // Score: 0
    setDefaultTextColor(Qt::white);
    setFont(QFont("times", 16));
}

void Score::increase(){
    // increase the score and show it
    currentScore++;
    setPlainText(QString("Score: ") + QString::number(currentScore));
}


int Score::getScore() const{
    // return current score
    return currentScore;
}

/*
void Score::advance(int phase){
    // 在场景更新时，将Score对象的位置设置为视图的左上角
    if (!phase) {
        QGraphicsView *view = qobject_cast<QGraphicsView *>(scene()->views().first());
        if (view) {
            QPointF viewTopLeft = view->mapToScene(0, 0);
            setPos(viewTopLeft);
        }
    }
}*/
