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
# #################
# Configuration
# GMlib Features
# GM_GL_EXTENSION enables OpenGL extensions
# GM_SCRIPT_LUA enables lua scripting support through wrapper classes
# DEFINES = GM_GL_EXTENSIONS
# DEFINES = GM_GL_EXTENSIONS GM_SCRIPT_LUA
DEFINES = 

# #########################
# Compiler flags
QMAKE_CXXFLAGS = 
QMAKE_CXXFLAGS_DEBUG = -frtti \
    -g
QMAKE_CXXFLAGS_RELEASE = -frtti

# ###########################
# Architecture/environment spesific configuration
# Windows
win32 { 
    # MingGW pacement
    MINGW_DIR = C:/MinGW
    
    # Compiler placement
    QMAKE_CXX = $${MINGW_DIR}/bin/mingw32-g++
    
    # Include Paths
    INCLUDEPATH += $${MINGW_DIR}/include \
        $${MINGW_DIR}/include/GL
}

# Unix
unix { 
    # Compiler
    QMAKE_CXX = g++
    
    # Include Paths
    INCLUDEPATH += "/usr/include" \
        "/usr/include/GL"
    contains( DEFINES, "GM_SCRIPT_LUA" ):INCLUDEPATH += "/usr/include/lua5.1"
}

# ################################################################################
# No configuration beneath this line, unless you know what you are doing.
# ################################################################################
# ################
# QMake project definitions
# Library name
TARGET = GMlib

# QMake template
TEMPLATE = lib

# QMake config
CONFIG -= qt
CONFIG += staticlib \
    debug_and_release

# Destination directory
DESTDIR = dist

# Compilers work directory
OBJECTS_DIR = work/qmake/tmp
RCC_DIR = work/qmake/rcc

# Target
CONFIG( debug, debug|release ) { 
    unix:TARGET = $$join(TARGET,,,_debug)
    win32:TARGET = $$join(TARGET,,,D)
}

# ###########################
# Basic qmake template setup
# Defines that it is a library
TEMPLATE = lib

# ##################################
# Header Files (sorted by "module")
# gmContainer
HEADERS += src/gmArray.h \
    src/gmArrayLX.h \
    src/gmArrayT.h \
    src/gmDMatrix.h \
    src/gmDVector.h \
    src/gmSArray.h \

# gmCore
HEADERS += src/gmAffineSpace.h \
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
HEADERS += src/gmCamera.h \
    src/gmCameraIso.h \
    src/gmDisplayObject.h \
    src/gmLight.h \
    src/gmScene.h \
    src/gmSceneObject.h \
    src/gmWindow.h

# gmDisplayUtils
HEADERS += src/gmArrow3D.h \
    src/gmColor.h \
    src/gmCoordinateSystem.h \
    src/gmGLColor.h \
    src/gmLightG.h \
    src/gmMaterial.h \
    src/gmPathTrack.h \
    src/gmSelector.h \
    src/gmSelectorGrid.h \
    src/gmSphere3D.h \
    src/gmStlObject.h \
    src/gmSurroundingSphere.h \
    src/gmTexture.h \
    src/gmTriangleSystem.h

# gmMisc
HEADERS += src/gmCodeExample.h

# gmOpenGL
HEADERS += src/gmOpenGL.h

# gmParametrics
HEADERS += src/gmParametrics.h \
    src/gmPCurve.h \
    src/gmPSurf.h \
    src/gmPApple.h \
    src/gmPArc.h \
    src/gmPAsteroidalSphere.h \
    src/gmPBezierCurve.h \
    src/gmPBezierSurf.h \
    src/gmPBSplineCurve.h \
    src/gmPButterfly.h \
    src/gmPChrysanthemumCurve.h \
    src/gmPCircle.h \
    src/gmPCylinder.h \
    src/gmPERBSCurve.h \
    src/gmPERBSSurf.h \
    src/gmPLuaScriptCurve.h \
    src/gmPLuaScriptSurf.h \
    src/gmPPlane.h \
    src/gmPRoseCurve.h \
    src/gmPSphere.h \
    src/gmPSteinerSurf.h \
    src/gmPTCurve.h \
    src/gmPTorus.h

# gmUtils
HEADERS += src/gmEvaluatorERBS.h \
    src/gmEvaluatorStatic.h \
    src/gmRandom.h \
    src/gmScript.h \
    src/gmStream.h \
    src/gmString.h \
    src/gmTimer.h

