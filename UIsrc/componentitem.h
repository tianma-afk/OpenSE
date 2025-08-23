#ifndef COMPONENTITEM_H
#define COMPONENTITEM_H

#include<QIcon>
#include<QString>
class ComponentItem
{
public:
    ComponentItem(const QString name,const QIcon icon,const QString description);
    QString name;
    QIcon icon;
    QString description;
};
#endif // COMPONENTITEM_H
