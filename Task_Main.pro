QT  += core gui multimedia multimediawidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17
QMAKE_CXXFLAGS_RELEASE -= -O2
QMAKE_LFLAGS_RELEASE -= -O1
SOURCES += \
    Edit.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    Edit.h \
    mainwindow.h

FORMS += \
    mainwindow.ui

RESOURCES += \
resources.qrc
