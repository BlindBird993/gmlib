
-include makeconf_global.mak

##############
# Project Name
PROJECTNAME = GMlib

##############
# Project Type
PROJECTTYPE = lib


#########
# Headers


# gmContainer
HEADERS = \
  gmContainer \
  \
  gmArray \
  gmArray.h \
  gmArrayLX \
  gmArrayLX.h \
  gmArrayT \
  gmArrayT.h \
  gmDMatrix \
  gmDMatrix.h \
  gmDVector \
  gmDVector.h \
  gmSArray \
  gmSArray.h \

# gmCore
HEADERS += \
  gmCore \
  \
  gmAffineSpace \
  gmAffineSpace.h \
  gmAngle \
  gmAngle.h \
  gmGlobal \
  gmGlobal.h \
  gmMatrix \
  gmMatrix.h \
  gmPoint \
  gmPoint.h \
  gmPoint2D \
  gmPoint2D.h \
  gmPoint3D \
  gmPoint3D.h \
  gmSimplex \
  gmSimplex.h \
  gmStaticProc \
  gmStaticProc.h \
  gmStaticProc2 \
  gmStaticProc2.h \
  gmSubSpace \
  gmSubSpace.h

# gmDisplay
HEADERS += \
  gmDisplay \
  \
	gmCamera \
	gmCamera.h \
	gmCameraIso \
	gmCameraIso.h \
  gmDisplayObject \
  gmDisplayObject.h \
  gmLight \
  gmLight.h \
  gmScene \
  gmScene.h \
  gmSceneObject \
  gmSceneObject.h \
  gmWindow \
  gmWindow.h

# gmDisplayUtils
HEADERS += \
  gmDisplayUtils \
  \
  gmArrow3D \
  gmArrow3D.h \
  gmColor \
  gmColor.h \
  gmDCurve \
  gmDCurve.h \
  gmDSurf \
  gmDSurf.h \
  gmGLColor \
  gmGLColor.h \
  gmLightG \
  gmLightG.h \
	gmMaterial \
	gmMaterial.h \
	gmSelector \
	gmSelector.h \
	gmSelectorGrid \
	gmSelectorGrid.h \
	gmSphere3D \
	gmSphere3D.h \
	gmStlObject \
	gmStlObject.h \
	gmTexture \
	gmTexture.h \
	gmTriangle \
	gmTriangle.h \

# gmMisc
HEADERS += \
  gmMisc \
  \
  gmCodeExample \
  gmCodeExample.h

# gmOpenGL
HEADERS += \
  gmOpenGL \
  \
  gmOpenGL.h

# gmParametrics
HEADERS += \
  gmParametrics \
  gmParametrics.h \
  \
  gmPApple \
  gmPApple.h \
  gmPArc \
  gmPArc.h \
  gmPBezierCurve \
  gmPBezierCurve.h \
  gmPBezierSurf \
  gmPBezierSurf.h \
  gmPBSplineCurve \
  gmPBSplineCurve.h \
  gmPButterfly \
  gmPButterfly.h \
  gmPCircle \
  gmPCircle.h \
  gmPCurve \
  gmPCurve.h \
  gmPCylinder \
  gmPCylinder.h \
  gmPERBSCurve \
  gmPERBSCurve.h \
  gmPERBSSurf \
  gmPERBSSurf.h \
  gmPPlane \
  gmPPlane.h \
  gmPRoseCurve \
  gmPRoseCurve.h \
  gmPSphere \
  gmPSphere.h \
  gmPSteinerSurf \
  gmPSteinerSurf.h \
  gmPSurf \
  gmPSurf.h \
  gmPTCurve \
  gmPTCurve.h \
  gmPTorus \
  gmPTorus.h

