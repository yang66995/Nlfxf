#-------------------------------------------------
#
# Project created by QtCreator 2021-10-26T11:04:39
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

TARGET = fft
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        mainwindow.cpp \
        qcustomplot.cpp \
    fft.cpp \
    fft.cpp \
    qcustomplot.cpp

HEADERS += \
        mainwindow.h \
        qcustomplot.h \
    fft.h \
    fftw3.h \
    fft.h \
    qcustomplot.h \
    fftw3.h

FORMS += \
        mainwindow.ui




unix:!macx|win32: LIBS += -L$$PWD/../build-fft-Desktop_Qt_5_9_6_MinGW_32bit-Debug/debug/fftw-3.3.5-dll32/ -llibfftw3-3

INCLUDEPATH += $$PWD/../build-fft-Desktop_Qt_5_9_6_MinGW_32bit-Debug/debug/fftw-3.3.5-dll32
DEPENDPATH += $$PWD/../build-fft-Desktop_Qt_5_9_6_MinGW_32bit-Debug/debug/fftw-3.3.5-dll32

unix:!macx|win32: LIBS += -L$$PWD/../fftw-3.3.5-dll32/ -llibfftw3-3

INCLUDEPATH += $$PWD/../fftw-3.3.5-dll32
DEPENDPATH += $$PWD/../fftw-3.3.5-dll32
