TEMPLATE = app

CONFIG += c++11

QT += qml quick widgets

SOURCES += main.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

HEADERS += \
    abstractasyncundoable.h \
    asyncexample1command.h \
    editor.h \
    abstracteditorbehavior.h \
    undoableeditorbehavior.h
