#include "projectdata.h"

ProjectData::ProjectData() {}


ProjectData::ProjectData(const ProjectData &data)
{
    this->setProjectName(data.getProjectName());
    this->setCreateTime(data.getCreateTime());
    this->setModifyTime(data.getModifyTime());
    this->setFilePath(data.getFilePath());
}

ProjectData &ProjectData::operator=(const ProjectData &other)
{
    if(this!=&other){
        this->setProjectName(other.getProjectName());
        this->setCreateTime(other.getCreateTime());
        this->setModifyTime(other.getModifyTime());
        this->setFilePath(other.getFilePath());
    }
    return *this;
}

QString ProjectData::getFilePath() const
{
    return filePath;
}

void ProjectData::setFilePath(const QString &newFilePath)
{
    filePath = newFilePath;
}

QString ProjectData::getProjectName() const
{
    return projectName;
}

void ProjectData::setProjectName(const QString &newProjectName)
{
    projectName = newProjectName;
}

void ProjectData::recordCreateTime()
{
    this->createTime=QDateTime::currentDateTime();
}

void ProjectData::setCreateTime(const QDateTime &createTime)
{
    this->createTime=createTime;
}

QDateTime ProjectData::getCreateTime() const
{
    return createTime;
}


QDateTime ProjectData::getModifyTime() const
{
    return modifyTime;
}

void ProjectData::setModifyTime(const QDateTime &newModifyTime)
{
    modifyTime = newModifyTime;
}

QString ProjectData::getJavaPath()
{
    return this->getFilePath()+"/app/src/main/java/com/example/helloworld/MainActivity.java";
}

QString ProjectData::getXMLPath()
{
    return this->getFilePath()+"/app/src/main/res/layout/activity_main.xml";
}

QString ProjectData::getAPKPath()
{
    return this->getFilePath()+"/app/build/outputs/apk/debug/app-debug.apk";
}