# gmDParametrics
HEADERS += \
  gmDParametrics \
  gmDParametrics.h \
  \
  gmDPApple \
  gmDPApple.h \
  gmDPArc \
  gmDPArc.h \
  gmDPBezierCurve \
  gmDPBezierCurve.h \
  gmDPBezierSurf \
  gmDPBezierSurf.h \
  gmDPBSplineCurve \
  gmDPBSplineCurve.h \
  gmDPButterfly \
  gmDPButterfly.h \
  gmDPCircle \
  gmDPCircle.h \
  gmDPCylinder \
  gmDPCylinder.h \
  gmDPERBSCurve \
  gmDPERBSCurve.h \
  gmDPERBSSurf \
  gmDPERBSSurf.h \
  gmDPPlane \
  gmDPPlane.h \
  gmDPRoseCurve \
  gmDPRoseCurve.h \
  gmDPSphere \
  gmDPSphere.h \
  gmDPSteinerSurf \
  gmDPSteinerSurf.h \
  gmDPTCurve \
  gmDPTCurve.h \
  gmDPTorus \
  gmDPTorus.h

# gmUtils
HEADERS += \
  gmUtils \
  \
  gmTimer \
  gmTimer.h \
  gmRandom \
  gmRandom.h \
  gmStream \
  gmStream.h \
  gmString \
  gmString.h

# gmVisualizers
HEADERS += \
  gmVisualizers \
  \
	gmVisualizer \
	gmVisualizer.h \
  gmVContours \
  gmVContours.h \
  gmVDefault \
  gmVDefault.h \
  gmVDerivatives \
  gmVDerivatives.h \
  gmVNormals \
  gmVNormals.h \
  gmVPoints \
  gmVPoints.h \
  gmVSurroundingSphere \
  gmVSurroundingSphere.h \


# Undefined TEMPORARY
HEADERS += \
  gmEvaluatorERBS \
  gmEvaluatorERBS.h \
  gmEvaluatorStatic \
  gmEvaluatorStatic.h


#################################
# Header Extentensions (template)
HEADER_EXTS = \
  gmAffineSpace.c \
  gmAngle.c \
  gmArray.c \
  gmArrayLX.c \
  gmArrayT.c \
  gmArrow3D.c \
  gmCamera.c \
  gmCameraIso.c \
  gmColor.c \
  gmDCurve.c \
  gmDMatrix.c \
  gmDParametrics.c \
  gmDPApple.c \
  gmDPArc.c \
  gmDPBezierCurve.c \
  gmDPBezierSurf.c \
  gmDPBSplineCurve.c \
  gmDPButterfly.c \
  gmDPCircle.c \
  gmDPCylinder.c \
  gmDPERBSCurve.c \
  gmDPERBSSurf.c \
  gmDPPlane.c \
  gmDPRoseCurve.c \
  gmDPSphere.c \
  gmDPSteinerSurf.c \
  gmDPTCurve.c \
  gmDPTorus.c \
  gmDSurf.c \
  gmDVector.c \
  gmDisplayObject.c \
  gmEvaluatorERBS.c \
  gmEvaluatorStatic.c \
  gmGLColor.c \
  gmLight_Light.c \
  gmLight_PointLight.c \
  gmLight_SpotLight.c \
  gmLight_Sun.c \
  gmMaterial_Material.c \
  gmMaterial_MaterialObject.c \
  gmMaterial_MaterialObjectList.c \
  gmMatrix_HqMatrix.c \
  gmMatrix_Matrix.c \
  gmMatrix_SqMatrix.c \
  gmOpenGL.c \
  gmOpenGL_Frustum.c \
  gmOpenGL_GLMatrix.c \
  gmOpenGL_ScaleObj.c \
	gmParametrics.c \
  gmPoint_Arrow.c \
  gmPoint_Box.c \
  gmPoint_M_I_.c \
  gmPoint_Point.c \
  gmPoint_ScalarPoint.c \
  gmPoint_Sphere.c  \
  gmPoint_UnitVector.c \
  gmPoint_Vector.c \
  gmPoint2D_Point2D.c \
  gmPoint2D_UnitVector2D.c \
  gmPoint2D_Vector2D.c \
  gmPoint3D_Plane3D.c \
  gmPoint3D_Point3D.c \
  gmPoint3D_UnitVector3D.c \
  gmPoint3D_Vector3D.c \
  gmPApple.c \
  gmPArc.c \
  gmPBezierCurve.c \
  gmPBezierSurf.c \
  gmPBSplineCurve.c \
  gmPButterfly.c \
  gmPCircle.c \
  gmPCurve.c \
  gmPCylinder.c \
  gmPERBSCurve.c \
  gmPERBSSurf.c \
  gmPPlane.c \
  gmPRoseCurve.c \
  gmPSphere.c \
  gmPSteinerSurf.c \
  gmPSurf.c \
  gmPTCurve.c \
  gmPTorus.c \
  gmRandom.c \
  gmSArray.c \
  gmScene.c \
  gmSceneObject.c \
  gmSelector.c \
  gmSelectorGrid.c \
  gmSimplex_LineSegment.c \
  gmSimplex_Simplex.c \
  gmSimplex_Tetrahedron.c \
  gmSimplex_Triangle.c \
  gmSphere3D.c \
  gmStaticProc_GM_Static_.c \
  gmStaticProc_GM_Static1_.c \
  gmStaticProc_GM_Static2_.c \
  gmStaticProc_GM_Static3_.c \
  gmStaticProc_GM_Std_.c \
  gmStaticProc2_GM_Static_P_.c \
  gmStaticProc2_GM_Static_P2_.c \
  gmStlObject.c \
  gmStream_Separator.c \
  gmString.c \
  gmSubSpace_Cube.c \
  gmSubSpace_Line.c \
  gmSubSpace_Plane.c \
  gmSubSpace_SubSpace.c \
  gmTimer.c \
  gmTriangle_Edge.c \
  gmTriangle_PWVLine.c \
  gmTriangle_Tile.c \
  gmTriangle_Triangle.c \
  gmTriangle_TriangleFacets.c \
  gmTriangle_TriangleSystem.c \
  gmTriangle_Vertex.c \
  gmVContours.c \
  gmVDefault.c \
  gmVDerivatives.c \
  gmVNormals.c \
  gmVPoints.c \
  gmVSurroundingSphere.c \
  gmWindow_GMWindow.c \
  gmWindow_View.c \
  gmWindow_ViewBorder.c \
  gmWindow_ViewSet.c \
  gmVisualizer.c \



