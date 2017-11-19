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
    field.cpp \
    level.cpp \
    cell.cpp \
    chip_graph.cpp \
    chip.cpp

HEADERS  += widget.h \
    field.h \
    level.h \
    cell.h \
    chip_graph.h \
    chip.h

FORMS    += widget.ui
