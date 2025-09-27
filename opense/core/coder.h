#ifndef CODER_H
#define CODER_H
#include<QObject>
#include<QStandardItem>
#include<QString>
#include<QFile>
#include"gui/projectdata.h"
#include"components/component.h"
class Coder:public QObject
{
    Q_OBJECT
public:
    Coder();
    void setProjectData(ProjectData&project);
    void addComponent(Component *parent, Component *self);
private:
    void initial();
    QString readCodeFile(const QString&path);
    void writeCodeFile(const QString& content,const QString&path);

    QString generateImport(const Component& info);     // 导入库
    QString generateVarDeclare(const Component& info); // 变量声明
    QString generateInitCode(const Component& info);   // 初始化代码（findViewById）
    QString generateEventCode(const Component& info);  // 事件处理代码（点击事件）

    QString generateXMLComponent(const Component& info);//XML中添加组件
    ProjectData project;
};

#endif // CODER_H
