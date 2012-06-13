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

####################
# Define helper vars

# Build target
set( TARGET gmlib )

# Source groups
set( G_HDRS_CXX "Headers(CXX)" )
set( G_HDRS "Headers" )
set( G_HDRS_IMPL "Impl" )
set( G_SRCS "Sources" )

# Modules
set( M_GLOBAL         "gmGlobal" )
set( M_CONTAINER      "gmContainer" )
set( M_CORE           "gmCore" )
set( M_DISPLAY        "gmDisplay" )
set( M_DISPLAYUTILS   "gmDisplayUtils" )
set( M_MISC           "gmMisc" )
set( M_OPENGL         "gmOpenGL" )
set( M_PARAMETRICS    "gmParametrics" )
set( M_UTILS          "gmUtils" )
set( M_VISUALIZERS    "gmVisualizers" )


################
# "Global" Files

# C++ headers
set( GLOBAL_HDRS_CXX
  gmGlobal
)

# Headers
set( GLOBAL_HDRS
  gmGlobal.h
)

# Global source vars
set( HEADERS_CXX ${HEADERS_CXX} ${GLOBAL_HDRS_CXX} )
set( HEADERS ${HEADERS} ${GLOBAL_HDRS} )

# Source groups
SOURCE_GROUP( "${G_HDRS_CXX}\\${M_GLOBAL}"           FILES ${GLOBAL_HDRS_CXX} )
SOURCE_GROUP( "${G_HDRS}\\${M_GLOBAL}"               FILES ${GLOBAL_HDRS} )

#######################
# Container Module Files

# C++ headers
set( CONTAINER_HDRS_CXX
  gmContainer

  gmArray
  gmArrayLX
  gmArrayT
  gmDMatrix
  gmDVector
  gmDVectorN
  gmSArray
)

# Headers
set( CONTAINER_HDRS
  gmArray.h
  gmArrayLX.h
  gmArrayT.h
  gmDMatrix.h
  gmDVector.h
  gmDVectorN.h
  gmSArray.h
)

# Header includes
set( CONTAINER_HDRS_I
  gmArray.c
  gmArrayLX.c
  gmArrayT.c
  gmDMatrix.c
  gmDVector.c
  gmDVectorN.c
  gmSArray.c
)

# Global source vars
set( HEADERS_CXX ${HEADERS_CXX} ${CONTAINER_HDRS_CXX} )
set( HEADERS ${HEADERS} ${CONTAINER_HDRS} )
set( HEADERS_I ${HEADERS_I} ${CONTAINER_HDRS_I} )

# Source groups
SOURCE_GROUP( "${G_HDRS_CXX}\\${M_CONTAINER}"           FILES ${CONTAINER_HDRS_CXX} )
SOURCE_GROUP( "${G_HDRS}\\${M_CONTAINER}"               FILES ${CONTAINER_HDRS} )
SOURCE_GROUP( "${G_HDRS}\\${G_HDRS_I}\\${M_CONTAINER}"  FILES ${CONTAINER_HDRS_I} )


##################
# Core Module Files

# C++ headers
set( CORE_HDRS_CXX
  gmCore

  gmAngle
  gmMatrix
  gmPoint
  gmPoint2D
  gmPoint3D
  gmSimplex
  gmStaticProc
  gmStaticProc2
  gmSubSpace
)

# Headers
set( CORE_HDRS
  gmAngle.h
  gmMatrix.h
  gmPoint.h
  gmPoint2D.h
  gmPoint3D.h
  gmSimplex.h
  gmStaticProc.h
  gmStaticProc2.h
  gmSubSpace.h
)

