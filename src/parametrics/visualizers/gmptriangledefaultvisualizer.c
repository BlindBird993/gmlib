
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


  template <typename T>
  PTriangleDefaultVisualizer<T>::PTriangleDefaultVisualizer() {

    _no_triangles= 0;

    glGenBuffers( 1, &_vbo );
    glGenBuffers( 1, &_ibo );
  }

  template <typename T>
  PTriangleDefaultVisualizer<T>::~PTriangleDefaultVisualizer() {

    glDeleteBuffers( 1, &_vbo );
    glDeleteBuffers( 1, &_ibo );
  }

  template <typename T>
  inline
  void PTriangleDefaultVisualizer<T>::display() {

    this->glSetDisplayMode();

    Array< Light* > lights = this->_obj->getScene()->getLights();
//    std::cout << "No. Lights: " << lights.getSize() << std::endl;
//    _dprog.setUniform( "u_light_pos", lights[0]->get );


    const GLProgram &prog = this->getRenderProgram();

    prog.setUniform( "u_color", this->_obj->getColor() );
    prog.setUniform( "u_selected", this->_obj->isSelected() );
    prog.setUniform( "u_lighted", this->_obj->isLighted() );
    prog.setUniform( "u_mat_dif", this->_obj->getMaterial().getDif() );
    prog.setUniform( "u_light_dif", Color( 1.0f, 1.0f, 1.0f ) );//lights[0]->getDiffuse() );
    prog.setUniform( "u_light_pos", Point3D<float>( 0.0f, 10.0f, 0.0f ) );

    // Get Material Data
    const Material &m = this->_obj->getMaterial();
    prog.setUniform( "u_amb", m.getAmb() );
    prog.setUniform( "u_dif", m.getDif() );
    prog.setUniform( "u_spc", m.getSpc() );
    prog.setUniform( "u_shin", m.getShininess() );

    prog.setUniform( "u_tex", (GLuint)m.getTextureID(), (GLenum)GL_TEXTURE0, 0 );

    GLuint vert_loc = prog.getAttributeLocation( "in_vertex" );
    GLuint normal_loc = prog.getAttributeLocation( "in_normal" );
    GLuint tex_loc = prog.getAttributeLocation( "in_tex" );


    const GLsizei v_size = sizeof(GLVertex2D);
    glBindBuffer( GL_ARRAY_BUFFER, _vbo );
    glVertexAttribPointer( vert_loc, 3, GL_FLOAT, GL_FALSE, v_size, (GLvoid*)GLVertex2D::getPointOffset() );
    glEnableVertexAttribArray( vert_loc );

    glVertexAttribPointer( normal_loc, 3, GL_FLOAT, GL_TRUE, v_size, (GLvoid*)GLVertex2D::getNormalOffset() );
    glEnableVertexAttribArray( normal_loc );


    glPointSize( 5.0f );


    glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, _ibo );
    glDrawElements( GL_TRIANGLES, _no_triangles * 3, GL_UNSIGNED_SHORT, (GLvoid*)0x0 );
    glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, 0x0 );


    glDisableVertexAttribArray( normal_loc );
    glDisableVertexAttribArray( vert_loc );

    glBindBuffer( GL_ARRAY_BUFFER, 0x0 );


  }

  template <typename T>
  std::string PTriangleDefaultVisualizer<T>::getIdentity() const {

    return "PTriangle Default Visualizer";
  }

  template <typename T>
  inline
  void PTriangleDefaultVisualizer<T>::replot( const DVector< DMatrix< Vector<T,3> > >& p, int m ) {

    _no_triangles = PTriangleVisualizer<float>::getNoTriangles( m );

    // Fill VBO
    PTriangleVisualizer<float>::fillStandardVBO( _vbo, p );

    // Fill IBO
    PTriangleVisualizer<float>::fillTriangleIBO( _ibo, m );
  }

  template <typename T>
  inline
  void PTriangleDefaultVisualizer<T>::select() {

    GLuint vert_loc = this->getSelectProgram().getAttributeLocation( "in_vertex" );

    const GLsizei v_size = sizeof(GLVertex2D);
    glBindBuffer( GL_ARRAY_BUFFER, _vbo );
    glVertexAttribPointer( vert_loc, 3, GL_FLOAT, GL_FALSE, v_size, (GLvoid*)GLVertex2D::getPointOffset() );
    glEnableVertexAttribArray( vert_loc );


    glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, _ibo );
    glDrawElements( GL_TRIANGLES, _no_triangles * 3, GL_UNSIGNED_SHORT, (GLvoid*)0x0 );
    glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, 0x0 );


    glDisableVertexAttribArray( vert_loc );

    glBindBuffer( GL_ARRAY_BUFFER, 0x0 );
  }

} // END namespace GMlib
