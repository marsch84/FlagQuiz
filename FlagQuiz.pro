TARGET  = FlagQuiz
QT += widgets xml
DESTDIR = bin

GEN_DIR = $$DESTDIR/GeneratedFiles

OBJECTS_DIR = $$GEN_DIR/obj
UI_DIR = $$GEN_DIR/ui
MOC_DIR = $$GEN_DIR/moc

INCLUDEPATH += $$PWD/src
DEPENDPATH += $$PWD/src

# Input
SOURCES += \
    src/main.cpp \
    src/mainwindow.cpp \
    src/start.cpp \
    src/highscores.cpp \
    src/data.cpp \
    src/game.cpp

HEADERS += \
    src/mainwindow.h \
    src/highscores.h \
    src/start.h \
    src/data.h \
    src/game.h

FORMS += \
    src/mainwindow.ui \
    src/signs.ui \
    src/meanings.ui \
    src/game.ui \
    src/start.ui

RESOURCES += \
    resources/resources_FlagQuiz.qrc
