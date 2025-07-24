#ifndef TERMINALWIDGET_H
#define TERMINALWIDGET_H

#include <QWidget>
#include <QPlainTextEdit>
#include <QProcess>

class TerminalWidget : public QWidget {
    Q_OBJECT
public:
    explicit TerminalWidget(const QString path,QWidget* parent = nullptr);
    ~TerminalWidget();

private slots:
    void handleProcessError();
    void handleProcessOutput();
    void handleProcessFinished(int exitCode, QProcess::ExitStatus exitStatus);

protected:
    bool eventFilter(QObject* obj, QEvent* event) override;
private:
    QPlainTextEdit* textEdit;
    QProcess* process;
    QString currentCommand;
    int promptPosition;
    QString path;

    void executeCommand(const QString& command);
    void updatePrompt();
};

#endif // TERMINALWIDGET_H
