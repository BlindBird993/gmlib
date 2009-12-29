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



/*! \file gmVContours.h
 *
 *  Interface for the VContours class.
 *
 *  \date   2009-01-27
 */

#ifndef __gmVCONTOURS_H__
#define __gmVCONTOURS_H__


#include "gmColor.h"
#include "gmMaterial.h"

#include "gmVDefault.h"


namespace GMlib {

  enum GM_VISUALIZER_CONTOURS_TYPE {
    GM_VISUALIZER_CONTOURS_TYPE_COLOR,
    GM_VISUALIZER_CONTOURS_TYPE_MATERIAL
  };

  enum GM_VISUALIZER_CONTOURS_MAP {
    GM_VISUALIZER_CONTOURS_MAP_X,
    GM_VISUALIZER_CONTOURS_MAP_Y,
    GM_VISUALIZER_CONTOURS_MAP_Z,
    GM_VISUALIZER_CONTOURS_MAP_T,
    GM_VISUALIZER_CONTOURS_MAP_U,
    GM_VISUALIZER_CONTOURS_MAP_V,
    GM_VISUALIZER_CONTOURS_MAP_SPEED,
    GM_VISUALIZER_CONTOURS_MAP_CURVATURE,
    GM_VISUALIZER_CONTOURS_MAP_CURVATURE_GAUSS,
    GM_VISUALIZER_CONTOURS_MAP_CURVATURE_MEAN
  };

  template <typename T, int n>
  class VContours : public VDefault<T,n> {
  public:
    VContours();
    VContours( const VContours<T,n>& copy );
    ~VContours();

    void                          display();
    const Array<Color>&           getColors() const;
    const Array<Material>&        getMaterials() const;
    std::string                   getIdentity() const;
    GM_VISUALIZER_CONTOURS_MAP    getMapping() const;
    GM_VISUALIZER_CONTOURS_TYPE   getType() const;

    void                          replot(
      DVector< DVector< Vector<T, 3> > >& p,
      int m, int d
    );
    void                          replot(
      DMatrix< DMatrix< Vector<T, 3> > >& p,
      DMatrix< Vector<T, 3> >& normals,
      int m1, int m2, int d1, int d2
    );

    void                          setColors( const Array<Color>& c );
    void                          setMaterials( const Array<Material>& mat );
    void                          setMapping( GM_VISUALIZER_CONTOURS_MAP );
    void                          setType( GM_VISUALIZER_CONTOURS_TYPE );

  private:
    Array<Color>                  _colors;
    Array<Material>               _materials;
    GM_VISUALIZER_CONTOURS_MAP    _mapping;
    GM_VISUALIZER_CONTOURS_TYPE   _type;

    DVector<Color>                _c1;
    DMatrix<Color>                _c2;

    Color                         _getColor( T d );
    T                             _getCurvatureCurve( DVector< Vector<T, 3> >& p );
    T                             _getCurvatureSurfGauss( DMatrix< Vector<T,3> >& p );
    T                             _getCurvatureSurfMean( DMatrix< Vector<T,3> >& p );
    Material                      _getMaterial( T d );
    void                          _init();

  };

} // END namespace GMlib

// Include VContours class function implementations
#include "gmVContours.c"


#endif // __gmVCONTOURS_H__





