#include "coder.h"
#include<QDebug>
Coder::Coder() {
    this->initial();
}

void Coder::initial()
{
    qDebug()<<"Coder初始化";
}

void Coder::work(QStandardItem *parent, QStandardItem *self)
{
    qDebug()<<"Coder工作";

}



