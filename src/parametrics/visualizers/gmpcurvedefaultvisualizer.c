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
  PCurveDefaultVisualizer<T>::PCurveDefaultVisualizer() : _vbo() {

    _no_vertices = 0;
  }

  template <typename T>
  PCurveDefaultVisualizer<T>::~PCurveDefaultVisualizer() {}

  template <typename T>
  inline
  void PCurveDefaultVisualizer<T>::display() {

    // GL States
    glLineWidth( this->_curve->getLineWidth() );

    const GLProgram &prog = this->getRenderProgram();
    prog.setUniform( "u_color", this->_obj->getColor() );
    prog.setUniform( "u_selected", this->_obj->isSelected() );

    GLuint vert_loc = prog.getAttributeLocation( "in_vertex" );

    _vbo.bind();
    _vbo.enable( vert_loc, 3, GL_FLOAT, GL_FALSE, sizeof(GLVertex), (const GLvoid*)0x0 );
    glDrawArrays( GL_LINE_STRIP, 0, _no_vertices );

    _vbo.disable( vert_loc );
    _vbo.unbind();
  }

  template <typename T>
  std::string PCurveDefaultVisualizer<T>::getIdentity() const {

    return "PCurve Default Visualizer";
  }

  template <typename T>
  inline
  void PCurveDefaultVisualizer<T>::replot(
    DVector< DVector< Vector<T, 3> > >& p,
    int /*m*/, int /*d*/, bool /*closed*/
  ) {

    PCurveVisualizer<T>::fillStandardVBO( _vbo, _no_vertices, p );
  }

  template <typename T>
  inline
  void PCurveDefaultVisualizer<T>::select() {

    GLuint vert_loc = this->getSelectProgram().getAttributeLocation( "in_vertex" );

    _vbo.bind();
    _vbo.enable( vert_loc, 3, GL_FLOAT, GL_FALSE, sizeof(GLVertex), (const GLvoid*)0x0 );
    glDrawArrays( GL_LINE_STRIP, 0, _no_vertices );

    _vbo.disable( vert_loc );
    _vbo.unbind();
  }


} // END namespace GMlib
