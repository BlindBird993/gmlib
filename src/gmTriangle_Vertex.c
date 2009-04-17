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



/*! \file gmTriangle_Vertex.c
 *  \brief Vertex class function implementations
 *
 *  \date   2008-10-22
 */


namespace GMlib {


  template <typename T>
  inline
  Vertex<T>::Vertex() : Arrow<T,3>(), _edges() {

    _const = false;
    _maxradius = _radius = 0.0;
  }


  template <typename T>
  inline
  Vertex<T>::Vertex( const Point<T,2>& v ) : Arrow<T,3>( Point3D<T>( v(0), v(1), 0 ) ) {

    _const = false;
    _maxradius = _radius = 0.0;
  }


  template <typename T>
  inline
  Vertex<T>::Vertex( const Point<T,3>& p ) : Arrow<T,3>( p ), _edges() {

    _const = false;
    _maxradius = _radius = 0.0;
  }


  template <typename T>
  inline
  Vertex<T>::Vertex( const Point<T,3>& p, const Vector<T,3>& n ) : Arrow<T,3>( p, n ), _edges() {

    _const = false;
    _maxradius = _radius = 0.0;
  }


  template <typename T>
  inline
  Vertex<T>::Vertex( const T& x, const T& y, const T& z ) : Arrow<T,3>( Point3D<T>( x, y, z ) ), _edges() {

    _const = false;
    _maxradius = _radius = 0.0;
  }


  template <typename T>
  Vertex<T>::~Vertex() {

    _edges.clear();
  }


  template <typename T>
  void Vertex<T>::_computeNormal() {

    Array<Triangle<T>*> tris = getTriangles();
    Point<T,3> nor = Point<T,3>(T(0));
    for( int i = 0; i < tris.getSize(); i++ )
      nor += tris[i]->getNormal();

    nor /= tris.getSize();
    setDir( UnitVector3D<T>(nor) );
  }


  template <typename T>
  void Vertex<T>::_deleteEdges() {

    while( _edges.getSize() > 0 )
      delete _edges[0];

    _edges.clear();
  }


  template <typename T>
  inline
  bool Vertex<T>::_insertEdge(Edge<T>* e)	{

    return _edges.insert( e );
  }


  template <typename T>
  inline
  bool Vertex<T>::_removeEdge(Edge<T>* e)	{

    return _edges.remove( e );
  }


  template <typename T>
  inline
  void Vertex<T>::_set( const Point<T,3>& p, const Vector<T,3>& n ) {

    setPos(p);
    setDir(n);
  }


  template <typename T>
  inline
  void Vertex<T>::_set( const Vertex<T>& v ) {

    _set( v.getPosition(), v.getNormal() );
    _const = v._const;
  }


  template <typename T>
  inline
  bool Vertex<T>::boundary() const {

    for( int i = 0; i < _edges.getSize(); i++ )
      if( _edges(i)->boundary() )
        return true;

    return false;
  }


  template <typename T>
  inline
  Arrow<T,3> Vertex<T>::getArrow() {

    Arrow<T,3> r( this->getPos(), this->getDir() );
    return r;
  }


  template <typename T>
  inline
  ArrayT<Edge<T>*>&	Vertex<T>::getEdges() {

    return _edges;
  }


  template <typename T>
  inline
  Point<T,3> Vertex<T>::getNormal() const {

    return this->getDir();
  }


  template <typename T>
  Array<Edge<T>*> Vertex<T>::getOuterEdges() const {

    Array<Triangle<T>*> tris  = getTriangles();
    Array<Edge<T>*>		s_edg = getEdges();
    Array<Edge<T>*>		o_edg( s_edg.getSize() );

    int i, j;
    for( i = 0; i < tris.getSize(); i++ ) {

      Array<Edge<T>*>	ee = tris[i]->getEdges();
      for( j = 0; j < ee.getSize(); j++ )
        if( !s_edg.exist( ee[j] ) )
          o_edg += ee[j];
    }

    return o_edg;
  }


  template <typename T>
  inline
  Point<T,2> Vertex<T>::getParameter() const {

    return Point2D<T>( this->getPos() );
  }


