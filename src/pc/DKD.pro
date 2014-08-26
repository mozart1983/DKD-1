#-------------------------------------------------
#
# Project created by QtCreator 2014-03-09T16:32:37
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = DKD
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    titlebar.cpp \
    centerwidget.cpp \
    bottomwidget.cpp \
    push_button.cpp \
    skinmgr.cpp \
    hostinfwnd.cpp \
    userslistitem.cpp \
    p2pchatwnd.cpp \
    pushbtnwithmenu.cpp \
    dkdsearchedit.cpp \
    dkdmovablewidget.cpp \
    shootscreen.cpp \
    shootscreenbuddy.cpp \
    shootscreenmenuwnd.cpp

HEADERS  += mainwindow.h \
    titlebar.h \
    centerwidget.h \
    bottomwidget.h \
    push_button.h \
    skinmgr.h \
    hostinfwnd.h \
    userslistitem.h \
    defs.h \
    p2pchatwnd.h \
    pushbtnwithmenu.h \
    dkdsearchedit.h \
    dkdmovablewidget.h \
    shootscreen.h \
    shootscreenbuddy.h \
    shootscreenmenuwnd.h

FORMS    += mainwindow.ui \
    p2pchatwnd.ui \
    shootscreenbuddy.ui \
    shootscreenmenuwnd.ui


RESOURCES += \
    image.qrc
