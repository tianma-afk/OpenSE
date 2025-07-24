#ifndef TABWIDGET_H
#define TABWIDGET_H

#include <QTabWidget>
#include <QHash>
#include <QVariant>
#include<QTabBar>
class TabWidget : public QTabWidget
{
    Q_OBJECT
public:
    enum tabProperty{
        code,
        terminal,
        measure,
        simulate
    };
    explicit TabWidget(QWidget *parent = nullptr);

    // 添加标签页并自动关联文件路径
    int addTab(QWidget *widget, const QString &label, const QString &filePath,const tabProperty property=code);
    // 设置标签页数据（重载原有函数，增加路径维护）
    void setTabData(int index, const QVariant &data);

    // 获取标签页数据
    QVariant tabData(int index) const;

    // 移除标签页数据（自动更新映射）
    void removeTabData(int index);

    // 获取标签页数量
    int getCount() const;

    // 根据文件路径查找标签页索引
    int findTabByFilePath(const QString &filePath) const;

    // 重建所有标签页的映射（在标签页顺序改变后调用）
    void rebuildFilePathMap();

    //获取终端标签页数量
    int getTerminalCount()const;
protected:
    // 监听标签页移动事件，自动更新映射
    void tabInserted(int index) override;
    void tabRemoved(int index) override;

private:
    // 使用文件路径作为键，标签页索引作为值的映射
    QHash<QString, int> filePathToIndexMap;
    //终端数量
    int terminalCount=0;
    int measureCount=0;
    int simulateCount=0;
};

#endif // TABWIDGET_H
