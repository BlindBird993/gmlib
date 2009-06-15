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



/*! \file gmTriangle.h
 *
 *  Interface of the Triangle system classes.
 *
 *  \date   2008-10-21
 */



#ifndef __gmTRIANGLE_H__
#define __gmTRIANGLE_H__




#include "gmPoint3D.h"
#include "gmPoint2D.h"
#include "gmArray.h"
#include "gmArrayT.h"
#include "gmArrayLX.h"
#include "gmSArray.h"
#include "gmDMatrix.h"
//#include "gmDPCylinder.h"



namespace GMlib {

  template <typename T>
  class TriangleFacets;

  template <typename T>
  class TriangleSystem;

  template <typename T>
  class Vertex;

  template <typename T>
  class Edge;

  template <typename T>
  class Triangle;

  template <typename T>
  class Tile;

  template <typename T>
  class PWVLine;


  /** \class  TriangleFacets gmTriangle.h <gmTriangle>
   *  \brief  The storage class of the Triangle system
   *
   *  This is the main class. Here you can make, adjust
   *  and handle a triangle based surface. The class is also
   *  the storage class for the vertices, edges and triangles
   */
  template <typename T>
  class  TriangleFacets : public ArrayLX< Vertex<T> >, public DisplayObject {
   public:

    TriangleFacets( int d = 0 );
    TriangleFacets( const ArrayLX<Vertex<T> >& v);
    ~TriangleFacets();



    Point<T,3>                        eval(T x, T y, int deg=1) const;
    Point<T,3>                        eval(const Point2D<T>& p, int deg=1) const;


    T                                 evalZ(const Point2D<T>&, int deg=1); //const
    T                                 evalZ(T x, T y, int deg=1);

    void                              clear(int d=-1);
    void                              computeNormals();
    Box<T,3>					                getBoundBox() const;

    Edge<T>*		                      getEdge(int i)		const;
    int                               getNoVertices()	const;
    int                               getNoEdges()		const;
    int                               getNoTriangles()	const;

    Triangle<T>*	                    getTriangle(int i)	const;
    Vertex<T>*		                    getVertex(int i)	const;

    int                               initRender(); //const;

    void                              insertPwl( PWVLine<T>& );
    bool                              insertVertex( Vertex<T>&, bool c = false );
    bool                              removeVertex( Vertex<T>& v );
    bool                              removeVertexNew( Vertex<T>& v);

    void                              render(); // const;

    bool                              setConstEdge(Vertex<T> v1, Vertex<T> v2);

    void                              triangulateDelaunay();


   protected:
    int	                              _dlist_name;

    void                              localDisplay();
    void                              localSelect();


  private:
    ArrayLX< Edge<T>* >		            _edges;
    ArrayLX< Triangle<T>* >           _triangles;
    Array< Tile<T> *>                 _tmptiles;

    int                               _d;

    DMatrix<ArrayT<Triangle<T>*> >    _tri_order;
    ArrayT<T>                         _u;
    ArrayT<T>                         _v;
    Box<T,3>                          _box;

   Vertex<T>	                        __v;		// dummy because of MS-VC++ compiler
   Edge<T>			                      __e;		// dummy because of MS-VC++ compiler
   Triangle<T> 	                      __t;		// dummy because of MS-VC++ compiler

    bool                              _fillPolygon(Array<Edge<T>*>&);
    bool                              _removeLastVertex();;
    void                              _set(int i);
    int                               _surroundingTriangle(Triangle<T>*&, const Vertex<T>&);// const;


  friend class TriangleSystem<T>;
  private:
    void                              _adjustTriangle( Triangle<T>*, bool wider = false );
    ArrayLX<Edge<T>* >&		            _getEdges();
    Vertex<T>*                        _find( const Point<T,3>& ) const;
    Edge<T>*                          _find( const Point<T,3>&, const Point<T,3>& ) const;
    void                              _insertTriangle( Triangle<T>* );
    void                              _removeTriangle( Triangle<T>* );
    ArrayLX<Triangle<T>* >&	          _triangle();



  #if defined GM_STREAM


//  public:
//    int  getStreamMode() const;
//    void print( string prompt = " TriangleFacets<T>", ostream& out = cout ) const;
//    void setStreamMode( int i = 1 );
//
//    friend ostream& operator<<(ostream& out, const  TriangleFacets<T>& v) {
//      return v._prOut(out);
//    }
//    friend ostream& operator<<(ostream& out, const  TriangleFacets<T>* v) {
//      return v->_prOut(out);
//    }
//    friend istream& operator>>(istream& in,  TriangleFacets<T>& v) {
//      return istream >> v;
//    }
//    friend istream& operator>>(istream& in,  TriangleFacets<T>* v) {
//      return v->_prIn(in);
//    }
//
//
//  private:
//    int _stream_mode;
//
//    ostream& _prOut(ostream& out) const;
//    istream& _prIn(istream& in);

  #endif
  };







  /** \class TriangleSystem gmTriangle.h <gmTriangle>
   *  \brief The TriangleSystem base class
   *
   *  The base class for vertices, edges and triangles
   */
  template <typename T>
  class TriangleSystem {
  public:
    void                        set( TriangleFacets<T>& ts );

