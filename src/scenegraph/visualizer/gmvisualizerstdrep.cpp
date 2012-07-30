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

#include "../gmsceneobject.h"


namespace GMlib {

  VisualizerStdRep::VisualizerStdRep()
    : _display( "color" ), _select( "select" ),
    _bo_cube( "std_rep_cube" ), _bo_cube_indices( "std_rep_cube_indices" ),
    _bo_cube_frame_indices( "std_rep_frame_indices" )
  {}

  VisualizerStdRep::~VisualizerStdRep() {}

  void VisualizerStdRep::display(Camera *cam) {

    glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );

    _display.bind();

    _display.setUniform( "u_mvpmat", this->_obj->getModelViewProjectionMatrix(cam), 1, true );
//    _display.setUniform( "u_selected", this->_obj->isSelected() );


    GLuint vert_loc = _display.getAttributeLocation( "in_vertex" );

    Color blend_color = GMcolor::LightGrey;
    blend_color.setAlpha( 0.5 );

    _display.setUniform( "u_selected", this->_obj->isSelected() );

    _bo_cube.enableVertexArrayPointer( vert_loc, 3, GL_FLOAT, GL_FALSE, 0, (const GLvoid*)0x0 );

    _bo_cube_frame_indices.bind(); {

      const GLsizei frame_stride = 2 * sizeof(GLushort);

      glLineWidth( 2.0f );
      _display.setUniform( "u_color", GMcolor::Red );
      glDrawElements( GL_LINES, 2, GL_UNSIGNED_SHORT, (const GLvoid*)(0x0) );

      _display.setUniform( "u_color", GMcolor::Green );
      glDrawElements( GL_LINES, 2, GL_UNSIGNED_SHORT, (const GLvoid*)(frame_stride) );

      _display.setUniform( "u_color", GMcolor::Blue );
      glDrawElements( GL_LINES, 2, GL_UNSIGNED_SHORT, (const GLvoid*)(2*frame_stride) );

      glLineWidth( 1.0f );
      _display.setUniform( "u_color", GMcolor::Grey );
      glDrawElements( GL_LINES, 18, GL_UNSIGNED_SHORT, (const GLvoid*)(3*frame_stride) );

    } _bo_cube_frame_indices.release();

    glEnable( GL_BLEND ); {

      glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
      _display.setUniform( "u_color", blend_color );
      _bo_cube_indices.bind();
        glDrawElements( GL_QUADS, 24, GL_UNSIGNED_SHORT, 0x0 );
      _bo_cube_indices.release();

    }glDisable( GL_BLEND );

    _bo_cube.disableVertexArrayPointer( vert_loc );

    _display.unbind();
  }

  std::string VisualizerStdRep::getIdentity() const {

    return "SceneObject Standard Representation Visualizer";
  }

  void VisualizerStdRep::select(Camera *cam, const Color &name) {

    _select.bind();

    _select.setUniform( "u_mvpmat", this->_obj->getModelViewProjectionMatrix(cam), 1, true );
    _select.setUniform( "u_color", name );

    GLuint vert_loc = _select.getAttributeLocation( "in_vertex" );
    _bo_cube.enableVertexArrayPointer( vert_loc, 3, GL_FLOAT, GL_FALSE, 0, (const GLvoid*)0x0 );
    _bo_cube_indices.bind();
      glDrawElements( GL_QUADS, 24, GL_UNSIGNED_SHORT, 0x0 );
    _bo_cube_indices.release();
    _bo_cube.disableVertexArrayPointer( vert_loc );

    _select.unbind();
  }

} // END namespace GMlib