# gmVisualizers
HEADERS += src/gmVContours.h \
    src/gmVDefault.h \
    src/gmVDerivatives.h \
    src/gmVDynamicTexture.h \
    src/gmVGLContoursPhongShader.h \
    src/gmVGLPhongShader.h \
    src/gmVGLShader.h \
    src/gmVisualizer.h \
    src/gmVNormals.h \
    src/gmVPoints.h

# gmGPU
HEADERS += src/gmGLSL.h \
    src/gmGLPhongShader.h

# #############
# Source Files
SOURCES += src/gmCamera.cpp \
    src/gmCameraIso.cpp \
    src/gmCodeExample.cpp \
    src/gmColor.cpp \
    src/gmCoordinateSystem.cpp \
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
    src/gmSurroundingSphere.cpp \
    src/gmTexture.cpp \
    src/gmWindow_GMWindow.cpp \
    src/gmWindow_View.cpp \
    src/gmWindow_ViewSet.cpp

# ######################
# Non C/C++ Source Files
OTHER_FILES += src/lua/pcircle_eval.lua \
    src/lua/psphere_eval.lua \
    src/gmCodeExample \
    src/gmCameraIso \
    src/gmCamera \
    src/gmArrow3D \
    src/gmArrayT \
    src/gmArrayLX \
    src/gmArray \
    src/gmAngle \
    src/gmPBSplineSurf.c \
    src/gmCameraIso.c \
    src/gmCamera.c \
    src/gmArrow3D.c \
    src/gmArrayT.c \
    src/gmArrayLX.c \
    src/gmArray.c \
    src/gmAngle.c \
    src/gmTimer \
    src/gmTexture \
    src/gmSubSpace \
    src/gmString \
    src/gmStream \
    src/gmStlObject \
    src/gmStaticProc2 \
    src/gmStaticProc \
    src/gmSphere3D \
    src/gmSimplex \
    src/gmSelectorGrid \
    src/gmSelector \
    src/gmScript \
    src/gmSceneObject \
    src/gmScene \
    src/gmSArray \
    src/gmRandom \
    src/gmPTorus \
    src/gmPTCurve \
    src/gmPSurf \
    src/gmPSteinerSurf \
    src/gmPSphere \
    src/gmPRoseCurve \
    src/gmPPlane \
    src/gmPoint3D \
    src/gmPoint2D \
    src/gmPoint \
    src/gmPLuaScriptSurf \
    src/gmPLuaScriptCurve \
    src/gmPERBSSurf \
    src/gmPERBSCurve \
    src/gmPCylinder \
    src/gmPCurve \
    src/gmPCircle \
    src/gmPButterfly \
    src/gmPBSplineCurve \
    src/gmPBezierSurf \
    src/gmPBezierCurve \
    src/gmPathTrack \
    src/gmPArc \
    src/gmParametrics \
    src/gmPApple \
    src/gmOpenGL \
    src/gmMisc \
    src/gmMatrix \
    src/gmMaterial \
    src/gmLightG \
    src/gmLight \
    src/gmGLSL \
    src/gmGLPhongShader \
    src/gmGlobal \
    src/gmGLColor \
    src/gmEvaluatorStatic \
    src/gmEvaluatorERBS \
    src/gmDVector \
    src/gmDMatrix \
    src/gmDisplayUtils \
    src/gmDisplayObject \
    src/gmDisplay \
    src/gmCore \
    src/gmContainer \
    src/gmColor \
    src/gmTimer.c \
    src/gmSubSpace_SubSpace.c \
    src/gmSubSpace_Plane.c \
    src/gmSubSpace_Line.c \
    src/gmSubSpace_Cube.c \
    src/gmString.c \
    src/gmStream_Separator.c \
    src/gmStlObject.c \
    src/gmStaticProc_GM_Std_.c \
    src/gmStaticProc_GM_Static_.c \
    src/gmStaticProc_GM_Static3_.c \
    src/gmStaticProc_GM_Static2_.c \
    src/gmStaticProc_GM_Static1_.c \
    src/gmStaticProc2_GM_Static_P_.c \
    src/gmStaticProc2_GM_Static_P2_.c \
    src/gmSphere3D.c \
    src/gmSimplex_Triangle.c \
    src/gmSimplex_Tetrahedron.c \
    src/gmSimplex_Simplex.c \
    src/gmSimplex_LineSegment.c \
    src/gmSelectorGrid.c \
    src/gmSelector.c \
    src/gmSceneObject.c \
    src/gmScene.c \
    src/gmSArray.c \
    src/gmRandom.c \
    src/gmPTorus.c \
    src/gmPTCurve.c \
    src/gmPSurf.c \
    src/gmPSteinerSurf.c \
    src/gmPSphere.c \
    src/gmPRoseCurve.c \
    src/gmPPlane.c \
    src/gmPoint_Vector.c \
    src/gmPoint_UnitVector.c \
    src/gmPoint_Sphere.c \
    src/gmPoint_ScalarPoint.c \
    src/gmPoint_Point.c \
    src/gmPoint_M_I_.c \
    src/gmPoint_Box.c \
    src/gmPoint_Arrow.c \
    src/gmPoint3D_Vector3D.c \
    src/gmPoint3D_UnitVector3D.c \
    src/gmPoint3D_Point3D.c \
    src/gmPoint3D_Plane3D.c \
    src/gmPoint2D_Vector2D.c \
    src/gmPoint2D_UnitVector2D.c \
    src/gmPoint2D_Point2D.c \
    src/gmPLuaScriptSurf.c \
    src/gmPLuaScriptCurve.c \
    src/gmPERBSSurf.c \
    src/gmPERBSCurve.c \
    src/gmPCylinder.c \
    src/gmPCurve.c \
    src/gmPCircle.c \
    src/gmPButterfly.c \
    src/gmPBSplineCurve.c \
    src/gmPBezierSurf.c \
    src/gmPBezierCurve.c \
    src/gmPArc.c \
    src/gmParametrics.c \
    src/gmPApple.c \
    src/gmOpenGL_ScaleObj.c \
    src/gmOpenGL_GLMatrix.cpp \
    src/gmOpenGL_GLMatrix.c \
    src/gmOpenGL_Frustum.c \
    src/gmOpenGL.c \
    src/gmMatrix_SqMatrix.c \
    src/gmMatrix_Matrix.c \
    src/gmMatrix_HqMatrix.c \
    src/gmMaterial_MaterialObjectList.c \
    src/gmMaterial_MaterialObject.c \
    src/gmMaterial_Material.c \
    src/gmLight_Sun.c \
    src/gmLight_SpotLight.c \
    src/gmLight_PointLight.c \
    src/gmLight_Light.c \
    src/gmGLColor.c \
    src/gmEvaluatorStatic.c \
    src/gmEvaluatorERBS.c \
    src/gmDVector.c \
    src/gmDMatrix.c \
    src/gmDisplayObject.c \
    src/gmColor.c \
    src/gmWindow \
    src/gmVPoints \
    src/gmVNormals \
    src/gmVisualizers \
    src/gmVisualizer \
    src/gmVGLShader \
    src/gmVGLPhongShader \
    src/gmVGLContoursPhongShader \
    src/gmVDynamicTextureAnimation \
    src/gmVDynamicTexture \
    src/gmVDerivatives \
    src/gmVDefault \
    src/gmVContours \
    src/gmUtils \
    src/gmWindow_ViewSet.c \
    src/gmWindow_ViewBorder.c \
    src/gmWindow_View.c \
    src/gmWindow_GMWindow.c \
    src/gmVPoints.c \
    src/gmVNormals.c \
    src/gmVisualizer.c \
    src/gmVGLShader.c \
    src/gmVGLPhongShader.c \
    src/gmVGLContoursPhongShader.c \
    src/gmVDynamicTextureAnimation.c \
    src/gmVDynamicTexture.c \
    src/gmVDerivatives.c \
    src/gmVDefault.c \
    src/gmVContours.c \
    src/gmPChrysanthemumCurve \
    src/gmPChrysanthemumCurve.c \
    src/gmPAsteroidalSphere \
    src/gmPAsteroidalSphere.c \
    src/gmTriangleSystem \
    src/gmTriangleSystem_TSVertex.c \
    src/gmTriangleSystem_TSTriangle.c \
    src/gmTriangleSystem_TSTile.c \
    src/gmTriangleSystem_TSLine.c \
    src/gmTriangleSystem_TSEdge.c \
    src/gmTriangleSystem_TriangleSystem.c \
    src/gmTriangleSystem_TriangleFacets.c \
    src/gmCoordinateSystem \
    src/gmSurroundingSphere