  protected:
    void                        adjust( Triangle<T> *t, bool wider = false );
    Vertex<T>*                  find( const Point<T,3>& p ) const;
    Edge<T>*                    find( const Point<T,3>& p1, const Point<T,3>& p2 );

//    int                         getStreamMode();

    void                        insert( Edge<T> *e );
    void                        insert( Triangle<T> *t );
    void                        remove( Edge<T> *e );
    void                        remove( Triangle<T> *t );


  private:
    static TriangleFacets<T>    *_tv;
  };







  /** \class  Vertex
   *  \brief  The Vertex class
   *
   *  The vertex class storing 3D position and a normal
   */
  template <typename T>
  class Vertex : private Arrow<T,3>, public TriangleSystem<T> {
  public:
    Vertex();
    Vertex( const Point<T,2>& v );
    Vertex( const Point<T,3>& p );
    Vertex( const Point<T,3>& p, const Vector<T,3>& n );
    Vertex( const T& x, const T& y, const T& z = T() );
    ~Vertex();


    bool                  boundary() const;
    Arrow<T,3>			      getArrow();
    ArrayT<Edge<T>*>&	    getEdges();
    Point<T,3>			      getNormal() const;
    Array<Edge<T>*>		    getOuterEdges() const;
    Point<T,2>			      getParameter() const;
    Point<T,3>			      getPosition() const;
    T                     getRadius();
    T                     getRadiusMax();
    T                     getRadiusMin();
    Array<Triangle<T>*>   getTriangles() const;

    bool                  isConst()	const;
    int                   isInside( Triangle<T>* ) const;

    void                  setConst( bool c = true );
    void                  setRadius( T r );
    void                  setRadiusMax( T r );
    void                  setRadiusMin( T r );
    void                  setZ( T z );

    Vertex<T>&            operator=(const Vertex<T>& t);
    bool                  operator==(const Vertex<T>& t)	const;
    bool                  operator<(const Vertex<T> &t) const;



  private:

    T                     _radius;
    T                     _maxradius;
    T                     _minradius;
    ArrayT<Edge<T>*>      _edges;

    bool                  _const;


    void                  _set( const Point<T,3>& p, const Vector<T,3>& n );


  friend class Edge<T>;
  friend class TriangleFacets<T>;
  private:

    void                  _computeNormal();
    void                  _deleteEdges();
    bool                  _insertEdge(Edge<T>* e);
    bool                  _removeEdge(Edge<T>* e);

    void                  _set( const Vertex<T>& v );


//  #if defined GM_STREAM
//
//
//  public:
//    friend ostream&       operator<<(ostream& out, const Vertex<T>& v) { return v._prOut(out); }
//    friend ostream&       operator<<(ostream& out, const Vertex<T>* v) { return v->_prOut(out); }
//    friend istream&       operator>>(istream& in, Vertex<T>& v)	{ return v._prIn(in); }
//    friend istream&       operator>>(istream& in, Vertex<T>* v)	{ return v->_prIn(in); }
//
//    void                  print(char prompt[]="Vertex<T>", ostream & out = cout) const
//    { out << prompt << ": " << (*this) << "\n"; }
//
//  private:
//    ostream&              _prOut(ostream& out)const;
//    istream&              _prIn(istream& in);
//
//  #endif

  };



  /** \class Edge gmTriangle.h <gmTriangle>
   *  \brief The Edge class
   *
   *  The edge class defined by 2 vertices, can be fixed
   */
  template <typename T>
  class Edge : public TriangleSystem<T> {
  public:
    Edge();
    Edge(Vertex<T>& s, Vertex<T>& e);
    Edge(const Edge<T>& e);
    ~Edge();

    bool                  boundary() const;

    Vertex<T>*	          getCommonVertex(const Edge<T>&) const;
    Vertex<T>*	          getFirstVertex() const;

    Point<T,3>	          getCenterPos();
    Point<T,2>	          getCenterPos2D();
    T                     getLength();
    T                     getLength2D();
    Array<Triangle<T>*>   getTriangle();
    Vector<T,3>	          getVector();
    Vector2D<T>	          getVector2D();
    Vertex<T>*	          getLastVertex() const;

    Vertex<T>*	          getOtherVertex(const Vertex<T>&) const;


    void                  setConst(bool c = true);


    bool                  operator <  (const Edge<T>& v) const;
    bool                  operator >  (const Edge<T>& v) const;
    bool                  operator <= (const Edge<T>& v) const;
    bool                  operator >= (const Edge<T>& v) const;


  private:
    Vertex<T>             *_vertex[2];
    Triangle<T>           *_triangle[2];
    bool	                _const;


    bool                  _swap();
    void                  _upv();


  friend class Triangle<T>;
  friend class TriangleFacets<T>;
  private:

    Edge<T>*              _getNext();
    bool                  _hasPoints(const Point<T,3>& , const Point<T,3>&) const;
    bool                  _isFirst(Vertex<T>* v);
    bool                  _isLast(Vertex<T>* v);