# Header includes
set( CORE_HDRS_I
  gmAngle.c
  gmMatrix_Matrix.c
  gmMatrix_SqMatrix.c
  gmMatrix_HqMatrix.c
  gmPoint_Arrow.c
  gmPoint_Box.c
  gmPoint_M_I_.c
  gmPoint_Point.c
  gmPoint_ScalarPoint.c
  gmPoint_Sphere.c
  gmPoint_UnitVector.c
  gmPoint_Vector.c
  gmPoint2D_Point2D.c
  gmPoint2D_UnitVector2D.c
  gmPoint2D_Vector2D.c
  gmPoint3D_Plane3D.c
  gmPoint3D_Point3D.c
  gmPoint3D_UnitVector3D.c
  gmPoint3D_Vector3D.c
  gmSimplex_LineSegment.c
  gmSimplex_Simplex.c
  gmSimplex_Tetrahedron.c
  gmSimplex_Triangle.c
  gmStaticProc_GM_Static1_.c
  gmStaticProc_GM_Static2_.c
  gmStaticProc_GM_Static3_.c
  gmStaticProc_GM_Static_.c
  gmStaticProc_GM_Std_.c
  gmStaticProc2_GM_Static_P2_.c
  gmStaticProc2_GM_Static_P_.c
  gmSubSpace_Cube.c
  gmSubSpace_Line.c
  gmSubSpace_Plane.c
  gmSubSpace_SubSpace.c
)

# Global source vars
set( HEADERS_CXX ${HEADERS_CXX} ${CORE_HDRS_CXX} )
set( HEADERS ${HEADERS} ${CORE_HDRS} )
set( HEADERS_I ${HEADERS_I} ${CORE_HDRS_I} )

# Source groups
SOURCE_GROUP( "${G_HDRS_CXX}\\${M_CORE}"        FILES ${CORE_HDRS_CXX} )
SOURCE_GROUP( "${G_HDRS}\\${M_CORE}"            FILES ${CORE_HDRS} )
SOURCE_GROUP( "${G_HDRS}\\${G_HDRS_I}\\${M_CORE}" FILES ${CORE_HDRS_I} )



##################
# Display Module Files

# C++ headers
set( DISPLAY_HDRS_CXX
  gmDisplay

  gmCamera
  gmCameraIso
  gmDisplayObject
  gmFrustum
  gmLight
  gmScaleObject
  gmScene
  gmSceneObject
  gmSortObject
  gmWindow
)

# Headers
set( DISPLAY_HDRS
  gmCamera.h
  gmCameraIso.h
  gmDisplayObject.h
  gmFrustum.h
  gmLight.h
  gmScaleObject.h
  gmScene.h
  gmSceneObject.h
  gmSortObject.h
  gmWindow.h
)

# Header includes
set( DISPLAY_HDRS_I
  gmCamera.c
  gmCameraIso.c
  gmDisplayObject.c
  gmFrustum.c
  gmLight_Light.c
  gmLight_PointLight.c
  gmLight_SpotLight.c
  gmLight_Sun.c
  gmScaleObject.c
  gmScene.c
  gmSceneObject.c
  gmSortObject.c
  gmWindow_GMWindow.c
  gmWindow_View.c
  gmWindow_ViewBorder.c
  gmWindow_ViewSet.c
)

# Sources
set( DISPLAY_SRCS
  gmCamera.cpp
  gmCameraIso.cpp
  gmDisplayObject.cpp
  gmLight_Light.cpp
  gmLight_PointLight.cpp
  gmLight_SpotLight.cpp
  gmLight_Sun.cpp
  gmScene.cpp
  gmSceneObject.cpp
  gmWindow_GMWindow.cpp
  gmWindow_View.cpp
  gmWindow_ViewSet.cpp
)

# Global source vars
set( HEADERS_CXX ${HEADERS_CXX} ${DISPLAY_HDRS_CXX} )
set( HEADERS ${HEADERS} ${DISPLAY_HDRS} )
set( HEADERS_I ${HEADERS_I} ${DISPLAY_HDRS_I} )
set( SOURCES ${SOURCES} ${DISPLAY_SRCS} )

