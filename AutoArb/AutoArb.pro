#-------------------------------------------------
#
# Project created by QtCreator 2023-03-29T17:48:42
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = AutoArb
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        ADialog.cpp \
        AddAccountWidget.cpp \
    AddRiskWidget.cpp \
    AddStragetyWidget.cpp \
        AddTraderWidget.cpp \
        Admin.cpp \
    AdminUserItem.cpp \
        AdminWindow.cpp \
        DefineFields.cpp \
    DeleteAccountWidget.cpp \
    DeleteTraderWidget.cpp \
    FileSystemWatcher.cpp \
        SettingsLogic.cpp \
        Trader.cpp \
        User.cpp \
    UserStrategyItem.cpp \
    UserWindow.cpp \
        loginwidget.cpp \
        main.cpp \
        MainWindow.cpp \
        protocol.cpp

HEADERS += \
        ADialog.h \
        AddAccountWidget.h \
    AddRiskWidget.h \
    AddStragetyWidget.h \
        AddTraderWidget.h \
        Admin.h \
    AdminUserItem.h \
        AdminWindow.h \
        DefineFields.h \
    DeleteAccountWidget.h \
    DeleteTraderWidget.h \
    FileSystemWatcher.h \
        MainWindow.h \
        SettingsLogic.h \
        Trader.h \
        User.h \
    UserStrategyItem.h \
    UserWindow.h \
        loginwidget.h \
        protocol.h

FORMS += \
        ADialog.ui \
        AddAccountWidget.ui \
    AddRiskWidget.ui \
    AddStragetyWidget.ui \
        AddTraderWidget.ui \
        Admin.ui \
    AdminUserItem.ui \
        AdminWindow.ui \
    DeleteAccountWidget.ui \
    DeleteTraderWidget.ui \
        MainWindow.ui \
        Trader.ui \
    UserStrategyItem.ui \
    UserWindow.ui \
        loginwidget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
