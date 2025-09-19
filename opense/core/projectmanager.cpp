#include "projectmanager.h"
#include"configreader.h"
#include"QDir"
#include<QJsonDocument>
ProjectManager &ProjectManager::getInstance()
{
    static ProjectManager instance;
    return instance;
}

ProjectData& ProjectManager::createProject(const QString &projectName, const QString &path)
{
    ProjectData project;
    project.recordCreateTime();
    project.setModifyTime(project.getCreateTime());
    project.setProjectName(projectName);
    project.setFilePath(path);
    this->projects.push_back(project);
    saveProject(projects.back());
    return projects.back();;
}

void ProjectManager::removeProject(const QString &projectName)
{
    QDir dir(projectsPath+"/"+projectName);

    bool result = dir.removeRecursively();

    if (result) {
        qDebug() << "目录删除成功:" << dir;
    } else {
        qDebug() << "目录删除失败:" << dir;
    }
}

void ProjectManager::loadProject(const QString &projectName)
{
    QDir dir(this->projectsPath);
    QString subDirPath=dir.filePath(projectName);
    QDir subDirectory(subDirPath);
    QString jsonFilePath = subDirectory.filePath("project.json");
    QFile jsonFile(jsonFilePath);

    if (!jsonFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qWarning()<<"加载"+projectName+"失败";
        return;
    }else{
        qDebug()<<"加载"+projectName+"成功";
    }

    QByteArray jsonData = jsonFile.readAll();
    jsonFile.close();
    QJsonParseError parseError;
    QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonData, &parseError);
    QJsonObject jsonObject = jsonDoc.object();
    ProjectData project;
    project.setProjectName(jsonObject["name"].toString());
    project.setCreateTime(jsonObject["createTime"].toVariant().toDateTime());
    project.setModifyTime(jsonObject["settings"].toObject()["modifyTime"].toVariant().toDateTime());
    project.setFilePath(this->projectsPath+"/"+project.getProjectName());
    this->projects.push_back(project);
}

void ProjectManager::loadAll()
{
    QStringList projectsList=this->getDirectSubDirectoryNames();
    for(int i=0;i<projectsList.size();i++){
        loadProject(projectsList.at(i));
    }
}

void ProjectManager::saveProject(const ProjectData &project)
{
    QDir dir(this->projectsPath);

    QString subDirPath = dir.filePath(project.getProjectName());
    if (!dir.mkdir(project.getProjectName())) {
        if (!QDir(subDirPath).exists()) {
            qWarning() << "创建子目录失败:" << subDirPath;
            return;
        }
        qWarning() << "子目录已存在:" << subDirPath;
    } else {
        qDebug() << "子目录创建成功:" << subDirPath;
    }

    QDir subDirectory(subDirPath);
    QString jsonFilePath = subDirectory.filePath("project.json");
    QFile jsonFile(jsonFilePath);

    if (!jsonFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qDebug() << "无法创建project.json文件:" << jsonFile.errorString();
        return;
    }

    QJsonObject jsonObject;
    // 添加项目基本信息
    jsonObject["projectName"] = project.getProjectName();
    jsonObject["version"] = "1.0.0";
    jsonObject["createTime"] = project.getCreateTime().toString();
    jsonObject["author"] = "Unknown";
    jsonObject["description"] = "Auto-generated project configuration";

    QJsonObject settings;
    settings["auto_save"] = true;
    settings["modifyTime"] = project.getModifyTime().toString();
    jsonObject["settings"] = settings;

    QJsonDocument jsonDoc(jsonObject);
    jsonFile.write(jsonDoc.toJson(QJsonDocument::Indented));
    jsonFile.close();

    qDebug() << "project.json文件创建成功:" << jsonFilePath;

    return;
}

void ProjectManager::setProjectsPath(const QString &path)
{
    this->projectsPath=path;
}

QVector<ProjectData> &ProjectManager::getProjectDatas()
{
    return projects;
}

ProjectManager::ProjectManager()
{
    QString projectsDir=ConfigReader::getInstance()->getProjectsDirectory();
    setProjectsPath(projectsDir);
    loadAll();
}

QStringList ProjectManager::getDirectSubDirectoryNames() const
{
    QDir dir(this->projectsPath);
    if (!dir.exists()) {
        qWarning() << "目录不存在:" << this->projectsPath;
        return QStringList();
    }
    dir.setFilter(QDir::Dirs | QDir::NoDotAndDotDot);
    return dir.entryList();
}