# Source groups
SOURCE_GROUP( "${G_HDRS_CXX}\\${M_DISPLAY}" FILES ${DISPLAY_HDRS_CXX} )
SOURCE_GROUP( "${G_HDRS}\\${M_DISPLAY}"     FILES ${DISPLAY_HDRS} )
SOURCE_GROUP( "${G_HDRS}\\${G_HDRS_I}\\${M_DISPLAY}"     FILES ${DISPLAY_HDRS_I} )
SOURCE_GROUP( "${G_SRCS}\\${M_DISPLAY}"     FILES ${DISPLAY_SRCS} )


##################
# Display Utils Module Files

# C++ headers
set( DISPLAYUTILS_HDRS_CXX
  gmDisplayUtils

  gmArrow3D
  gmColor
  gmCoordinateSystem
  gmLightG
  gmMaterial
  gmPathTrack
  gmSelector
  gmSelectorGrid
  gmSphere3D
  gmStlObject
  gmSurroundingSphere
  gmTexture
  gmTriangleSystem
)

# Headers
set( DISPLAYUTILS_HDRS
  gmArrow3D.h
  gmColor.h
  gmCoordinateSystem.h
  gmLightG.h
  gmMaterial.h
  gmPathTrack.h
  gmSelector.h
  gmSelectorGrid.h
  gmSphere3D.h
  gmStlObject.h
  gmSurroundingSphere.h
  gmTexture.h
  gmTriangleSystem.h
)

# Header includes
set( DISPLAYUTILS_HDRS_I
  gmArrow3D.c
  gmColor.c
  gmMaterial_Material.c
  gmMaterial_MaterialObject.c
  gmMaterial_MaterialObjectList.c
  gmSelector.c
  gmSelectorGrid.c
  gmSphere3D.c
  gmStlObject.c
  gmTriangleSystem_TSEdge.c
  gmTriangleSystem_TSLine.c
  gmTriangleSystem_TSTile.c
  gmTriangleSystem_TSTriangle.c
  gmTriangleSystem_TSVEdge.c
  gmTriangleSystem_TSVertex.c
  gmTriangleSystem_TriangleFacets.c
  gmTriangleSystem_TriangleSystem.c
)

# Sources
set( DISPLAYUTILS_SRCS
  gmColor.cpp
  gmCoordinateSystem.cpp
  gmLightG_PointLightG.cpp
  gmLightG_SpotLightG.cpp
  gmMaterial_Material.cpp
  gmMaterial_MaterialObjectList.cpp
  gmPathTrack.cpp
  gmStlObject.cpp
  gmSurroundingSphere.cpp
  gmTexture.cpp
)

# Global source vars
set( HEADERS_CXX ${HEADERS_CXX} ${DISPLAYUTILS_HDRS_CXX} )
set( HEADERS ${HEADERS} ${DISPLAYUTILS_HDRS} )
set( HEADERS_I ${HEADERS_I} ${DISPLAYUTILS_HDRS_I} )
set( SOURCES ${SOURCES} ${DISPLAYUTILS_SRCS} )

# Source groups
SOURCE_GROUP( "${G_HDRS_CXX}\\${M_DISPLAYUTILS}" FILES ${DISPLAYUTILS_HDRS_CXX} )
SOURCE_GROUP( "${G_HDRS}\\${M_DISPLAYUTILS}"     FILES ${DISPLAYUTILS_HDRS} )
SOURCE_GROUP( "${G_HDRS}\\${G_HDRS_I}\\${M_DISPLAYUTILS}"     FILES ${DISPLAYUTILS_HDRS_I} )
SOURCE_GROUP( "${G_SRCS}\\${M_DISPLAYUTILS}"     FILES ${DISPLAYUTILS_SRCS} )


##################
# Misc Module Files

# C++ headers
set( MISC_HDRS_CXX
  gmMisc

  gmCodeExample
)

# Headers
set( MISC_HDRS
  gmCodeExample.h
)

# Sources
set( MISC_SRCS
  gmCodeExample.cpp
)

