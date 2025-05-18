TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        app.cpp \
        gomb.cpp \
        legordulowidget.cpp \
        main.cpp \
        graphics/graphics.cpp \
        statictext.cpp \
        sudokuapp.cpp \
        sudokugame.cpp \
        sudokugenerator.cpp \
        sudokunumber.cpp \
        widget.cpp


INCLUDEPATH += $$PWD/.
DEPENDPATH += $$PWD/.

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/./ -llibSDL2.dll
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/./ -llibSDL2.dll
else:unix: LIBS += -L$$PWD/./ -llibSDL2.dll

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/./ -llibSDL2_ttf.dll
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/./ -llibSDL2_ttf.dll
else:unix: LIBS += -L$$PWD/./ -llibSDL2_ttf.dll


INCLUDEPATH += $$PWD/SDL2
DEPENDPATH += $$PWD/SDL2

HEADERS += \
    app.hpp \
    gomb.hpp \
    legordulowidget.hpp \
    statictext.hpp \
    sudokuapp.hpp \
    sudokugame.hpp \
    sudokugenerator.hpp \
    sudokunumber.hpp \
    widget.hpp
