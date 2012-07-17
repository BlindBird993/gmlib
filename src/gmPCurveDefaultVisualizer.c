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



/*! \file gmPCurveDefaultVisualizer.c
 *
 *  Implementation of the PCurveDefaultVisualizer template class.
 *
 *  \date   2011-01-17
 */


namespace GMlib {

  template <typename T>
  PCurveDefaultVisualizer<T>::PCurveDefaultVisualizer() : _display( "pcurve" ), _select( "select" ) {

    _no_vertices = 0;

    glGenBuffers( 1, &_vbo_v );
  }

  template <typename T>
  PCurveDefaultVisualizer<T>::~PCurveDefaultVisualizer() {

    glDeleteBuffers( 1, &_vbo_v );
  }

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

    glBindBuffer( GL_ARRAY_BUFFER, _vbo_v );
    glVertexAttribPointer( vert_loc, 3, GL_FLOAT, GL_FALSE, 0, (const GLvoid*)0x0 );
    glEnableVertexAttribArray( vert_loc );

    glDrawArrays( GL_LINE_STRIP, 0, _no_vertices );

    glDisableVertexAttribArray( vert_loc );
    glBindBuffer( GL_ARRAY_BUFFER, 0x0 );

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

    PCurveVisualizer<T>::populateLineStripVBO( _vbo_v, _no_vertices, p );
  }

  template <typename T>
  inline
  void PCurveDefaultVisualizer<T>::select( Camera* cam, const Color& name ) {

    _select.bind();

    _select.setUniform( "u_mvpmat", this->_obj->getModelViewProjectionMatrix(cam), 1, true );
    _select.setUniform( "u_color", name );

    GLuint vert_loc = _select.getAttributeLocation( "in_vertex" );

    glBindBuffer( GL_ARRAY_BUFFER, _vbo_v );
    glVertexAttribPointer( vert_loc, 3, GL_FLOAT, GL_FALSE, 0, (const GLvoid*)0x0 );

    glEnableVertexAttribArray( vert_loc );

    glDrawArrays( GL_LINE_STRIP, 0, _no_vertices );

    glDisableVertexAttribArray( vert_loc );

    glBindBuffer( GL_ARRAY_BUFFER, 0x0 );
    _select.unbind();
  }


} // END namespace GMlib
