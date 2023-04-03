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
        AddTraderWidget.cpp \
        Admin.cpp \
        AdminWindow.cpp \
        DefineFields.cpp \
        SettingsLogic.cpp \
        Trader.cpp \
        User.cpp \
        loginwidget.cpp \
        main.cpp \
        MainWindow.cpp \
        protocol.cpp

HEADERS += \
        ADialog.h \
        AddTraderWidget.h \
        Admin.h \
        AdminWindow.h \
        DefineFields.h \
        MainWindow.h \
        SettingsLogic.h \
        Trader.h \
        User.h \
        loginwidget.h \
        protocol.h

FORMS += \
        ADialog.ui \
        AddTraderWidget.ui \
        Admin.ui \
        AdminWindow.ui \
        MainWindow.ui \
        Trader.ui \
        loginwidget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
