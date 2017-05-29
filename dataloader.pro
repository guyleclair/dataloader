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
        FenetrePrincipale.cpp \
    h5utils.cpp

HEADERS  += FenetrePrincipale.h\
    h5utils.h \
    Point3D.h \
    rapidjson/error/en.h \
    rapidjson/error/error.h \
    rapidjson/internal/biginteger.h \
    rapidjson/internal/diyfp.h \
    rapidjson/internal/dtoa.h \
    rapidjson/internal/ieee754.h \
    rapidjson/internal/itoa.h \
    rapidjson/internal/meta.h \
    rapidjson/internal/pow10.h \
    rapidjson/internal/regex.h \
    rapidjson/internal/stack.h \
    rapidjson/internal/strfunc.h \
    rapidjson/internal/strtod.h \
    rapidjson/internal/swap.h \
    rapidjson/msinttypes/inttypes.h \
    rapidjson/msinttypes/stdint.h \
    rapidjson/allocators.h \
    rapidjson/document.h \
    rapidjson/encodedstream.h \
    rapidjson/encodings.h \
    rapidjson/filereadstream.h \
    rapidjson/filewritestream.h \
    rapidjson/fwd.h \
    rapidjson/istreamwrapper.h \
    rapidjson/memorybuffer.h \
    rapidjson/memorystream.h \
    rapidjson/ostreamwrapper.h \
    rapidjson/pointer.h \
    rapidjson/prettywriter.h \
    rapidjson/rapidjson.h \
    rapidjson/reader.h \
    rapidjson/schema.h \
    rapidjson/stream.h \
    rapidjson/stringbuffer.h \
    rapidjson/writer.h

CONFIG += c++11


unix:!macx: LIBS += -L/usr/lib/x86_64-linux-gnu/hdf5/serial/lib/lib/ -lhdf5_hl_cpp

INCLUDEPATH += /usr/lib/x86_64-linux-gnu/hdf5/serial/lib/include
DEPENDPATH += /usr/lib/x86_64-linux-gnu/hdf5/serial/lib/include

unix:!macx: PRE_TARGETDEPS += /usr/lib/x86_64-linux-gnu/hdf5/serial/lib/lib/libhdf5_hl_cpp.a

unix:!macx: LIBS += -L/usr/lib/x86_64-linux-gnu/hdf5/serial/lib/ -lhdf5

INCLUDEPATH += /usr/lib/x86_64-linux-gnu/hdf5/serial/lib/include
DEPENDPATH += /usr/lib/x86_64-linux-gnu/hdf5/serial/lib/include

unix:!macx: PRE_TARGETDEPS += /usr/lib/x86_64-linux-gnu/hdf5/serial/lib/libhdf5.a

unix:!macx: LIBS += -L/usr/lib/x86_64-linux-gnu/hdf5/serial/lib/ -lhdf5_cpp

INCLUDEPATH += /usr/lib/x86_64-linux-gnu/hdf5/serial/lib/include
DEPENDPATH += /usr/lib/x86_64-linux-gnu/hdf5/serial/lib/include

unix:!macx: PRE_TARGETDEPS += /usr/lib/x86_64-linux-gnu/hdf5/serial/lib/libhdf5_cpp.a
