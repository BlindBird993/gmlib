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



/*! \file gmpcurvepointsvisualizer.c
 *
 *  Implementation of the PCurvePointsVisualizer template class.
 */


namespace GMlib {

  template <typename T>
  PCurvePointsVisualizer<T>::PCurvePointsVisualizer() {

    _size = 1.0;
    _color = GMcolor::BlueViolet;

    _no_elements = 0;
    glGenBuffers( 1, &_vbo_v );
  }

  template <typename T>
  PCurvePointsVisualizer<T>::~PCurvePointsVisualizer() {

    glDeleteBuffers( 1, &_vbo_v );
  }

  template <typename T>
  inline
  void PCurvePointsVisualizer<T>::display() {

    glPointSize( _size );

    const GLProgram &prog = this->getRenderProgram();
    prog.setUniform( "u_color", _color );
    prog.setUniform( "u_selected", this->_obj->isSelected() );


    GLuint vert_loc = prog.getAttributeLocation( "in_vertex" );

    glBindBuffer( GL_ARRAY_BUFFER, _vbo_v );
    glVertexAttribPointer( vert_loc, 3, GL_FLOAT, GL_FALSE, 0, (const GLvoid*)0x0 );
    glEnableVertexAttribArray( vert_loc );

    // Draw
    glDrawArrays( GL_POINTS, 0, _no_elements );

    glDisableVertexAttribArray( vert_loc );

    glBindBuffer( GL_ARRAY_BUFFER, 0x0 );


  }

  template <typename T>
  const Color& PCurvePointsVisualizer<T>::getColor() const {

    return _color;
  }

  template <typename T>
  std::string PCurvePointsVisualizer<T>::getIdentity() const {

    return "PSurf Point Visualizer";
  }

  template <typename T>
  float PCurvePointsVisualizer<T>::getSize() const {

    return _size;
  }

  template <typename T>
  inline
  void PCurvePointsVisualizer<T>::replot(
    DVector< DVector< Vector<T, 3> > >& p,
    int /*m*/, int /*d*/, bool /*closed*/
  ) {

    PCurveVisualizer<T>::populateLineStripVBO( _vbo_v, _no_elements, p );
  }

  template <typename T>
  void PCurvePointsVisualizer<T>::setColor( const Color& color ) {

    _color = color;
  }

  template <typename T>
  void PCurvePointsVisualizer<T>::setSize( float size ) {

    _size = size;
  }

} // END namespace GMlib
