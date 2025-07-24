#include "terminalwidget.h"
#include <QVBoxLayout>
#include <QKeyEvent>
#include <QScrollBar>
#include<QShortcut>
#include<QDebug>
TerminalWidget::TerminalWidget(const QString path,QWidget* parent) : QWidget(parent) {
    this->path=path;
    // 创建主布局
    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);
    // 创建文本编辑区域
    textEdit = new QPlainTextEdit(this);
    textEdit->setFont(QFont("Consolas", 16));
    textEdit->setReadOnly(false);
    textEdit->setLineWrapMode(QPlainTextEdit::NoWrap);
    textEdit->setStyleSheet(R"(
        QPlainTextEdit {
            background-color: black;    /* 背景色：黑色 */
            color: white;              /* 文字色：白色 */
            selection-background-color: #444444;  /* 选中区域背景：深灰色 */
            selection-color: white;    /* 选中区域文字：白色 */
            border: none;              /* 去掉边框（可选） */
        }
    )");
    layout->addWidget(textEdit);
    textEdit->installEventFilter(this);
    // 启动 shell 进程并设置工作路径
    process = new QProcess(this);
    process->setWorkingDirectory(path);

#ifdef Q_OS_WIN
    process->start("cmd.exe", QStringList(), QIODevice::ReadWrite);
#else
    process->start("/bin/bash", QStringList() << "--norc", QIODevice::ReadWrite);
#endif
    connect(process, &QProcess::readyReadStandardError, this, &TerminalWidget::handleProcessError);
    connect(process, &QProcess::readyReadStandardOutput, this, &TerminalWidget::handleProcessOutput);
    connect(process, QOverload<int, QProcess::ExitStatus>::of(&QProcess::finished),
            this, &TerminalWidget::handleProcessFinished);
}

TerminalWidget::~TerminalWidget() {
    if (process && process->state() == QProcess::Running) {
        process->write("exit\n");
        if (!process->waitForFinished(1000)) {
            process->terminate();
        }
    }
    delete process;
    process = nullptr;
    delete textEdit;
    textEdit = nullptr;
}

void TerminalWidget::updatePrompt() {
    promptPosition = textEdit->toPlainText().length();
}

void TerminalWidget::executeCommand(const QString& command) {
    process->write(command.toUtf8() + "\n");
    textEdit->verticalScrollBar()->setValue(textEdit->verticalScrollBar()->maximum());
}

void TerminalWidget::handleProcessError() {
    // 读取进程错误输出并显示
    QString error = QString::fromLocal8Bit(process->readAllStandardError());
    textEdit->moveCursor(QTextCursor::End);
    textEdit->insertPlainText(error);
    textEdit->verticalScrollBar()->setValue(textEdit->verticalScrollBar()->maximum());
    updatePrompt();
}

void TerminalWidget::handleProcessOutput() {
    // 读取进程输出并显示
    QString output = QString::fromLocal8Bit(process->readAllStandardOutput());
    textEdit->moveCursor(QTextCursor::End);
    textEdit->insertPlainText(output);
    textEdit->verticalScrollBar()->setValue(textEdit->verticalScrollBar()->maximum());
    updatePrompt();
}


void TerminalWidget::handleProcessFinished(int exitCode, QProcess::ExitStatus exitStatus) {
    textEdit->appendPlainText("\n[进程已结束，退出代码: " + QString::number(exitCode) + "]");
}

bool TerminalWidget::eventFilter(QObject* obj, QEvent* event)
{
    if (obj == textEdit && event->type() == QEvent::KeyPress) {
        QKeyEvent* keyEvent = static_cast<QKeyEvent*>(event);

        if (keyEvent->key() == Qt::Key_Return || keyEvent->key() == Qt::Key_Enter) {
            // 获取当前命令
            QTextCursor cmdCursor = textEdit->textCursor();
            cmdCursor.setPosition(promptPosition);
            cmdCursor.movePosition(QTextCursor::EndOfLine, QTextCursor::KeepAnchor);
            currentCommand = cmdCursor.selectedText().trimmed();
            // 执行命令
            if (!currentCommand.isEmpty()) {
                executeCommand(currentCommand);
            }
            // 添加换行并更新提示符位置
            textEdit->appendPlainText("\n");
            updatePrompt();
            return true;
        }
    }
    return QWidget::eventFilter(obj, event);
}
