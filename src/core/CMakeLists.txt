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

# Headers
set( HDRS
  gmangle.h
  gmglobal.h
  gmmatrix.h
  gmpoint.h
  gmpoint2d.h
  gmpoint3d.h
  gmsimplex.h
  gmstaticproc.h
  gmstaticproc2.h
  gmstream.h
  gmsubspace.h
)

# Header includes
set( HDRS_I
  gmMatrix.c
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

# Source files
set( SRCS
  gmstream.cpp
)


##########################
# Add files to the library
add_library( ${MODULE_TARGET} SHARED ${HDRS} ${SRCS} )
set_default_target_properties( ${MODULE_TARGET} )

#######################
# Post-build copy files
#set( FILES_CPY ${HDRS} )
#add_module_cpy_commands( ${MODULE} ${MODULE_TARGET} ${FILES_CPY} )
