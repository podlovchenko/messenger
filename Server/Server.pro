QT += core sql
QT -= gui
QT += network
TARGET = Server
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    mytcpserver.cpp

HEADERS += \
    mytcpserver.h

