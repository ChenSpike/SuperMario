#ifndef VIEW_H
#define VIEW_H

#include <QGraphicsScene>
#include <QGraphicsView>

class view : public QGraphicsView {
public:
    view(QGraphicsScene *scene);
    QGraphicsView View;
};

#endif // VIEW_H
