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



##########################
# Compiler/Linker Settings

win32 {

  ## Compiler
  QMAKE_CXX = C:/MinGW_tdm/bin/mingw32-g++

  ## Compiler Flags
  QMAKE_CXXFLAGS_DEBUG = -g -pg -frtti -fexceptions -c -Wall
  QMAKE_CXXFLAGS_RELEASE = -frtti -fexceptions -c -Wall

  ## Linker Flags
  QMAKE_LFLAGS_DEBUG = -g -pg -frtti -fexceptions -Wall
  QMAKE_LFLAGS_RELEASE = -frtti -fexceptions -Wall
}

unix {

  ## Compiler
  QMAKE_CXX = g++

  ## Compiler Flags
  QMAKE_CXXFLAGS_DEBUG = -g -frtti -fexceptions -c -Wall
  QMAKE_CXXFLAGS_RELEASE = -frtti -fexceptions -c -Wall

  ## Linker Flags
  QMAKE_LFLAGS_DEBUG = -g -frtti -fexceptions -Wall
  QMAKE_LFLAGS_RELEASE = -frtti -fexceptions -Wall
}



##########
# Settings

#DEFINES = GM_GL_EXTENSION


## Defines that it is a library
TEMPLATE = lib
## Adds support for debug and release mode, and tells the qmake it should be a static library
CONFIG += debug_and_release staticlib static

## Turns off Qt libs
QT -= core gui



######################
# Internal Directories

## Defines some internal work directories
OBJECTS_DIR = ../../work/qmake/tmp
RCC_DIR = ../../work/qmake/rcc



###############
# Include paths

INCLUDEPATH += ../../src

## Windows include paths
win32 {
INCLUDEPATH += \
  C:/MinGW_tdm/include \
  C:/MinGW_tdm/include/GL
}

## Unix include paths
unix {
INCLUDEPATH += \
  -I"/usr/include" \
  -I"/usr/include/GL" \
  -I"/usr/include/qt4"
}


###########
# Libraries

## Windows linkage
win32 {
LIBS = \
  -lopengl32 \
  -lglu32 \
  -lglee
}

## Unix Linkage
unix {
LIBS = \
  -L"/usr/lib" \
  -lstdc++ \
  -lGL \
  -lGLU
}



##############
# Header Files

# gmContainer
HEADERS += \
  ../../src/gmArray.h \
  ../../src/gmArrayLX.h \
  ../../src/gmArrayT.h \
  ../../src/gmDMatrix.h \
  ../../src/gmDVector.h \
  ../../src/gmSArray.h


# gmCore
HEADERS += \
  ../../src/gmAffineSpace.h \
  ../../src/gmAngle.h \
  ../../src/gmGlobal.h \
  ../../src/gmMatrix.h \
  ../../src/gmPoint.h \
  ../../src/gmPoint2D.h \
  ../../src/gmPoint3D.h \
  ../../src/gmSimplex.h \
  ../../src/gmStaticProc.h \
  ../../src/gmStaticProc2.h \
  ../../src/gmSubSpace.h


# gmDisplay
HEADERS += \
  ../../src/gmCamera.h \
  ../../src/gmCameraIso.h \
  ../../src/gmDisplayObject.h \
  ../../src/gmLight.h \
  ../../src/gmScene.h \
  ../../src/gmSceneObject.h \
  ../../src/gmWindow.h


# gmDisplayUtils
HEADERS += \
  ../../src/gmArrow3D.h \
  ../../src/gmColor.h \
  ../../src/gmDCurve.h \
  ../../src/gmDSurf.h \
  ../../src/gmGLColor.h \
  ../../src/gmLightG.h \
  ../../src/gmMaterial.h \
  ../../src/gmSelector.h \
  ../../src/gmSelectorGrid.h \
  ../../src/gmSphere3D.h \
  ../../src/gmStlObject.h \
  ../../src/gmTexture.h \
  ../../src/gmTriangle.h


# gmMisc
HEADERS += \
  ../../src/gmCodeExample.h