# Global source vars
set( HEADERS_CXX ${HEADERS_CXX} ${MISC_HDRS_CXX} )
set( HEADERS ${HEADERS} ${MISC_HDRS} )
set( SOURCES ${SOURCES} ${MISC_SRCS} )

# Source groups
SOURCE_GROUP( "${G_HDRS_CXX}\\${M_MISC}" FILES ${MISC_HDRS_CXX} )
SOURCE_GROUP( "${G_HDRS}\\${M_MISC}"     FILES ${MISC_HDRS} )
SOURCE_GROUP( "${G_SRCS}\\${M_MISC}"     FILES ${MISC_SRCS} )


##################
# OpenGL Module Files

# C++ headers
set( OPENGL_HDRS_CXX
  gmOpenGL

  gmGLSL
  gmGLMatrix
)

# Headers
set( OPENGL_HDRS
  gmGLMatrix.h
  gmGLSL.h
  gmOpenGL.h
)

# Header includes
set( OPENGL_HDRS_I
  gmGLMatrix.c
)

# Sources
set( OPENGL_SRCS
  gmGLMatrix.cpp
  gmGLSL.cpp
)

# Global source vars
set( HEADERS_CXX ${HEADERS_CXX} ${OPENGL_HDRS_CXX} )
set( HEADERS ${HEADERS} ${OPENGL_HDRS} )
set( HEADERS_I ${HEADERS_I} ${OPENGL_HDRS_I} )
set( SOURCES ${SOURCES} ${OPENGL_SRCS} )

# Source groups
SOURCE_GROUP( "${G_HDRS_CXX}\\${M_OPENGL}" FILES ${OPENGL_HDRS_CXX} )
SOURCE_GROUP( "${G_HDRS}\\${M_OPENGL}"     FILES ${OPENGL_HDRS} )
SOURCE_GROUP( "${G_HDRS}\\${G_HDRS_I}\\${M_OPENGL}"     FILES ${OPENGL_HDRS_I} )
SOURCE_GROUP( "${G_SRCS}\\${M_OPENGL}"     FILES ${OPENGL_SRCS} )


##################
# Parametrics Module Files

# C++ headers
set( PARAMETRICS_HDRS_CXX
  gmParametrics

  # Evaluators
  gmEvaluatorStatic
  gmBasisEvaluator
  gmBFBSEvaluator
  gmERBSEvaluator

  # Direct subclasses of Parametrics
  gmPCurve                  # Curve
  gmPSurf                   # Surface
  gmPTriangle               # Triangle

  # Parametric Curves
  gmPArc                    # An Arc
  gmPBSplineCurve           # BSpline curve
  gmPBasisCurve             # A curve which can visualize a basis
  gmPBezierCurve            # Bezier curve
  gmPButterfly              # The so called "Butterfly" curve
  gmPChrysanthemumCurve     # The Chrysanthemum cuve
  gmPCircle                 # Circle
  gmPERBSCurve              # Expo Rational BSpline curve
  gmPRoseCurve              # Rose curve

  # Parametric Tensor Product Surfaces
  gmPApple                  # Apple
  gmPApple2                 # Apple
  gmPAsteroidalSphere       # Asteroidal Sphere
  gmPBenthorns              # Bent Horns
  gmPBohemianDome           # Bohemian Dome
  gmPBottle8                # Bottle 8
  gmPBoysSurface            # Boy's Surface
  gmPBezierSurf             # Bezier Surface
  gmPCircularSurface        # Circular Surface
  gmPCone                   # Cone
  gmPCrossCap               # CrossCap
  gmPCylinder               # Cylinder
  gmPDiniSurface            # Dini Surface
  gmPEightSurface           # Eight Surface
  gmPEnnepersSurface        # Ennepers Surface
  gmPERBSSurf               # Expo Rational BSpline Surface
  gmPHeart                  # Heart
  gmPHelicoid               # Helicoid
  gmPHermiteSurface         # Hermite interpolated surface
  gmPInsideOutTorus         # Inside-out Torus
  gmPKleinsBottle           # Kleins Bottle
  gmPKuenSurface            # Kuen Surface
  gmPMoebiusStrip           # Moebius Strip
  gmPPlane                  # Plane
  gmPSeashell               # Seashell
  gmPSinSurface             # Sin Surface
  gmPSlippersSurface        # Slipper's Surface
  gmPSphere                 # Sphere
  gmPSteinerSurf            # The Steiner Surface
  gmPSwallowTail            # Swallow Tail
  gmPTorus                  # Torus Surface
  gmPTrianguloidTrefoil     # Trianguloid Trefoil
  gmPWhitneyUmbrella        # Whitney Umbrella

  # Parametric Triangle Surfaces
  gmPBezierTriangle         # Bezier Triangle
  gmPERBSTriangle           # Expo Rational BSpline Triangle

  # Trasformation
  gmPTCurve                 # Transformable TCurve (special curve)

  # Scriptable
  gmPLuaScriptCurve         # Lua scriptable curve
  gmPLuaScriptSurf          # Lua scriptable surface
)

