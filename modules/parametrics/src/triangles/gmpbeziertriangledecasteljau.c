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





#include "../evaluators/gmevaluatorstatic.h"

// gmlib
#include <scene/visualizers/gmselectorgridvisualizer.h>

#include <iostream>

namespace GMlib {


  template <typename T>
  PBezierTriangleDeCasteljau<T>::PBezierTriangleDeCasteljau( const DVector< Vector<T,3> >& c ) {

    _c = c;
//    for( int i = 0; i < _c.getDim(); i++ )
//      _c[i] -= c(0);
//    this->translateGlobal(c(0));

    _selectors = false;
    _c_moved   = false;
    _sgv       = new SelectorGridVisualizer<T>;


    DVector<T> _bary;
    _bary.push_back(0.333333);
    _bary.push_back(0.333333);
    _bary.push_back(0.333333);
    DeCasteljau(3,3,_c,_bary);
  }

  template <typename T>
  PBezierTriangleDeCasteljau<T>::PBezierTriangleDeCasteljau( const PBezierTriangleDeCasteljau<T>& copy ) : PTriangle<T,3>( copy ) {

    _c = copy._c;

    _selectors = false;
    _c_moved   = false;
    _sgv       = new SelectorGridVisualizer<T>;
  }

  template <typename T>
  PBezierTriangleDeCasteljau<T>::~PBezierTriangleDeCasteljau() {

    delete _sgv;
  }

  template <typename T>
  inline
  void PBezierTriangleDeCasteljau<T>::edit( int /*selector*/ ) {

    _c_moved = true;

      if( this->_parent )
        this->_parent->edit( this );

      this->replot();
    _sgv->update();

    _c_moved = false;
  }

  template <typename T>
  inline
  void PBezierTriangleDeCasteljau<T>::eval( T u, T v, T w, int d ) {

//    this->_p.setDim(4);

//    if( _c.getDim() == 3 ) {
//      this->_p[0]= _c[0]*u + _c[1]*v + _c[2]*w;
//      this->_p[1] = _c[0];
//      this->_p[2] = _c[1];
//      this->_p[3] = _c[2];
//    }
//    else if( _c.getDim() == 6 ) {
//      this->_p[0] = _c[0]*(u*u) + _c[1]*(2*u*v) + _c[2]*(2*u*w)
//                    + _c[3]*(v*v) + _c[4]*(2*v*w) + _c[5]*(w*w);
//      this->_p[1] = _c[0]*(2*u) + _c[1]*(2*v) + _c[2]*(2*w);
//      this->_p[2] = _c[1]*(2*u) + _c[3]*(2*v) + _c[4]*(2*w);
//      this->_p[3] = _c[2]*(2*u) + _c[4]*(2*v) + _c[5]*(2*w);
//    }
//    else if( _c.getDim() == 10 ) {
//      this->_p[0] = _c[0]*(u*u*u) + _c[1]*(3*u*u*v) + _c[2]*(3*u*u*w) +
//                    _c[3]*(3*u*v*v) + _c[4]*(6*u*v*w) + _c[5]*(3*u*w*w) +
//                    _c[6]*(v*v*v) + _c[7]*(3*v*v*w) + _c[8]*(3*v*w*w) + _c[9]*(w*w*w);
//      this->_p[1] = _c[0]*(3*u*u) + _c[1]*(6*u*v) + _c[2]*(6*u*w) + _c[3]*(3*v*v) + _c[4]*(6*v*w) + _c[5]*(3*w*w);
//      this->_p[2] = _c[1]*(3*u*u) + _c[3]*(6*u*v) + _c[4]*(6*u*w) + _c[6]*(3*v*v) + _c[7]*(6*v*w) + _c[8]*(3*w*w);
//      this->_p[3] = _c[2]*(3*u*u) + _c[4]*(6*u*v) + _c[5]*(6*u*w) + _c[7]*(3*v*v) + _c[8]*(6*v*w) + _c[9]*(3*w*w);
//    }
  }

