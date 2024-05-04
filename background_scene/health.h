#ifndef HEALTH_H
#define HEALTH_H

#include <QGraphicsTextItem>

class Health : public QGraphicsTextItem{
public:
    Health(QGraphicsItem *parent = nullptr);
    int getHealth() const;
    void updateHealthText();
    static Health* getInstance();
    void increase();
    void decrease();
private:
    int hp;
    static Health* instance;

};

#endif // HEALTH_H
