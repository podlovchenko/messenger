QT += core sql
QT -= gui
QT += network
TARGET = Server
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    mytcpserver.cpp \
    ../ServerSocket/serversocket.cpp \
    ../Database/database.cpp

HEADERS += \
    mytcpserver.h \
    ../ServerSocket/serversocket.h \
    ../Database/database.h

