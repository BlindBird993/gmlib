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



/*! \file gmtrianglefacetsvisualizer.h
 *
 *  TriangleFacetsVisualizer implementations
 */

namespace GMlib {

  template <typename T>
  TriangleFacetsVisualizer<T>::TriangleFacetsVisualizer() {

    _tf = 0x0;
  }

  template <typename T>
  TriangleFacetsVisualizer<T>::~TriangleFacetsVisualizer() {}

  template <typename T>
  void TriangleFacetsVisualizer<T>::fillStandardVBO(
      VertexBufferObject &vbo, const TriangleFacets<T> *tf) {

    int no_vertices = tf->getSize();
    DVector<GLVertexNormal> vertices(no_vertices);

    for( int i = 0; i < no_vertices; i++ ) {

      TSVertex<float> *v = tf->getVertex(i);
      const Point<float,3> &pos = v->getPos();
      const Vector<float,3> &nor = v->getDir();

      vertices[i].x = pos(0);
      vertices[i].y = pos(1);
      vertices[i].z = pos(2);

      vertices[i].nx = nor(0);
      vertices[i].ny = nor(1);
      vertices[i].nz = nor(2);
    }

    vbo.bind();
    vbo.createBufferData( no_vertices * sizeof(GLVertexNormal), vertices.getPtr(), GL_STATIC_DRAW );
    vbo.unbind();
  }

  template <typename T>
  void TriangleFacetsVisualizer<T>::fillStandardIBO(
      TrianglesIBO& ibo, const TriangleFacets<T>* tf ) {

    int no_indices = tf->getNoTriangles() * 3;

    DVector<GLuint> indices(no_indices);
    GLuint *iptr = indices.getPtr();

    for( int i = 0; i < tf->getNoTriangles(); i++ ) {

      Array< TSVertex<float>* > tri_verts = tf->getTriangle(i)->getVertices();
      for( int j = 0; j < tri_verts.getSize(); j++ )
        for( int k = 0; k < tf->getSize(); k++ )
          if( tri_verts[j] == tf->getVertex(k) )
            *iptr++ = k;
    }

    ibo._no_indices = no_indices;
    ibo.bind();
    ibo.createBufferData( no_indices, indices.getPtr(), GL_STATIC_DRAW );
    ibo.unbind();
  }

  template <typename T>
  inline
  void TriangleFacetsVisualizer<T>::replot() {}

  template <typename T>
  void TriangleFacetsVisualizer<T>::set( SceneObject* obj ) {

    Visualizer::set( obj );

    _tf = dynamic_cast<TriangleFacets<T>*>( obj );
  }



} // END namespace GMlib
