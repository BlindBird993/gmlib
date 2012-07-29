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



/*! \file gmtrianglefacetsdefaultvisualizer.h
 *
 *  TriangleFacetsDefaultVisualizer implementations
 */

#include "../gmtrianglesystem.h"


namespace GMlib {

  template <typename T>
  TriangleFacetsDefaultVisualizer<T>::TriangleFacetsDefaultVisualizer()
    : _dprog("default"), _sprog("select")
  {

    glGenBuffers( 1, &_ibo );
    glGenBuffers( 1, &_vbo );
  }

  template <typename T>
  TriangleFacetsDefaultVisualizer<T>::~TriangleFacetsDefaultVisualizer() {

    glDeleteBuffers( 1, &_vbo );
    glDeleteBuffers( 1, &_ibo );
  }

  template <typename T>
  inline
  void TriangleFacetsDefaultVisualizer<T>::display( Camera* cam ) {

        this->glSetDisplayMode();

        Array< Light* > lights = this->_obj->getScene()->getLights();
    //    std::cout << "No. Lights: " << lights.getSize() << std::endl;
    //    _display.setUniform( "u_light_pos", lights[0]->get );

        _dprog.bind();

        const HqMatrix<float,3> &mvmat = this->_obj->getModelViewMatrix(cam);
        _dprog.setUniform( "u_mvmat", mvmat, 1, true );
        _dprog.setUniform( "u_mvpmat", cam->getProjectionMatrix() * mvmat, 1, true );

        _dprog.setUniform( "u_color", this->_obj->getColor() );
        _dprog.setUniform( "u_selected", this->_obj->isSelected() );
        _dprog.setUniform( "u_lighted", this->_obj->isLighted() );
        _dprog.setUniform( "u_mat_dif", this->_obj->getMaterial().getDif() );
        _dprog.setUniform( "u_light_dif", GMlib::Color( 1.0f, 1.0f, 1.0f ) );//lights[0]->getDiffuse() );
        _dprog.setUniform( "u_light_pos", Point3D<float>( 0.0f, 10.0f, 0.0f ) );

        // Get Material Data
        const Material &m = this->_obj->getMaterial();
        _dprog.setUniform( "u_amb", m.getAmb() );
        _dprog.setUniform( "u_dif", m.getDif() );
        _dprog.setUniform( "u_spc", m.getSpc() );
        _dprog.setUniform( "u_shin", m.getShininess() );

        GLuint vert_loc = _dprog.getAttributeLocation( "in_vertex" );
        GLuint normal_loc = _dprog.getAttributeLocation( "in_normal" );


        const GLsizei v_size = sizeof(GLVertex);
        glBindBuffer( GL_ARRAY_BUFFER, _vbo );
        glVertexAttribPointer( vert_loc, 3, GL_FLOAT, GL_FALSE, v_size, (GLvoid*)getGLVertexPointOffset() );
        glEnableVertexAttribArray( vert_loc );

        glVertexAttribPointer( normal_loc, 3, GL_FLOAT, GL_TRUE, v_size, (GLvoid*)getGLVertexNormalOffset() );
        glEnableVertexAttribArray( normal_loc );

        glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, _ibo );
        glDrawElements( GL_TRIANGLES, this->_tf->getNoTriangles() * 3, GL_UNSIGNED_SHORT, (const GLvoid*)0x0 );
        glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, 0x0 );

        glDisableVertexAttribArray( normal_loc );
        glDisableVertexAttribArray( vert_loc );

        glBindBuffer( GL_ARRAY_BUFFER, 0x0 );

        _dprog.unbind();
  }

  template <typename T>
  std::string TriangleFacetsDefaultVisualizer<T>::getIdentity() const {

    return "TriangleFacets Default Visualizer";
  }

  template <typename T>
  inline
  void TriangleFacetsDefaultVisualizer<T>::replot() {

    // Fill the VBO
    int no_vertices = this->_tf->getSize();
    GLVertex vertices[no_vertices];

    for( int i = 0; i < no_vertices; i++ ) {

      TSVertex<T> *v = this->_tf->getVertex(i);
      const Point<T,3> &pos = v->getPos();
      const Vector<T,3> &nor = v->getDir();

      vertices[i].x = pos(0);
      vertices[i].y = pos(1);
      vertices[i].z = pos(2);

      vertices[i].nx = nor(0);
      vertices[i].ny = nor(1);
      vertices[i].nz = nor(2);
    }

    glBindBuffer( GL_ARRAY_BUFFER, _vbo );
    glBufferData( GL_ARRAY_BUFFER, no_vertices * sizeof(GLVertex), vertices, GL_STATIC_DRAW );
    glBindBuffer( GL_ARRAY_BUFFER, 0x0 );

    int no_indices = this->_tf->getNoTriangles() * 3;
    GLushort indices[no_indices];
    GLushort *iptr = indices;

    for( int i = 0; i < this->_tf->getNoTriangles(); i++ ) {

      Array< TSVertex<T>* > tri_verts = this->_tf->getTriangle(i)->getVertices();
      for( int j = 0; j < tri_verts.getSize(); j++ )
        for( int k = 0; k < this->_tf->getSize(); k++ )
          if( tri_verts[j] == this->_tf->getVertex(k) )
            *iptr++ = k;
    }

    glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, _ibo );
    glBufferData( GL_ELEMENT_ARRAY_BUFFER, no_indices * sizeof(GLushort), indices, GL_STATIC_DRAW );
    glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, 0x0 );
  }

  template <typename T>
  inline
  void TriangleFacetsDefaultVisualizer<T>::select( Camera * cam, const Color& name ) {

    _sprog.bind();

    _sprog.setUniform( "u_mvpmat", this->_obj->getModelViewProjectionMatrix(cam), 1, true );
    _sprog.setUniform( "u_color", name );

    GLuint vert_loc = _sprog.getAttributeLocation( "in_vertex" );

    const GLsizei v_size = sizeof(GLVertex);
    glBindBuffer( GL_ARRAY_BUFFER, _vbo );
    glVertexAttribPointer( vert_loc, 3, GL_FLOAT, GL_FALSE, v_size, (GLvoid*)getGLVertexPointOffset() );
    glEnableVertexAttribArray( vert_loc );

    glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, _ibo );
    glDrawElements( GL_TRIANGLES, this->_tf->getNoTriangles() * 3, GL_UNSIGNED_SHORT, (const GLvoid*)0x0 );
    glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, 0x0 );

    glDisableVertexAttribArray( vert_loc );

    glBindBuffer( GL_ARRAY_BUFFER, 0x0 );

    _sprog.unbind();
  }



} // END namespace GMlib
