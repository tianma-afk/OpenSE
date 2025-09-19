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
    void saveProject(const ProjectData&project);
    void setProjectsPath(const QString&path);
    QVector<ProjectData>& getProjectDatas();
private:
    ProjectManager();
    QVector<ProjectData> projects;
    QString projectsPath;
    QStringList getDirectSubDirectoryNames()const;
    void loadProject(const QString&projectName);
    void loadAll();
signals:
};

#endif // PROJECTMANAGER_H
