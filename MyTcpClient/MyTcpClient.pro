QT += core
QT -= gui

TARGET = MyTcpClient
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    mytcpclient.cpp

HEADERS += \
    mytcpclient.h

QT += network

