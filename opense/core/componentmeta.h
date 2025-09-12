// ComponentMeta.h
#ifndef COMPONENTMETA_H
#define COMPONENTMETA_H

#include <QString>
#include <QIcon>

// 组件元信息：名称、图标路径、描述等
struct ComponentMeta {
    QString type;         // 组件类型（如"Button"）
    QString iconPath;     // 图标资源路径（如":/icons/Button.png"）
    QString description;  // 组件描述（如"用于触发点击事件"）
};

#endif // COMPONENTMETA_H
