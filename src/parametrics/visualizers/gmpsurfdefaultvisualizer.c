
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



/*! \file gmpsurfdefaultvisualizer.c
 *
 *  Implementation of the PSurfDefaultVisualizer template class.
 */


#include "../gmpsurf.h"

// gmlib::opengl
#include <opengl/gmopengl.h>
#include <opengl/gmglprogram.h>
#include <opengl/gmglshadermanager.h>

// gmlib::scenegraph
#include <scenegraph/gmscene.h>
#include <scenegraph/camera/gmcamera.h>
#include <scenegraph/light/gmlight.h>
#include <scenegraph/utils/gmmaterial.h>

// stl
#include <set>
#include <string>

namespace GMlib {

  template <typename T>
  PSurfDefaultVisualizer<T>::PSurfDefaultVisualizer() : _display( "default" ), _vbo(), _ibo() {

    glGenTextures( 1, &_tex );
  }

  template <typename T>
  PSurfDefaultVisualizer<T>::~PSurfDefaultVisualizer() {

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
    _display.setUniform( "u_light_dif", Color( 1.0f, 1.0f, 1.0f ) );//lights[0]->getDiffuse() );
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


    _vbo.bind();
    _vbo.enable( vert_loc, normal_loc, tex_loc );

    _ibo.draw();

    _vbo.disable( vert_loc, normal_loc, tex_loc );

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

    _vbo.fill(p);
    _ibo.fill( p.getDim1(), p.getDim2() );
  }

  template <typename T>
  inline
  void PSurfDefaultVisualizer<T>::select() {

    GLuint vert_loc = this->getSelectProgram().getAttributeLocation( "in_vertex" );

    _vbo.bind();
    _vbo.enableVertexPointer( vert_loc );

    _ibo.draw();

    _vbo.disableVertexPointer( vert_loc );
    _vbo.release();
  }

} // END namespace GMlib






