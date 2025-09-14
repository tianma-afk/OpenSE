#include "projectmanager.h"

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
    return projects.back();;
}

void ProjectManager::removeProject(const QString &projectName)
{

}

void ProjectManager::loadProject(const QString &projectName)
{

}

void ProjectManager::saveProject(const QString &projectName)
{

}

void ProjectManager::setProjectsPath(const QString &path)
{

}

QVector<ProjectData> &ProjectManager::getProjectDatas()
{
    return projects;
}
