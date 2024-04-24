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
    score++;
    setPlainText(QString("Score: ") + QString::number(score));
}


int Score::getScore() const{
    return score;
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
