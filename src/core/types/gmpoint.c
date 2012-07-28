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



/*! \file gmpoint.c
 *  \brief Implementations for the Point class
 *
 *  Implementations for the Point class
 */


#include <cstring>

namespace GMlib {



  template <typename T, int n>
  Arrow<T, n>* Point<T, n>::_arrow = new Arrow<T, n>();

  template <typename T, int n>
  int Point<T, n>::_sortType = 1;



  /*! Point::Point()
   *  \brief  Default Constructor
   *
   *  Default constructor
   *  Takes no paramters, and will not initalize any values.
   *  This has been done intentionaly, to speedup creation of matrices.
   *  If point should be used by itself, use one of the other constructors.
   *  \see Point( T t )
   *  \see Point( const T *t )
   */
  template <typename T, int n>
  inline
  Point<T, n>::Point() {
    // SHOULD NOT INITIALIZE ANYTHING
    // Intentinonal speed enhancement.
  }


  /*! Point::Point( const Point<T, n> &p )
   *  \brief  Default Copy Constructor
   *
   *  Default copy constructor
   *
   *  \param p The Point object to be copied.
   */
  template <typename T, int n>
  inline
  Point<T, n>::Point( const Point<T, n> &p ) {
    _cpy(p);
  }


  /*! Point::Point( T t )
   *  \brief  Constructuer taking an init value
   *
   *  Initializing each component of the point to the init value
   *
   * \param t An initial value
   */
  template <typename T, int n>
  inline
  Point<T, n>::Point( T t ) {
    _cpy(t);
  }


  /*! Point::Point( const T *t )
   *  \brief  Constructuer taking an array of n T values.
   *
   *  This constructor has been created to make the point class
   *  compatible with other librarys and generel datasets.
   *  The constructor presupposes that the input array has n T values.
   *
   * \param t A const T pointer of n values.
   */
  template <typename T, int n>
  inline
  Point<T, n>::Point( const T *t ) {
    _cpy(t);
  }


  /*! Angle Point<T, n>::getAngle( Point<T, n> v ) const
   *  \brief Returns the angle between two points
   *
   *  Returns the angle between two vectors
   *  Has been moved down into the point class from the vector class,
   *  for convenience.
   *
   *  \param v The point to which the angle should be calculated.
   *  \return The angle between this point and the given point.
   */
  template <typename T, int n>
  Angle Point<T, n>::getAngle( Point<T, n> v ) const {

     Point<T, n> u = (*this);
     u /= u.getLength();
     v /= v.getLength();
     double ang = u*v;
     if (ang > 1.0) ang = 1.0;
     else if (ang < -1.0) ang = -1.0;
     ang = acos(ang);
     if (n ==2)
     {
        double orient = u[0]*v[1]-u[1]*v[0];
        if (orient >= 0.0) 	return Angle(ang);
        else 		            return Angle(2*M_PI - ang);
     }
     else                     return Angle(ang);
  }


  /*! T Point<T, n>::getLength() const
   *  \brief Returns the length of the point (vector)
   *
   *  Returns the length of the point (vector)
   *  Has been moved down into the point class from the vector class for convenience.
   *
   *  \return The length of the point (vector)
   */
  template <typename T, int n>
  inline
  T Point<T, n>::getLength() const {
    return T( sqrt( double( (*this) * (*this) ) ) );
  }


  /*! int Point<T, n>::getMaxIndex() const
   *  \brief Returns the index of the first point element with the max value.
   *
   *  Returns the index of the first point element with the max value.
   *  Dependent on the > (greater then) operator
   *
   *  \return The index of the first max value
   */
  template <typename T, int n>
  inline
  int Point<T, n>::getMaxIndex() const {
    // return GM_Static_<T,n>::maxIndex(pt);
    int j=0;
    for(int i=1; i<n; i++)
      if( _pt[i] > _pt[j] ) j = i;
    return j;
  }


  /*! int Point<T, n>::getMaxAbsIndex() const
   *  \brief Returns the index of the first point element with the max absolute value.
   *
   *  Returns the index of the first point element with the max absolute value.
   *  Dependent on the > (greater then) operator.
   *
   *  \return The index of the first max absolute value.
   */
  template <typename T, int n>
  inline
  int Point<T, n>::getMaxAbsIndex() const {
    // return GM_Static_<T,n>::maxIndex(pt);
    int j=0;
    for(int i=1; i<n; i++)
      if( std::fabs( _pt[i] ) > std::fabs( _pt[j] ) ) j = i;
    return j;
  }


  /*! T* Point<T, n>::getPtr() const
   *  \brief Returns a pointer to the point element dataset.
   *
   *  Returns a pointer to the point element dataset.
   *
   *  \return The pointer to the point element dataset.
   */
  template <typename T, int n>
  inline
  T* Point<T, n>::getPtr() const {
    return (T*)this;
  }


