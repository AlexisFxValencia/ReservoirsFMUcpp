TEMPLATE = app
TARGET = Reservoirs_valve_cpp
QT += widgets
SOURCES += main.cpp \
    fmureader.cpp \
    mainwindow.cpp

FORMS += \
    mainwindow.ui

HEADERS += \
    fmureader.h \
    mainwindow.h

unix: LIBS += -L$$PWD/../FMI4cpp/build/src/ -lfmi4cpp

INCLUDEPATH += $$PWD/../FMI4cpp/include
DEPENDPATH += $$PWD/../FMI4cpp/include

DISTFILES += \
    readme.md
