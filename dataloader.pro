#-------------------------------------------------
#
# Project created by QtCreator 2017-04-11T22:36:26
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = dataloader
TEMPLATE = app


SOURCES += main.cpp\
        FenetrePrincipale.cpp

HEADERS  += FenetrePrincipale.h\

CONFIG += c++11


unix:!macx: LIBS += -L$$PWD/../../../usr/lib/x86_64-linux-gnu/hdf5/serial/lib/lib/ -lhdf5_hl_cpp

INCLUDEPATH += $$PWD/../../../usr/lib/x86_64-linux-gnu/hdf5/serial/lib/include
DEPENDPATH += $$PWD/../../../usr/lib/x86_64-linux-gnu/hdf5/serial/lib/include

unix:!macx: PRE_TARGETDEPS += $$PWD/../../../usr/lib/x86_64-linux-gnu/hdf5/serial/lib/lib/libhdf5_hl_cpp.a

unix:!macx: LIBS += -L$$PWD/../../../usr/lib/x86_64-linux-gnu/hdf5/serial/lib/ -lhdf5

INCLUDEPATH += $$PWD/../../../usr/lib/x86_64-linux-gnu/hdf5/serial/lib/include
DEPENDPATH += $$PWD/../../../usr/lib/x86_64-linux-gnu/hdf5/serial/lib/include

unix:!macx: PRE_TARGETDEPS += $$PWD/../../../usr/lib/x86_64-linux-gnu/hdf5/serial/lib/libhdf5.a

unix:!macx: LIBS += -L$$PWD/../../../usr/lib/x86_64-linux-gnu/hdf5/serial/lib/ -lhdf5_cpp

INCLUDEPATH += $$PWD/../../../usr/lib/x86_64-linux-gnu/hdf5/serial/lib/include
DEPENDPATH += $$PWD/../../../usr/lib/x86_64-linux-gnu/hdf5/serial/lib/include

unix:!macx: PRE_TARGETDEPS += $$PWD/../../../usr/lib/x86_64-linux-gnu/hdf5/serial/lib/libhdf5_cpp.a
