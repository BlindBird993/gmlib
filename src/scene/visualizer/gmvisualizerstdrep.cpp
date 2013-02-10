/**********************************************************************************
**
** Copyright (C) 1994 Narvik University College
** Contact: GMlib Online Portal at http://episteme.hin.no
**
** This file is part of the Geometric Modeling Library, GMlib.
**
** GMlib is free software: you can redistribute it and/or modify
** it under the terms of the GNU Lesser General Public License as published by
** the Free Software Foundation, either version 3 of the License, or
** (at your option) any later version.
**
** GMlib is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU Lesser General Public License for more details.
**
** You should have received a copy of the GNU Lesser General Public License
** along with GMlib.  If not, see <http://www.gnu.org/licenses/>.
**
**********************************************************************************/



/*! \file gmvisualizerstdrep.cpp
 *
 *  Implementations VisualizerStdRep class.
 */

#include "gmvisualizerstdrep.h"

#include "../gmdisplayobject.h"


namespace GMlib {

  VisualizerStdRep::VisualizerStdRep() :
    _bo_cube( "std_rep_cube" ), _bo_cube_indices( "std_rep_cube_indices" ),
    _bo_cube_frame_indices( "std_rep_frame_indices" ) {

    setRenderProgram( GL::GLProgram( "color" ) );
  }

  VisualizerStdRep::~VisualizerStdRep() {}

  void VisualizerStdRep::display() {

    glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );


    const GL::GLProgram &prog = this->getRenderProgram();
//    prog.setUniform( "u_selected", this->_obj->isSelected() );


    GLuint vert_loc = prog.getAttributeLocation( "in_vertex" );

    Color blend_color = GMcolor::LightGrey;
    blend_color.setAlpha( 0.5 );

    prog.setUniform( "u_selected", this->_obj->isSelected() );

    _bo_cube.bind();
    _bo_cube.enableVertexArrayPointer( vert_loc, 3, GL_FLOAT, GL_FALSE, 0, (const GLvoid*)0x0 );

    _bo_cube_frame_indices.bind(); {

      const GLsizei frame_stride = 2 * sizeof(GLushort);

      glLineWidth( 2.0f );
      prog.setUniform( "u_color", GMcolor::Red );
      glDrawElements( GL_LINES, 2, GL_UNSIGNED_SHORT, (const GLvoid*)(0x0) );

      prog.setUniform( "u_color", GMcolor::Green );
      glDrawElements( GL_LINES, 2, GL_UNSIGNED_SHORT, (const GLvoid*)(frame_stride) );

      prog.setUniform( "u_color", GMcolor::Blue );
      glDrawElements( GL_LINES, 2, GL_UNSIGNED_SHORT, (const GLvoid*)(2*frame_stride) );

      glLineWidth( 1.0f );
      prog.setUniform( "u_color", GMcolor::Grey );
      glDrawElements( GL_LINES, 18, GL_UNSIGNED_SHORT, (const GLvoid*)(3*frame_stride) );

    } _bo_cube_frame_indices.unbind();

    glEnable( GL_BLEND ); {

      glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
      prog.setUniform( "u_color", blend_color );
      _bo_cube_indices.bind();
        glDrawElements( GL_QUADS, 24, GL_UNSIGNED_SHORT, 0x0 );
      _bo_cube_indices.unbind();

    }glDisable( GL_BLEND );

    _bo_cube.disableVertexArrayPointer( vert_loc );
    _bo_cube.unbind();
  }

  void VisualizerStdRep::select() {

    GLuint vert_loc = getSelectProgram().getAttributeLocation( "in_vertex" );
    _bo_cube.bind();
    _bo_cube.enableVertexArrayPointer( vert_loc, 3, GL_FLOAT, GL_FALSE, 0, (const GLvoid*)0x0 );
    _bo_cube_indices.bind();
      glDrawElements( GL_QUADS, 24, GL_UNSIGNED_SHORT, 0x0 );
    _bo_cube_indices.unbind();
    _bo_cube.disableVertexArrayPointer( vert_loc );
    _bo_cube.unbind();
  }

} // END namespace GMlib