  /*! void Point<T, n>::setTestType( int t, const Point<T, n> &p, const Vector<T, n> &v )
   *  \brief Set how a point should be sorted in accordance to other points.
   *
   *  Set how a point should be sorted in accordance to other points.
   *  When set to type 1 the point will be sorted as closest to a point.
   *  When set to type 2 the point will be sorted as closes to a directional vector.
   *  When set to type 3 the point will be sorted as closes to a radar vector rotating 360 degreas from the offset point and vector.
   *
   *  \param[in] t The sorting type/method
   *  \param[in] p The point to sort after
   *  \param[in] v A complementary directional vector, when sorting according to degreas (radar)
   */
  template <typename T, int n>
  inline
  void Point<T, n>::setTestType( int t, const Point<T, n> &p, const Vector<T, n> &v ) {

    _sortType = t;
    if (t==1)
      _arrow->setPos(p);
    else if (t==2)
      _arrow->setDir(p);
    else if (t==3){
      _arrow->setPos(p);
      _arrow->setDir(v);
    }
    else {
      // Use a debug error message
    }
  }


  template <typename T, int n>
  inline
  Point<T, n>& Point<T, n>::operator = ( const T t ) {
    _cpy(t);
    return (*this);
  }


  template <typename T, int n>
  inline
  Point<T, n>& Point<T, n>::operator = ( const T *t ) {
    _cpy(t);
    return (*this);
  }


  template <typename T, int n>
  inline
  Point<T, n>& Point<T, n>::operator = ( const Point<T, n>& p) {
    _cpy(p);
    return (*this);
  }


  template <typename T, int n>
  inline
  Point<T, n>& Point<T, n>::operator += ( const Point<T, n>& p ) {
    GM_Static_<T, n>::peq( getPtr(), p.getPtr() );
    return *this;
  }


  template <typename T, int n>
  inline
  Point<T, n>& Point<T, n>::operator -= ( const Point<T, n>& p ) {
    GM_Static_<T, n>::meq( getPtr(), p.getPtr() );
    return *this;
  }


  template <typename T, int n>
  inline
  Point<T, n>& Point<T, n>::operator - () const {
    static Point<T, n> r;
    GM_Static_<T, n>::eqm( r.getPtr(), getPtr());
    return r;
  }


  template <typename T, int n>
  inline
  Point<T, n>& Point<T, n>::operator + ( const Point<T, n> &p ) const {
    static Point<T, n> r;
    GM_Static_<T, n>::eq_p( r.getPtr(), getPtr(), p.getPtr());
    return r;
  }


  template <typename T, int n>
  inline
  Point<T, n>& Point<T, n>::operator - ( const Point<T, n> &p ) const {
    static Point<T, n> r;
    GM_Static_<T, n>::eq_m( r.getPtr(), getPtr(), p.getPtr() );
    return r;
  }

  // Inner product
  template <typename T, int n>
  inline
  T Point<T, n>::operator * ( const Point<T, n> &p ) const {
    return GM_Static_<T, n>::dpr( getPtr(), p.getPtr() );
  }

  template <typename T, int n>
  inline
  T& Point<T, n>::operator [] ( int i) {
    return _pt[i];   //return given element.
  }

  template <typename T, int n>
  inline
  T const& Point<T, n>::operator () ( int i) const {
    return _pt[i]; //return copy.
  }


  template <typename T, int n>
  inline
  Point<T, n>& Point<T, n>::operator *= ( double d ) {
    GM_Static_<T, n>::sc( getPtr(), d );
    return *this;
  }


  template <typename T, int n>
  inline
  Point<T, n> Point<T, n>::operator * ( double d ) const {
  //  static Point<T, n> r;
    Point<T, n> r;
    GM_Static_<T, n>::sc_r( r.getPtr(), getPtr(), d);
    return r;
  }

  template <typename T, int n>
  inline
  Point<T, n>& Point<T, n>::operator %= ( const Point<T, n> &p ) {
    GM_Static_<T, n>::xeq( getPtr(), p.getPtr());
    return *this;
  }

  template <typename T, int n>
  inline
  Point<T, n>& Point<T, n>::operator % ( const Point<T, n> &p ) const {
    static Point<T, n> r;
    GM_Static_<T, n>::eq_x( r.getPtr(), getPtr(), p.getPtr());
    return r;
  }

  template <typename T, int n>
  inline
  Point<T, n>& Point<T, n>::operator /= ( double d ) {
    d = 1/d;
    return (*this)*=d;
  }

  template <typename T, int n>
  inline
  Point<T, n> Point<T, n>::operator /  ( double d ) const {
    d = 1/d;
    return (*this)*d;
  }



  template <typename T, int n>
  inline
  bool Point<T, n>::operator == ( const Point<T, n> &p ) const {
    Point<T,n> d=(*this)-p;
    return bool((d*d)<POS_TOLERANCE);
  }


