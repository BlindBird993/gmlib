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



/*! \file gmDCurve.c
 *
 *  Implementation of the gmDCurve template class.
 *
 *  \date   2008-09-09
 */


//#include "gmOpenGL.h"

#include "gmPCurve.h"


namespace GMlib {


  template <typename T>
  inline
  DCurve<T>::DCurve() {

    _p_ref = 0;
    _init();
  }


  template <typename T>
  inline
  DCurve<T>::DCurve( const DCurve<T>& copy ) : DParametrics<T,1>( copy ) {

    _p_ref        = copy._p_ref;
    _line_width   = copy._line_width;
    _no_der       = copy._no_der;
    _no_samp      = copy._no_samp;
  }


  template <typename T>
  inline
  DCurve<T>::DCurve( const PCurve<T,3>& copy ) : DParametrics<T,1>( copy ), _p_ref( copy ) {

    _init();
  }


  template <typename T>
  inline
  DCurve<T>::DCurve( PCurve<T,3>* copy ) : DParametrics<T,1>( copy ) {

    _p_ref = copy;

    _init();
  }


  template <typename T>
  void DCurve<T>::_init() {

    this->_lighted = false;
    _line_width = 1.0;
    _no_der = 0;
    _no_samp = 0;

    this->_default_visualizer.set( this );
  }

  template <typename T>
  inline
  float DCurve<T>::getLineWidth() const {

    return _line_width;
  }


  template <typename T>
  inline
  int DCurve<T>::getNoDer() const {

    return _no_der;
  }


  template <typename T>
  inline
  int DCurve<T>::getNoSamp() const {

    return _no_samp;
  }


  template <typename T>
  inline
  PCurve<T,3>* DCurve<T>::getPCurve() {

    return _p_ref;
  }


  template <typename T>
  inline
  void  DCurve<T>::localDisplay() {

    glPushAttrib( GL_LIGHTING_BIT | GL_LINE_BIT ); {

      // Set Properties
      glDisable( GL_LIGHTING );
      glLineWidth( _line_width );

      for( int i = 0; i < this->_visualizers.getSize(); i++ )
        this->_visualizers[i]->display();

    } glPopAttrib();
  }


  template <typename T>
  inline
  void DCurve<T>::localSelect() {

    glPushAttrib( GL_LINE_BIT ); {

      glLineWidth( 2 * _line_width );

      if( this->_dynamic ) {

        glVertexPointer( 3, GL_FLOAT, 2*3*sizeof(float), this->_vertices_n1[0].getPtr() );
        glDrawArrays( GL_LINE_STRIP, 0, this->_vertices_n1.getDim() );
      }
      else
        glCallList( this->_dlist );

    } glPopAttrib();

    for( int i = 0; i < this->_visualizers.getSize(); i++ )
      this->_visualizers[i]->select();
  }


  template <typename T>
  void DCurve<T>::replot( int m, bool dynamic, int d ) {

    // Check wheather or not PCurve is valid
    if( !_p_ref )
      return;


    // Correct sample domain
    if( m < 2 )
      m = _p_ref->_sam;
    else
      _p_ref->_sam = m;


    // Set Properties
    this->_dynamic = dynamic;
    _no_samp = m;
    _no_der = d;


    // Resample
    DVector< DVector< Vector<T, 3> > > p;
    _p_ref->resample( p, m, 1, _p_ref->getStartP(), _p_ref->getEndP() );


    // Set The Surrounding Sphere
    setSurroundingSphere( p );


    // Clean up Display Lists
    if( this->_dlist ) {

      glDeleteLists( this->_dlist, 1 );
      this->_dlist = 0;
    }


    // Create Display lists or input data into vertex arrays...
    // Dependent on wheather or not the Curve is dynamic
    if(dynamic) {

      glEnableClientState( GL_VERTEX_ARRAY );
      this->_vertices_n1.setDim( p.getDim() );

      for( int i = 0; i < p.getDim(); i++ )
        this->_vertices_n1[i] = p[i][0].toFloat();
    }
    else {

      this->_dlist = glGenLists(1);

      // Make displaylist for display of lined curve and select
      glNewList( this->_dlist, GL_COMPILE ); {
        glBegin(GL_LINE_STRIP); {

          for( int i = 0; i < p.getDim(); i++ )
            glPoint( Point<float, 3>( p[i][0].toFloat() ) );

        }glEnd();
      } glEndList();
    }


    // Replot Visaulizers
    for( int i = 0; i < this->_visualizers.getSize(); i++ )
      this->_visualizers[i]->replot( p, m, d );
  }


  template <typename T>
  inline
  void DCurve<T>::setLineWidth( float width ) {

    _line_width = width;
  }


  template <typename T>
  inline
  void DCurve<T>::setPCurve( PCurve<T,3>* pcurve ) {

    _p_ref = pcurve;
    DParametrics<T,1>::setParametrics( _p_ref );
  }


  template <typename T>
  inline
  void DCurve<T>::setSurroundingSphere( const DVector< DVector< Vector<T, 3> > >& p ) {

    Sphere<float,3>  s;
    s.resetPos( Point<float,3>( p(0)(0) ) );
    s += Point<float,3>( p(p.getDim() - 1)(0) );
    for( int i = p.getDim() - 2; i > 0; i-- )
      s += Point<float,3>( p(i)(0) );
    DParametrics<T,1>::setSurroundingSphere(s);
  }
}
