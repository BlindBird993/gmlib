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

set( MODULE core )

#################
# Module target
set( MODULE_TARGET ${LIB_PREFIX}${MODULE} )

##################
# Core Module Files

# C++ headers
set( HDRS_CXX
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
set( HDRS
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
set( HDRS_I
  gmAngle.c
  gmMatrix.c
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


##########################
# Add files to the library
add_library( ${MODULE_TARGET} STATIC ${HDRS} )
set_default_target_properties( ${MODULE_TARGET} )

#######################
# Post-build copy files
#set( FILES_CPY ${HDRS} )
#add_module_cpy_commands( ${MODULE} ${MODULE_TARGET} ${FILES_CPY} )