  template <typename T, int n>
  inline
  bool Point<T, n>::operator != ( const Point<T, n> &pt ) const {
    return !((*this) == pt);
  }

  template <typename T, int n>
  inline
  bool Point<T, n>::operator <  ( const Point<T, n> &v ) const {
     switch(_sortType){
     case 1: return bool((_arrow->getPos()-(*this)).getLength() < (_arrow->getPos()-v).getLength());
     case 2: return bool((_arrow->getDir()*(*this)) <  (_arrow->getDir()*v));
     case 3: return bool(_arrow->getDir().getAngle((*this)-_arrow->getPos()) < _arrow->getDir().getAngle(v-_arrow->getPos()));
     default: return false;// Use a debug error-message
     }
  }

  template <typename T, int n>
  inline
  bool Point<T, n>::operator >  ( const Point<T, n> &v ) const {
     switch(_sortType){
     case 1: return bool((_arrow->getPos()-(*this)).getLength() > (_arrow->getPos()-v).getLength());
     case 2: return bool((_arrow->getDir()*(*this)) >  (_arrow->getDir()*v));
     case 3: return bool(_arrow->getDir().getAngle((*this)-_arrow->getPos()) > _arrow->getDir().getAngle(v-_arrow->getPos()));
     default: return false;// Use a debug error-message
     }
  }

  template <typename T, int n>
  inline
  bool Point<T, n>::operator <= ( const Point<T, n> &v ) const {
    return !((*this) > v);
  }

  template <typename T, int n>
  inline
  bool Point<T, n>::operator >= ( const Point<T, n> &v ) const {
    return !((*this) < v);
  }


  template <typename T, int n>
  template <typename G, int m>
  inline
  Point<T, n>::operator Point<G,m>& () const {
    static Point<G,m> v;
    GM_Static1_<G,T,(n<m?n:m)>::eq( v.getPtr(), getPtr());
    return v;
  }


  /*! Point<float,n>& Point<T, n>::toFloat() const
   *  \brief Returns a point where all point elements is casted to float type
   *
   *  Returns a point where all point elements is casted to float type
   *
   *  \return A point where all point elemets is of float type
   */
  template <typename T, int n>
  inline
  Point<float,n>& Point<T, n>::toFloat() const {
    static Point<float,n> v;
    GM_Static1_<float,T,n>::eq(v.getPtr(), getPtr());
    return v;
  }


  /*! Point<double,n> Point<T, n>::toDouble() const
   *  \brief Returns a point where all point elements is casted to double type
   *
   *  Returns a point where all point elements is casted to double type
   *
   *  \return A point where all point elemets is of double type
   */
  template <typename T, int n>
  inline
  Point<double,n> Point<T, n>::toDouble() const {
    static Point<double,n> v;
    GM_Static1_<double,T,n>::eq( v.getPtr(), getPtr());
    return v;
  }


  /*! void Point<T, n>::_cpy( const Point<T, n> &v )
   *  \brief Copys a point element data set.
   *
   *  Copys a point element data set.
   *  Takes a point-object as parameter,
   *  and uses memcpy to copy the data raw from the src point to the dest point (this).
   *
   *  \param[in] v The src Point, from where the data is collected.
   */
  template <typename T, int n>
  inline
  void Point<T, n>::_cpy( const Point<T, n> &v ) {
    std::memcpy( _pt, v._pt, sizeof( Point<T,n> ) );
  }


  /*! void Point<T, n>::_cpy( const T p[n] )
   *  \brief Copys a point element data set.
   *
   *  Copys a point element data set.
   *  Takes a point element array
   *  and uses memcpy to copy the data raw from the src point to the dest point (this).
   *
   *  \param[in] p The src point element data set, from where the data is collected.
   */
  template <typename T, int n>
  inline
  void Point<T, n>::_cpy( const T p[n] ) {
    memcpy( _pt, p, sizeof( Point<T,n> ) );
  }


  /*! void Point<T, n>::_cpy( const T &d )
   *  \brief Copys a point element data set.
   *
   *  Copys a point element data set.
   *  Takes a T value, and copys the value into every point element in the data set of the point object.
   *
   *  \param[in] d The value to be set in every point element.
   */
  template <typename T, int n>
  inline
  void Point<T, n>::_cpy( const T &d ) {
    GM_Static_<T,n>::eq( getPtr(), d );
  }

 /*! Vector<T, n>::Vector() : Point<T, n>()
   *  \brief Default constructor, does not initalize the vector
   *
   *  Default constructor, does not initalize the vector.
   *  If the default constructor should be used, the vector needs to be initalized at a later point.
   */
  template <typename T, int n>
  inline
  Vector<T, n>::Vector() : Point<T, n>() {}

