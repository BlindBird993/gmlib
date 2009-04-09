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



/*! \file gmAffineSpace.c
 *  \brief AffineSpace class implementations
 *
 *  Implementations of the AffineSpace class.
 *
 *  \date   2008-11-24
 */


namespace GMlib {


  template <typename T, int n>
  inline
  AffineSpace<T,n>::AffineSpace() : _matrix() {

    if( n == 3 )
      _init();
  }


  template <typename T, int n>
  inline
  AffineSpace<T,n>::AffineSpace( const AffineSpace<T,n>& copy ) {

    _matrix = copy._matrix;

    if( n == 3 ) {

      _pos  = copy._pos;
      _dir  = copy._dir;
      _side = copy._side;
      _up   = copy._up;
    }
  }


  template <typename T, int n>
  void AffineSpace<T,n>::_init () {

    Point<T,n>  pos( T(0) );
    Vector<T,n> dir( T(0) );
    Vector<T,n> up( T(0) );

    dir[0] = up[2] = T(1);

    _pos	= pos;
    _dir	= dir;
    _up		= up - (up*_dir)*_dir;
    _side	= Vector3D<T>(_up)^_dir;

    basisChange(_side, _up, _dir, _pos);
  }


  /*! void AffineSpace<T,n>::basisChange( const Vector<T,n>& x, const Vector<T,n>& y, const Vector<T,n>& z, const Vector<T,n>& p )
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  template <typename T, int n>
  inline
  void AffineSpace<T,n>::basisChange( const Vector<T,n>& x, const Vector<T,n>& y, const Vector<T,n>& z, const Vector<T,n>& p ) {

    HqMatrix<T,n> mat;
    for( int i = 0; i < n; i++ ) {
      mat[0][i] = z(i);
      mat[1][i] = x(i);
      mat[2][i] = y(i);
      mat[3][i] = p(i);
    }
    mat[0][n] = 0;
    mat[1][n] = 0;
    mat[2][n] = 0;
    mat[3][n] = 1;

    _matrix.basisChange( mat );
  }


  /*! Vector<T,n>	AffineSpace<T,n>::getDir()
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  template <typename T, int n>
  inline
  Vector<T,n>	AffineSpace<T,n>::getDir()	{

//    const Vector<float,3> tmp = _matrix * _dir;
//    Vector<T,n> tmp2;
//    for( int i = 0; i < 3; i++ )
//      tmp2[i] = tmp(i);
//    return tmp2;
//     return _matrix * _dir;
     return _dir;
  }


  template <typename T, int n>
  inline
  std::string AffineSpace<T,n>::getIdentity() const {

    return "AffineSpace";
  }


  template <typename T, int n>
  inline
  HqMatrix<float,3>& AffineSpace<T,n>::getMatrix() {

    /*! \todo fix how the matrix is handled */
    static HqMatrix<float,3> retmat;
    for( int i = 0; i < 4; i++ )
      for( int j = 0; j < 4; j++ )
        retmat[i][j] = _matrix[i][j];
    return retmat;
  }


  /*! Point<T,n> AffineSpace<T,n>::getPos()
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  template <typename T, int n>
  inline
  Point<T,n> AffineSpace<T,n>::getPos() {

//    const Point<float,3> tmp = _matrix * _pos;
//    Point<T,n> tmp2;
//    for( int i = 0; i < 3; i++ )
//      tmp2[i] = tmp(i);
//    return tmp2;
//    return _matrix * _pos;
    return _pos;
  }


  /*! Vector<T,n>	AffineSpace<T,n>::getSide()
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  template <typename T, int n>
  inline
  Vector<T,n>	AffineSpace<T,n>::getSide() {

//    const Vector<float,3> tmp = _matrix * _side;
//    Vector<T,n> tmp2;
//    for( int i = 0; i < 3; i++ )
//      tmp2[i] = tmp(i);
//    return tmp2;
//    return _matrix * _side;
    return _side;
  }


  /*! Vector<T,n>	AffineSpace<T,n>::getUp()
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  template <typename T, int n>
  inline
  Vector<T,n>	AffineSpace<T,n>::getUp() {

//    const Vector<float,3> tmp = _matrix * _up;
//    Vector<T,n> tmp2;
//    for( int i = 0; i < 3; i++ )
//      tmp2[i] = tmp(i);
//    return tmp2;
//    return _matrix * _up;
    return _up;
  }


  /*! void AffineSpace<T,n>::move( const Vector<T,n>& t )
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   *  Move in direction t.
   */
  template <typename T, int n>
  void AffineSpace<T,n>::move( const Vector<T,n>& t ) {

    _pos += t;
    basisChange(_side, _up, _dir, _pos);
  }


  template <typename T, int n>
  inline
  void AffineSpace<T,n>::rotate( Angle a, const Point<T,n>& p,const UnitVector<T,n>& ra ) {

//    GLMatrix m(a,p.toFloat(),d.toFloat());
//    _pos  *= m;
//    _up   *= m;
//    _dir  *= m;
//    _side *= m;
//
//    basisChange(_side, _up, _dir, _pos);

//    Vector<T,n> lu = ra.getLinIndVec();
//    Vector<T,n> u = Vector3D<T>( lu[0], lu[1], lu[2] ) ^ ra;
//    Vector<T,n> v = Vector3D<T>( u[0], u[1], u[2] ) ^ ra;
//    _matrix.rotate(a, u, v, p.toFloat() );
  }


  template <typename T, int n>
  inline
  void AffineSpace<T,n>::rotate( Angle a, const Vector<T,n>& ra ) {

//    GLMatrix m( a,rot_axel.toFloat() );
//    _up   *= m;
//    _dir  *= m;
//    _side *= m;
//    basisChange(_side, _up, _dir, _pos);

//    Vector<T,n> lu = ra.getLinIndVec();
//    Vector<T,n> u = Vector3D<T>( lu[0], lu[1], lu[2] ) ^ ra;
//    Vector<T,n> v = Vector3D<T>( u[0], u[1], u[2] ) ^ ra;
//    _matrix.rotate(a, u, v);
  }


  template <typename T, int n>
  inline
  void AffineSpace<T,n>::rotateGlobal( Angle a, const Point<T,n>& p,const UnitVector<T,n>& ra ) {

//    Vector<T,n> lu = ra.getLinIndVec();
//    Vector<T,n> u = Vector3D<T>( lu[0], lu[1], lu[2] ) ^ ra;
//    Vector<T,n> v = Vector3D<T>( u[0], u[1], u[2] ) ^ ra;
//    _matrix.rotateGlobal(a, u, v, p.toFloat() );
//    _matrix.rotateGlobal(a,p.toFloat(),d.toFloat());
  }


  template <typename T, int n>
  inline
  void AffineSpace<T,n>::rotateGlobal( Angle a, const Vector<T,n>& ra ) {

//    Vector<T,n> lu = ra.getLinIndVec();
//    Vector<T,n> u = Vector3D<T>( lu[0], lu[1], lu[2] ) ^ ra;
//    Vector<T,n> v = Vector3D<T>( u[0], u[1], u[2] ) ^ ra;
//    _matrix.rotateGlobal(a, u, v);
//    _matrix.rotateGlobal( a, (Vector<T,n>)rot_axel.toFloat() );
  }


  template <typename T, int n>
  inline
  void AffineSpace<T,n>::translate( const Vector<T,n>& trans_vector ) {

    cout << "Translate (AS)" << endl;
//    move( trans_vector );
//    _matrix.translate(trans_vector);
  }


  template <typename T, int n>
  inline
  void AffineSpace<T,n>::translateGlobal( const Vector<T,n>& trans_vector ) {

    cout << "Translate Global (AS)" << endl;
//    _matrix.translateGlobal(trans_vector);
  }

}
