QT += core websockets
QT -= gui

CONFIG += c++11

TARGET = Service
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    service.cpp \
    websocket.cpp

HEADERS += \
    service.h \
    timer.h \
    config.h \
    websocket.h \