#########
# Sources
SOURCES = \
  gmCamera.cpp \
  gmCameraIso.cpp \
	gmCodeExample.cpp \
	gmColor.cpp \
  gmDisplayObject.cpp \
  gmLight_Light.cpp \
  gmLight_PointLight.cpp \
  gmLight_SpotLight.cpp \
  gmLight_Sun.cpp \
  gmLightG_PointLightG.cpp \
  gmLightG_SpotLightG.cpp \
  gmMaterial_Material.cpp \
  gmMaterial_MaterialObjectList.cpp \
  gmOpenGL_GLMatrix.cpp \
  gmScene.cpp \
  gmSceneObject.cpp \
  gmStlObject.cpp \
  gmStream_Separator.cpp \
  gmTexture.cpp \
  gmWindow_GMWindow.cpp \
  gmWindow_View.cpp \
  gmWindow_ViewSet.cpp


#####################################
# Archiver (uncomment to set globaly)
#ARCHIVER = tar_bzip




##--------------------------------------------------------------##
##--------------------------------------------------------------##
##--------------------------------------------------------------##

##################################
# Platform dependent configuration
##################################

############
# linux/un*x
ifeq "$(COMPILE_ENV)" "linux"

  # Compileflags
  CC = g++
  CFLAGS = -g -c -Wall

  # Incpaths
  INCPATHS = \
    -I"/usr/include" \
    -I"/usr/include/GL" \
    -I"/usr/include/qt4"

  # Archiver
  ARCHIVER = tar_bzip

else

  #######
  # Win32
  ifeq "$(COMPILE_ENV)" "win32"
    echo "not yet supported"
  else

    #######
    # Win64
    ifeq "$(COMPILE_ENV)" "win64"
      echo "not yet supported"
    endif
  endif
endif