# Headers
set( PARAMETRICS_HDRS

  # The base class of all Parameterized Curvss, Surfaces, Volumes, Flows, etc.
  gmParametrics.h

  gmEvaluatorStatic.h
  gmBasisEvaluator.h
  gmBFBSEvaluator.h
  gmERBSEvaluator.h
  
  gmPCurve.h
  gmPSurf.h
  gmPTriangle.h
  gmPArc.h
  gmPBSplineCurve.h
  gmPBasisCurve.h
  gmPBezierCurve.h
  gmPButterfly.h
  gmPChrysanthemumCurve.h
  gmPCircle.h
  gmPERBSCurve.h
  gmPRoseCurve.h
  gmPApple.h
  gmPApple2.h
  gmPAsteroidalSphere.h
  gmPBenthorns.h
  gmPBohemianDome.h
  gmPBottle8.h
  gmPBoysSurface.h
  gmPBezierSurf.h
  gmPCircularSurface.h
  gmPCone.h
  gmPCrossCap.h
  gmPCylinder.h
  gmPDiniSurface.h
  gmPEightSurface.h
  gmPEnnepersSurface.h
  gmPERBSSurf.h
  gmPHeart.h
  gmPHelicoid.h
  gmPHermiteSurface.h
  gmPInsideOutTorus.h
  gmPKleinsBottle.h
  gmPKuenSurface.h
  gmPMoebiusStrip.h
  gmPPlane.h
  gmPSeashell.h
  gmPSinSurface.h
  gmPSlippersSurface.h
  gmPSphere.h
  gmPSteinerSurf.h
  gmPSwallowTail.h
  gmPTorus.h
  gmPTrianguloidTrefoil.h
  gmPWhitneyUmbrella.h
  gmPBezierTriangle.h
  gmPERBSTriangle.h
  gmPTCurve.h
  gmPLuaScriptCurve.h
  gmPLuaScriptSurf.h
)

# Header includes
set( PARAMETRICS_HDRS_I

  # The base class of all Parameterized Curvss, Surfaces, Volumes, Flows, etc.
  gmParametrics.c

  gmEvaluatorStatic.c
  gmBasisEvaluator.c
  gmBFBSEvaluator.c
  gmERBSEvaluator.c
  
  gmPCurve.c
  gmPSurf.c
  gmPTriangle.c
  gmPArc.c
  gmPBSplineCurve.c
  gmPBasisCurve.c
  gmPBezierCurve.c
  gmPButterfly.c
  gmPChrysanthemumCurve.c
  gmPCircle.c
  gmPERBSCurve.c
  gmPRoseCurve.c
  gmPApple.c
  gmPApple2.c
  gmPAsteroidalSphere.c
  gmPBenthorns.c
  gmPBohemianDome.c
  gmPBottle8.c
  gmPBoysSurface.c
  gmPBezierSurf.c
  gmPCircularSurface.c
  gmPCone.c
  gmPCrossCap.c
  gmPCylinder.c
  gmPDiniSurface.c
  gmPEightSurface.c
  gmPEnnepersSurface.c
  gmPERBSSurf.c
  gmPHeart.c
  gmPHelicoid.c
  gmPHermiteSurface.c
  gmPInsideOutTorus.c
  gmPKleinsBottle.c
  gmPKuenSurface.c
  gmPMoebiusStrip.c
  gmPPlane.c
  gmPSeashell.c
  gmPSinSurface.c
  gmPSlippersSurface.c
  gmPSphere.c
  gmPSteinerSurf.c
  gmPSwallowTail.c
  gmPTorus.c
  gmPTrianguloidTrefoil.c
  gmPWhitneyUmbrella.c
  gmPBezierTriangle.c
  gmPERBSTriangle.c
  gmPTCurve.c
  gmPLuaScriptCurve.c
  gmPLuaScriptSurf.c
)