    void                  _okDelaunay();

    Triangle<T>*          _getOther(Triangle<T>*);
    bool                  _removeTriangle(Triangle<T>*);
    void                  _reverse();
    void                  _setTriangle(Triangle<T>* t1,Triangle<T>* t2);
    bool                  _split( Vertex<T>& p );
    bool                  _swapTriangle(Triangle<T>* ot, Triangle<T>* nt);
    bool                  _swapVertex(Vertex<T>& is_v,Vertex<T>& new_v);



//  #if defined GM_STREAM
//  private:
//    ostream& _prOut(ostream& out)const;
//    istream& _prIn(istream& in);
//  public:
//
//    friend ostream& operator<<(ostream& out, const Edge<T>& v);
//    friend ostream& operator<<(ostream& out, const Edge<T>* v);
//    friend istream& operator>>(istream& in, Edge<T>& v);
//    friend istream& operator>>(istream& in, Edge<T>* v);
//
//    void print(char prompt[]="Edge<T>", ostream & out = cout) const;
//  #endif
  };









  /** \class  Triangle gmTriangle.h <gmTriangle>
   *  \brief  The Trangle class
   *
   *  The triangle class defined by 3 edges
   */
  template <typename T>
  class Triangle: public TriangleSystem<T> {
  public:

    Triangle();
    Triangle( Edge<T>* e1, Edge<T>* e2, Edge<T>* e3 );
    Triangle( const Triangle<T>& t );
    ~Triangle();


    T					              getAngleLargest();
    T					              getAngleSmallest();
    T					              getArea();
    T					              getArea2D();

    Point<T,3>			        getCenterPos();
    Point<T,2>			        getCenterPos2D();
    T					              getCircum();
    T					              getCircum2D();

    Array<Edge<T>*>		      getEdges() const;
    Vector<T,3>		          getNormal() const;
    Array<Vertex<T>*>	      getVertices() const;
    int	                    isAround(const Vertex<T>& v) const;



  private:
    Edge<T>                 *_edge[3];
    Box<unsigned char,2>    _box;



  friend class Edge<T>;
  friend class TriangleFacets<T>;
  private:

    T                       _evalZ( const Point2D<T>& p, int deg = 1 ) const;
    Box<unsigned char,2>&   _getBox();
    void                    _render();//  const;
    bool                    _reverse( Edge<T>* edge );
    void                    _setEdges( Edge<T>* e1, Edge<T>* e2, Edge<T>* e3 );
    bool                    _split( Vertex<T>& p );
    void                    _updateBox( ArrayT<T>& u, ArrayT<T>& v, int d );



//  #if defined GM_STREAM
//  public:
//    friend ostream& operator << ( ostream& out, const Triangle<T>& v );
//    friend ostream& operator << ( ostream& out, const Triangle<T>* v );
//    friend istream& operator >> ( istream& in, Triangle<T>& v );
//    friend istream& operator >> ( istream& in, Triangle<T>* v );
//
//    void print( char prompt[] = "Triangle<T>", ostream & out = cout ) const;
//
//  private:
//    ostream& _prOut( ostream& out )const;
//    istream& _prIn( istream& in );
//  #endif
  };







  /** \class  Tile gmTriangle.h <gmTriangle>
   *  \brief  The Tile class
   *
   *  The tile class defined by vertex, and dual of its triangles
   */
  template <typename T>
  class Tile : public DisplayObject {
  public:
    Tile();
    Tile( Vertex<T>* v, Box<T,3> domain );

    T                     getBigR();
    string                getIdentity() const;
    T                     getSmallR();
    void                  render();

  protected:
    void                  localDisplay();
    void                  localSelect();

  private:
    Array< Point<T,2> >   _vorpts;
    Vertex<T>             *_vertex;
    T                     _inscribed;
    T                     _circumscribed;

    Point2D<T>            _voronoi( const Point2D<T>& v1, const Point2D<T>& v2, const Point2D<T>& v3 );
  };






  /** \class  PWVLine gmTriangle.h <gmTriangle>
   *  \brief  The PWVLine class
   *
   *  This is a picewice linear curve based on vertices. You can also use the normal
   */
  template <typename T>
  class PWVLine : public Array< Vertex<T> > {
  public:
    PWVLine( int d = 0);
    PWVLine( const Array<Vertex<T> >& v );

    Vertex<T> interpolate( int i, double t ) const;
  };


} // end namespace




// Include TriangleFacets class function implementations
#include "gmTriangle_TriangleFacets.c"

// Include TriangleSystem class function implementations
#include "gmTriangle_TriangleSystem.c"

// Include Vertex class function implementations
#include "gmTriangle_Vertex.c"

// Include Edge class function implementations
#include "gmTriangle_Edge.c"

// Include Triangle class function implementations
#include "gmTriangle_Triangle.c"

// Include Tile class function implementations
#include "gmTriangle_Tile.c"

// Include PWVLine class function implementations
#include "gmTriangle_PWVLine.c"





#endif // __gmTRIANGLE_H__


