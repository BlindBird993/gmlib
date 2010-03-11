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



/*! \file gmVContours.c
 *
 *  VContours class function implementations.
 *
 *  \date   2009-01-27
 */


namespace GMlib {

  template <typename T, int n>
  VContours<T,n>::VContours() {

    _init();
  }


  template <typename T, int n>
  inline
  VContours<T,n>::VContours( const VContours<T,n>& copy ) : VDefault<T,n>( copy ) {}


  template <typename T, int n>
  inline
  VContours<T,n>::~VContours() {}


  template <typename T, int n>
  inline
  Color VContours<T,n>::_getColor( T d ) {

    // Find Index
    int idx;
    idx = d * ( _colors.getSize()-1 );
    if( idx == _colors.getSize()-1 ) idx--;
    if( (idx < 0) || (idx > _colors.getSize()-1) ) idx = 0;


    double local_d = (double( _colors.getSize()-1 ) * d) - idx;
    Color ret = _colors[idx].getInterpolatedHSV( local_d, _colors[idx+1] );

    return ret;
  }


  template <typename T, int n>
  inline
  T VContours<T,n>::_getCurvatureCurve( DVector< Vector<T,3> >& p ) {

    Vector<T,3> d1 = p[1];
    T a1= d1.getLength();

    if( a1 < T(1.0e-5) )
      return T(0);

    d1 /= a1;

    Vector<T,3> d2 = ( p[2] - ( d1 * p[2] ) * d1 ) / ( a1 * a1 );

    return d2.getLength();
  }


  template <typename T, int n>
  inline
  T VContours<T,n>::_getCurvatureSurfGauss( DMatrix< Vector<T,3> >& p ) {

    UnitVector<T,3> N   = Vector3D<T>(p[1][0])^p[0][1];
    Vector<T,3>		  du  = p[1][0];
    Vector<T,3>		  dv  = p[0][1];
    Vector<T,3>		  duu = p[2][0];
    Vector<T,3>		  duv = p[1][1];
    Vector<T,3>		  dvv = p[0][2];

    T E = du  * du;
    T F = du  * dv;
    T G = dv  * dv;
    T e = N   * duu;
    T f = N   * duv;
    T g = N   * dvv;

    return (e*g - f*f) / (E*G - F*F);
  }


  template <typename T, int n>
  inline
  T VContours<T,n>::_getCurvatureSurfMean( DMatrix< Vector<T,3> >& p ) {

    UnitVector<T,3> N   = Vector3D<T>(p[1][0])^p[0][1];
    Vector<T,3>		  du  = p[1][0];
    Vector<T,3>		  dv  = p[0][1];
    Vector<T,3>		  duu = p[2][0];
    Vector<T,3>		  duv = p[1][1];
    Vector<T,3>		  dvv = p[0][2];

    T E = du  * du;
    T F = du  * dv;
    T G = dv  * dv;
    T e = N   * duu;
    T f = N   * duv;
    T g = N   * dvv;

    return 0.5 * (e*G - 2 * (f*F) + g*E) / (E*G - F*F);
  }


  template <typename T, int n>
  inline
  T VContours<T,n>::_getCurvatureSurfPrincipalMax( DMatrix< Vector<T,3> >& p ) {

    T K = _getCurvatureSurfGauss( p );
    T H = _getCurvatureSurfMean( p );

    return H + sqrt( H*H - K );
  }


  template <typename T, int n>
  inline
  T VContours<T,n>::_getCurvatureSurfPrincipalMin( DMatrix< Vector<T,3> >& p ) {

    T K = _getCurvatureSurfGauss( p );
    T H = _getCurvatureSurfMean( p );

    return H - sqrt( H*H - K );
  }


