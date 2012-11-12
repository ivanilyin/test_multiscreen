#-------------------------------------------------
#
# Project created by QtCreator 2012-11-12T15:37:16
#
#-------------------------------------------------

QT       += core gui webkit

SERVICE_DIR = $$PWD/service

TARGET = test_multiscreen
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui

MOC_DIR = $$SERVICE_DIR
UI_DIR = $$SERVICE_DIR
OBJECTS_DIR = $$SERVICE_DIR
DESTDIR = $$SERVICE_DIR