  /*! Vector<T, n>::Vector( T d ) : Point<T, n>(d)
   *  \brief Constructor taking a value t of T
   *
   *  Constructor taking a value t of T.
   *  The vector will be initialzied with t in each axis.
   *
   *  \param[in] t The initialization value.
   */
  template <typename T, int n>
  inline
  Vector<T, n>::Vector( T t ) : Point<T, n>(t) {}

  /*! Vector<T, n>::Vector( const T *t ) : Point<T, n>(t)
   *  \brief  Constructuer taking an array of n T values.
   *
   *  This constructor has been created to make the vector class
   *  compatible with other librarys and general datasets.
   *  The constructor presupposes that the input array has n T values.
   *
   * \param[in] t A const T pointer of n values.
   */
  template <typename T, int n>
  inline
  Vector<T, n>::Vector( const T *t ) : Point<T, n>(t) {}

  /*! Vector<T, n>::Vector( const Point<T, n> &p ) : Point<T, n>(p)
   *  \brief Default copy constructor
   *
   *  Default copy constructor.
   *  Taking a Point or Vector as parameter.
   *
   *  \param[in] p Point/Vector to copy from.
   */
  template <typename T, int n>
  inline
  Vector<T, n>::Vector( const Point<T, n> &p ) : Point<T, n>(p) {}

  /*! Point<T,n>& Vector<T, n>::getNormalized()
   *  \brief Get the vector normalized.
   *
   *  Get the vector normalized.
   *
   *  \return A normalized Vector
   */
  template <typename T, int n>
  inline
  Point<T,n> Vector<T, n>::getNormalized() {
    return (*this)/Point<T,n>::getLength();
  }

  /*! Vector<T,n> Vector<T, n>::getLinIndVec() const
   *  \brief Get a linear independent vector to the vector
   *
   *  Get a linear independent vector to the vector
   *
   *  \return A linear independent vector
   */
  template <typename T, int n>
  Vector<T,n> Vector<T, n>::getLinIndVec() const {

    if(n==1|| Point<T,n>::getLength()==0) return Vector<T,n>(T(0));
    else
    {
      int i,j=0;
      for(i=1; i < n;i++) if(( Point<T,n>::_pt[i]*Point<T,n>::_pt[i])>(Point<T,n>::_pt[j]*Point<T,n>::_pt[j])) j=i;
      if(j==0) i = 1;
      else	 i = j-1;

      Vector<T,n> r = *this;
      T tmp = -r[j];
      r[j]  = r[i];
      r[i]  = tmp;
      r    -= ((r*(*this))/((*this)*(*this)))*(*this);
      return r;
    }
  }

  /*! void Vector<T, n>::normalize()
   *  \brief Normalize the vector
   *
   *  Normalize the vector
   */
  template <typename T, int n>
  inline
  void Vector<T, n>::normalize() {
    (*this)/=Point<T,n>::getLength();
  }

  /*! void Vector<T, n>::setLength( T length )
   *  \brief Set the length of the vector
   *
   *  Set the length of the vector and adjust it accordingly
   *
   *  \param[in] length The new vector length
   */
  template <typename T, int n>
  inline
  void Vector<T, n>::setLength( T length ) {
    length /= Point<T,n>::getLength();
    (*this) *= length;
  }

  template <typename T, int n>
  inline
  UnitVector<T, n>::UnitVector( T t ) : Vector<T, n>(t) {
    Point<T, n>::operator/=(Point<T,n>::getLength());
  }

  template <typename T, int n>
  inline
  UnitVector<T, n>::UnitVector( const T t[n] ) : Vector<T, n>(t) {
    Point<T, n>::operator/=( Point<T,n>::getLength() );
  }

  template <typename T, int n>
  inline
  UnitVector<T, n>::UnitVector( const Point<T, n> &p ) : Vector<T,n>(p) {
    Point<T, n>::operator/=( Point<T,n>::getLength() );
  }

  template <typename T, int n>
  inline
  UnitVector<T, n>::UnitVector( const UnitVector<T, n> &uv ) : Vector<T, n>(uv) {}


  template <typename T, int n>
  inline
  Point<T, n>& UnitVector<T, n>::operator = ( const T t ) {
    _cpy(t);
    return Point<T,n>::operator/=( Point<T,n>::getLength() );
  }


  template <typename T, int n>
  inline
  Point<T, n>& UnitVector<T, n>::operator = ( const T t[n] ) {
    _cpy(t);
    return Point<T,n>::operator/=( Point<T,n>::getLength() );
  }


  template <typename T, int n>
  inline
  Point<T, n>& UnitVector<T, n>::operator = ( const Point<T, n> &p ) {
    this->_cpy(p);
    return Point<T,n>::operator/=( Point<T,n>::getLength() );
  }


  template <typename T, int n>
  inline
  Point<T, n>& UnitVector<T, n>::operator = ( const UnitVector<T, n>& uv )	{
    this->_cpy(uv);
    return *this;
  }


