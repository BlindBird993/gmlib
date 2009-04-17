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



/*! \file gmTriangle_Edge.c
 *  \brief Edge class function implementations
 *
 *  \date   2008-10-22
 */


namespace GMlib {



  template <typename T>
  inline
  Edge<T>::Edge() {

    _vertex[0] = _vertex[1] = NULL;
    _triangle[0] = _triangle[1] = NULL;
    _const = false;
  }


  template <typename T>
  inline
  Edge<T>::Edge( Vertex<T>& s, Vertex<T>& e ) : _triangle() {

    _vertex[0] = &s;
    _vertex[1] = &e;
    _const = false;
    _upv();
  }


  template <typename T>
  inline
  Edge<T>::Edge( const Edge<T>& e ) : _vertex( e._vertex ), _triangle( e._triangle ) {

    _const = e._const;
    _upv();
  }


  template <typename T>
  Edge<T>::~Edge() {

    if( _triangle[0] != NULL )  delete _triangle[0];
    if( _triangle[1] != NULL )	delete _triangle[1];
    if( _vertex[0] != NULL )  _vertex[0]->_removeEdge(this);
    if( _vertex[1] != NULL )  _vertex[1]->_removeEdge(this);

    this->remove(this);
  }


  template <typename T>
  Edge<T>* Edge<T>::_getNext() {

    ArrayT< Edge<T>* > edg = _vertex[1]->getEdges();
    edg.remove(this);

    if( boundary() )
      for( int i = 0; i < edg.getSize(); i++ )
        if( edg[i]->boundary() )
          if( _vertex[1] == getCommonVertex(*(edg[i])) )
            return edg[i];

    return NULL;
  }


  template <typename T>
  bool Edge<T>::_hasPoints( const Point<T,3>& p1, const Point<T,3>& p2 ) const {

    Vertex<T> * v1 = find(p1);
    ArrayT<Edge<T>*> edges = v1->getEdges();

    for( int i = 0; i < edges.getSize(); i++ )
      if( edges[i]->getOtherVertex(v1)->getPos() == p2 )
        return true;

    return false;
  /*
    Vertex<T> * v2 = find(p2);
    if(_vertex[0] == v1 && _vertex[1] == v2)		return true;
    else if(_vertex[1] == v1 && _vertex[0] == v2)	return true;
    else											return false;
  */
  }


  template <typename T>
  inline
  bool Edge<T>::_isFirst( Vertex<T>* v ) {

    return v == _vertex[0];
  }


  template <typename T>
  inline
  bool Edge<T>::_isLast( Vertex<T>* v ) {

    return v == _vertex[1];
  }


  template <typename T>
  void Edge<T>::_okDelaunay() {

    if( _vertex[0]->isConst() && _vertex[1]->isConst() )
      setConst();

    if( _const || _triangle[0] == NULL || _triangle[1] == NULL )
      return;

    Array<Vertex<T>*> a = _triangle[0]->getVertices();

    a.insert( _triangle[1]->getVertices() );

    a.remove( _vertex[0] );
    a.remove( _vertex[1] );

    Point2D<T> pt = a[0]->getParameter();

    if(
      pt.isInsideCircle(
        _vertex[0]->getParameter(),
        a[1]->getParameter(),
        _vertex[1]->getParameter()
      ) == 1
    )	this->_swap();
  }


  template <typename T>
  Triangle<T>* Edge<T>::_getOther( Triangle<T>* t ) {

    if( t == _triangle[0] )
      return _triangle[1];
    else if( t == _triangle[1] )
      return _triangle[0];
    else
      return NULL;
  }


  template <typename T>
  bool Edge<T>::_removeTriangle( Triangle<T>* t ) {

    if( _triangle[0] == t )
      _triangle[0] = NULL;
    else if( _triangle[1] == t )
      _triangle[1] = NULL;
    else
      return false;

    return true;
  }


  template <typename T>
  inline
  void Edge<T>::_reverse() {

    Vertex<T> *v = _vertex[0];
    _vertex[0] = _vertex[1];
    _vertex[1] = v;
  }


  template <typename T>
  inline
  void Edge<T>::_setTriangle( Triangle<T>* t1, Triangle<T>* t2 ) {

    _triangle[0] = t1;
    _triangle[1] = t2;
  }


