#include "health.h"
#include <QDebug>
#include <QFont>
#include <QGraphicsView>
#include <QGraphicsTextItem>

Health::Health()
{
}

int Health::count = 3;

int Health::decreasement(){
    count--;
    qDebug() <<"health decreases to " << count <<Qt::endl;
    return count;
}

int Health::increasement(){
    count++;
    if(count >3){
        count = 3;
    }
    qDebug() <<"health increases to " << count <<Qt::endl;
    return count;
}
