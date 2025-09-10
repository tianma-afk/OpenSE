#include "projectdata.h"

ProjectData::ProjectData() {}

ProjectData::ProjectData(const QString &projectName)
{
    this->projectName=projectName;
    this->createTime=QDateTime::currentDateTime();
    this->modifyTime=this->createTime;
}

ProjectData::ProjectData(const ProjectData &data)
{
    this->projectName=data.projectName;
    this->createTime=data.createTime;
    this->modifyTime=data.modifyTime;
}

QDataStream& operator<<(QDataStream&stream,const ProjectData data)
{
    stream<<data.projectName<<data.createTime<<data.modifyTime;
    return stream;
}

QDataStream& operator>>(QDataStream&stream,ProjectData data)
{
    stream>>data.projectName>>data.createTime>>data.modifyTime;
    return stream;
}

void ProjectData::saveData(const ProjectData &data)
{
    QFile file(this->filePath+this->projectName);
    file.open(QIODevice::WriteOnly|QIODevice::Append);
    QDataStream ds(&file);
    ds<<data;
    file.close();
}

void ProjectData::readData()
{
    QFile file(this->filePath+this->projectName);
    file.open(QIODevice::ReadOnly);
    QDataStream ds(&file);
    ProjectData data;
    ds>>data;
    this->projectName=data.projectName;
    this->createTime=data.createTime;
    this->modifyTime=data.modifyTime;
    file.close();
}

void ProjectData::setFilePath(const QString &path)
{
    this->filePath=path;
}
