#ifndef CODER_H
#define CODER_H
#include<QObject>
#include<QStandardItem>
#include<QString>
#include<QFile>
#include"components/component.h"
class Coder:public QObject
{
    Q_OBJECT
public:
    Coder();
    void work(Component *parent, Component *self);
private:
    void initial();
};

#endif // CODER_H
