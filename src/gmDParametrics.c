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



/*! \file gmDParametrics.c
 *
 *  Implementation of the DParametrics class.
 *
 *  \date   2009-01-26
 */


namespace GMlib {

  template <typename T, int n>
  inline
  DParametrics<T,n>::DParametrics() {

    _ref = 0;
    _init();
  }


  template <typename T, int n>
  inline
  DParametrics<T,n>::DParametrics( const DParametrics<T,n>& copy ) : DisplayObject( copy ) {

    _dynamic = copy._dynamic;
    _lighted = copy._lighted;
    _dlist = copy._dlist;
    _ref = copy._ref;

    enableDefaultVisualizer();
  }


  template <typename T, int n>
  inline
  DParametrics<T,n>::DParametrics( const Parametrics<T,3>& copy ) : _ref( copy ) {

    _init();
  }


  template <typename T, int n>
  inline
  DParametrics<T,n>::DParametrics( Parametrics<T,3>* copy ) {

    _ref = copy;
    _init();
  }


  template <typename T, int n>
  void DParametrics<T,n>::_init() {

    _dynamic = false;
    _lighted = true;
    _dlist = 0;

    enableDefaultVisualizer();
  }


  template <typename T, int n>
  void DParametrics<T,n>::enableDefaultVisualizer( bool enable ) {

    if( !enable )
      removeVisualizer( &_default_visualizer );
    else {
      if( !_visualizers.exist( &_default_visualizer ) )
        insertVisualizer( &_default_visualizer );
    }
  }


  template <typename T, int n>
  inline
  const GLColor& DParametrics<T,n>::getColor() const {

    return _color;
  }


  template <typename T, int n>
  inline
  GLColor& DParametrics<T,n>::getColor() {

    return _color;
  }


  template <typename T, int n>
  inline
  Vector<float,3> DParametrics<T,n>::getDir() {

    return (Vector<float,3>)(this->_present * _ref->getDir().toFloat());
//    const Vector<T,3> tmp = getTDir();
//    return Vector3D<float>( tmp(0), tmp(1), tmp(2) );
  }


  template <typename T, int n>
  inline
  unsigned int DParametrics<T,n>::getDisplayListIdx() const {

    return _dlist;
  }


  template <typename T, int n>
  inline
  const Material& DParametrics<T,n>::getMaterial() const {

    return _material;
  }


  template <typename T, int n>
  inline
  Material& DParametrics<T,n>::getMaterial() {

    return _material;
  }


  template <typename T, int n>
  inline
  GLMatrix& DParametrics<T,n>::getMatrix() {

    return _ref->getMatrix();
  }


  template <typename T, int n>
  inline
  Parametrics<T,3>* DParametrics<T,n>::getParametrics() {

    return _ref;
  }


  template <typename T, int n>
  inline
  Point<float,3> DParametrics<T,n>::getPos() {

    return (Point<float,3>)(this->_present * _ref->getPos().toFloat());
//    const Point<T,3> tmp = getTPos();
//    return Point3D<float>( tmp(0), tmp(1), tmp(2) );
  }


  template <typename T, int n>
  inline
  Vector<float,3> DParametrics<T,n>::getSide() {

    return (Vector<float,3>)(this->_present * _ref->getSide().toFloat());
//    const Vector<T,3> tmp = getTSide();
//    return Vector3D<float>( tmp(0), tmp(1), tmp(2) );
  }


  template <typename T, int n>
  inline
  const DMatrix<Point<float,2> >& DParametrics<T,n>::getTextureCoords() const {

    return _texture_coords;
  }


  template <typename T, int n>
  Vector<float,3> DParametrics<T,n>::getUp() {

    return (Vector<float,3>)(this->_present * _ref->getUp().toFloat());
//    const Vector<T,3> tmp = getTUp();
//    return Vector3D<float>( tmp(0), tmp(1), tmp(2) );
  }


  template <typename T, int n>
  inline
  const DVector<Vector<float,3> >& DParametrics<T,n>::getVerticesN1() const {

    return _vertices_n1;
  }


  template <typename T, int n>
  inline
  const DMatrix<Arrow<float,3> >& DParametrics<T,n>::getVerticesN2() const {

    return _vertices_n2;
  }


  template <typename T, int n>
  Visualizer<T,n>* DParametrics<T,n>::getVisualizer( const std::string& str ) {

    for( int i = 0; i < _visualizers.getSize(); i++ )
      if( _visualizers[i]->getIdentity() == str )
        return _visualizers[i];

    return 0;
  }


  template <typename T, int n>
  inline
  Array< Visualizer<T,n>* >& DParametrics<T,n>::getVisualizers() {

    return _visualizers;
  }


