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



/*! \file gmpcurvedefaultvisualizer.c
 *
 *  Implementation of the PCurveDefaultVisualizer template class.
 */


namespace GMlib {

  template <typename T>
  PCurveDefaultVisualizer<T>::PCurveDefaultVisualizer() : _display( "pcurve" ), _select( "select" ), _vbo() {

    _no_vertices = 0;
  }

  template <typename T>
  PCurveDefaultVisualizer<T>::~PCurveDefaultVisualizer() {}

  template <typename T>
  inline
  void PCurveDefaultVisualizer<T>::display( Camera* cam ) {

    // GL States
    glLineWidth( this->_curve->getLineWidth() );

    _display.bind();

    _display.setUniform( "u_mvpmat", this->_obj->getModelViewProjectionMatrix(cam), 1, true );
    _display.setUniform( "u_color", this->_obj->getColor() );
    _display.setUniform( "u_selected", this->_obj->isSelected() );

    GLuint vert_loc = _display.getAttributeLocation( "in_vertex" );

    _vbo.bind();
    _vbo.enableVertexPointer( vert_loc );
    glDrawArrays( GL_LINE_STRIP, 0, _no_vertices );

    _vbo.disableVertexPointer( vert_loc );
    _vbo.release();

    _display.unbind();
  }

  template <typename T>
  std::string PCurveDefaultVisualizer<T>::getIdentity() const {

    return "PCurve Default Visualizer";
  }

  template <typename T>
  inline
  void PCurveDefaultVisualizer<T>::replot(
    DVector< DVector< Vector<T, 3> > >& p,
    int /*m*/, int /*d*/
  ) {

    _no_vertices = p.getDim();
    _vbo.fill( p );
  }

  template <typename T>
  inline
  void PCurveDefaultVisualizer<T>::select( Camera* cam, const Color& name ) {

    _select.bind();

    _select.setUniform( "u_mvpmat", this->_obj->getModelViewProjectionMatrix(cam), 1, true );
    _select.setUniform( "u_color", name );

    GLuint vert_loc = _select.getAttributeLocation( "in_vertex" );

    _vbo.bind();
    _vbo.enableVertexPointer( vert_loc );
    glDrawArrays( GL_LINE_STRIP, 0, _no_vertices );

    _vbo.disableVertexPointer( vert_loc );
    _vbo.release();

    _select.unbind();
  }


} // END namespace GMlib
