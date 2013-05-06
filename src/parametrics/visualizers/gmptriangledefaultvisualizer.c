
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



/*! \file gmptriangledefaultvisualizer.c
 *
 *  Implementation of the PTriangleDefaultVisualizer template class.
 */


namespace GMlib {


  template <typename T, int n>
  PTriangleDefaultVisualizer<T,n>::PTriangleDefaultVisualizer()
    : _vbo(), _ibo(), _lights_ubo("lights_ubo"), _no_elements(0) {}

  template <typename T, int n>
  inline
  void PTriangleDefaultVisualizer<T,n>::render(const DisplayObject *obj, const Camera *cam) const {

    const HqMatrix<float,3> &mvmat = obj->getModelViewMatrix(cam);
    const HqMatrix<float,3> &pmat = obj->getProjectionMatrix(cam);

    this->glSetDisplayMode();

    const GL::GLProgram &prog = this->getRenderProgram();
    prog.bind(); {

      // Model view and projection matrices
      prog.setUniform( "u_mvmat", mvmat );
      prog.setUniform( "u_mvpmat", pmat * mvmat );

      // Lights
      prog.setUniformBlockBinding( "Lights", _lights_ubo, 0 );

      // Get Material Data
      const Material &m = obj->getMaterial();
      prog.setUniform( "u_mat_amb", m.getAmb() );
      prog.setUniform( "u_mat_dif", m.getDif() );
      prog.setUniform( "u_mat_spc", m.getSpc() );
      prog.setUniform( "u_mat_shin", m.getShininess() );

      GL::AttributeLocation vert_loc = prog.getAttributeLocation( "in_vertex" );
      GL::AttributeLocation normal_loc = prog.getAttributeLocation( "in_normal" );

      _vbo.bind();
      _vbo.enable( vert_loc, 3, GL_FLOAT, GL_FALSE,  sizeof(GL::GLVertexNormal), reinterpret_cast<const GLvoid*>(0x0) );
      _vbo.enable( normal_loc, 3, GL_FLOAT, GL_TRUE, sizeof(GL::GLVertexNormal), reinterpret_cast<const GLvoid*>(sizeof(GL::GLVertex) ) );

      draw();

      _vbo.disable( vert_loc );
      _vbo.disable( normal_loc );
      _vbo.unbind();

    } prog.unbind();
  }

  template <typename T, int n>
  inline
  void PTriangleDefaultVisualizer<T,n>::replot( const DVector< DVector< Vector<T,3> > >& p, int m ) {

    _no_elements = PTriangleVisualizer<T,n>::getNoTriangles( m )*3;

    // Fill VBO
    PTriangleVisualizer<T,n>::fillStandardVBO( _vbo, p );

    // Fill IBO
    PTriangleVisualizer<T,n>::fillTriangleIBO( _ibo, m );
  }

  template <typename T, int n>
  inline
  void PTriangleDefaultVisualizer<T,n>::renderGeometry(const GL::AttributeLocation &vertice_loc) const {

    _vbo.bind();
    _vbo.enable( vertice_loc, 3, GL_FLOAT, GL_FALSE, sizeof(GL::GLVertexNormal), reinterpret_cast<const GLvoid*>(0x0) );

    draw();

    _vbo.disable( vertice_loc );
    _vbo.unbind();
  }

  template <typename T, int n>
  inline
  void PTriangleDefaultVisualizer<T,n>::draw() const {

    _ibo.bind();
    _ibo.drawElements( GL_TRIANGLES, _no_elements, GL_UNSIGNED_INT, reinterpret_cast<const GLvoid*>(0x0) );
    _ibo.unbind();
  }

} // END namespace GMlib
