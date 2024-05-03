#ifndef SCORE_H
#define SCORE_H

#include <QGraphicsTextItem>

class Score : public QGraphicsTextItem{
public:
    Score(QGraphicsItem *parent = nullptr);
    int getScore() const;
    void updateScoreText();
    static Score* getInstance();
public slots:
    void increase();
private:
    int score;
    static Score* instance;
};

#endif // SCORE_H

