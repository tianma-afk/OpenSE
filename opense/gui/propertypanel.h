#ifndef PROPERTYPANEL_H
#define PROPERTYPANEL_H

#include <QWidget>
#include<QVBoxLayout>
#include<QLabel>
#include <QMap>
#include"components/component.h"
class PropertyPanel : public QWidget
{
    Q_OBJECT
public:
    explicit PropertyPanel(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent*event)override;
    void initialUI();
public slots:
    void slot_ComponentSelected(Component*component);//设置被选中的组件

private:
    QVBoxLayout*mainLayout;
    QMap<QString, QWidget*> propertyWidgets;
    Component*component;
    void clearProperties();//清空现有属性
    void createProperties();//创建属性
};

#endif // PROPERTYPANEL_H