  template <typename T, int n>
  inline
  const T& UnitVector<T, n>::operator [] ( int i ) {
    return Point<T,n>::_pt[i];
  }


  template <typename T, int n>
  inline
  Point<T,n>& UnitVector<T, n>::operator += ( const Point<T, n> &p ) {
    Point<T,n>::operator += (p);
    return Point<T,n>::operator/=( Point<T,n>::getLength() );
  }


  template <typename T, int n>
  inline
  Point<T,n>& UnitVector<T, n>::operator -= ( const Point<T, n> &p ) {

    Point<T,n>::operator-=(p);
    return Point<T,n>::operator/=( Point<T,n>::getLength() );
  }


  template <typename T, int n>
  inline
  Point<T,n>& UnitVector<T, n>::operator %= ( const Point<T, n> &p ) {

    Point<T,n>::operator%=(p); return Point<T,n>::operator/=( Point<T,n>::getLength() );
  }


  template <typename T, int n>
  inline
  Point<T,n>& UnitVector<T, n>::operator *= ( const double d ) {

    return *this;
  }


  template <typename T, int n>
  inline
  Point<T,n>& UnitVector<T, n>::operator /= ( double d ) {

    return *this;
  }

  template <typename T, int n>
  inline
  Arrow<T, n>::Arrow() : Point<T, n>()	{
    _dir = Vector<T,n>(1);
  }

  template <typename T, int n>
  inline
  Arrow<T, n>::Arrow( const Point<T, n> &p ) : Point<T, n>(p) {
    _dir = Vector<T,n>(1);
  }

  template <typename T, int n>
  inline
  Arrow<T, n>::Arrow( const Point<T, n> &p, const Vector<T, n> &v ) : Point<T,n>(p) {
    _dir = v;
  }

  template <typename T, int n>
  inline
  Arrow<T, n>::Arrow( const Arrow<T, n> &a ) : Point<T, n>(a) {
    _dir = a._dir;
  }

  template <typename T, int n>
  inline
  const Vector<T, n>& Arrow<T, n>::getDir() const {
    return _dir;
  }

  template <typename T, int n>
  inline
  const Point<T, n>&  Arrow<T, n>::getPos() const {
    return (*this);
  }

  template <typename T, int n>
  inline
  void Arrow<T, n>::setDir( const Vector<T, n> &v ) {
    _dir = v;
  }

  template <typename T, int n>
  inline
  void Arrow<T, n>::setPos( const Point<T, n> &v ) {
    this->_cpy(v);
  }

  template <typename T, int n>
  inline
  Arrow<T, n>& Arrow<T, n>::operator = ( const Arrow<T, n> &a ) {
    memcpy( Point<T, n>::getPtr(), a.getPtr(), sizeof( Arrow<T, n> ) );
    return *this;
  } // setPos(v.pos()); setDir(v.dir()); return *this;}

  template <typename T, int n>
  inline
  Arrow<T, n>& Arrow<T, n>::operator += ( const Point<T, n> &p ) {
    Point<T, n>::operator += (p);
    return *this;
  }

  template <typename T, int n>
  inline
  Arrow<T, n>& Arrow<T, n>::operator -= ( const Point<T, n> &p ) {
    Point<T,n>::operator-=(p);
    return *this;
  }

  template <typename T, int n>
  inline
  Arrow<T, n> Arrow<T, n>::operator + ( const Point<T, n> &p ) const {
    //Point<T, n> r = (*this);
    Arrow<T, n> r = (*this);
    return r += p;
  }

  template <typename T, int n>
  inline
  Arrow<T, n> Arrow<T, n>::operator - ( const Point<T, n> &p ) const {
    //Point<T,n> r = (*this);
    Arrow<T,n> r = (*this);
    return r -= p;
  }

  template <typename T, int n>
  inline
  Arrow<T, n>& Arrow<T, n>::operator += ( const Vector<T, n> &v ) {
    _dir += v;
    return (*this);
  }

  template <typename T, int n>
  inline
  Arrow<T, n>& Arrow<T, n>::operator -= ( const Vector<T, n> &v ) {
    _dir -= v;
    return (*this);
  }

  template <typename T, int n>
  inline
  Arrow<T, n> Arrow<T, n>::operator + ( const Vector<T, n> &v ) const {
    //Point<T, n> r = (*this);
    Arrow<T, n> r = (*this);
    return r += v;
  }

  template <typename T, int n>
  inline
  Arrow<T, n> Arrow<T, n>::operator - ( const Vector<T, n> &v ) const {
    //Point<T, n> r = (*this);
    Arrow<T, n> r = (*this);
    return r -= v;
  }

  template <typename T, int n>
  inline
  Arrow<T, n> Arrow<T, n>::operator - () const {
    Point<T, n> p = -(*this);
    return p;
  }

