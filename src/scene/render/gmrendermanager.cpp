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

/*! \file gmrendermanager.h
 *  \brief Pending Documentation
 *
 *  Pending Documentation
 */


#include "gmrendermanager.h"

// local
#include "gmrenderer.h"
#include "../camera/gmcamera.h"
#include "../gmscene.h"
#include "../gmsceneobject.h"

//gmlib
#include <opengl/gmopengl.h>



namespace GMlib {

  RenderManager::RenderManager(Scene *scene) : _objs(128), _clear_color( 0.5f, 0.5f, 0.5f, 1.0f ), _select_color( GMcolor::Pink ) {

    _scene = scene;
    _disp = new DisplayRenderer( scene );
    _select = new SelectRenderer( scene );


    glGenBuffers( 1, &_vbo_quad );
    glGenBuffers( 1, &_vbo_quad_tex );

    // Gen quad data (vertex)
    glBindBuffer( GL_ARRAY_BUFFER, _vbo_quad );

    DVector< Point<float,3> > data(4);
//    data[0] = Point3D<float>( 0.25f, 0.25f, 0.0f );
//    data[1] = Point3D<float>( 0.25f, 0.75f, 0.0f );
//    data[2] = Point3D<float>( 0.75f, 0.75f, 0.0f );
//    data[3] = Point3D<float>( 0.75f, 0.25f, 0.0f );
    data[0] = Point3D<float>( 0.0f, 0.0f, 0.0f );
    data[1] = Point3D<float>( 0.0f, 1.0f, 0.0f );
    data[2] = Point3D<float>( 1.0f, 1.0f, 0.0f );
    data[3] = Point3D<float>( 1.0f, 0.0f, 0.0f );

    glBufferData( GL_ARRAY_BUFFER, 4 * 3 * sizeof(float), data.getPtr(), GL_STATIC_DRAW );
    glBindBuffer( GL_ARRAY_BUFFER, 0x0 );

    // Gen quad data (tex)
    glBindBuffer( GL_ARRAY_BUFFER, _vbo_quad_tex );

    DVector< Point<float,2> > data_tex(4);
    data_tex[0] = Point2D<float>( 0.0f, 0.0f );
    data_tex[1] = Point2D<float>( 0.0f, 1.0f );
    data_tex[2] = Point2D<float>( 1.0f, 1.0f );
    data_tex[3] = Point2D<float>( 1.0f, 0.0f );
  //  data_tex[0] = Point2D<float>( 0.25f, 0.25f );
  //  data_tex[1] = Point2D<float>( 0.25f, 0.75f );
  //  data_tex[2] = Point2D<float>( 0.75f, 0.75f );
  //  data_tex[3] = Point2D<float>( 0.75f, 0.25f );

    glBufferData( GL_ARRAY_BUFFER, 4 * 2 * sizeof(float), data_tex.getPtr(), GL_STATIC_DRAW );
    glBindBuffer( GL_ARRAY_BUFFER, 0x0 );
  }

  const Color &RenderManager::getClearColor() const {

    return _clear_color;
  }

  const Color &RenderManager::getSelectColor() const {

    return _select_color;
  }

  SceneObject *RenderManager::findObject(int x, int y) {

    _select->findObject( x, y );
  }

  void RenderManager::resize(int w, int h) {

    _disp->resize(w,h);
    _select->resize(w,h);

    _w = w;
    _h = h;
  }

  void RenderManager::render(const Array<Camera*>& cameras ) {


    _disp->render( _objs, cameras );

//    _disp->renderSelect( _objs, cameras );





    float near_plane = -1.0f;
    float far_plane = 1.0f;

    float l, r, b, t, n, f;
    l = 0.0f;
    r = 1.0f;
    b = 0.0f;
    t = 1.0f;
    n = near_plane;
    f = far_plane;

    float A, B, C;
    A = - ( r + l ) / ( r - l );
    B = - ( t + b ) / ( t - b );
    C = - ( f + n ) / ( f - n );

    HqMatrix<float,3> ortho_mat;

    ortho_mat[0][0] = 2 / (r - l);
    ortho_mat[0][1] = 0.0f;
    ortho_mat[0][2] = 0.0f;
    ortho_mat[0][3] = A;

    ortho_mat[1][0] = 0.0f;
    ortho_mat[1][1] = 2 / ( t - b );
    ortho_mat[1][2] = 0.0f;
    ortho_mat[1][3] = B;

    ortho_mat[2][0] = 0.0f;
    ortho_mat[2][1] = 0.0f;
    ortho_mat[2][2] = - 2.0f / (f-n);
    ortho_mat[2][3] = C;

    ortho_mat[3][0] = 0.0f;
    ortho_mat[3][1] = 0.0f;
    ortho_mat[3][2] = 0.0f;
    ortho_mat[3][3] = 1.0f;


    glViewport( 0, 0, _w, _h );
    glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
    glDisable(GL_DEPTH_TEST);

    GL::GLProgram prog( "render" );

    prog.bind();

    prog.setUniform( "u_mvpmat", ortho_mat, 1, true );
    prog.setUniform( "u_tex", _disp->_rbo_color.getId(), (GLenum)GL_TEXTURE0, 0 );
    prog.setUniform( "u_tex_selected", _disp->_rbo_select.getId(), (GLenum)GL_TEXTURE1, 1 );
    prog.setUniform( "u_buf_w", float(_w) );
    prog.setUniform( "u_buf_h", float(_h) );
    prog.setUniform( "u_select_color", _select_color );

    GLuint vert_loc = prog.getAttributeLocation( "in_vertex" );
    GLuint tex_coord_loc = prog.getAttributeLocation( "in_tex_coord" );

    glBindBuffer( GL_ARRAY_BUFFER, _vbo_quad );
    glVertexAttribPointer( vert_loc, 3, GL_FLOAT, GL_FALSE, 0, (const GLvoid*)0x0 );
    glEnableVertexAttribArray( vert_loc );

    glBindBuffer( GL_ARRAY_BUFFER, _vbo_quad_tex );
    glVertexAttribPointer( tex_coord_loc, 2, GL_FLOAT, GL_FALSE, 0, (const GLvoid*)0x0 );
    glEnableVertexAttribArray( tex_coord_loc );

    glBindBuffer( GL_ARRAY_BUFFER, 0x0 );

    glDrawArrays( GL_QUADS, 0, 4 );

    glDisableVertexAttribArray( tex_coord_loc );
    glDisableVertexAttribArray( vert_loc );

    prog.unbind();


    GL::GLProgram color_prog( "color" );
    color_prog.bind();

    color_prog.setUniform( "u_mvpmat", ortho_mat, 1, true );
    color_prog.setUniform( "u_selected", false );

//    _view_set_stack.back().drawBorder();

    color_prog.unbind();


    glEnable(GL_DEPTH_TEST);
  }

  void RenderManager::select(Camera *cam, int type_id) {

      _select->select( _objs, cam, type_id );
  }

  void RenderManager::setClearColor(const Color &c) {

    _clear_color = c;
  }

  void RenderManager::setSelectColor(const Color &c) {

    _select_color = c;
  }

  void RenderManager::updateMaxObjects(int no_objs) {

    if( _objs.getMaxSize() < no_objs )
      _objs.setMaxSize(no_objs);
  }



} // END namespace GMlib