  template <typename T, int n>
  inline
  Material VContours<T,n>::_getMaterial( T d ) {

    // Find Index
    int idx;
    idx = d * (_materials.getSize()-1);
    if( idx == _materials.getSize()-1 ) idx--;
    if( (idx < 0) || (idx > _materials.getSize()-1) ) idx = 0;


    double local_d = (double( _materials.getSize()-1 ) * d) - idx;
    Color amb = _materials[idx].getAmb().getInterpolatedHSV( local_d, _materials[idx+1].getAmb() );
    Color dif = _materials[idx].getDif().getInterpolatedHSV( local_d, _materials[idx+1].getDif() );
    Color spc= _materials[idx].getSpc().getInterpolatedHSV( local_d, _materials[idx+1].getSpc() );
    float shininess = ( _materials[idx].getShininess() + _materials[idx+1].getShininess() ) / 2.0f;

    Material ret( amb, dif, spc, shininess );
    return ret;
  }


  template <typename T, int n>
  inline
  T VContours<T,n>::_getValueCurve( DVector< DVector< Vector<T, 3> > >& p, int i ) {

    switch( _mapping ) {
    case GM_VISUALIZER_CONTOURS_MAP_X:
      return p[i][0][0];
    case GM_VISUALIZER_CONTOURS_MAP_Y:
      return p[i][0][1];
    case GM_VISUALIZER_CONTOURS_MAP_Z:
      return p[i][0][2];

    default: break;
    }


    // Values requireing 1st derivative
    if( p[i].getDim() < 2 )
      return T(0);

    switch( _mapping ) {
    case GM_VISUALIZER_CONTOURS_MAP_SPEED:
    case GM_VISUALIZER_CONTOURS_MAP_SPEED_U:
      return p[i][1].getLength();

    default: break;
    }


    // Values requireing 2nd derivative
    if( p[i].getDim() < 2 )
      return T(0);

    switch( _mapping ) {
    case GM_VISUALIZER_CONTOURS_MAP_CURVATURE:
      return _getCurvatureCurve(p[i]);

    default: break;
    }

    return T(0);
  }


  template <typename T, int n>
  inline
  T VContours<T,n>::_getValueSurface( DMatrix< DMatrix< Vector<T, 3> > >& p, int i, int j ) {

    switch( _mapping ) {
    case GM_VISUALIZER_CONTOURS_MAP_X:
      return p[i][j][0][0][0];
    case GM_VISUALIZER_CONTOURS_MAP_Y:
      return p[i][j][0][0][1];
    case GM_VISUALIZER_CONTOURS_MAP_Z:
      return p[i][j][0][0][2];

    default: break;
    }


    // Values requireing 1st derivatives
    if( p[i][j].getDim1() < 2 || p[i][j].getDim2() < 2 )
      return T(0);

    switch( _mapping ) {
    case GM_VISUALIZER_CONTOURS_MAP_SPEED_U:
      return p[i][j][1][0].getLength();
    case GM_VISUALIZER_CONTOURS_MAP_SPEED_V:
      return p[i][j][0][1].getLength();

    default: break;
    }


    // Values requireing 2nd derivatives
    if( p[i][j].getDim1() < 3 || p[i][j].getDim2() < 3 )
      return T(0);

    switch( _mapping ) {
    case GM_VISUALIZER_CONTOURS_MAP_CURVATURE_GAUSS:
      return _getCurvatureSurfGauss(p[i][j]);

    case GM_VISUALIZER_CONTOURS_MAP_CURVATURE_MEAN:
      return _getCurvatureSurfMean(p[i][j]);

    case GM_VISUALIZER_CONTOURS_MAP_CURVATURE_PRINCIPAL_MAX:
      return _getCurvatureSurfPrincipalMax( p[i][j] );

    case GM_VISUALIZER_CONTOURS_MAP_CURVATURE_PRINCIPAL_MIN:
      return _getCurvatureSurfPrincipalMin( p[i][j] );

    default: break;
    }

    return T(0);
  }


  template <typename T, int n>
  inline
  void VContours<T,n>::_init() {

    _type = GM_VISUALIZER_CONTOURS_TYPE_COLOR;
    _mapping = GM_VISUALIZER_CONTOURS_MAP_X;

    // Set default colors
    _colors += GMcolor::Red;
    _colors += GMcolor::Blue;

    // Set default materials
    _materials += GMmaterial::Obsidian;
    _materials += GMmaterial::Gold;

  }


