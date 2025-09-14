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
#include"projectlistmodel.h"
#include"projectdelegate.h"
class ProjectWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ProjectWidget(QWidget *parent = nullptr);

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
    ProjectDelegate* delegate;
    ProjectListModel *model;

    void initialUI();
    void initialData();
    void initialCore();
    void initialConnect();
signals:
    void openProject();
public slots:
    void onNewProjectBtnClicked();
    void onRemoveProjectBtnClicked();
};

#endif // PROJECTWIDGET_H
