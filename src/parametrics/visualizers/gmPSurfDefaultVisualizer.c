
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



/*! \file gmPSurfDefaultVisualizer.c
 *
 *  Implementation of the PSurfDefaultVisualizer template class.
 *
 *  \date   2011-01-17
 */


// STL
#include <set>
#include <string>
#include <iostream>

// local
#include "gmCamera.h"
#include "gmMaterial.h"
#include "gmPSurf.h"
#include "gmOpenGL.h"
#include "gmGLProgram.h"
#include "gmGLShaderManager.h"
#include "gmLight.h"
#include "gmScene.h"


namespace GMlib {

  template <typename T>
  PSurfDefaultVisualizer<T>::PSurfDefaultVisualizer() : _display( "default" ), _select( "select" ) {

    _tri_strips = 0;
    _tri_strip_offset = 0;
    _indices_per_tri_strip = 0;

    glGenBuffers( 1, &_ibo );
    glGenBuffers( 1, &_vbo );

    glGenTextures( 1, &_tex );
  }

  template <typename T>
  PSurfDefaultVisualizer<T>::~PSurfDefaultVisualizer() {

    glDeleteBuffers( 1, &_ibo );
    glDeleteBuffers( 1, &_vbo );

    glDeleteBuffers( 1, &_tex );
  }

  template <typename T>
  inline
  void PSurfDefaultVisualizer<T>::display( Camera* cam ) {

    this->glSetDisplayMode();

    Array< Light* > lights = this->_obj->getScene()->getLights();
//    std::cout << "No. Lights: " << lights.getSize() << std::endl;
//    _display.setUniform( "u_light_pos", lights[0]->get );

    _display.bind();

    const HqMatrix<float,3> &mvmat = this->_obj->getModelViewMatrix(cam);
    _display.setUniform( "u_mvmat", mvmat, 1, true );
    _display.setUniform( "u_mvpmat", cam->getProjectionMatrix() * mvmat, 1, true );

    _display.setUniform( "u_color", this->_obj->getColor() );
    _display.setUniform( "u_selected", this->_obj->isSelected() );
    _display.setUniform( "u_lighted", this->_obj->isLighted() );
    _display.setUniform( "u_mat_dif", this->_obj->getMaterial().getDif() );
    _display.setUniform( "u_light_dif", GMlib::Color( 1.0f, 1.0f, 1.0f ) );//lights[0]->getDiffuse() );
    _display.setUniform( "u_light_pos", Point3D<float>( 0.0f, 10.0f, 0.0f ) );

    // Get Material Data
    const Material &m = this->_obj->getMaterial();
    _display.setUniform( "u_amb", m.getAmb() );
    _display.setUniform( "u_dif", m.getDif() );
    _display.setUniform( "u_spc", m.getSpc() );
    _display.setUniform( "u_shin", m.getShininess() );

    _display.setUniform( "u_tex", (GLuint)m.getTextureID(), (GLenum)GL_TEXTURE0, 0 );

    GLuint vert_loc = _display.getAttributeLocation( "in_vertex" );
    GLuint normal_loc = _display.getAttributeLocation( "in_normal" );
    GLuint tex_loc = _display.getAttributeLocation( "in_tex" );


    const GLsizei v_size = sizeof(GLVertex);
    glBindBuffer( GL_ARRAY_BUFFER, _vbo );
    glVertexAttribPointer( vert_loc, 3, GL_FLOAT, GL_FALSE, v_size, (GLvoid*)getGLVertexPointOffset() );
    glEnableVertexAttribArray( vert_loc );

    glVertexAttribPointer( normal_loc, 3, GL_FLOAT, GL_TRUE, v_size, (GLvoid*)getGLVertexNormalOffset() );
    glEnableVertexAttribArray( normal_loc );

    glVertexAttribPointer( tex_loc, 2, GL_FLOAT, GL_FALSE, v_size, (GLvoid*)getGLVertexTexOffset1() );
    glEnableVertexAttribArray( tex_loc );


    glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, _ibo );
    for( int i = 0; i < _tri_strips; i++ )
      glDrawElements( GL_TRIANGLE_STRIP, _indices_per_tri_strip, GL_UNSIGNED_SHORT, (const GLvoid*)( i*_tri_strip_offset ) );
    glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, 0x0 );


    glDisableVertexAttribArray( tex_loc );
    glDisableVertexAttribArray( normal_loc );
    glDisableVertexAttribArray( vert_loc );

    glBindBuffer( GL_ARRAY_BUFFER, 0x0 );


    _display.unbind();
  }

  template <typename T>
  std::string PSurfDefaultVisualizer<T>::getIdentity() const {

    return "PSurf Default Visualizer";
  }

  template <typename T>
  inline
  void PSurfDefaultVisualizer<T>::replot(
    DMatrix< DMatrix< Vector<T, 3> > >& p,
    DMatrix< Vector<T, 3> >& normals,
    int /*m1*/, int /*m2*/, int /*d1*/, int /*d2*/
  ) {

    _tri_strips = PSurfVisualizer<T>::getNoTriangleStrips( p.getDim1(), p.getDim2() );

    _indices_per_tri_strip = PSurfVisualizer<T>::getNoIndicesPerTriangleStrip( p.getDim1(), p.getDim2() );
    _tri_strip_offset =  sizeof(GLushort) * _indices_per_tri_strip;

    PSurfVisualizer<T>::fillStandardVBO( _vbo, p );
    PSurfVisualizer<T>::fillTriangleStripIBO( _ibo, p.getDim1(), p.getDim2() );
  }

  template <typename T>
  inline
  void PSurfDefaultVisualizer<T>::select( Camera * cam, const Color& name ) {

    _select.bind();

    _select.setUniform( "u_mvpmat", this->_obj->getModelViewProjectionMatrix(cam), 1, true );
    _select.setUniform( "u_color", name );

    GLuint vert_loc = _select.getAttributeLocation( "in_vertex" );

    const GLsizei v_size = sizeof(GLVertex);
    glBindBuffer( GL_ARRAY_BUFFER, _vbo );
    glVertexAttribPointer( vert_loc, 3, GL_FLOAT, GL_FALSE, v_size, (GLvoid*)getGLVertexPointOffset() );
    glEnableVertexAttribArray( vert_loc );


    glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, _ibo );
    for( int i = 0; i < _tri_strips; i++ )
      glDrawElements( GL_TRIANGLE_STRIP, _indices_per_tri_strip, GL_UNSIGNED_SHORT, (const GLvoid*)( i*_tri_strip_offset ) );
    glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, 0x0 );


    glDisableVertexAttribArray( vert_loc );

    glBindBuffer( GL_ARRAY_BUFFER, 0x0 );

    _select.unbind();
  }

} // END namespace GMlib