  template <typename T, int n>
  template <class G, int m>
  inline
  Arrow<T, n>::operator Arrow<G, m>& () const {
    static Arrow<G,m> v;
    GM_Static1_<G,T,(n<m?n:m)>::eq( v.getPtr(), Point<T, n>::getPtr());
    GM_Static1_<G,T,(n<m?n:m)>::eq( v.getDir().getPtr(), _dir.getPtr());
    return v;
  }

  template <typename T, int n>
  inline
  Arrow<float, n>& Arrow<T, n>::toFloat() const {
    static Arrow<float,n> v;
    GM_Static1_<float,T,n>::eq( v.getPtr(), Point<T, n>::getPtr() );
    GM_Static1_<float,T,n>::eq( v.getDir().getPtr(), Point<T, n>::getPtr() );
    return v;
  }

  template <typename T, int n>
  inline
  Arrow<double, n>& Arrow<T, n>::toDouble() const
  {
    static Arrow<double,n> v;
    GM_Static1_<double,T,n>::eq( v.getPtr(), Point<T, n>::getPtr());
    GM_Static1_<double,T,n>::eq( v.getDir().getPtr(), Point<T, n>::getPtr());
    return v;
  }

  template <typename T, int n>
  inline
  ScalarPoint<T, n>::ScalarPoint() : _pos( T(0) ), _value( T(0) ) {}


  template <typename T, int n>
  inline
  ScalarPoint<T, n>::ScalarPoint( const Point<T, n>& p, T v )	{
    _pos = p;
    _value = v;
  }

  template <typename T, int n>
  inline
  ScalarPoint<T, n>::ScalarPoint( const ScalarPoint<T, n>& s )			{
    _pos = s._pos;
    _value = s._value;
  }

  template <typename T, int n>
  inline
  Point<T, n> ScalarPoint<T, n>::getPos() const {
    return _pos;
  }

  template <typename T, int n>
  inline
  T* ScalarPoint<T, n>::getPtr() const {
    return (T*)this;
  }

  template <typename T, int n>
  inline
  T ScalarPoint<T, n>::getValue() const {
    return _value;
  }

  template <typename T, int n>
  inline
  void ScalarPoint<T, n>::reset( const Point<T, n>& p , T v )	{
    _pos = p;
    _value = v;
  }

  template <typename T, int n>
  inline
  void ScalarPoint<T, n>::reset() {
    _pos = (T)0;
    _value = (T)0;
  }

  template <typename T, int n>
  inline
  void ScalarPoint<T, n>::resetValue( T t ) {
    _value = t;
  }

  template <typename T, int n>
  inline
  void ScalarPoint<T, n>::resetPos( const Point<T, n>& p ) {
    _pos = p;
  }

  template <typename T, int n>
  inline
  ScalarPoint<T, n>& ScalarPoint<T, n>::operator += ( const Point<T, n>& p ) {
    _pos += p;
    return *this;
  }

  template <typename T, int n>
  inline
  ScalarPoint<T, n>  ScalarPoint<T, n>::operator +  ( const Point<T, n>& p ) const	{
    ScalarPoint<T,n> a=(*this);
    a+=p;
    return a;
  }

  template <typename T, int n>
  inline
  ScalarPoint<T, n>& ScalarPoint<T, n>::operator += ( T p ) {
    _value += p;
    return *this;
  }

  template <typename T, int n>
  inline
  ScalarPoint<T, n>  ScalarPoint<T, n>::operator +  ( T p ) const {
    ScalarPoint<T,n> a=(*this);
    a+=p;
    return a;
  }

  template <typename T, int n>
  inline
  ScalarPoint<T, n>& ScalarPoint<T, n>::operator += ( const ScalarPoint<T, n>& p ) {
    _pos += p._pos;
    _pos /= 2.0;
    _value += p._value;
    _value /= 2.0;
    return *this;
  }

  template <typename T, int n>
  inline
  ScalarPoint<T, n>  ScalarPoint<T, n>::operator +  ( const ScalarPoint<T, n>& p ) const {
    ScalarPoint<T,n> a=(*this);
    a+=p;
    return a;
  }

  template <typename T, int n>
  inline
  ScalarPoint<T, n>& ScalarPoint<T, n>::operator *= ( double d ) {
    _value *= d;
    return *this;
  }

  template <typename T, int n>
  inline
  ScalarPoint<T, n>  ScalarPoint<T, n>::operator *  ( double d ) const {
    ScalarPoint<T,n> a=(*this);
    a*=d;
    return a;
  }

  template <typename T, int n>
  inline
  ScalarPoint<T, n>& ScalarPoint<T, n>::operator /= ( double d ) {
    _value /= d;
    return *this;
  }

  template <typename T, int n>
  inline
  ScalarPoint<T, n>  ScalarPoint<T, n>::operator /  ( double d ) const {
    ScalarPoint<T,n> a=(*this);
    a/=d;
    return a;
  }

