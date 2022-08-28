QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Algorithms/transformations.cpp \
    Algorithms/windowtransform.cpp \
    Exceptions/exceptions.cpp \
    ImageMiscellaneous/imagefunctions.cpp \
    MainWidgets/histogram.cpp \
    MainWidgets/imagewidget.cpp \
    MenuAndTools/diffTool.cpp \
    MenuAndTools/graphmenuwidget.cpp \
    MenuAndTools/optionstool.cpp \
    MenuAndTools/rangeslider.cpp \
    MenuAndTools/transformoptions.cpp \
    MenuAndTools/graphmenuwidget.cpp \
    main.cpp \
    mainwindow.cpp \

HEADERS += \
    Algorithms/transformations.h \
    Algorithms/windowtransform.h \
    Exceptions/exceptions.h \
    ImageMiscellaneous/imagefunctions.h \
    MainWidgets/histogram.h \
    MainWidgets/imagewidget.h \
    MainWidgets/observer.h \
    MainWidgets/subject.h \
    MenuAndTools/diffTool.h \
    MenuAndTools/graphmenuwidget.h \
    MenuAndTools/optionstool.h \
    MenuAndTools/rangeslider.h \
    MenuAndTools/transformoptions.h \
    MenuAndTools/graphmenuwidget.h \
    mainwindow.h \

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
