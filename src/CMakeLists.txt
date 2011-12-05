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

# Path(s)
#set( SRC_ROOT . )

# Source groups
set( G_HDRS_CXX "Headers(CXX)" )
set( G_HDRS "Headers" )
set( G_SRCS "Sources" )

# Modules
set( M_CONTAINER      "gmContainer" )
set( M_CORE           "gmCore" )
set( M_DISPLAY        "gmDisplay" )
set( M_DISPLAYUTILS   "gmDisplayUtils" )
set( M_MISC           "gmMisc" )
set( M_OPENGL         "gmOpenGL" )
set( M_PARAMETRICS    "gmParametrics" )
set( M_UTILS          "gmUtils" )
set( M_VISUALIZERS    "gmVisualizers" )


#######################
# Container Module Files

# C++ headers
set( CONTAINER_HDRS_CXX
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

# Source groups
SOURCE_GROUP( "${G_HDRS_CXX}\\${M_CONTAINER}" FILES ${CONTAINER_HDRS_CXX} )
SOURCE_GROUP( "${G_HDRS}\\${M_CONTAINER}"     FILES ${CONTAINER_HDRS} )


##################
# Core Module Files

# C++ headers
set( CORE_HDRS_CXX
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

# Source groups
SOURCE_GROUP( "${G_HDRS_CXX}\\${M_CORE}"  FILES ${CORE_HDRS_CXX} )
SOURCE_GROUP( "${G_HDRS}\\${M_CORE}"      FILES ${CORE_HDRS} )


##################
# Display Module Files

# C++ headers
set( DISPLAY_HDRS_CXX
  gmCamera
  gmCameraIso
  gmDisplayObject
  gmLight
  gmScene
  gmSceneObject
  gmWindow
)

# Headers
set( DISPLAY_HDRS
  gmCamera.h
  gmCameraIso.h
  gmDisplayObject.h
  gmLight.h
  gmScene.h
  gmSceneObject.h
  gmWindow.h
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

# Source groups
SOURCE_GROUP( "${G_HDRS_CXX}\\${M_DISPLAY}" FILES ${DISPLAY_HDRS_CXX} )
SOURCE_GROUP( "${G_HDRS}\\${M_DISPLAY}"     FILES ${DISPLAY_HDRS} )
SOURCE_GROUP( "${G_SRCS}\\${M_DISPLAY}"     FILES ${DISPLAY_SRCS} )


##################
# Display Utils Module Files

# C++ headers
set( DISPLAYUTILS_HDRS_CXX
  gmArrow3D
  gmColor
  gmCoordinateSystem
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

# Source groups
SOURCE_GROUP( "${G_HDRS_CXX}\\${M_DISPLAYUTILS}" FILES ${DISPLAYUTILS_HDRS_CXX} )
SOURCE_GROUP( "${G_HDRS}\\${M_DISPLAYUTILS}"     FILES ${DISPLAYUTILS_HDRS} )
SOURCE_GROUP( "${G_SRCS}\\${M_DISPLAYUTILS}"     FILES ${DISPLAYUTILS_SRCS} )


##################
# Misc Module Files

# C++ headers
set( MISC_HDRS_CXX
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

# Source groups
SOURCE_GROUP( "${G_HDRS_CXX}\\${M_MISC}" FILES ${MISC_HDRS_CXX} )
SOURCE_GROUP( "${G_HDRS}\\${M_MISC}"     FILES ${MISC_HDRS} )
SOURCE_GROUP( "${G_SRCS}\\${M_MISC}"     FILES ${MISC_SRCS} )


##################
# OpenGL Module Files

# C++ headers
set( OPENGL_HDRS_CXX
  gmOpenGL
)

# Headers
set( OPENGL_HDRS
  gmOpenGL.h
)

# Sources
set( OPENGL_SRCS
  gmGLMatrix.cpp
  gmGLSL.cpp
)

# Source groups
SOURCE_GROUP( "${G_HDRS_CXX}\\${M_OPENGL}" FILES ${OPENGL_HDRS_CXX} )
SOURCE_GROUP( "${G_HDRS}\\${M_OPENGL}"     FILES ${OPENGL_HDRS} )
SOURCE_GROUP( "${G_SRCS}\\${M_OPENGL}"     FILES ${OPENGL_SRCS} )


##################
# Parametrics Module Files

# C++ headers
set( PARAMETRICS_HDRS_CXX

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

# Source groups
SOURCE_GROUP( "${G_HDRS_CXX}\\${M_PARAMETRICS}" FILES ${PARAMETRICS_HDRS_CXX} )
SOURCE_GROUP( "${G_HDRS}\\${M_PARAMETRICS}"     FILES ${PARAMETRICS_HDRS} )


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

  gmTimer.h
  gmRandom.h
  gmScript.h
  gmStream.h
  gmString.h
)

# Sources
set( UTILS_SRCS
  gmScript_LuaScript.cpp
  gmScript_LuaVar.cpp
  gmScript_Script.cpp
  gmStream_Separator.cpp
)

# Source groups
SOURCE_GROUP( "${G_HDRS_CXX}\\${M_OPENGL}" FILES ${OPENGL_HDRS_CXX} )
SOURCE_GROUP( "${G_HDRS}\\${M_OPENGL}"     FILES ${OPENGL_HDRS} )
SOURCE_GROUP( "${G_SRCS}\\${M_OPENGL}"     FILES ${OPENGL_SRCS} )


##################
# Visualizers Module Files

# C++ headers
set( VISUALIZERS_HDRS_CXX

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

# Sources
set( VISUALIZERS_SRCS
  gmVisualizer.cpp
)


##########################
# Add files to the library
add_library( GMlib STATIC

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

set_target_properties( GMlib PROPERTIES DEBUG_POSTFIX _debug )
set_target_properties( GMlib PROPERTIES LINKER_LANGUAGE CXX )

add_custom_command( TARGET GMlib POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E make_directory 
    ${CMAKE_BINARY_DIR}/build/lib/gmlib/
  COMMAND ${CMAKE_COMMAND} -E copy
    ${CMAKE_CURRENT_SOURCE_DIR}/libGMlib.a
    ${CMAKE_BINARY_DIR}/build/lib/gmlib/
)

add_custom_command( TARGET GMlib POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E make_directory 
    ${CMAKE_BINARY_DIR}/build/src
  COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/src
    ${CMAKE_BINARY_DIR}/build/src
)
