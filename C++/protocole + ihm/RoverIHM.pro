#-------------------------------------------------
#
# Project created by QtCreator 2017-02-20T09:53:31
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = RoverIHM
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    update.cpp \
    sync.cpp \
    sipHash_2_4.cpp \
    sensors.cpp \
    rover.cpp \
    record.cpp \
    nack.cpp \
    move.cpp \
    manager.cpp \
    keyexchangeprotocol.cpp \
    hash.cpp \
    getinfo.cpp \
    frame.cpp \
    erase.cpp \
    encryption.cpp \
    disconnect.cpp \
    controlstation.cpp \
    commands.cpp \
    command.cpp \
    changesecurity.cpp \
    ack.cpp

HEADERS  += mainwindow.h \
    sipHash_2_4.h \
    sensors.h \
    sensor.h \
    rover.h \
    record.h \
    move.h \
    manager.h \
    hash.h \
    frame.h \
    crypto_stream.h \
    controlstation.h \
    commands.h \
    command.h \
    changesecurity.h \
    crypto_stream_xsalsa20_cpp.h \
    crypto_stream_cpp.h

FORMS    += mainwindow.ui

QMAKE_CXXFLAGS += -std=c++11

OTHER_FILES += \
    commands.xml
