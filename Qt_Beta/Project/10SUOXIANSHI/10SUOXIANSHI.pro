#-------------------------------------------------
#
# Project created by QtCreator 2022-03-07T16:08:29
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = 10SUOXIANSHI
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
        mainwindow.cpp

HEADERS += \
        mainwindow.h \
    ../../YJC66995/sp_avc_h26dec_sdk-20220304/include/vid_receiver.h \
    ../../YJC66995/sp_avc_h26dec_sdk-20220304/include/sp_avc_h264dec.h \
    ../../YJC66995/sp_avc_h26dec_sdk-20220304/include/sp_avc_mux.h \
    ../../YJC66995/sp_avc_h26dec_sdk-20220304/include/sp_avc_section.h \
    ../../YJC66995/sp_avc_h26dec_sdk-20220304/include/sp_avc_uld.h \
    ../../YJC66995/sp_avc_h26dec_sdk-20220304/include/vid_decoder.h \
    ../../YJC66995/sp_avc_h26dec_sdk-20220304/include/vid_display.h \
    ../../YJC66995/sp_avc_h26dec_sdk-20220304/include/vid_mux.h

FORMS += \
        mainwindow.ui


win32: LIBS += -L$$PWD/../../YJC66995/sp_avc_h26dec_sdk-20220304/lib32/ -lvid_receiver

INCLUDEPATH += $$PWD/../../YJC66995/sp_avc_h26dec_sdk-20220304/include
DEPENDPATH += $$PWD/../../YJC66995/sp_avc_h26dec_sdk-20220304/include
