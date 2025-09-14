#ifndef PROJECTMANAGER_H
#define PROJECTMANAGER_H
#include<QVector>
#include"gui/projectdata.h"
class ProjectManager
{
public:
    static ProjectManager& getInstance();
    ProjectManager(const ProjectManager&) = delete;
    ProjectManager& operator=(const ProjectManager&) = delete;
    ProjectData& createProject(const QString&projectName,const QString& path);
    void removeProject(const QString&projectName);
    void loadProject(const QString&projectName);
    void saveProject(const QString&projectName);
    void setProjectsPath(const QString&path);
    QVector<ProjectData>& getProjectDatas();
private:
    ProjectManager()=default;
    QVector<ProjectData> projects;
signals:
};

#endif // PROJECTMANAGER_H
