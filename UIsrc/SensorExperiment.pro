QT       += core gui charts

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    appinventorwidget.cpp \
    clicklabel.cpp \
    componentitem.cpp \
    componentlist.cpp \
    componentmenuitem.cpp \
    componentpanel.cpp \
    componentpaneldelegate.cpp \
    componentpanelmodel.cpp \
    headwidget.cpp \
    main.cpp \
    mainwindow.cpp \
    projectdata.cpp \
    projectdelegate.cpp \
    projectlistmodel.cpp \
    projectwidget.cpp \
    propertypanel.cpp \
    workspace.cpp

HEADERS += \
    appinventorwidget.h \
    clicklabel.h \
    componentitem.h \
    componentlist.h \
    componentmenuitem.h \
    componentpanel.h \
    componentpaneldelegate.h \
    componentpanelmodel.h \
    headwidget.h \
    mainwindow.h \
    projectdata.h \
    projectdelegate.h \
    projectlistmodel.h \
    projectwidget.h \
    propertypanel.h \
    workspace.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    icon.qrc
