#include "configreader.h"
#include <QFile>
#include <QJsonDocument>
#include <QJsonParseError>
#include <QDebug>
#include<QDir>
#include<QCoreApplication>
ConfigReader* ConfigReader::m_instance = nullptr;
ConfigReader::ConfigReader(QObject *parent) : QObject(parent)
{
}


ConfigReader* ConfigReader::getInstance()
{
    if (m_instance == nullptr) {
        m_instance = new ConfigReader();
        m_instance->loadConfig();
    }
    return m_instance;
}

bool ConfigReader::loadConfig()
{
    QString filePath=QCoreApplication::applicationDirPath() + "/config.json";
    QFile file(filePath);
    if (!file.exists()) {
        qWarning() << "配置文件不存在:" << filePath;
        qDebug()<<QDir::currentPath();
        qDebug()<<QCoreApplication::applicationDirPath() + "/config.json";
        return false;
    }

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qWarning() << "无法打开配置文件:" << file.errorString();
        return false;
    }

    QByteArray data = file.readAll();
    file.close();

    QJsonParseError parseError;
    QJsonDocument jsonDoc = QJsonDocument::fromJson(data, &parseError);

    if (parseError.error != QJsonParseError::NoError) {
        qWarning() << "JSON解析错误:" << parseError.errorString();
        return false;
    }

    if (!jsonDoc.isObject()) {
        qWarning() << "JSON不是一个对象";
        return false;
    }

    m_configData = jsonDoc.object();
    m_configFilePath = filePath;
    qDebug() << "配置文件加载成功:" << filePath;
    return true;
}

bool ConfigReader::saveConfig(const QString &filePath)
{
    QString savePath = filePath;
    if (savePath.isEmpty()) {
        savePath = m_configFilePath;
    }

    if (savePath.isEmpty()) {
        qWarning() << "未指定配置文件路径";
        return false;
    }

    QFile file(savePath);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qWarning() << "无法打开配置文件进行写入:" << file.errorString();
        return false;
    }

    QJsonDocument jsonDoc(m_configData);
    file.write(jsonDoc.toJson(QJsonDocument::Indented)); // 缩进格式，便于阅读
    file.close();

    m_configFilePath = savePath;
    qDebug() << "配置文件保存成功:" << savePath;
    return true;
}

QString ConfigReader::getWorkDirectory() const
{
    return m_configData["work_directory"].toString();
}

void ConfigReader::setWorkDirectory(const QString &workDir)
{
    m_configData["work_directory"] = workDir;
}

QString ConfigReader::getProjectsDirectory() const
{
    return m_configData["projects_directory"].toString();
}

void ConfigReader::setProjectsDirectory(const QString &projectsDir)
{
    m_configData["projects_directory"] = projectsDir;
}

