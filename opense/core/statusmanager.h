#ifndef STATUSMANAGER_H
#define STATUSMANAGER_H

#include <QObject>

class StatusManager : public QObject
{
    Q_OBJECT // 必须添加，否则信号槽无效
public:
    static StatusManager* getInstance() {
        static StatusManager instance;
        return &instance;
    }

    StatusManager(const StatusManager&) = delete;
    StatusManager& operator=(const StatusManager&) = delete;

signals:
    void showStatusMessage(const QString& text, int timeout = 3000);

private:
    StatusManager(QObject* parent = nullptr) : QObject(parent) {}
};

#endif // STATUSMANAGER_H