# Global source vars
set( HEADERS_CXX ${HEADERS_CXX} ${PARAMETRICS_HDRS_CXX} )
set( HEADERS ${HEADERS} ${PARAMETRICS_HDRS} )
set( HEADERS_I ${HEADERS_I} ${PARAMETRICS_HDRS_I} )

# Source groups
SOURCE_GROUP( "${G_HDRS_CXX}\\${M_PARAMETRICS}" FILES ${PARAMETRICS_HDRS_CXX} )
SOURCE_GROUP( "${G_HDRS}\\${M_PARAMETRICS}"     FILES ${PARAMETRICS_HDRS} )
SOURCE_GROUP( "${G_HDRS}\\${G_HDRS_I}\\${M_PARAMETRICS}"     FILES ${PARAMETRICS_HDRS_I} )


##################
# Utils Module Files

# C++ headers
set( UTILS_HDRS_CXX
  gmUtils

  gmTimer
  gmRandom
  gmScript
  gmStream
  gmString
)

# Headers
set( UTILS_HDRS
  gmUtils.h

  gmRandom.h
  gmScript.h
  gmStream.h
  gmString.h
  gmTimer.h
)

# Header includes
set( UTILS_HDRS_I
  gmUtils.c

  gmRandom.c
  gmStream_Separator.c
  gmString.c
  gmTimer.c
)

# Sources
set( UTILS_SRCS
  gmScript_LuaScript.cpp
  gmScript_LuaVar.cpp
  gmScript_Script.cpp
  gmStream_Separator.cpp
)

# Global source vars
set( HEADERS_CXX ${HEADERS_CXX} ${UTILS_HDRS_CXX} )
set( HEADERS ${HEADERS} ${UTILS_HDRS} )
set( HEADERS_I ${HEADERS_I} ${UTILS_HDRS_I} )
set( SOURCES ${SOURCES} ${UTILS_SRCS} )

# Source groups
SOURCE_GROUP( "${G_HDRS_CXX}\\${M_UTILS}" FILES ${UTILS_HDRS_CXX} )
SOURCE_GROUP( "${G_HDRS}\\${M_UTILS}"     FILES ${UTILS_HDRS} )
SOURCE_GROUP( "${G_HDRS}\\${G_HDRS_I}\\${M_UTILS}"     FILES ${UTILS_HDRS_I} )
SOURCE_GROUP( "${G_SRCS}\\${M_UTILS}"     FILES ${UTILS_SRCS} )


##################
# Visualizers Module Files

