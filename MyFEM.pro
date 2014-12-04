#QT += core gui
CONFIG += c++11
#greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

HEADERS += \
    area.h \
    MyFEM.h \
    simplex.h \
    matrix.h \
    lesystem.h \
    numvector.h \
    abstractfunctor.h \
    myfunctor.h \
    nesystem.h

SOURCES += \
    area.cpp \
    main.cpp \
    simplex.cpp \
    matrix.cpp \
    lesystem.cpp \
    numvector.cpp \
    abstractfunctor.cpp \
    myfunctor.cpp \
    nesystem.cpp

TARGET = FEM_lab
