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
    QString javaPath=this->project.getJavaPath();
    QString code = readCodeFile(javaPath);
    if (code.isEmpty()) return;
    // 2. 生成代码片段
    QString import=generateImport(*self);
    QString varDeclare = generateVarDeclare(*self);
    QString initCode = generateInitCode(*self);
    QString eventCode = generateEventCode(*self);

    // 3. 找到插入位置并插入（基于标记注释）
    // 插入导入库到 [COMPONENT_VARS] 下方
    code.replace("//[IMPORT]",
                 "//[IMPORT]\n    " + import);

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
    QString xmlPath=this->project.getXMLPath();
    qDebug()<<xmlPath;
    QString xml = readCodeFile(xmlPath);
    if (xml.isEmpty()) return;
    // 2. 生成代码片段
    qDebug()<<"马上要生产xml文件";
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
    qDebug()<<path;
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {

        QString code=file.readAll();
        qDebug()<<code;
        file.close();
        return code;
    }
    qDebug()<<"文件没打开";
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

QString Coder::generateImport(const Component &info)
{
    return QString("import android.widget.%1;").arg(info.componentType());
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

