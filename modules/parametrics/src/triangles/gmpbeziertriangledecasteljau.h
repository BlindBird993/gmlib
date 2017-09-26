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





#ifndef GM_PARAMETRICS_TRIANGLES_PBEZIERTRIANGLEDECASTELJAU_H
#define GM_PARAMETRICS_TRIANGLES_PBEZIERTRIANGLEDECASTELJAU_H



#include "../gmptriangle.h"

// gmlib



namespace GMlib {

template <typename T, int n>
class Selector;

template <typename T>
class SelectorGridVisualizer;


  template <typename T>
  class PBezierTriangleDeCasteljau : public PTriangle<T,3> {
    GM_SCENEOBJECT(PBezierTriangleDeCasteljau)
  public:
    PBezierTriangleDeCasteljau( const DVector< Vector<T,3> >& c );
    PBezierTriangleDeCasteljau( const PBezierTriangleDeCasteljau& copy );
    ~PBezierTriangleDeCasteljau();

    DVector< Vector<T,3> >      getControlPoints();
    void                        edit( int selector ) override;
    virtual void                hideSelectors();
    bool                        isSelectorsVisible() const;
    void                        setControlPoints( const DVector< Vector<T,3> >& c );
    virtual void                showSelectors( bool grid, Color selector_color = GMcolor::darkBlue(), Color grid_color = GMcolor::lightGreen() );
    void                        updateCoeffs( const Vector<T,3>& d ) override;
    Vector<T,3> DeCasteljau(int d, DVector<Vector<T,3>> p, Vector<T,3> b) const;
    Vector<T,3> DeCasteljauMatrix(int n, const Vector<T,3>& u) const;

  protected:
    DVector< Vector<T,3> >      _c;

    bool                        _selectors;
    SelectorGridVisualizer<T>  *_sgv;
    DVector< Selector<T,3>* >   _s;
    bool                        _c_moved;

    /* implemented from PTriangle */
    void                        eval( T u, T v, T w, int d ) const override;

  private:
    //Vector<T,3> DeCasteljau(int d, DVector<Vector<T,3>> p, Vector<T,3> b, int numDer, Vector<T,3> dir) const;
    Vector<T,3> cornerCutting(DVector<Vector<T,3>> q, Vector<T,3> b) const;
    void evalDeCasteljau(T u, T v, T w) const;
    void evalHardCoded(T u, T v, T w, int d) const;
  public:
    // Should not be public. Only for testing purpose.
    DMatrix<T> computeM(int d, int n, DVector<T> u) const;

  }; // END class PBezierTriangleDeCasteljau



} // END namespace GMlib




// Include PBezierTriangle class function implementations
#include "gmpbeziertriangledecasteljau.c"


#endif // GM_PARAMETRICS_TRIANGLES_PBEZIERTRIANGLEDECASTELJAU_H
