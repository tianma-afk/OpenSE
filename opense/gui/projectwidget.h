#ifndef PROJECTWIDGET_H
#define PROJECTWIDGET_H

#include <QWidget>
#include<QPushButton>
#include<QVBoxLayout>
#include<QHBoxLayout>
#include<QLabel>
#include<QListView>
#include<QCheckBox>
#include"gui/headwidget.h"
class ProjectWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ProjectWidget(QWidget *parent = nullptr);

signals:
    void openProject();
private:
    QVBoxLayout *vLayout;
    QWidget *topWidget;
    QWidget *bodyWidget;
    QWidget *bottomWidget;

    QHBoxLayout *topHLayout;
    QLabel *headLabel;
    QPushButton *newProjectBtn;
    QPushButton *removeProjectBtn;

    QVBoxLayout *bodyVLayout;
    HeadWidget *headWidget;
    QListView *listView;

    void initialUI();
    void initialData();

};

#endif // PROJECTWIDGET_H
