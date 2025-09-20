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
    void makeProject(const ProjectData&project);
    void removeProject(const QString&projectName);
    void saveProject(const ProjectData&project);
    void setProjectsPath(const QString&path);
    QVector<ProjectData>& getProjectDatas();
    void setWorkProject(const QString&projectName);
    ProjectData& getWorkProject();
    bool haveWorkProject();
private:
    ProjectManager();
    QVector<ProjectData> projects;
    QString projectsPath;
    QStringList getDirectSubDirectoryNames()const;
    void loadProject(const QString&projectName);
    void loadAll();
    bool copyTemplate(const QString&resourcePath,const QString&targetPath);
    ProjectData workProject;
    bool isWorkProject=false;
    QString resourcePath="://templates/blank";
signals:
};

#endif // PROJECTMANAGER_H
