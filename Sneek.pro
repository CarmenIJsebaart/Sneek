TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp

QMAKE_CXXFLAGS += -std=c++11 -Wall -Wextra
LIBS += -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
LIBS += -LC:/SFML/lib
LIBS += -LC:\SFML\bin

include(deployment.pri)
qtcAddDeployment()

INCLUDEPATH += C:/SFML/include
INCLUDEPATH += C:/Boost/include

INCLUDEPATH += C:/Boost
LIBS += C:/Boost/stage/lib/libboost_filesystem-mgw49-mt-1_59.a
LIBS += C:/Boost/stage/lib/libboost_system-mgw49-mt-d-1_59.a

HEADERS +=