# C++ headers
set( VISUALIZERS_HDRS_CXX
  gmVisualizers

  # Visualizer Base Classes
  gmVisualizer
  gmPCurveVisualizer                # PCurve Visualizer Base
  gmPSurfVisualizer                 # PSurf Visualizer Base
  gmPTriangleVisualizer             # PTriangleVisualizer Base

  # PCurve Visualizers( non-glsl )
  gmPCurveContoursVisualizer        # PCurve Contours Visualizer
  gmPCurveDerivativesVisualizer     # PCurve Derivatives Visualizer
  gmPCurvePointsVisualizer          # PCurve Points Visualizer

  # PSurf Visualizers( non-glsl )
  gmPSurfContoursVisualizer         # PSurf Contours Visualizer
  gmPSurfDerivativesVisualizer      # PSurf Derivatives Visualizer
  gmPSurfNormalsVisualizer          # PSurf Normals Visualizer
  gmPSurfPointsVisualizer           # PSurf Points Visualizer

  # PTriangle visualizers( non-glsl )
  gmPTriangleColorVisualizer        # PTriangle Color Visualizer
  gmPTriangleColorPointVisualizer   # PTriangle Color-Point Visualizer

  # PCurve GLSL Visualizer
  gmPCurveGLSLVisualizer            # PCurve GLSL Visualizer

  # PSurf GLSL Visualizer
  gmPSurfGLSLVisualizer             # PSurf GLSL Visualizer
)

# Headers
set( VISUALIZERS_HDRS

  gmVisualizer.h
  gmPCurveVisualizer.h
  gmPSurfVisualizer.h
  gmPTriangleVisualizer.h
  gmPCurveContoursVisualizer.h
  gmPCurveDerivativesVisualizer.h
  gmPCurvePointsVisualizer.h
  gmPSurfContoursVisualizer.h
  gmPSurfDerivativesVisualizer.h
  gmPSurfNormalsVisualizer.h
  gmPSurfPointsVisualizer.h
  gmPTriangleColorVisualizer.h
  gmPTriangleColorPointVisualizer.h
  gmPCurveGLSLVisualizer.h
  gmPSurfGLSLVisualizer.h
)

# Header inclues
set( VISUALIZERS_HDRS_I

  gmPCurveVisualizer.c
  gmPSurfVisualizer.c
  gmPTriangleVisualizer.c
  gmPCurveContoursVisualizer.c
  gmPCurveDerivativesVisualizer.c
  gmPCurvePointsVisualizer.c
  gmPSurfContoursVisualizer.c
  gmPSurfDerivativesVisualizer.c
  gmPSurfNormalsVisualizer.c
  gmPSurfPointsVisualizer.c
  gmPTriangleColorVisualizer.c
  gmPTriangleColorPointVisualizer.c
  gmPCurveGLSLVisualizer.c
  gmPSurfGLSLVisualizer.c
)

# Sources
set( VISUALIZERS_SRCS
  gmVisualizer.cpp
)

# Global source vars
set( HEADERS_CXX ${HEADERS_CXX} ${VISUALIZERS_HDRS_CXX} )
set( HEADERS ${HEADERS} ${VISUALIZERS_HDRS} )
set( HEADERS_I ${HEADERS_I} ${VISUALIZERS_HDRS_I} )
set( SOURCES ${SOURCES} ${VISUALIZERS_SRCS} )

# Source groups
SOURCE_GROUP( "${G_HDRS_CXX}\\${M_VISUALIZERS}" FILES ${VISUALIZERS_HDRS_CXX} )
SOURCE_GROUP( "${G_HDRS}\\${M_VISUALIZERS}"     FILES ${VISUALIZERS_HDRS} )
SOURCE_GROUP( "${G_HDRS}\\${G_HDRS_I}\\${M_VISUALIZERS}"     FILES ${VISUALIZERS_HDRS_I} )
SOURCE_GROUP( "${G_SRCS}\\${M_VISUALIZERS}"     FILES ${VISUALIZERS_SRCS} )


