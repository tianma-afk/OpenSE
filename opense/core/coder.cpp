#include "coder.h"
#include<QDebug>
#include<QStandardPaths>
#include<QApplication>
#include<QFileInfo>
Coder::Coder() {
    this->initial();
}

void Coder::setProjectData(ProjectData &project)
{
    this->project=project;
}

void Coder::addComponent(Component *parent, Component *self)
{
    qDebug()<<"加入组件"<<self->componentType();
    //增加java代码
    // 1. 读取现有代码
    QString javaPath=this->project.getFilePath()+"/app/src/main/java/com/example/helloworld/MainActivity.java";
    QString code = readCodeFile(javaPath);
    if (code.isEmpty()) return;
    // 2. 生成代码片段
    QString varDeclare = generateVarDeclare(*self);
    QString initCode = generateInitCode(*self);
    QString eventCode = generateEventCode(*self);

    // 3. 找到插入位置并插入（基于标记注释）
    // 插入变量声明到 [COMPONENT_VARS] 下方
    code.replace("//[COMPONENT_VARS]",
                 "//[COMPONENT_VARS]\n    " + varDeclare);

    // 插入初始化代码到 [COMPONENT_INIT] 下方
    code.replace("//[COMPONENT_INIT]",
                 "//[COMPONENT_INIT]\n        " + initCode);

    // 插入事件代码到 [COMPONENT_EVENTS] 下方
    code.replace("//[COMPONENT_EVENTS]",
                 "//[COMPONENT_EVENTS]\n        " + eventCode);
    // 4. 保存修改
    writeCodeFile(code,javaPath);

    //增加xml代码
    // 1. 读取现有代码
    QString xmlPath=this->project.getFilePath()+"/app/src/main/res/layout/activity_main.xml";
    QString xml = readCodeFile(xmlPath);
    if (xml.isEmpty()) return;
    // 2. 生成代码片段
    QString componentCode = generateXMLComponent(*self);

    // 3. 找到插入位置并插入（基于标记注释）
    // 插入变量声明到 [COMPONENT] 下方
    xml.replace("//[COMPONENT]",
                 "//[COMPONENT]\n    " + componentCode);
    // 4. 保存修改
    writeCodeFile(xml,xmlPath);
}

void Coder::initial()
{
    qDebug()<<"Coder初始化";
}

QString Coder::readCodeFile(const QString&path)
{
    QFile file(path);
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QString code=file.readAll();
        file.close();
        return code;
    }
    return "";
}

void Coder::writeCodeFile(const QString &content,const QString&path)
{
    QFile file(path);
    qDebug()<<"进入写入函数";
    if (file.open(QIODevice::WriteOnly | QIODevice::Text|QIODevice::Truncate)) {
        qDebug()<<"写入。。。";
        QTextStream out(&file);
        out << content;
        file.close();
    }else{
        qDebug() << "OpenError 错误详情：" << file.errorString();
    }
}

QString Coder::generateVarDeclare(const Component &info)
{
    return QString("private %1 %2;").arg(info.componentType()).arg(info.item->data(Component::Data::objName).toString());
}

QString Coder::generateInitCode(const Component &info)
{
    return QString("%1 = findViewById(R.id.%1);").arg(info.item->data(Component::Data::objName).toString());
}

QString Coder::generateEventCode(const Component &info)
{
    return " ";
}

QString Coder::generateXMLComponent(const Component &info)
{
    qDebug()<<"info:"<<info.componentType();
    if(info.componentType()=="Button"){
        return QString("<Button \n\
                       android:id=\"@+id/%1\"\n\
                       android:layout_width=\"wrap_content\"\n\
                       android:layout_height=\"wrap_content\"\n\
                       android:text=\"%2\"\n\
                       android:textSize=\"18sp\"/>\n")
            .arg(info.item->data(Component::Data::objName).toString())
            .arg(info.item->data(Component::Data::text).toString());
    }else{
        return " ";
    }
}