  template <typename T, int n>
  inline
  ScalarPoint<T, n>& ScalarPoint<T, n>::operator %= ( const Point<T, n>& p ) {
    _pos %= p;
    return *this;
  }

  template <typename T, int n>
  inline
  ScalarPoint<T, n>  ScalarPoint<T, n>::operator %  ( const Point<T, n>& p ) const	{
    ScalarPoint<T,n> a=(*this);
    a%=p;
    return a;
  }

  template <typename T, int n>
  inline
  Sphere<T, n>::Sphere( bool valid ) : ScalarPoint<T,n>() {
    _valid = valid;
  }

  template <typename T, int n>
  inline
  Sphere<T, n>::Sphere( const Point<T, n>& p, T v ) : ScalarPoint<T,n>(p,v)	{
    _valid = true;
  }

  template <typename T, int n>
  inline
  Sphere<T, n>::Sphere( const ScalarPoint<T, n>& s ) : ScalarPoint<T,n>(s) {
    _valid = true;
  }

  template <typename T, int n>
  inline
  Sphere<T, n>::Sphere( const Sphere<T, n>& s ) : ScalarPoint<T,n>(s) {
    _valid = s._valid;
  }

  template <typename T, int n>
  inline
  T	Sphere<T, n>::getRadius() const	{
    return ScalarPoint<T, n>::_value;
  }

  template <typename T, int n>
  inline
  bool Sphere<T, n>::isValid() const {
    return _valid;
  }

  template <typename T, int n>
  bool Sphere<T, n>::isIntersecting(const Sphere<T,n>& p) const {
    if(ScalarPoint<T, n>::_valid && p._valid)
    {
      T d = (ScalarPoint<T, n>::_pos - p._pos).getLength();
      return (ScalarPoint<T, n>::_value+p._value) > d;
    }
    return false;
  }

  template <typename T, int n>
  inline
  void Sphere<T, n>::resetPos( const Point<T, n>& p )	{
    _valid = true;
    ScalarPoint<T,n>::resetPos(p);
  }

  template <typename T, int n>
  inline
  void Sphere<T, n>::resetRadius( T t ) {
    this->resetValue(t);
  }

  template <typename T, int n>
  inline
  void Sphere<T, n>::reset() {
    _valid = false;
    ScalarPoint<T,n>::reset();
  }

  template <typename T, int n>
  Sphere<T, n>& Sphere<T, n>::operator += ( const Point<T, n>& p ) {
    if(_valid)
    {
      Vector<T,n> v = p - ScalarPoint<T, n>::_pos;
      T r, d = v.getLength();

      if (d > ScalarPoint<T, n>::_value)
      {
        r		= (d+ScalarPoint<T, n>::_value)/2;
        ScalarPoint<T, n>::_pos   += ((r-ScalarPoint<T, n>::_value)/d)*v;
        ScalarPoint<T, n>::_value	= r;
      }
    }
    else
    {
      ScalarPoint<T, n>::_pos   = p;
      ScalarPoint<T, n>::_value = T(0);
      _valid = true;
    }

    return *this;
  }

  template <typename T, int n>
  inline
  Sphere<T, n> Sphere<T, n>::operator +  ( const Point<T, n>& p ) const {

    Sphere<T, n> a = (*this);
    a += p;
    return a;
  }

  template <typename T, int n>
  Sphere<T, n>& Sphere<T, n>::operator += ( const Sphere<T, n>& p ) {

    if(p._valid)
    {
      if(_valid)
      {
        Vector<T,n> v =  p._pos - ScalarPoint<T, n>::_pos;
        T r, d = v.getLength();
        if(ScalarPoint<T, n>::_value > p._value)
        {
          if (d > ScalarPoint<T, n>::_value - p._value)
          {
            r		= (d+ScalarPoint<T, n>::_value+p._value)/2;
            ScalarPoint<T, n>::_pos   += ((r-ScalarPoint<T, n>::_value)/d)*v;
            ScalarPoint<T, n>::_value	= r;
          }
        }
        else
        {
          if (d > p._value - ScalarPoint<T, n>::_value)
          {
            r		= (d+ScalarPoint<T, n>::_value+p._value)/2;
            ScalarPoint<T, n>::_pos   += ((r-ScalarPoint<T, n>::_value)/d)*v;
            ScalarPoint<T, n>::_value	= r;
          }
          else
            *this = p;
        }
      }
      else
        *this  = p;
    }
    return *this;
  }

  template <typename T, int n>
  inline
  Sphere<T, n>  Sphere<T, n>::operator +  ( const Sphere<T, n>& p ) const {
    Sphere<T,n> a=(*this);
    a+=p;
    return a;
  }

  template <typename T, int n>
  inline
  Box<T, n>::Box() {
    _min = _max = (T) 0;
  }

  template <typename T, int n>
  inline
  Box<T, n>::Box( const Point<T, n>& p ) {
    _min = _max = p;
  }