  template <typename T, int n>
  inline
  void DParametrics<T,n>::insertVisualizer( Visualizer<T,n>* visualizer ) {

    if( _visualizers.exist( visualizer ) )
      return;

    visualizer->set( this );
    _visualizers += visualizer;
  }


  template <typename T, int n>
  inline
  bool DParametrics<T,n>::isDefaultVisualizerActive() {

    return _visualizers.exist( &_default_visualizer );
  }


  template <typename T, int n>
  inline
  bool DParametrics<T,n>::isDynamic() const {

    return _dynamic;
  }


  template <typename T, int n>
  inline
  bool DParametrics<T,n>::isLighted() const {

    return _lighted;
  }


  template <typename T, int n>
  inline
  void DParametrics<T,n>::removeVisualizer( Visualizer<T,n>* visualizer ) {

    _visualizers.remove( visualizer );
  }


  template <typename T, int n>
  inline
  void DParametrics<T,n>::rotate( Angle a, const Vector<float,3>& rot_axel ) {

    if(!_ref)
      return;

    Vector<T,3> tmp(0.0);
    for( int i = 0; i < 3; i++ )
      tmp[i] = rot_axel(i);

    _ref->rotate( a, tmp );
  }


  template <typename T, int n>
  inline
  void DParametrics<T,n>::rotate( Angle a, const Point<float,3>& p, const UnitVector<float,3>& d ) {

    if(!_ref)
      return;

    Point<T,3> tmp1(0.0);
    for( int i = 0; i < 3; i++ )
      tmp1[i] = p(i);

    Vector<T,3> tmp2(0.0);
    for( int i = 0; i < 3; i++ )
      tmp2[i] = d(i);

    _ref->rotate( a, tmp1, tmp2 );
  }


  template <typename T, int n>
  inline
  void DParametrics<T,n>::rotateGlobal(Angle a, const Vector<float,3>& rot_axel) {

    if(!_ref)
      return;

    UnitVector<float,3> tmp_rot_axel = _matrix_scene_inv * rot_axel;

    Vector<T,3> tmp(0.0);
    for( int i = 0; i < 3; i++ )
      tmp[i] = tmp_rot_axel(i);

    _ref->rotateGlobal( a, tmp );
  }


  template <typename T, int n>
  inline
  void DParametrics<T,n>::rotateGlobal(Angle a, const Point<float,3>& p,const UnitVector<float,3>& d) {

    if(!_ref)
      return;

    Point<float,3> tmp_p = _matrix_scene_inv * p;
    UnitVector<float,3> tmp_d = _matrix_scene_inv * d;

    Point<T,3> tmp1(0.0);
    for( int i = 0; i < 3; i++ )
      tmp1[i] = tmp_p(i);

    Vector<T,3> tmp2(0.0);
    for( int i = 0; i < 3; i++ )
      tmp2[i] = tmp_d(i);

    _ref->rotateGlobal( a, tmp1, tmp2 );
  }


  template <typename T, int n>
  inline
  void DParametrics<T,n>::setColor( const GLColor& color ) {

    _color = color;
  }


  template <typename T, int n>
  inline
  void DParametrics<T,n>::setLighted( bool lighted ) {

    _lighted = lighted;
  }


  template <typename T, int n>
  inline
  void DParametrics<T,n>::setMaterial( const Material& material ) {

    _material = material;
  }


  template <typename T, int n>
  inline
  void DParametrics<T,n>::setParametrics( Parametrics<T,3>* ref ) {

    _ref = ref;
  }


  template <typename T, int n>
  inline
  void DParametrics<T,n>::toggleDefaultVisualizer() {

    if( !_visualizers.exist( &_default_visualizer ) )
      enableDefaultVisualizer( true );
    else
      enableDefaultVisualizer( false );
  }


  template <typename T, int n>
  inline
  void DParametrics<T,n>::translate( const Vector<float,3>& trans_vector ) {

    if(!_ref)
      return;

    Vector<T,3> tmp(0.0);
    for( int i = 0; i < 3; i++ )
      tmp[i] = trans_vector(i);

    _ref->translate( tmp );
  }


  template <typename T, int n>
  inline
  void DParametrics<T,n>::translateGlobal( const Vector<float,3>& trans_vector ) {

    if(!_ref)
      return;

    Vector<float,3> tmp_vec = this->_matrix_scene_inv * trans_vector;

    Vector<T,3> tmp(0.0);
    for( int i = 0; i < 3; i++ )
      tmp[i] = tmp_vec(i);

    _ref->translateGlobal( tmp );
  }
}
