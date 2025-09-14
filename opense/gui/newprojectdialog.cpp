#include "NewProjectDialog.h"
#include <QGridLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QFileDialog>
#include <QMessageBox>
#include <QDir>

NewProjectDialog::NewProjectDialog(QWidget *parent) : QDialog(parent)
{
    // 设置对话框基本属性
    setWindowTitle(tr("新建项目"));
    setMinimumWidth(500);

    // 1. 创建项目名相关控件
    m_projectNameLabel = new QLabel(tr("项目名称:"), this);
    m_projectNameEdit = new QLineEdit(this);
    m_projectNameEdit->setPlaceholderText(tr("请输入项目名称，不包含特殊字符"));

    // 2. 创建路径相关控件
    m_savePathLabel = new QLabel(tr("保存路径:"), this);
    m_savePathEdit = new QLineEdit(this);
    m_browseButton = new QPushButton(tr("浏览..."), this);
    m_savePathEdit->setReadOnly(true); // 路径编辑框设为只读，通过浏览按钮选择

    // 3. 创建确认和取消按钮
    m_confirmButton = new QPushButton(tr("确认"), this);
    m_cancelButton = new QPushButton(tr("取消"), this);

    // 4. 设置布局
    QGridLayout *mainLayout = new QGridLayout();
    mainLayout->addWidget(m_projectNameLabel, 0, 0, 1, 1);
    mainLayout->addWidget(m_projectNameEdit, 0, 1, 1, 2);
    mainLayout->addWidget(m_savePathLabel, 1, 0, 1, 1);
    mainLayout->addWidget(m_savePathEdit, 1, 1, 1, 1);
    mainLayout->addWidget(m_browseButton, 1, 2, 1, 1);

    // 设置按钮布局
    QHBoxLayout *buttonLayout = new QHBoxLayout();
    buttonLayout->addStretch();
    buttonLayout->addWidget(m_confirmButton);
    buttonLayout->addWidget(m_cancelButton);

    // 主布局
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addLayout(mainLayout);
    layout->addLayout(buttonLayout);
    setLayout(layout);

    // 5. 连接信号槽
    connect(m_browseButton, &QPushButton::clicked, this, &NewProjectDialog::onBrowseClicked);
    connect(m_confirmButton, &QPushButton::clicked, this, &NewProjectDialog::onConfirmClicked);
    connect(m_cancelButton, &QPushButton::clicked, this, &QDialog::reject);
}

QString NewProjectDialog::projectName() const
{
    return m_projectNameEdit->text().trimmed();
}

QString NewProjectDialog::savePath() const
{
    return m_savePathEdit->text().trimmed();
}

void NewProjectDialog::onBrowseClicked()
{
    QString defaultPath = QDir::homePath(); // 默认路径为用户主目录
    if (!m_savePathEdit->text().isEmpty()) {
        defaultPath = m_savePathEdit->text();
    }

    // 打开目录选择对话框
    QString selectedDir = QFileDialog::getExistingDirectory(
        this,
        tr("选择保存路径"),
        defaultPath,
        QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks
        );

    if (!selectedDir.isEmpty()) {
        m_savePathEdit->setText(selectedDir);
    }
}

void NewProjectDialog::onConfirmClicked()
{
    // 验证项目名称
    if (projectName().isEmpty()) {
        QMessageBox::warning(this, tr("输入错误"), tr("项目名称不能为空！"));
        m_projectNameEdit->setFocus();
        return;
    }

    // 验证路径
    if (savePath().isEmpty()) {
        QMessageBox::warning(this, tr("输入错误"), tr("请选择保存路径！"));
        return;
    }

    // 验证路径是否存在
    QDir dir(savePath());
    if (!dir.exists()) {
        QMessageBox::warning(this, tr("路径错误"), tr("所选路径不存在！"));
        return;
    }

    // 验证项目是否已存在
    QString projectPath = savePath() + "/" + projectName();
    if (dir.exists(projectName())) {
        QMessageBox::warning(this, tr("项目已存在"), tr("该路径下已存在同名项目！"));
        return;
    }

    // 所有验证通过，关闭对话框并返回成功
    accept();
}
