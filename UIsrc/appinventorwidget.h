#ifndef APPINVENTORWIDGET_H
#define APPINVENTORWIDGET_H

#include <QWidget>
#include<QPushButton>
#include<QVBoxLayout>
#include<QHBoxLayout>
#include<QLabel>

class AppInventorWidget : public QWidget
{
    Q_OBJECT
public:
    explicit AppInventorWidget(QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    QVBoxLayout*vLayout;

    //头部
    QWidget*headWidget;
    QHBoxLayout*headHLayout;
    QLabel*nameLabel;

    //主体
    QWidget*bodyWidget;
    QHBoxLayout*bodyHLayout;

    QWidget*component;
    QVBoxLayout*comVlayout;
    QLabel*componentName;

    QWidget*workspace;
    QVBoxLayout*wsVlayout;
    QLabel*workspaceName;

    QWidget*list;
    QVBoxLayout*listVlayout;
    QLabel*listName;

    QWidget*property;
    QVBoxLayout*proVlayout;
    QLabel*propertyName;

    void initialUI();
    void initialComponent();
    void initialWorkspace();
    void initialList();
    void initialProperty();
    void initialData();

signals:
};

#endif // APPINVENTORWIDGET_H
