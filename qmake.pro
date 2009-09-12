################################################################################
##
## Copyright (C) 1994 Narvik University College
## Contact: GMlib Online Portal at http://episteme.hin.no
##
## This file is part of the Geometric Modeling Library, GMlib.
##
## GMlib is free software: you can redistribute it and/or modify
## it under the terms of the GNU Lesser General Public License as published by
## the Free Software Foundation, either version 3 of the License, or
## (at your option) any later version.
##
## GMlib is distributed in the hope that it will be useful,
## but WITHOUT ANY WARRANTY; without even the implied warranty of
## MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
## GNU Lesser General Public License for more details.
##
## You should have received a copy of the GNU Lesser General Public License
## along with GMlib.  If not, see <http://www.gnu.org/licenses/>.
##
################################################################################



################
# GMlib Features

#DEFINES = GM_GL_EXTENSION
#DEFINES = GM_GL_EXTENSION GM_SCRIPT_LUA



##################################
# Compiler/Linker && Include Paths

## Win32 spesific options
win32 {

  # MingGW pacement
  MINGW_DIR = C:/MinGW

  # Compiler placement
  QMAKE_CXX = $${MINGW_DIR}/bin/mingw32-g++

  # Include Paths
  INCLUDEPATH += \
    $${MINGW_DIR}/include \
    $${MINGW_DIR}/include/GL

  LIBS += \
    -L"$${MINGW_DIR}/lib" \
    -lGLee \
    -lopengl32 \
    -lglu32
}

## Unix Spesific options
unix {

  # Compiler
  QMAKE_CXX = g++

  # Include Paths
  INCLUDEPATH += \
    "/usr/include" \
    "/usr/include/GL"
#    "/usr/include/lua5.1"

  # Tells qmake to create a static library
  CONFIG += staticlib
}



#######################
# Compiler/Linker Flags

# Compiler
# Debug / Release
QMAKE_CXXFLAGS_DEBUG =
QMAKE_CXXFLAGS_RELEASE =
#QMAKE_CXXFLAGS = -g -pg -frtti
QMAKE_CXXFLAGS = -frtti

# Linker
QMAKE_LFLAGS = ${QMAKE_CXXFLAGS}



############################
# Basic qmake template setup

# Defines that it is a library
TEMPLATE = lib

# Removes stuff specialized for qt applications and libraries
CONFIG -= qt

# Tells qmake to create a static library
#CONFIG += staticlib



#################
# GMlib Internals

# Library Name
TARGET = GMlib

# Defines some internal work directories
DESTDIR = dist/lib
OBJECTS_DIR = work/qmake/tmp
RCC_DIR = work/qmake/rcc



###################################
# Header Files (sorted by "module")

# gmContainer
HEADERS += \
  src/gmArray.h \
  src/gmArrayLX.h \
  src/gmArrayT.h \
  src/gmDMatrix.h \
  src/gmDVector.h \
  src/gmSArray.h


# gmCore
HEADERS += \
  src/gmAffineSpace.h \
  src/gmAngle.h \
  src/gmGlobal.h \
  src/gmMatrix.h \
  src/gmPoint.h \
  src/gmPoint2D.h \
  src/gmPoint3D.h \
  src/gmSimplex.h \
  src/gmStaticProc.h \
  src/gmStaticProc2.h \
  src/gmSubSpace.h


# gmDisplay
HEADERS += \
  src/gmCamera.h \
  src/gmCameraIso.h \
  src/gmDisplayObject.h \
  src/gmLight.h \
  src/gmScene.h \
  src/gmSceneObject.h \
  src/gmWindow.h


# gmDisplayUtils
HEADERS += \
  src/gmArrow3D.h \
  src/gmColor.h \
  src/gmDCurve.h \
  src/gmDSurf.h \
  src/gmGLColor.h \
  src/gmLightG.h \
  src/gmMaterial.h \
  src/gmPathTrack.h \
  src/gmSelector.h \
  src/gmSelectorGrid.h \
  src/gmSphere3D.h \
  src/gmStlObject.h \
  src/gmTexture.h \
  src/gmTriangle.h


