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
        widget.cpp \
    cell.cpp \
    chip.cpp \
    field.cpp \
    level.cpp


HEADERS  += widget.h \
    cell.h \
    chip.h \
    field.h \
    level.h


FORMS    += widget.ui
