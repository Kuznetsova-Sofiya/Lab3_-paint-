QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ConnectorsFig.cpp \
    drawingarea.cpp \
    drawingwidget.cpp \
    ellipse.cpp \
    main.cpp \
    mainwindow.cpp \
    rectangle.cpp \
    triangle.cpp

HEADERS += \
    Connectors.h \
    DrawingArea.h \
    Ellipse.h \
    drawingwidget.h \
    figure.h \
    mainwindow.h \
    rectangle.h \
    triangle.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
