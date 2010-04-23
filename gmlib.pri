# ###############################################################################
# #
# # Copyright (C) 1994 Narvik University College
# # Contact: GMlib Online Portal at http://episteme.hin.no
# #
# # This file is part of the Geometric Modeling Library, GMlib.
# #
# # GMlib is free software: you can redistribute it and/or modify
# # it under the terms of the GNU Lesser General Public License as published by
# # the Free Software Foundation, either version 3 of the License, or
# # (at your option) any later version.
# #
# # GMlib is distributed in the hope that it will be useful,
# # but WITHOUT ANY WARRANTY; without even the implied warranty of
# # MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
# # GNU Lesser General Public License for more details.
# #
# # You should have received a copy of the GNU Lesser General Public License
# # along with GMlib. If not, see <http://www.gnu.org/licenses/>.
# #
# ###############################################################################


GMLIB_ROOT = $$PWD


isEmpty(GMLIB_LIBRARY_BASENAME) {
    GMLIB_LIBRARY_BASENAME = lib
}




# #################
# Configuration
# GMlib Features
# GM_GL_EXTENSION enables OpenGL extensions
# GM_SCRIPT_LUA enables lua scripting support through wrapper classes
 DEFINES += GM_GL_EXTENSION
# DEFINES = GM_GL_EXTENSION GM_SCRIPT_LUA
# DEFINES += GMLIB_LIBRARY_BASENAME=\\\"$$GMLIB_LIBRARY_BASENAME\\\"




# Binary dir path
GMLIB_BIN_PATH = $$GMLIB_ROOT/bin

# Include dir path
GMLIB_INCLUDE_PATH = $$GMLIB_ROOT/include/gmlib
GMLIB_INCLUDE_LUA_PATH = $$GMLIB_INCLUDE_PATH/lua

# Lib dir path
GMLIB_LIBRARY_PATH = $$GMLIB_ROOT/$$GMLIB_LIBRARY_BASENAME/gmlib

# Code dir path
GMLIB_SRC_PATH = $$GMLIB_ROOT/src


DEPENDPATH += \
    $$GMLIB_SRC_PATH


CONFIG(debug, debug|release):OBJECTS_DIR = $${OUT_PWD}/.obj/debug
CONFIG(release, debug|release):OBJECTS_DIR = $${OUT_PWD}/.obj/release

CONFIG(debug, debug|release):MOC_DIR = $${OUT_PWD}/.moc/debug
CONFIG(release, debug|release):MOC_DIR = $${OUT_PWD}/.moc/release

RCC_DIR = $${OUT_PWD}/.rcc
UI_DIR = $${OUT_PWD}/.uic




win32 {
    DLLDESTDIR = GMLIB_BIN_PATH
}

DESTDIR = $$GMLIB_LIBRARY_PATH

