#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "player.h"
#include <QDebug>
#include <QGraphicsView>

MainWindow::MainWindow(QWidget *parent):
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

int k=0;
void MainWindow::mousePressEvent(QMouseEvent *event){
    qDebug()<<"left click"<<k++;
    // Calculate target position based on click coordinates
    // QPointF target = mapToScene(event->pos());

    // Iterate over all items in the scene and find the Player object
    QList<QGraphicsItem *> items = scene->items();
    for (QGraphicsItem *item : items) {
        if (Player *player = dynamic_cast<Player *>(item)) {
            // If Player object is found, shoot a bullet from it
            player->shoot(event->pos());
            break;
        }
    }
}