  template <typename T, int n>
  inline
  void VContours<T,n>::display() {

    // Push GL Attribs
    glPushAttrib( GL_LIGHTING_BIT | GL_POINT_BIT | GL_LINE_BIT );

    // Set Properties
    if( _type == GM_VISUALIZER_CONTOURS_TYPE_COLOR )          glDisable( GL_LIGHTING );
    else if( _type == GM_VISUALIZER_CONTOURS_TYPE_MATERIAL )  glEnable( GL_LIGHTING );


    if( n == 1 ) {

      // Enable the Vertex Array
      glEnableClientState( GL_VERTEX_ARRAY );
      glEnableClientState( GL_COLOR_ARRAY );

      // Give Pointer to Vertex Data
      glColorPointer( 4, GL_UNSIGNED_BYTE, 0, &_c1[0] );
      glVertexPointer( 3, GL_FLOAT, 0, this->_n1(0).getPtr() );

      // Draw
      glDrawArrays( GL_LINE_STRIP, 0, this->_n1.getDim() );

      glDisableClientState( GL_VERTEX_ARRAY );
      glDisableClientState( GL_COLOR_ARRAY );
    }
    else if( n == 2 ) {

      // Enable Vertex and Normal Array
      glEnableClientState( GL_VERTEX_ARRAY );
      glEnableClientState( GL_COLOR_ARRAY );

      // Draw
      for( int i = 0; i < this->_n2.getDim1(); i++ ) {

        // Give Pointers to Vertex and Normal Data
        glColorPointer( 4, GL_UNSIGNED_BYTE, 0, &_c2[i][0] );
        glVertexPointer( 3, GL_FLOAT, 2*3*sizeof(float), this->_n2(i)(0).getPos().getPtr() );

        // Draw Strip
        glDrawArrays( GL_TRIANGLE_STRIP, 0, this->_n2(i).getDim() );
      }

      // Disable Client States
      glDisableClientState( GL_VERTEX_ARRAY );
      glDisableClientState( GL_COLOR_ARRAY );
    }

    // Pop GL Attribs
    glPopAttrib();
  }


  template <typename T, int n>
  inline
  const Array<Color>& VContours<T,n>::getColors() const {

    return _colors;
  }


  template <typename T, int n>
  inline
  std::string VContours<T,n>::getIdentity() const {

    return "VContours";
  }


  template <typename T, int n>
  inline
  GM_VISUALIZER_CONTOURS_MAP VContours<T,n>::getMapping() const {

    return _mapping;
  }


  template <typename T, int n>
  inline
  const Array<Material>& VContours<T,n>::getMaterials() const {

    return _materials;
  }


  template <typename T, int n>
  inline
  GM_VISUALIZER_CONTOURS_TYPE VContours<T,n>::getType() const {

    return _type;
  }


  template <typename T, int n>
  inline
  void VContours<T,n>::replot(
    DVector< DVector< Vector<T, 3> > >& p,
    int m, int d
  ) {

    // Replot the default visualizer
    VDefault<T,n>::replot( p, m, d );

    T min, max;
    T C; // Color Factor, (map to local)
    _c1.setDim( p.getDim() );
    switch( _mapping ) {

    case GM_VISUALIZER_CONTOURS_MAP_T:
    case GM_VISUALIZER_CONTOURS_MAP_U:
      {
        for( int i = 0; i < p.getDim(); i++ )
          _c1[i] = _getColor( double(i) / double(p.getDim()-1) );
      }
      break;
    default:
      {
        // Init min/max
        min = max = _getValueCurve( p, 0 );//_getCurvatureCurve(p[0]);

        // Extract all speed data
        for( int i = 0; i < p.getDim(); i++ ) {

          const T curvature = _getValueCurve( p, i );//_getCurvatureCurve(p[i]);
          if( curvature < min )
            min = curvature;
          if( curvature > max )
            max = curvature;
        }

        // Correct interval
        if( (max-min) < 1e-5 ) {

          for( int i = 0; i < p.getDim(); i++ )
            _c1[i] = _colors[0];
        }
        else {
          C = 1.0f / (max-min);
          min /= (max-min);

          // Compute interpolated color values
          for( int i = 0; i < p.getDim(); i++ ) {

            const T curvature = _getValueCurve( p, i );//_getCurvatureCurve(p[i]);
            _c1[i] = _getColor( ( C * curvature ) - min );
          }
        }
      }
      break;
    }
  }


