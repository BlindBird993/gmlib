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

#include "gmstdrepvisualizer.h"

#include "../gmsceneobject.h"
#include "../camera/gmcamera.h"
#include "../render/gmdefaultrenderer.h"


namespace GMlib {


  VisualizerStdRep *VisualizerStdRep::_s_instance = 0x0;




  VisualizerStdRep::VisualizerStdRep() {

    _prog.acquire("color");
    assert(_prog.isValid());

    _bo_cube.acquire("std_rep_cube");
    assert(_bo_cube.isValid());

    _bo_cube_indices.acquire("std_rep_cube_indices");
    assert(_bo_cube_indices.isValid());

    _bo_cube_frame_indices.acquire("std_rep_frame_indices");
    assert(_bo_cube_frame_indices.isValid());
  }

  void VisualizerStdRep::render( const SceneObject* obj, const DefaultRenderer* renderer ) const {

    const Camera* cam = renderer->getCamera();
    render( obj->getModelViewMatrix(cam), obj->getProjectionMatrix(cam) );
  }

  VisualizerStdRep *VisualizerStdRep::getInstance() {

    if( !_s_instance )
      _s_instance = new VisualizerStdRep;

    return _s_instance;
  }

  void VisualizerStdRep::renderGeometry( const SceneObject* obj, const Renderer* renderer, const Color& color ) const {

    const Camera* cam = renderer->getCamera();
    _prog.setUniform( "u_color", color );
    _prog.setUniform( "u_mvpmat", obj->getModelViewProjectionMatrix(cam) );
    GL::AttributeLocation vertice_loc = _prog.getAttributeLocation( "in_vertex" );

    _bo_cube.bind();
    _bo_cube.enableVertexArrayPointer( vertice_loc, 3, GL_FLOAT, GL_FALSE, 0, (const GLvoid*)0x0 );
    _bo_cube_indices.bind();
      glDrawElements( GL_QUADS, 24, GL_UNSIGNED_SHORT, 0x0 );
    _bo_cube_indices.unbind();
    _bo_cube.disableVertexArrayPointer( vertice_loc );
    _bo_cube.unbind();
  }

  void VisualizerStdRep::render(const HqMatrix<float,3> &mvmat,
                                 const HqMatrix<float,3> &pmat) const {

    glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );

    _prog.bind();

    _prog.setUniform( "u_mvmat", mvmat );
    _prog.setUniform( "u_mvpmat", pmat * mvmat );

    GL::AttributeLocation vert_loc = _prog.getAttributeLocation( "in_vertex" );

    Color blend_color = GMcolor::LightGrey;
    blend_color.setAlpha( 0.5 );

    _bo_cube.bind();
    _bo_cube.enableVertexArrayPointer( vert_loc, 3, GL_FLOAT, GL_FALSE, 0, (const GLvoid*)0x0 );

    _bo_cube_frame_indices.bind(); {

      const GLsizei frame_stride = 2 * sizeof(GLushort);

      glLineWidth( 2.0f );
      _prog.setUniform( "u_color", GMcolor::Red );
      glDrawElements( GL_LINES, 2, GL_UNSIGNED_SHORT, (const GLvoid*)(0x0) );

      _prog.setUniform( "u_color", GMcolor::Green );
      glDrawElements( GL_LINES, 2, GL_UNSIGNED_SHORT, (const GLvoid*)(frame_stride) );

      _prog.setUniform( "u_color", GMcolor::Blue );
      glDrawElements( GL_LINES, 2, GL_UNSIGNED_SHORT, (const GLvoid*)(2*frame_stride) );

      glLineWidth( 1.0f );
      _prog.setUniform( "u_color", GMcolor::LightGrey );
      glDrawElements( GL_LINES, 18, GL_UNSIGNED_SHORT, (const GLvoid*)(3*frame_stride) );

    } _bo_cube_frame_indices.unbind();

    ::glEnable( GL_CULL_FACE );
    ::glCullFace( GL_BACK );
    ::glEnable( GL_BLEND ); {

      glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
      _prog.setUniform( "u_color", blend_color );
      _bo_cube_indices.bind();
        glDrawElements( GL_QUADS, 24, GL_UNSIGNED_SHORT, 0x0 );
      _bo_cube_indices.unbind();

    }
    ::glDisable( GL_BLEND );
    ::glDisable( GL_CULL_FACE );

    _bo_cube.disableVertexArrayPointer( vert_loc );
    _bo_cube.unbind();
  }


} // END namespace GMlib
