include(../RibiClasses/CppAbout/CppAbout.pri)
include(../RibiClasses/CppFileIo/CppFileIo.pri)
include(../RibiClasses/CppHelp/CppHelp.pri)
include(../RibiClasses/CppMenuDialog/CppMenuDialog.pri)
include(../RibiClasses/CppQtAboutDialog/CppQtAboutDialog.pri)
include(../RibiClasses/CppQtHideAndShowDialog/CppQtHideAndShowDialog.pri)

DEFINES += QWT_NO_SVG

include(../RibiLibraries/Qwt.pri)
include(../SurfacePlotter/QtSurfacePlotWidget.pri)

#Specific, console
include(korter_project_desktop.pri)

SOURCES += qtmain.cpp

# Qt goes bad with -Weffc++
CONFIG += c++14
QMAKE_CXXFLAGS += -Wall -Wextra -Werror -std=c++14

# Qt
equals(QT_MAJOR_VERSION, 4): LIBS +=  -lQtSvg

# QResources give this error
QMAKE_CXXFLAGS += -Wno-unused-variable

# gcov
QMAKE_CXXFLAGS += -fprofile-arcs -ftest-coverage
LIBS += -lgcov

# Thanks QDateTime
QMAKE_CXXFLAGS += -Wno-unused-result
