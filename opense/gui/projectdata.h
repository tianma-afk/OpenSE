#ifndef PROJECTDATA_H
#define PROJECTDATA_H
#include<QFile>
#include<QDataStream>
#include<QString>
#include<QDateTime>
class ProjectData
{
public:
    ProjectData();
    ProjectData(const ProjectData&data);

    QString getFilePath() const;
    void setFilePath(const QString &newFilePath);
    QString getProjectName() const;
    void setProjectName(const QString &newProjectName);
    void recordCreateTime();
    void setCreateTime(const QDateTime &createTime);
    QDateTime getCreateTime() const;
    QDateTime getModifyTime() const;
    void setModifyTime(const QDateTime &newModifyTime);
private:
    QString filePath;
    QString projectName;
    QDateTime createTime;
    QDateTime modifyTime;
};

#endif // PROJECTDATA_H
