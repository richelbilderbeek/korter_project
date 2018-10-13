#!/bin/sh
#From http://richelbilderbeek.nl/CppQtCrosscompileToWindowsExample15.htm
i686-w64-mingw32.static-qmake-qt5 Toolkorter_project_desktop.pro
make
echo "Done"
