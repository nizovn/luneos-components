TEMPLATE = lib
TARGET = ../LuneOSApplication

QT += core-private qml qml-private quick quick-private gui-private
CONFIG += qt plugin

CONFIG += c++11 no_keywords

TARGET = $$qtLibraryTarget($$TARGET)
uri = LuneOS.Application

HEADERS += \
    plugin.h \
    applicationwindow.h

SOURCES += \
    plugin.cpp \
    applicationwindow.cpp

installPath = $$[QT_INSTALL_QML]/$$replace(uri, \\., /)
target.path = $$installPath
INSTALLS += target
