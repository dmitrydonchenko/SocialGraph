#-------------------------------------------------
#
# Project created by QtCreator 2014-11-11T01:42:04
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = graph_research
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    graph.cpp \
    node.cpp \
    edge.cpp

HEADERS  += mainwindow.h \
    graph.h \
    node.h \
    edge.h

FORMS    += mainwindow.ui