  template <typename T>
  bool Edge<T>::_split( Vertex<T>& p ) {

    Vertex<T>* v = NULL;
    Edge<T>*   e = NULL;
    Triangle<T> *t1 = NULL, *t2 = NULL;

    if( _triangle[0] != NULL )
      _triangle[0]->_reverse(this);
    if( _triangle[1] != NULL )
      _triangle[1]->_reverse(this);

//    Array<Edge<T>*> edg1 = _triangle[0] == NULL ? NULL : _triangle[0]->getEdges();
//    Array<Edge<T>*> edg2 = _triangle[1] == NULL ? NULL : _triangle[1]->getEdges();

      Array<Edge<T>*> edg1;
      Array<Edge<T>*> edg2;
      if( _triangle[0] != NULL ) edg1 = _triangle[0]->getEdges();
      if( _triangle[1] != NULL ) edg2 = _triangle[1]->getEdges();

    if( _triangle[0] != NULL ) {
      // swap triangles, _triang[0] should be on left
      if(_vertex[0] == getCommonVertex(*(edg1[1]))) {

        Triangle<T>* st = _triangle[0];
        _triangle[0] = _triangle[1];
        _triangle[1] = st;
        if( _triangle[0] != NULL ) edg1 = _triangle[0]->getEdges();
        if( _triangle[1] != NULL ) edg2 = _triangle[1]->getEdges();
      }
    }
    else {
      // swap triangles, _triang[0] should be on left
      if(_vertex[0] != getCommonVertex(*(edg2[1]))) {

        Triangle<T>* st = _triangle[0];
        _triangle[0] = _triangle[1];
        _triangle[1] = st;
        if( _triangle[0] != NULL ) edg1 = _triangle[0]->getEdges();
        if( _triangle[1] != NULL ) edg2 = _triangle[1]->getEdges();
      }
    }


    // Splitt edge in two
    Edge<T>* e1 = this;
    Edge<T>* e2 = new Edge<T>(*(_vertex[1]),p);
    _vertex[1]->_removeEdge(this);
    _vertex[1] = &p;
    p._insertEdge(this);
    e2->setConst(_const);
    insert(e2);

    // Splitt triangle 0
    if( _triangle[0] != NULL ) {

      v = edg1[1]->getCommonVertex(*(edg1[2]));
      e = new Edge<T>(p,*v);

      t1 = new Triangle<T>( e2, edg1[1], e );
      _triangle[0]->_setEdges( e1, e, edg1[2] );
      e->_setTriangle( t1, _triangle[0] );
      edg1[1]->_swapTriangle( _triangle[0], t1 );

      insert(e);
      insert(t1);

      this->adjust( _triangle[0] );
    }

    // Splitt triangle 1
    if( _triangle[1] != NULL ) {

      v = edg2[1]->getCommonVertex(*(edg2[2]));
      e = new Edge<T>(p,*v);

      t2 = new Triangle<T>(e2,e,edg2[2]);
      _triangle[1]->_setEdges(e1,edg2[1],e);
      e->_setTriangle(t2,_triangle[1]);

      e2->_setTriangle(t1,t2);
      edg2[2]->_swapTriangle(_triangle[1], t2);

      insert(e);
      insert(t2);

      adjust(_triangle[1]);
    }

    if( _triangle[0] != NULL ) {

      edg1[1]->_okDelaunay();
      edg1[2]->_okDelaunay();
    }

    if( _triangle[1] != NULL ) {

      edg2[1]->_okDelaunay();
      edg2[2]->_okDelaunay();
    }

    return true;
  }


  template <typename T>
  bool Edge<T>::_swap() {

    if( _const || _triangle[0] == NULL || _triangle[1] == NULL )
      return false;

    _triangle[0]->_reverse(this);
    _triangle[1]->_reverse(this);

    Array<Edge<T>*> edg1 = _triangle[0]->getEdges();
    Array<Edge<T>*> edg2 = _triangle[1]->getEdges();

    _vertex[0]->_removeEdge(this);
    _vertex[1]->_removeEdge(this);

    _vertex[0] = edg1[1]->getCommonVertex(*(edg1[2]));
    _vertex[1] = edg2[1]->getCommonVertex(*(edg2[2]));

    _vertex[0]->_insertEdge(this);
    _vertex[1]->_insertEdge(this);

    _triangle[0]->_setEdges( this, edg1[2], edg2[1] );
    _triangle[1]->_setEdges( this, edg2[2], edg1[1] );

    edg1[1]->_setTriangle( edg1[1]->_getOther( _triangle[0] ), _triangle[1] );
    edg2[1]->_setTriangle( edg2[1]->_getOther( _triangle[1] ), _triangle[0] );

    adjust( _triangle[0], true );
    adjust( _triangle[1], true );

    edg1[1]->_okDelaunay();
    edg1[2]->_okDelaunay();
    edg2[1]->_okDelaunay();
    edg2[2]->_okDelaunay();

    return true;
  }


  template <typename T>
  bool Edge<T>::_swapTriangle( Triangle<T>* ot, Triangle<T>* nt ) {

    if( ot == _triangle[0] ) {

      _triangle[0] = nt;
      return true;
    }
    else if( ot == _triangle[1] ) {

      _triangle[1] = nt;
      return true;
    }
    else
      return false;
  }


  template <typename T>
  bool Edge<T>::_swapVertex( Vertex<T>& match_vtx, Vertex<T>& rep_vtx ) {

    bool ret = false;

    if (_vertex[0] == &match_vtx) {

      _vertex[0] = &rep_vtx;
      ret = true;
    }

    if (_vertex[1] == &match_vtx) {

      _vertex[1] = &rep_vtx;
      ret = true;
    }

    if( _vertex[0]->isConst() && _vertex[1]->isConst() )
      _const = true;

    return ret;
  }


