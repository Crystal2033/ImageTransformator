QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    exceptions.cpp \
    graphmenuwidget.cpp \
    histogram.cpp \
    imagefunctions.cpp \
    imagewidget.cpp \
    main.cpp \
    mainwindow.cpp \
    singlepixeltransforms.cpp

HEADERS += \
    exceptions.h \
    graphmenuwidget.h \
    histogram.h \
    imagefunctions.h \
    imagewidget.h \
    mainwindow.h \
    singlepixeltransforms.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
