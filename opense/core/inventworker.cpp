#include "inventworker.h"
#include<QDebug>
#include<QTimer>
#include<QDateTime>
#include<QStandardPaths>
#include<QFileInfo>
#include<QDir>
#include<QFile>
#include"core/statusmanager.h"
InventWorker::InventWorker(QObject *parent)
    : QObject{parent}
{
    this->initial();
}

InventWorker::~InventWorker()
{
    this->stopWork();
}

void InventWorker::initial()
{
    qDebug()<<"InventorWorker初始化";
    // 初始化命令列表
    m_commands << command_wrap << command_assemble;

    // 连接进程信号
    connect(&m_process, &QProcess::readyReadStandardOutput, this, &InventWorker::onReadyRead);
    connect(&m_process, &QProcess::readyReadStandardError, this, [this]() {
        QString error = m_process.readAllStandardError();
        emit errorOccurred(error);
    });

    connect(&m_process, QOverload<int, QProcess::ExitStatus>::of(&QProcess::finished),
            this, [this](int exitCode, QProcess::ExitStatus) {
                qDebug() << "进程已退出，退出码：" << exitCode;
                emit finished(exitCode);
                emit workFinished();
            });
}


void InventWorker::setWorkDir(const QString &newWorkDir)
{
    workDir = newWorkDir;
}

void InventWorker::setAPKPath(const QString &newAPKPath)
{
    this->APKPath=newAPKPath;
}

void InventWorker::copyToDownloads()
{
    // 获取系统下载文件夹路径
    QString downloadsPath = QStandardPaths::writableLocation(QStandardPaths::DownloadLocation);

    if (downloadsPath.isEmpty()) {
        qWarning() << "无法获取下载文件夹路径";
        return;
    }

    QDir downloadsDir(downloadsPath);
    // 提取源文件的文件名
    QFileInfo fileInfo(this->APKPath);
    QString fileName = fileInfo.fileName();

    // 目标文件路径
    QString targetFilePath = downloadsDir.filePath(fileName);

    // 如果目标文件已存在，添加编号避免覆盖
    int counter = 1;
    while (QFile::exists(targetFilePath)) {
        QString newFileName = QString("%1(%2).%3")
        .arg(fileInfo.baseName())
            .arg(counter)
            .arg(fileInfo.suffix());
        targetFilePath = downloadsDir.filePath(newFileName);
        counter++;
    }

    // 复制文件
    if (QFile::copy(this->APKPath, targetFilePath)) {
        qDebug() << "文件已成功复制到下载文件夹:" << targetFilePath;
        return;
    } else {
        qWarning() << "文件复制失败";
        return;
    }
    emit StatusManager::getInstance()->showStatusMessage("APP文件已经放入下载文件夹");
}

void InventWorker::onReadyRead()
{
    // 读取输出并发送信号
    QString output = m_process.readAllStandardOutput();
    if (!output.isEmpty()) {
        emit outputReceived(output);
    }

    // 检查当前命令是否执行完成
    // 这里使用简单的判断，实际应用可能需要更复杂的逻辑
    // 或者使用等待命令完成的标志
}

void InventWorker::startWork()
{
    qDebug()<<"InventorWorker开始工作";
    if (workDir.isEmpty()) {
        emit errorOccurred("工作目录未设置");
        emit workFinished();
        return;
    }
    // 重置命令索引
    m_commandIndex = 0;
    // 设置工作目录
    m_process.setWorkingDirectory(workDir);
    // 启动命令行
    m_process.start("cmd.exe");
    if (!m_process.waitForStarted()) {
        emit errorOccurred("无法启动命令行进程");
        emit workFinished();
        return;
    }

    // 执行第一个命令
    if (m_commandIndex < m_commands.size()) {
        QString firstCommand = m_commands[m_commandIndex];
        qDebug() << "执行命令：" << firstCommand;
        m_process.write((firstCommand + "\n").toLocal8Bit());
        m_commandIndex++;
    }

    // 使用定时器检查命令是否完成，避免阻塞
    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, [this, timer]() {
        // 检查当前命令是否执行完成
        // 简单判断：如果超过3秒没有输出，认为命令执行完成
        // 实际应用中应根据具体命令的特性调整
        static qint64 lastOutputTime = QDateTime::currentMSecsSinceEpoch();
        qint64 currentTime = QDateTime::currentMSecsSinceEpoch();

        if (currentTime - lastOutputTime > 10000) { // 10秒无输出
            if (m_commandIndex < m_commands.size()) {
                // 执行下一个命令
                QString nextCommand = m_commands[m_commandIndex];
                qDebug() << "执行命令：" << nextCommand;
                m_process.write((nextCommand + "\n").toLocal8Bit());
                m_commandIndex++;
                lastOutputTime = currentTime;
            } else {
                // 所有命令执行完成，退出cmd
                qDebug() << "所有命令执行完成，退出命令行";
                m_process.write("exit\n");
                timer->stop();
                timer->deleteLater();
                copyToDownloads();
                this->stopWork();
            }
        } else if (m_process.bytesAvailable() > 0) {
            lastOutputTime = currentTime;
        }
    });
    timer->start(1000); // 每秒检查一次
}

void InventWorker::stopWork()
{
    qDebug()<<"InventorWorker结束工作";
    emit StatusManager::getInstance()->showStatusMessage("APP生成结束");
    if (m_process.state() == QProcess::Running) {
        m_process.kill();
        m_process.waitForFinished();
    }
}
