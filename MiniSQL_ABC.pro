#-------------------------------------------------
#
# Project created by QtCreator 2017-06-04T08:08:58
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MiniSQL_ABC
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES +=\
    API.cpp \
    MiniSQL_ABC.cpp \
    DBMS_UI.cpp \
    Buffer.cpp \
    Catalog.cpp \
    Interpreter.cpp \
    Record.cpp \
    Index.cpp

HEADERS  += \
    API.h \
    MiniSQL_ABC.h \
    DBMS_UI.h \
    Buffer.h \
    Catalog.h \
    Interpreter.h \
    Index.h \
    Record.h \
    Config.h

FORMS    += \
    DBMS_UI.ui
