#ifndef INVENTWORKER_H
#define INVENTWORKER_H

#include <QObject>
#include<QString>
#include<QFile>
#include<QProcess>
class InventWorker : public QObject
{
    Q_OBJECT
public:
    explicit InventWorker(QObject *parent = nullptr);
    ~InventWorker();
    void initial();
    void setWorkDir(const QString &newWorkDir);
    void setAPKPath(const QString &newAPKPath);
private:
    QProcess m_process;
    // 用于跟踪当前执行的命令
    int m_commandIndex = 0;
    // 命令列表
    QStringList m_commands;
    QString workDir;
    QString command_wrap=R"(gradle wrapper --gradle-version 8.2.1 --distribution-type all)";
    QString command_assemble=R"(gradlew.bat assembleDebug)";
    QString APKPath;
    void copyToDownloads();
private slots:
    // 处理命令输出并执行下一个命令
    void onReadyRead();

signals:
    // 命令输出信号
    void outputReceived(const QString &output);
    // 错误信息信号
    void errorOccurred(const QString &error);
    // 命令完成信号
    void finished(int exitCode);
    // 工作完成信号(用于线程退出)
    void workFinished();

public slots:
    // 开始执行命令
    void startWork();
    // 停止命令执行
    void stopWork();
};

#endif // INVENTWORKER_H
