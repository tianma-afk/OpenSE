#include "projectmanager.h"
#include"configreader.h"
#include"QDir"
#include"core/statusmanager.h"
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
    makeProject(projects.back());
    return projects.back();;
}

void ProjectManager::makeProject(const ProjectData &project)
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
    this->copyTemplate(this->resourcePath,project.getFilePath()+"/"+project.getProjectName());
}

void ProjectManager::removeProject(const QString &projectName)
{
    QDir dir(projectsPath+"/"+projectName);
    bool result = dir.removeRecursively();
    if (result) {
        emit StatusManager::getInstance()->showStatusMessage(projectName+"删除成功");
    } else {
        emit StatusManager::getInstance()->showStatusMessage(projectName+"删除失败");
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
    project.setProjectName(jsonObject["projectName"].toString());
    project.setCreateTime(QDateTime::fromString(jsonObject["createTime"].toString()));
    project.setModifyTime(QDateTime::fromString(jsonObject["settings"].toObject()["modifyTime"].toString()));
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

bool ProjectManager::copyTemplate(const QString&resourcePath,const QString&targetPath)
{
    QDir resourceDir(resourcePath);
    QStringList entries = resourceDir.entryList(QDir::Files | QDir::Dirs | QDir::NoDotAndDotDot);
    foreach (const QString& entry, entries) {
        QString resourceEntryPath = resourcePath + "/" + entry;
        QString targetEntryPath = targetPath + "/" + entry;
        //判断是文件还是目录
        QFileInfo entryInfo(resourceEntryPath);
        if (entryInfo.isDir()) {
            //如果是目录，先创建目标目录，再递归复制子内容
            QDir targetDir(targetEntryPath);
            if (!targetDir.exists() && !targetDir.mkpath(".")) {
                qWarning() << "无法创建子目录:" << targetEntryPath;
                return false;
            }
            // 递归处理子目录
            if (!copyTemplate(resourceEntryPath, targetEntryPath)) {
                return false;
            }
        } else {
            //如果是文件，直接复制
            if (!QFile::copy(resourceEntryPath, targetEntryPath)) {
                qWarning() << "复制文件失败:" << resourceEntryPath << "→" << targetEntryPath;
                return false;
            }else{
                QFile(targetEntryPath).setPermissions(QFileDevice::ReadOwner | QFileDevice::WriteOwner);
            }
        }
    }
    return true;
}

void ProjectManager::saveProject(const ProjectData &project)
{

}

void ProjectManager::setProjectsPath(const QString &path)
{
    this->projectsPath=path;
}

QVector<ProjectData> &ProjectManager::getProjectDatas()
{
    return projects;
}

void ProjectManager::setWorkProject(const QString &projectName)
{
    for(int i=0;i<projects.count();i++){
        if(projects.at(i).getProjectName()==projectName){
            this->workProject=projects.at(i);
            this->isWorkProject=true;
            return;
        }
    }
}

ProjectData &ProjectManager::getWorkProject()
{
    return this->workProject;
}

bool ProjectManager::haveWorkProject()
{
    return this->isWorkProject;
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
