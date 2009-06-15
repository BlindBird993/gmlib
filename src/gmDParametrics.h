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



/*! \file gmDParametrics.h
 *
 *  Interface for the Displayable Parametrics class.
 *
 *  \date   2009-01-26
 */

#ifndef __gmDPARAMETRICS_H__
#define __gmDPARAMETRICS_H__

// STL
#include <string>

// GMlib
#include "gmArray.h"
#include "gmMaterial.h"
#include "gmDisplayObject.h"
#include "gmVisualizer.h"
#include "gmVDefault.h"
#include "gmParametrics.h"

namespace GMlib {


  enum GM_DPARAMETRICS {
    GM_POINT = 0,
    GM_CURVE = 1,
    GM_SURFACE = 2,
    GM_FLOW = 3
  };


  //////////////////////// PARAMETRICS !!!!!!!!!!!!!! PARAMETRICS ////////////////////////
//
//  enum GM_RESAMPLE_MODE {
//    GM_RESAMPLE_INLINE,
//    GM_RESAMPLE_PREEVAL
//  };
//
//  enum GM_DERIVATION_METHOD {
//    GM_DERIVATION_EXPLICIT,
//    GM_DERIVATION_DD
//  };
  //////////////////////// PARAMETRICS !!!!!!!!!!!!!! PARAMETRICS ////////////////////////


  template <typename T, int n>
  class DParametrics : public DisplayObject {
  public:
    DParametrics();
    DParametrics( const DParametrics<T,n>& copy );
    DParametrics( const Parametrics<T,3>& copy );
    DParametrics( Parametrics<T,3>* copy );
    ~DParametrics();

    void                                  enableDefaultVisualizer( bool enable = true );
//    Vector<float,3>                       getDir();
    unsigned int                          getDisplayListIdx() const;
    Parametrics<T,3>*                     getParametrics();
//    Point<float,3>	                      getPos();
//    Vector<float,3>	                      getSide();
    const DMatrix<Point<float,2> >&       getTextureCoords() const;
//    Vector<float,3>                       getUp();
    const DVector<Vector<float,3> >&      getVerticesN1() const;
    const DMatrix<Arrow<float,3> >&       getVerticesN2() const;
    Visualizer<T,n>*                      getVisualizer( const std::string& str );
    Array< Visualizer<T,n>* >&            getVisualizers();
    void                                  insertVisualizer( Visualizer<T,n>* visualizer );
    bool                                  isDynamic() const;
    bool                                  isDefaultVisualizerActive();
    void                                  removeVisualizer( Visualizer<T,n>* visualizer );
//    void                                  rotate( Angle a, const Vector<float,3>& rot_axel );
//    void                                  rotate( Angle a, const Point<float,3>& p,const UnitVector<float,3>& d );
//    void                                  rotateGlobal(Angle a, const Vector<float,3>& rot_axel);
//    void                                  rotateGlobal(Angle a, const Point<float,3>& p,const UnitVector<float,3>& d);
    void                                  rotate(Angle a, const Vector<float,3>& rot_axel);
    void                                  rotate(Angle a, const Point<float,3>& p,const UnitVector<float,3>& d);
    void                                  rotateGlobal(Angle a, const Vector<float,3>& rot_axel);
    void                                  rotateGlobal(Angle a, const Point<float,3>& p,const UnitVector<float,3>& d);
    void                                  setParametrics( Parametrics<T,3> *ref );
    void                                  toggleDefaultVisualizer();
//    void                                  translate( const Vector<float,3>& trans_vector );
//    void                                  translateGlobal( const Vector<float,3>& trans_vector );
    void                                  translate(const Vector<float,3>& trans_vector);
    void                                  translateGlobal(const Vector<float,3>& trans_vector);

  protected:
    Array< Visualizer<T,n>* >             _visualizers;
    VDefault<T,n>                         _default_visualizer;

    Parametrics<T,3>                      *_ref;

    // States
    bool                                  _dynamic;



    unsigned int                          _dlist;


    DMatrix< Point<float,2> >           _texture_coords;
    DVector< Vector<float,3> >	          _vertices_n1;
    DMatrix< Arrow<float,3> >           _vertices_n2;		// Vertex-arrays for dynamic display


//    HqMatrix<float,3>&                  getMatrix();


  private:
    void                                  _init();
    void                                  _initSoType();










  //////////////////////// PARAMETRICS !!!!!!!!!!!!!! PARAMETRICS ////////////////////////
  //////////////////////// PARAMETRICS !!!!!!!!!!!!!! PARAMETRICS ////////////////////////
  //////////////////////// PARAMETRICS !!!!!!!!!!!!!! PARAMETRICS ////////////////////////
  //////////////////////// PARAMETRICS !!!!!!!!!!!!!! PARAMETRICS ////////////////////////
  //////////////////////// PARAMETRICS !!!!!!!!!!!!!! PARAMETRICS ////////////////////////


    void                    setDerivationMethod( GM_DERIVATION_METHOD method );

  protected:
    GM_DERIVATION_METHOD    _dm;


  };
}

// Include DParamterics class function implementations
#include "gmDParametrics.c"



#endif // __gmDPARAMETRICS_H__
