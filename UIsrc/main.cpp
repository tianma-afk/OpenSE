#include "mainwindow.h"

#include <QApplication>
#include<QFile>
// 加载外部样式表文件
QString loadStyleSheet(const QString &fileName) {
    QFile file(fileName);
    if (file.open(QFile::ReadOnly | QFile::Text)) {
        return QLatin1String(file.readAll());
    }
    return "";
}
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QString style = loadStyleSheet(":/styles/normal.qss");
    if (!style.isEmpty()) {
        a.setStyleSheet(style);
    }
    MainWindow w;
    w.show();
    return a.exec();
}