  template <typename T, int n>
  inline
  Box<T, n>::Box( const Box<T, n>& b ) {
    _min = b._min;
    _max = b._max;
  }

  template <typename T, int n>
  inline
  Box<T, n>::Box( const Point<T, n>& p1, const Point<T, n>& p2 )	{
    _min = _max = p1;
    insert(p2);
  }

  template <typename T, int n>
  inline
  Box<T, n>::Box( const Point<T, n>& p1, const Point<T, n>& p2, const Point<T,n>& p3 ) {
    _min = _max = p1;
    insert(p2);
    insert(p3);
  }

  template <typename T, int n>
  inline
  Point<T, n>	Box<T, n>::getPointMin() const {
    return _min;
  }

  template <typename T, int n>
  inline
  Point<T, n>	Box<T, n>::getPointMax() const {
    return _max;
  }

  template <typename T, int n>
  inline
  Point<T, n>	Box<T, n>::getPointCenter() const {
    return (_max + _min)*0.5;
  }

  template <typename T, int n>
  inline
  Vector<T, n>	Box<T, n>::getPointDelta() const {
    return _max - _min;
  }

  template <typename T, int n>
  inline
  T* Box<T, n>::getPtr() const {
    return (T*)this;
  }

  template <typename T, int n>
  inline
  T&		Box<T, n>::getValueAt( int i, int j ) {
    return i == 0 ? _min[j] : _max[j];
  }

  template <typename T, int n>
  inline
  T Box<T, n>::getValueMin( int i ) const	{
    return _min(i);
  }

  template <typename T, int n>
  inline
  T Box<T, n>::getValueMax( int i ) const	{
    return _max(i);
  }

  template <typename T, int n>
  inline
  T Box<T, n>::getValueCenter( int i ) const {
    return (_max(i) + _min(i))*0.5;
  }

  template <typename T, int n>
  inline
  T Box<T, n>::getValueDelta( int i ) const {
    return _max(i) - _min(i);
  }

  template <typename T, int n>
  void Box<T, n>::insert( const Point<T, n>& p) {
    for(int i=0;i<n;i++)
    {
      if(p(i) < _min[i]) _min[i] = p(i);
      if(p(i) > _max[i]) _max[i] = p(i);
    }
  }


  template <typename T, int n>
  void Box<T, n>::insert( const Box<T, n>& b) {
    for(int i=0;i<n;i++)
    {
      if(b._min(i) < _min[i]) _min[i] = b._min(i);
      if(b._max(i) > _max[i]) _max[i] = b._max(i);
    }
  }

  template <typename T, int n>
  bool Box<T, n>::isIntersecting( const Box<T,n>& b ) const {
    for(int i=0;i<n;i++)
    {
      if(b._min(i) > _max(i)) return false;
      if(b._max(i) < _min(i)) return false;
    }
    return true;
  }

  template <typename T, int n>
  bool Box<T, n>::isSurrounding( const Point<T,n>& p ) const {
    for(int i=0;i<n;i++)
    {
      if(p(i) < _min(i)) return false;
      if(p(i) > _max(i)) return false;
    }
    return true;
  }

  template <typename T, int n>
  bool Box<T, n>::isSurrounding( const Box<T,n>& b )  const {
    for(int i=0;i<n;i++)
    {
      if(b._min(i) < _min(i)) return false;
      if(b._max(i) > _max(i)) return false;
    }
    return true;
  }

  template <typename T, int n>
  inline
  void Box<T, n>::reset() {
    reset( Point<T, n>( (T)0 ) );
  }

  template <typename T, int n>
  inline
  void Box<T, n>::reset( const Point<T, n>& p ) {
    _min = _max = p;
  }

  template <typename T, int n>
  inline
  Box<T,n>&	Box<T, n>::operator += ( const Point<T, n>& p ) {
    insert(p);
    return *this;
  }

  template <typename T, int n>
  inline
  Box<T,n> Box<T, n>::operator +  ( const Point<T, n>& p ) {
    Box<T,n> a=(*this);
    a+=p;
    return a;
  }

  template <typename T, int n>
  inline
  Box<T,n>&	Box<T, n>::operator += ( const Box<T, n>& b ) {
    insert(b);
    return *this;
  }

  template <typename T, int n>
  inline
  Box<T,n> Box<T, n>::operator +  ( const Box<T, n>& b ) {
    Box<T,n> a=(*this);
    a+=b;
    return a;
  }

  template <typename T, int n, int m>
  M_I_<T, n, m>::M_I_() {
    for(int k=0,i=0; i<n; i++)
      for(int j=0; j<m; j++)
        if(i==j)	_p[k++] = T(1);
        else		_p[k++] = T(0);
  }

  template <typename T, int n, int m>
  inline
  T* M_I_<T, n, m>::getPtr() const {
    return (T*)this;
  }

} // END namespace GMlib
