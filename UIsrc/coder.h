#ifndef CODER_H
#define CODER_H
#include<QObject>
#include<QStandardItem>
#include<QString>
#include<QFile>
class Coder:public QObject
{
    Q_OBJECT
public:
    Coder();
    void work(QStandardItem*parent,QStandardItem*self);
private:
    void initial();
};

#endif // CODER_H
