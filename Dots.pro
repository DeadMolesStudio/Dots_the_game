#-------------------------------------------------
#
# Project created by QtCreator 2017-01-15T20:52:13
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Dots
TEMPLATE = app


SOURCES += main.cpp\
    cell.cpp \
    chip.cpp \
    field.cpp \
    level.cpp \
    requirement.cpp \
    reqset.cpp \
    bonuses.cpp \
    selecter.cpp \
    mainwindow.cpp \
    menu.cpp \
    line_selecter.cpp \
    level_selecter.cpp \
    help.cpp




HEADERS  += cell.h \
    chip.h \
    field.h \
    level.h \
    requirement.h \
    reqset.h \
    bonuses.h \
    selecter.h \
    mainwindow.h \
    menu.h \
    line_selecter.h \
    level_selecter.h \
    help.h




FORMS    += field.ui

RESOURCES += \
    my_res.qrc