# gmMisc
HEADERS += \
  src/gmCodeExample.h


# gmOpenGL
HEADERS += \
  src/gmOpenGL.h


# gmParametrics
HEADERS += \
  src/gmPApple.h \
  src/gmParametrics.h \
  src/gmPArc.h \
  src/gmPBezierCurve.h \
  src/gmPBezierSurf.h \
  src/gmPBSplineCurve.h \
  src/gmPButterfly.h \
  src/gmPCircle.h \
  src/gmPCurve.h \
  src/gmPCylinder.h \
  src/gmPERBSCurve.h \
  src/gmPERBSSurf.h \
  src/gmPPlane.h \
  src/gmPRoseCurve.h \
  src/gmPSphere.h \
  src/gmPSteinerSurf.h \
  src/gmPSurf.h \
  src/gmPTCurve.h \
  src/gmPTorus.h


# gmDParametrics
HEADERS += \
  src/gmDPApple.h \
  src/gmDParametrics.h \
  src/gmDPArc.h \
  src/gmDPBezierCurve.h \
  src/gmDPBezierSurf.h \
  src/gmDPBSplineCurve.h \
  src/gmDPButterfly.h \
  src/gmDPCircle.h \
  src/gmDPCylinder.h \
  src/gmDPERBSCurve.h \
  src/gmDPERBSSurf.h \
  src/gmDPLuaScriptCurve.h \
  src/gmDPLuaScriptSurf.h \
  src/gmDPPlane.h \
  src/gmDPRoseCurve.h \
  src/gmDPSphere.h \
  src/gmDPSteinerSurf.h \
  src/gmDPTCurve.h \
  src/gmDPTorus.h


# gmUtils
HEADERS += \
  src/gmEvaluatorERBS.h \
  src/gmEvaluatorStatic.h \
  src/gmRandom.h \
  src/gmScript.h \
  src/gmStream.h \
  src/gmString.h \
  src/gmTimer.h


# gmVisualizers
HEADERS += \
  src/gmVContours.h \
  src/gmVCoordinateSystem.h \
  src/gmVDefault.h \
  src/gmVDerivatives.h \
  src/gmVDynamicTexture.h \
  src/gmVGLContoursPhongShader.h \
  src/gmVGLPhongShader.h \
  src/gmVGLShader.h \
  src/gmVisualizer.h \
  src/gmVNormals.h \
  src/gmVPoints.h \
  src/gmVSurroundingSphere.h


# gmGPU
HEADERS += \
  src/gmGLSL.h \
  src/gmGLPhongShader.h





##############
# Source Files

SOURCES += \
  src/gmCamera.cpp \
  src/gmCameraIso.cpp \
  src/gmCodeExample.cpp \
  src/gmColor.cpp \
  src/gmDisplayObject.cpp \
  src/gmGLSL.cpp \
  src/gmGLPhongShader.cpp \
  src/gmLight_Light.cpp \
  src/gmLight_PointLight.cpp \
  src/gmLight_SpotLight.cpp \
  src/gmLight_Sun.cpp \
  src/gmLightG_PointLightG.cpp \
  src/gmLightG_SpotLightG.cpp \
  src/gmMaterial_Material.cpp \
  src/gmMaterial_MaterialObjectList.cpp \
  src/gmOpenGL_GLMatrix.cpp \
  src/gmPathTrack.cpp \
  src/gmScene.cpp \
  src/gmSceneObject.cpp \
  src/gmScript_LuaScript.cpp \
  src/gmScript_LuaVar.cpp \
  src/gmScript_Script.cpp \
  src/gmStlObject.cpp \
  src/gmStream_Separator.cpp \
  src/gmTexture.cpp \
  src/gmWindow_GMWindow.cpp \
  src/gmWindow_View.cpp \
  src/gmWindow_ViewSet.cpp


