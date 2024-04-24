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
//    void advance(int phase); score跟著遊戲畫面一起動(未完成)
private:
    int score;
    static Score* instance;
};

#endif // SCORE_H