  template <typename T>
  inline
  DVector< Vector<T,3> > PBezierTriangleDeCasteljau<T>::getControlPoints() {

    return _c;
  }

  template <typename T>
  inline
  void PBezierTriangleDeCasteljau<T>::hideSelectors() {

    if( !_selectors )
      return;

    // Remove Selector Grid Visualizer
    this->removeVisualizer( _sgv );
    _sgv->reset();

    // Remove selectors
    for( int i = 0; i < _s.getDim(); i++ ) {
      this->remove( _s[i] );
      delete _s[i];
    }

    _selectors = false;
  }

  template <typename T>
  inline
  bool PBezierTriangleDeCasteljau<T>::isSelectorsVisible() const {

    return _selectors;
  }

  template <typename T>
  inline
  void PBezierTriangleDeCasteljau<T>::setControlPoints( const DVector< Vector<T,3> >& c ) {

    _c = c;
  }

  template <typename T>
  inline
  void PBezierTriangleDeCasteljau<T>::showSelectors( bool grid, Color selector_color, Color grid_color ) {

    if( _selectors )
      return;

    _s.setDim( _c.getDim() );
    for( int i = 0, k = 0; i < _s.getDim(); i++ ) {
      Selector<T,3> *sel;
      if( i == 0 )
        sel = new Selector<T,3>( _c[i], k++, this, T(0.2), GMcolor::red() );
      else
        sel = new Selector<T,3>( _c[i], k++, this, T(0.2), selector_color );

      this->insert( sel );
      _s[i] = sel;
    }

    if( grid ) {
      _sgv->setSelectors( _c, 1 );
      this->insertVisualizer( _sgv );
    }

    _selectors = true;
  }



  template <typename T>
  inline
  void PBezierTriangleDeCasteljau<T>::updateCoeffs( const Vector<T,3>& d ) {

    if( _c_moved ) {

      HqMatrix<T,3> invmat = this->_matrix.template toType<T>();
      invmat.invertOrthoNormal();

      Vector<T,3> diff = invmat * d;
      for( int i = 0; i < _c.getDim(); i++ ) {

        _c[i] += diff;
        _s[i]->translateParent( diff.template toType<float>() );
      }

      this->translateParent( -d.template toType<float>(), false );

      _sgv->update();
    }
  }

  template <typename T>
  Vector<T,3> PBezierTriangleDeCasteljau<T>::DeCasteljau(int n, int d, DVector<Vector<T,3>> p, DVector<T> b)
  {
      if(p.getDim() == n)
          return cornerCutting(p, b);
      else
          {
              DVector<Vector<T,3>> q;
              q.setDim(n);
              DVector<DVector<Vector<T,3>>> subs;
              subs.setDim(n);

              DVector<int> index = DVector<int>(n,0);
              index[0] = d;
              for(int i = 1, k=0; i <= n; i++)
              {
                  //Add to sub
                  for(int l = 0; l < index.getDim(); l++)
                  {
                      if(index[l] > 0)
                          subs[l].push_back(p[k]);
                  }
                  if(i == n)
                  {
                      if(index[i-1] == d)
                          break;
                      int j = n-2;
                      for(; index[j] == 0 and j >= 0; j--);
                      if(j < 0)
                          break;
                      i = j+1;
                      index[i]=index[n-1];
                      if(i != n-1)
                          index[n-1]=0;

                  }
                  index[i]++;
                  index[i-1]--;
                  k++;
              }

              for(int i = 0; i < subs.getDim(); i++)
              {
                  q[i] = DeCasteljau(n,d-1,subs[i],b);
              }
              return cornerCutting(q, b);
          }
  }

  template <typename T>
  Vector<T,3> PBezierTriangleDeCasteljau<T>::cornerCutting(DVector<Vector<T,3>> q, DVector<T> b)
  {
      Vector<T,3> final = Vector<T,3>(0,0,0);
      for(int i = 0; i < q.getDim(); i++)
      {
         final +=  b[i]*q[i];
      }
      std::cout<< final[0]<<", "<<final[1]<<", "<<final[2]<<std::endl;
      return final;
  }



} // END namespace GMlib









