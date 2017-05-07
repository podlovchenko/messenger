QT += core
QT -= gui

TARGET = MyTcpServer
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    mytcpserver.cpp

HEADERS += \
    mytcpserver.h

QT += network
