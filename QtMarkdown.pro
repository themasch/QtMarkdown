#-------------------------------------------------
#
# Project created by QtCreator 2011-07-19T01:41:40
#
#-------------------------------------------------

QT       += core gui

TARGET = QtMarkdown
TEMPLATE = app

LIBS += -lmarkdown

SOURCES += main.cpp\
        MainWindow.cpp

HEADERS  += MainWindow.h \
    Config.h

FORMS    += MainWindow.ui

OTHER_FILES += \
    Readme.md