  template <typename T, int n>
  inline
  void VContours<T,n>::replot(
    DMatrix< DMatrix< Vector<T, 3> > >& p,
    DMatrix< Vector<T, 3> >& normals,
    int m1, int m2, int d1, int d2
  ) {

    // Replot the default visualizer
    VDefault<T,n>::replot( p, normals, m1, m2, d1, d2 );

    // Color/Material Countours
    DMatrix<double> cmap;

    T min, max;
    T C;
    cmap.setDim( p.getDim1(), p.getDim2() );
    switch( _mapping ) {

    case GM_VISUALIZER_CONTOURS_MAP_U:
      {
        for( int i = 0; i < p.getDim1(); i++ )
          for( int j = 0; j < p.getDim2(); j++ )
            cmap[i][j] = double(i) / double(p.getDim1()-1);
      }
      break;
    case GM_VISUALIZER_CONTOURS_MAP_V:
      {
        for( int i = 0; i < p.getDim1(); i++ )
          for( int j = 0; j < p.getDim2(); j++ )
            cmap[i][j] = double(j) / double(p.getDim2()-1);
      }
      break;

    default:
      {
        // Init min/max
        min = max = _getValueSurface(p, 0, 0);

        // Extract all Gaussian Curvature data
        for( int i = 0; i < p.getDim1(); i++ ) {
          for( int j = 0; j < p.getDim2(); j++ ) {

            const T curvature = _getValueSurface(p, i, j);
            if( curvature < min )
              min = curvature;
            if( curvature > max )
              max = curvature;
          }
        }

        // Correct interval
        if( (max-min) < 1e-5 ) {

          for( int i = 0; i < p.getDim1(); i++ )
            for( int j = 0; j < p.getDim2(); j++ )
              cmap[i][j] = 0.0;
        }
        else {
          C = 1.0f / (max-min);
          min /= (max-min);

          // Compute interpolated map values
          for( int i = 0; i < p.getDim1(); i++ ) {
            for( int j = 0; j < p.getDim2(); j++ ) {

              const T curvature = _getValueSurface(p, i, j);
              cmap[i][j] = ( C * curvature ) - min;
            }
          }
        }
      }
      break;
    }


    DMatrix<Color> ccs;
//    DMatrix<Material> mcs;
//    if( _type == GM_VISUALIZER_CONTOURS_TYPE_COLOR ) {

      ccs.setDim( p.getDim1(), p.getDim2() );
      for( int i = 0; i < p.getDim1(); i++ )
        for( int j = 0; j < p.getDim2(); j++ )
          ccs[i][j] = _getColor( cmap[i][j] );
//    }
//    else if( _type == GM_VISUALIZER_CONTOURS_TYPE_MATERIAL ) {
//
//      mcs.setDim( p.getDim1(), p.getDim2() );
//      for( int i = 0; i < p.getDim1(); i++ )
//        for( int j = 0; j < p.getDim2(); j++ )
//          mcs[i][j] = _getMaterial( cmap[i][j] );
//    }


    // Create Vertex arrays ^^
    _c2.setDim( p.getDim1()-1, p.getDim2()*2 );

    for( int i = 0; i < p.getDim1()-1; i++ ) {
      for( int j = 0; j < p.getDim2(); j++ ) {

        _c2[i][ 2*j   ] = ccs[ i   ][j];
        _c2[i][ 2*j+1 ] = ccs[ i+1 ][j];
      }
    }
  }


  template <typename T, int n>
  inline
  void VContours<T,n>::setColors( const Array<Color>& c ) {

    _colors = c;
  }


  template <typename T, int n>
  inline
  void VContours<T,n>::setMaterials( const Array<Material>& mat ) {

    _materials = mat;
  }


  template <typename T, int n>
  inline
  void VContours<T,n>::setMapping( GM_VISUALIZER_CONTOURS_MAP mapping ) {

    _mapping = mapping;
  }


  template <typename T, int n>
  inline
  void VContours<T,n>::setType( GM_VISUALIZER_CONTOURS_TYPE type ) {

    _type = type;
  }
}