# gmOpenGL
HEADERS += \
  ../../src/gmOpenGL.h


# gmParametrics
HEADERS += \
  ../../src/gmPApple.h \
  ../../src/gmParametrics.h \
  ../../src/gmPArc.h \
  ../../src/gmPBezierCurve.h \
  ../../src/gmPBezierSurf.h \
  ../../src/gmPBSplineCurve.h \
  ../../src/gmPButterfly.h \
  ../../src/gmPCircle.h \
  ../../src/gmPCurve.h \
  ../../src/gmPCylinder.h \
  ../../src/gmPERBSCurve.h \
  ../../src/gmPERBSSurf.h \
  ../../src/gmPPlane.h \
  ../../src/gmPRoseCurve.h \
  ../../src/gmPSphere.h \
  ../../src/gmPSteinerSurf.h \
  ../../src/gmPSurf.h \
  ../../src/gmPTCurve.h \
  ../../src/gmPTorus.h


# gmDParametrics
HEADERS += \
  ../../src/gmDPApple.h \
  ../../src/gmDParametrics.h \
  ../../src/gmDPArc.h \
  ../../src/gmDPBezierCurve.h \
  ../../src/gmDPBezierSurf.h \
  ../../src/gmDPBSplineCurve.h \
  ../../src/gmDPButterfly.h \
  ../../src/gmDPCircle.h \
  ../../src/gmDPCylinder.h \
  ../../src/gmDPERBSCurve.h \
  ../../src/gmDPERBSSurf.h \
  ../../src/gmDPPlane.h \
  ../../src/gmDPRoseCurve.h \
  ../../src/gmDPSphere.h \
  ../../src/gmDPSteinerSurf.h \
  ../../src/gmDPTCurve.h \
  ../../src/gmDPTorus.h


# gmUtils
HEADERS += \
  ../../src/gmEvaluatorERBS.h \
  ../../src/gmEvaluatorStatic.h \
  ../../src/gmRandom.h \
  ../../src/gmStream.h \
  ../../src/gmString.h \
  ../../src/gmTimer.h


# gmVisualizers
HEADERS += \
  ../../src/gmVContours.h \
  ../../src/gmVDefault.h \
  ../../src/gmVDerivatives.h \
  ../../src/gmVGLContoursPhongShader.h \
  ../../src/gmVGLPhongShader.h \
  ../../src/gmVGLShader.h \
  ../../src/gmVisualizer.h \
  ../../src/gmVNormals.h \
  ../../src/gmVPoints.h \
  ../../src/gmVSurroundingSphere.h


# gmGPU
HEADERS += \
  ../../src/gmGLSL.h \
  ../../src/gmGLPhongShader.h





##############
# Source Files

SOURCES += \
  ../../src/gmCamera.cpp \
  ../../src/gmCameraIso.cpp \
  ../../src/gmCodeExample.cpp \
  ../../src/gmColor.cpp \
  ../../src/gmDisplayObject.cpp \
  ../../src/gmGLSL.cpp \
  ../../src/gmGLPhongShader.cpp \
  ../../src/gmLight_Light.cpp \
  ../../src/gmLight_PointLight.cpp \
  ../../src/gmLight_SpotLight.cpp \
  ../../src/gmLight_Sun.cpp \
  ../../src/gmLightG_PointLightG.cpp \
  ../../src/gmLightG_SpotLightG.cpp \
  ../../src/gmMaterial_Material.cpp \
  ../../src/gmMaterial_MaterialObjectList.cpp \
  ../../src/gmOpenGL_GLMatrix.cpp \
  ../../src/gmScene.cpp \
  ../../src/gmSceneObject.cpp \
  ../../src/gmStlObject.cpp \
  ../../src/gmStream_Separator.cpp \
  ../../src/gmTexture.cpp \
  ../../src/gmWindow_GMWindow.cpp \
  ../../src/gmWindow_View.cpp \
  ../../src/gmWindow_ViewSet.cpp