  template <typename T>
  inline
  Point<T,3> Vertex<T>::getPosition() const	{

    return this->getPos();
  }


  template <typename T>
  inline
  T Vertex<T>::getRadius() {

    return _radius;
  }


  template <typename T>
  inline
  T Vertex<T>::getRadiusMax() {

    return _maxradius;
  }


  template <typename T>
  inline
  T Vertex<T>::getRadiusMin() {

    return _minradius;
  }


  template <typename T>
  Array<Triangle<T>*> Vertex<T>::getTriangles() const {

    Array<Triangle<T>*> tris;
    for( int i = 0; i < _edges.getSize(); i++ )
      tris.insert( _edges(i)->getTriangle() );

    return tris;
  }


  template <typename T>
  inline
  bool Vertex<T>::isConst() const {

    return _const;
  }


  template <typename T>
  int  Vertex<T>::isInside( Triangle<T>* t ) const {

    Array<Vertex<T>*> v = t->getVertices();
    Array<Point<T,2> > a;

    for( int i = 0; i < 3; i++ )
      a += v[i]->getParameter();

    Point2D<T> p = this->getPos();

    return p.isInside( a );
  }


  template <typename T>
  inline
  void Vertex<T>::setConst( bool c ) {

    _const = c;
  }


  template <typename T>
  inline
  void Vertex<T>::setRadius( T r ) {

    _radius = r;
  }


  template <typename T>
  inline
  void Vertex<T>::setRadiusMax( T r ) {

    _maxradius = r;
  }


  template <typename T>
  inline
  void Vertex<T>::setRadiusMin( T r ) {

    _minradius = r;
  }


  template <typename T>
  void Vertex<T>::setZ( T z ) {

    setPos( Point3D<T>( this->getPosition()[0], this->getPosition()[1], z ) );
  }


  template <typename T>
  Vertex<T>& Vertex<T>::operator = ( const Vertex<T>& t ) {

    _edges = t._edges;
    _const = t._const;

    _set( t.getPosition(),	t.getNormal() );

    return (*this);
  }


  template <typename T>
  inline
  bool Vertex<T>::operator == (const Vertex<T>& t) const {

    return getParameter() == t.getParameter();
  }


  template <typename T>
  inline
  bool Vertex<T>::operator < (const Vertex<T> &t) const {

    return true;
  }




  //
  //#if defined GM_STREAM
  //
  //
  //template <typename T>
  //inline
  //ostream& Vertex<T>::operator<<(ostream& out, const Vertex<T>& v) {
  //
  //  return v._prOut(out);
  //}
  //
  //
  //template <typename T>
  //inline
  //ostream& Vertex<T>::operator<<(ostream& out, const Vertex<T>* v) {
  //
  //  return v->_prOut(out);
  //}
  //
  //
  //template <typename T>
  //inline
  //istream& Vertex<T>::operator>>(istream& in, Vertex<T>& v)	{
  //
  //  return v._prIn(in);
  //}
  //
  //
  //template <typename T>
  //inline
  //istream& Vertex<T>::operator>>(istream& in, Vertex<T>* v)	{
  //
  //  return v->_prIn(in);
  //}
  //
  //
  //
  //template <typename T>
  //inline
  //void Vertex<T>::print(char prompt[]="Vertex<T>", ostream & out = cout) const {
  //
  //  out << prompt << ": " << (*this) << "\n";
  //}
  //
  //
  //
  //
  //
  //template <typename T>
  //inline
  //ostream& Vertex<T>::_prOut(ostream& out)const
  //{
  //	out << getPosition() << GMlib::GMseparator::Group;
  ////	if(  ) out << dir() << "\n ";
  //
  //	return out;
  //}
  //
  //
  //template <typename T>
  //inline
  //istream& Vertex<T>::_prIn(istream& in)
  //{
  //	Point<T,3> p;
  //	in >> p; setPos(p);
  ////	if(  ) in >> p; setDir(p);
  //	return in;
  //}
  //
  //
  //#endif


}
