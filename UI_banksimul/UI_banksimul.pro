QT       += core gui
QT += serialport
QT += network
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    kortinluku.cpp \
    main.cpp \
    mainwindow.cpp \
    nosto.cpp \
    saldo.cpp \
    siirto.cpp \
    tilitapahtumat.cpp

HEADERS += \
    kortinluku.h \
    mainwindow.h \
    nosto.h \
    saldo.h \
    siirto.h \
    tilitapahtumat.h

FORMS += \
    kortinluku.ui \
    mainwindow.ui \
    nosto.ui \
    saldo.ui \
    siirto.ui \
    tilitapahtumat.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

win32: LIBS += -L$$PWD/../build-rfid_dll-Desktop_Qt_5_15_0_MinGW_32_bit-Debug/debug/ -lrfid_dll

INCLUDEPATH += $$PWD/../rfid_dll
DEPENDPATH += $$PWD/../rfid_dll

win32: LIBS += -L$$PWD/../build-DLLPinCodeComponent-Desktop_Qt_5_15_0_MinGW_32_bit-Debug/debug/ -lDLLPinCodeComponent

INCLUDEPATH += $$PWD/../DLLPinCodeComponent
DEPENDPATH += $$PWD/../DLLPinCodeComponent

win32: LIBS += -L$$PWD/../build-restApi_dll-Desktop_Qt_5_15_0_MinGW_32_bit-Debug/debug/ -lrestApi_dll

INCLUDEPATH += $$PWD/../restApi_dll
DEPENDPATH += $$PWD/../restApi_dll
