#ifndef NEWPROJECTDIALOG_H
#define NEWPROJECTDIALOG_H

#include <QDialog>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>

class NewProjectDialog : public QDialog
{
    Q_OBJECT
public:
    explicit NewProjectDialog(QWidget *parent = nullptr);

    // 获取用户输入的项目信息
    QString projectName() const;
    QString savePath() const;

private slots:
    // 浏览路径按钮点击事件
    void onBrowseClicked();
    // 确认按钮点击事件
    void onConfirmClicked();

private:
    // 项目名相关控件
    QLabel *m_projectNameLabel;
    QLineEdit *m_projectNameEdit;

    // 路径相关控件
    QLabel *m_savePathLabel;
    QLineEdit *m_savePathEdit;
    QPushButton *m_browseButton;

    // 按钮控件
    QPushButton *m_confirmButton;
    QPushButton *m_cancelButton;
};

#endif // NEWPROJECTDIALOG_H
