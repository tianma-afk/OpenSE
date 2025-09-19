#ifndef CONFIGREADER_H
#define CONFIGREADER_H

#include <QObject>
#include <QJsonObject>
#include <QString>

class ConfigReader : public QObject
{
    Q_OBJECT
public:
    ConfigReader(const ConfigReader&) = delete;
    ConfigReader& operator=(const ConfigReader&) = delete;
    static ConfigReader* getInstance();
    bool loadConfig();
    bool saveConfig(const QString& filePath = "");
    QString getWorkDirectory() const;
    void setWorkDirectory(const QString& workDir);
    QString getProjectsDirectory()const;
    void setProjectsDirectory(const QString& projectsDir);
private:
    explicit ConfigReader(QObject *parent = nullptr);
    static ConfigReader* m_instance;
    QJsonObject m_configData;
    QString m_configFilePath;
};

#endif // CONFIGREADER_H