##########################
# Add files to the library
add_library( ${TARGET} STATIC

  # gmContainer
  ${CONTAINER_HDRS_CXX} ${CONTAINER_HDRS}

  # gmCore
  ${CORE_HDRS_CXX} ${CORE_HDRS}

  # gmDisplay
  ${DISPLAY_HDRS_CXX} ${DISPLAY_HDRS} ${DISPLAY_SRCS}

  # gmDisplayUtils
  ${DISPLAYUTILS_HDRS_CXX} ${DISPLAYUTILS_HDRS} ${DISPLAYUTILS_SRCS}

  # gmMisc
  ${MISC_HDRS_CXX} ${MISC_HDRS} ${MISC_SRCS}

  # gmOpenGL
  ${OPENGL_HDRS_CXX} ${OPENGL_HDRS} ${OPENGL_SRCS}

  # gmParametrics
  ${PARAMETRICS_HDRS_CXX} ${PARAMETRICS_HDRS}

  # gmUtils
  ${UTILS_HDRS_CXX} ${UTILS_HDRS} ${UTILS_SRCS}

  # gmVisualizers
  ${VISUALIZERS_HDRS_CXX} ${VISUALIZERS_HDRS} ${VISUALIZERS_SRCS}
)

set_target_properties( ${TARGET} PROPERTIES DEBUG_POSTFIX _debug )
set_target_properties( ${TARGET} PROPERTIES LINKER_LANGUAGE CXX )

set( FILES_CPY

  # gmGlobal
  ${GLOBAL_HDRS_CXX} ${GLOBAL_HDRS}

  # gmContainer
  ${CONTAINER_HDRS_CXX} ${CONTAINER_HDRS} ${CONTAINER_HDRS_I} ${CONTAINER_OTHRS}

  # gmCore
  ${CORE_HDRS_CXX} ${CORE_HDRS} ${CORE_HDRS_I}

  # gmDisplay
  ${DISPLAY_HDRS_CXX} ${DISPLAY_HDRS} ${DISPLAY_HDRS_I} ${DISPLAY_SRCS}

  # gmDisplayUtils
  ${DISPLAYUTILS_HDRS_CXX} ${DISPLAYUTILS_HDRS} ${DISPLAYUTILS_HDRS_I} ${DISPLAYUTILS_SRCS}

  # gmMisc
  ${MISC_HDRS_CXX} ${MISC_HDRS} ${MISC_SRCS}

  # gmOpenGL
  ${OPENGL_HDRS_CXX} ${OPENGL_HDRS} ${OPENGL_HDRS_I} ${OPENGL_SRCS}

  # gmParametrics
  ${PARAMETRICS_HDRS_CXX} ${PARAMETRICS_HDRS} ${PARAMETRICS_HDRS_I}

  # gmUtils
  ${UTILS_HDRS_CXX} ${UTILS_HDRS} ${UTILS_HDRS_I} ${UTILS_SRCS}

  # gmVisualizers
  ${VISUALIZERS_HDRS_CXX} ${VISUALIZERS_HDRS} ${VISUALIZERS_HDRS_I} ${VISUALIZERS_SRCS}
)


#################################
# Copy lib file to "build/lib/gmlib" directory
# Copy lib file to "lib/gmlib" directory for in-place builds
add_custom_command( TARGET ${TARGET} POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E make_directory 
    ${CMAKE_BINARY_DIR}/build/lib/gmlib/
  COMMAND ${CMAKE_COMMAND} -E copy
    ${CMAKE_BINARY_DIR}/src/lib${TARGET}.a
    ${CMAKE_BINARY_DIR}/build/lib/gmlib/
  COMMAND ${CMAKE_COMMAND} -E make_directory
    ${CMAKE_BINARY_DIR}/lib/gmlib/
  COMMAND ${CMAKE_COMMAND} -E copy
    ${CMAKE_BINARY_DIR}/src/lib${TARGET}.a
    ${CMAKE_BINARY_DIR}/lib/gmlib/
)

#################################
# Copy src files to "build/src" directory
foreach(f ${FILES_CPY})
  add_custom_command( TARGET ${TARGET} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E make_directory
      ${CMAKE_BINARY_DIR}/build/src
    COMMAND ${CMAKE_COMMAND} -E copy 
      ${CMAKE_SOURCE_DIR}/src/${f}
      ${CMAKE_BINARY_DIR}/build/src/${f}
  )
endforeach(f)

