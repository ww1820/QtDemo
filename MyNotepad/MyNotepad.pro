#-------------------------------------------------
#
# Project created by QtCreator 2023-05-22T11:43:21
#
#-------------------------------------------------

QT       += core gui printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MyNotepad
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    subdialog.cpp

HEADERS  += mainwindow.h \
    subdialog.h

FORMS    += mainwindow.ui \
    subdialog.ui

