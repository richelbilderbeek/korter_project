include(../RibiClasses/CppAbout/CppAbout.pri)
include(../RibiClasses/CppFileIo/CppFileIo.pri)
include(../RibiClasses/CppHelp/CppHelp.pri)
include(../RibiClasses/CppMenuDialog/CppMenuDialog.pri)
include(../RibiClasses/CppQtAboutDialog/CppQtAboutDialog.pri)
include(../RibiClasses/CppQtHideAndShowDialog/CppQtHideAndShowDialog.pri)

#DEFINES += QWT_NO_SVG
#include(../RibiLibraries/Qwt.pri)

include(../SurfacePlotter/QtSurfacePlotWidget.pri)

#Specific, console
include(korter_project_desktop.pri)

SOURCES += qtmain.cpp

# Qt goes bad with -Weffc++
CONFIG += c++14
QMAKE_CXXFLAGS += -Wall -Wextra -Werror -std=c++14

# Qt
QT += core gui widgets svg

# QResources give this error
QMAKE_CXXFLAGS += -Wno-unused-variable

# gcov
QMAKE_CXXFLAGS += -fprofile-arcs -ftest-coverage
LIBS += -lgcov

# Thanks QDateTime
QMAKE_CXXFLAGS += -Wno-unused-result

# Qwt
# Normal compiling
LIBS += -lqwt-qt5
INCLUDEPATH += /usr/include/qwt

# For crosscompiling
#INCLUDEPATH += /home/richel/GitHubs/RibiLibraries/mxe/usr/i686-w64-mingw32.static/qt5/include
#LIBS += -lqwt
#QT += svg
