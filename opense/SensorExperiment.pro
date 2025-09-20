QT       += core gui charts

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    components/Button.cpp \
    components/TextBox.cpp \
    core/coder.cpp \
    core/componentfactory.cpp \
    core/configreader.cpp \
    core/inventworker.cpp \
    core/projectmanager.cpp \
    gui/appinventorwidget.cpp \
    gui/clicklabel.cpp \
    gui/componentdelegate.cpp \
    gui/componentlist.cpp \
    gui/componentmenuitem.cpp \
    gui/componentmodel.cpp \
    gui/componentpanel.cpp \
    gui/componentpaneldelegate.cpp \
    gui/componentpanelmodel.cpp \
    gui/headwidget.cpp \
    gui/mainwindow.cpp \
    gui/newprojectdialog.cpp \
    gui/projectdata.cpp \
    gui/projectdelegate.cpp \
    gui/projectlistmodel.cpp \
    gui/projectwidget.cpp \
    gui/propertypanel.cpp \
    gui/workspace.cpp \
    gui/wsscene.cpp \
    main.cpp
HEADERS += \
    components/component.h \
    components/Button.h \
    components/TextBox.h \
    core/coder.h \
    core/componentfactory.h \
    core/componentmeta.h \
    core/componentregister.h \
    core/configreader.h \
    core/inventworker.h \
    core/projectmanager.h \
    core/statusmanager.h \
    gui/appinventorwidget.h \
    gui/clicklabel.h \
    gui/componentdelegate.h \
    gui/componentlist.h \
    gui/componentmenuitem.h \
    gui/componentmodel.h \
    gui/componentpanel.h \
    gui/componentpaneldelegate.h \
    gui/componentpanelmodel.h \
    gui/headwidget.h \
    gui/mainwindow.h \
    gui/newprojectdialog.h \
    gui/projectdata.h \
    gui/projectdelegate.h \
    gui/projectlistmodel.h \
    gui/projectwidget.h \
    gui/propertypanel.h \
    gui/workspace.h \
    gui/wsscene.h

FORMS += \
    gui/mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    icon.qrc \
    setting.qrc \
    template.qrc
