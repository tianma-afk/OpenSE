#ifndef PROJECTDATA_H
#define PROJECTDATA_H
#include<QFile>
#include<QDataStream>
#include<QString>
#include<QDateTime>
class ProjectData
{
public:
    //无参构造
    ProjectData();
    //有参构造
    ProjectData(const QString&projectName);
    //复制构造
    ProjectData(const ProjectData&data);
    QString projectName;
    QDateTime createTime;
    QDateTime modifyTime;

    friend QDataStream& operator<<(QDataStream&stream,const ProjectData data);
    friend QDataStream& operator>>(QDataStream&stream,ProjectData data);

    void saveData(const ProjectData& data);
    void readData();

    void setFilePath(const QString&path);
private:

    QString filePath;
};

#endif // PROJECTDATA_H