  template <typename T>
  inline
  void Edge<T>::_upv() {

    _vertex[0]->_insertEdge( this );
    _vertex[1]->_insertEdge(this);

    if( _vertex[0]->isConst() && _vertex[1]->isConst() )
      _const = true;
  }


  template <typename T>
  inline
  bool Edge<T>::boundary() const {

    return _triangle[0] == NULL || _triangle[1] == NULL;
  }


  template <typename T>
  Vertex<T>* Edge<T>::getCommonVertex( const Edge<T>& e ) const {

    if( _vertex[0] == e._vertex[0] || _vertex[0] == e._vertex[1] )
      return _vertex[0];
    else if( _vertex[1] == e._vertex[0] || _vertex[1] == e._vertex[1] )
      return _vertex[1];

    return NULL;
  }


  template <typename T>
  inline
  Vertex<T>* Edge<T>::getFirstVertex() const {

    return _vertex[0];
  }


  template <typename T>
  inline
  Point<T,3> Edge<T>::getCenterPos() {

    return (_vertex[1]->getPosition() + _vertex[0]->getPosition()) * 0.5;
  }


  template <typename T>
  inline
  Point<T,2> Edge<T>::getCenterPos2D() {

    return ( _vertex[1]->getParameter() + _vertex[0]->getParameter() ) * 0.5;
  }


  template <typename T>
  inline
  T Edge<T>::getLength() {

    return getVector().getLength();
  }


  template <typename T>
  inline
  T Edge<T>::getLength2D()	{

    return getVector2D().getLength();
  }


  template <typename T>
  Array<Triangle<T>*> Edge<T>::getTriangle() {

    Array<Triangle<T>*> arr;
    if( _triangle[0] != NULL ) arr.insert( _triangle[0] );
    if( _triangle[1] != NULL ) arr.insert( _triangle[1] );
    return arr;
  }


  template <typename T>
  inline
  Vector<T,3> Edge<T>::getVector() {

    return _vertex[1]->getPosition() - _vertex[0]->getPosition();
  }


  template <typename T>
  inline
  Vector2D<T> Edge<T>::getVector2D(){

    return _vertex[1]->getParameter() - _vertex[0]->getParameter();
  }


  template <typename T>
  inline
  Vertex<T>* Edge<T>::getLastVertex() const {

    return _vertex[1];
  }


  template <typename T>
  Vertex<T>* Edge<T>::getOtherVertex( const Vertex<T>& v ) const {

    if( (*_vertex[0]) == v )
      return _vertex[1];
    else if( (*_vertex[1]) == v )
      return _vertex[0];
    else
      return NULL;
  }


  template <typename T>
  inline
  void Edge<T>::setConst( bool c ) {

    _const = c;
  }


  template <typename T>
  inline
  bool Edge<T>::operator <  (const Edge<T>& v) const {

    Vertex<T>* c = (*this).commonVertex(v);
    Vector<T,3> a = (*this).otherVertex((*c))->getPosition()-c->getPosition();
    Vector<T,3> b = v.otherVertex((*c))->getPosition()-c->getPosition();

    if( a*b > 0 )
      return true;
    else
      return false;
  }


  template <typename T>
  inline
  bool Edge<T>::operator >  ( const Edge<T>& v ) const {

    return !((*this) < v);
  }


  template <typename T>
  inline
  bool Edge<T>::operator <= ( const Edge<T>& v ) const {

    return !((*this) > v);
  }


  template <typename T>
  inline
  bool Edge<T>::operator >= ( const Edge<T>& v ) const {

    return !((*this) < v);
  }







  //#if defined GM_STREAM
  //
  //
  //
  //template <template T>
  //inline
  //ostream& Edge<T>::_prOut(ostream& out)const
  //{
  //	out << (*_vertex[0]) << " " << (*_vertex[1])
  //		<< " " << _const << "\n ";
  //
  //	return out;
  //}
  //
  //template <template T>
  //inline
  //istream& Edge<T>::_prIn(istream& in)
  //{
  //	Point<T,3> p1, p2;
  //	in >> p1 >> p2 >> _const;
  //	_vertex[0] = find(p1);
  //	_vertex[1] = find(p2);
  //
  //	return in;
  //}
  //
  //
  //template <typename T>
  //inline
  //ostream& Edge<T>::operator<<( ostream& out, const Edge<T>& v ) {
  //
  //  return v._prOut(out);
  //}
  //
  //
  //template <typename T>
  //inline
  //ostream& Edge<T>::operator<<( ostream& out, const Edge<T>* v ) {
  //
  //  return v->_prOut(out);
  //}
  //
  //
  //template <typename T>
  //inline
  //istream& Edge<T>::operator >> ( istream& in, Edge<T>& v )	{
  //
  //  return v._prIn(in);
  //}
  //
  //
  //template <typename T>
  //inline
  //istream& Edge<T>::operator>>( istream& in, Edge<T>* v ) {
  //
  //  return v->_prIn(in);
  //}
  //
  //
  //template <typename T>
  //inline
  //void print(char prompt[]="Edge<T>", ostream & out = cout) const {
  //
  //  out << prompt << ": " << (*this) << "\n";
  //}
  //
  //
  //
  //#endif


}

