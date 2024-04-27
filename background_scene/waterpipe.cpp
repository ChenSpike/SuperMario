#include "waterpipe.h"
#include <QGraphicsScene>
#include <QPixmap>

WaterPipe::WaterPipe(const QPixmap& pixmap) {
    setPixmap(pixmap);
}

void WaterPipe::CreateWaterPipes(QGraphicsScene *scene){
    //water pipe image path
    QPixmap WaterPipeImage(":/new/dataset/dataset/water pipe.png");
    //Create water pipe pointer
    QVector <WaterPipe*> pipes;
    for (int i=0;i<4;i++){
        if(i==0){
            WaterPipe *pipe0 = new WaterPipe(WaterPipeImage);
            pipe0 -> setPos(1400,419);
            scene -> addItem(pipe0);
            pipes.append(pipe0);
        }
        if(i==1){
            WaterPipe *pipe1 = new WaterPipe(WaterPipeImage);
            pipe1 -> setPos(1900,419);
            scene -> addItem(pipe1);
            pipes.append(pipe1);
        }
        if(i==2){
            WaterPipe *pipe2 = new WaterPipe(WaterPipeImage);
            pipe2 -> setPos(2850,420);
            scene -> addItem(pipe2);
            pipes.append(pipe2);
        }
        if(i==3){
            WaterPipe *pipe3 = new WaterPipe(WaterPipeImage);
            pipe3 -> setPos(5450,420);
            scene -> addItem(pipe3);
            pipes.append(pipe3);
        }
        else{
            continue;
        }
    }
}
