#include "TabWidget.h"
#include <QDebug>

TabWidget::TabWidget(QWidget *parent) : QTabWidget(parent)
{
    // 设置标签页可移动，触发 tabMoved 信号
    setMovable(true);

    // 连接标签页移动信号到重建映射函数
    connect(tabBar(), &QTabBar::tabMoved, this, &TabWidget::rebuildFilePathMap);
}

int TabWidget::addTab(QWidget *widget, const QString &label, const QString &filePath,const tabProperty property)
{
    int index = QTabWidget::addTab(widget, label);
    switch (property)
    {
    case code:
        setTabData(index, filePath);
        break;
    case terminal:
        terminalCount++;
        setTabData(index,label+QString::number(terminalCount));
        break;
    case measure:
        measureCount++;
        setTabData(index,label+QString::number(measureCount));
        break;
    case simulate:
        simulateCount++;
        setTabData(index,label+QString::number(simulateCount));
        break;
    }
    return index;
}


void TabWidget::setTabData(int index, const QVariant &data)
{
    if (index >= 0 && index < count()) {
        // 先移除旧的路径映射（如果有）
        QString oldFilePath = tabData(index).toString();
        if (!oldFilePath.isEmpty() && filePathToIndexMap.value(oldFilePath) == index) {
            filePathToIndexMap.remove(oldFilePath);
        }

        // 添加新的路径映射
        QString newFilePath = data.toString();
        if (!newFilePath.isEmpty()) {
            filePathToIndexMap.insert(newFilePath, index);
        }

        // 调用基类函数设置标签页数据
        tabBar()->setTabData(index, data);
    }
}

QVariant TabWidget::tabData(int index) const
{
    if (index >= 0 && index < count()) {
        return tabBar()->tabData(index);
    }
    return QVariant();
}

void TabWidget::removeTabData(int index)
{
    if (index >= 0 && index < count()) {
        QString filePath = tabData(index).toString();
        if (!filePath.isEmpty()) {
            filePathToIndexMap.remove(filePath);
        }
    }
}

int TabWidget::getCount() const
{
    return count();
}

int TabWidget::findTabByFilePath(const QString &filePath) const
{
    return filePathToIndexMap.value(filePath, -1);
}

void TabWidget::rebuildFilePathMap()
{
    filePathToIndexMap.clear();
    for (int i = 0; i < count(); ++i) {
        QString filePath = tabData(i).toString();
        if (!filePath.isEmpty()) {
            filePathToIndexMap.insert(filePath, i);
        }
    }
}

int TabWidget::getTerminalCount() const
{
    return terminalCount;
}

void TabWidget::tabInserted(int index)
{
    // 标签页插入后，重建映射
    rebuildFilePathMap();
    QTabWidget::tabInserted(index);
}

void TabWidget::tabRemoved(int index)
{
    // 标签页移除后，重建映射
    rebuildFilePathMap();
    QTabWidget::tabRemoved(index);
}
