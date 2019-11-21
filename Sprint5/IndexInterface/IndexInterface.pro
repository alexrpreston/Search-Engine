TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        documentparser.cpp \
        main.cpp

HEADERS += \
    AVLTree.h \
    HashMap.h \
    IndexInterface.h \
    documentparser.h

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../myhtml/lib/release/ -lmyhtml
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../myhtml/lib/debug/ -lmyhtml
else:unix: LIBS += -L$$PWD/../../../myhtml/lib/ -lmyhtml

INCLUDEPATH += $$PWD/../../../myhtml/include
DEPENDPATH += $$PWD/../../../myhtml/include
