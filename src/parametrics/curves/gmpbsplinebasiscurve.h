#ifndef BSPLINEBASIS1_H
#define BSPLINEBASIS1_H



// GMlib includes+
#include <gmParametricsModule>



namespace GMlib {


  template <typename T>
  class PBSplineBasisCurve : public PCurve<T,3> {
      GM_SCENEOBJECT(PBSplineBasisCurve)
  public:
    PBSplineBasisCurve( const DVector<T>& t );

    PBSplineBasisCurve( const PBSplineBasisCurve<T>& copy );

    virtual ~PBSplineBasisCurve();

    bool            isClosed() const;

  protected:

    DVector<T>      _t;

    void            eval( T t, int d = 0, bool l = false );
    T               getEndP();
    T               getStartP();

    T               W(T t, int d, int i);
    T               delta(T s, int d, int i);
    void            makeMat(DMatrix<T>& mat, int i, int d, T t, T scale);
    int             findIndex(T t, int s);

  }; // END class PBSplineBasisCurve

} // END namepace GMlib


// Include PBSplineBasisCurve class function implementations
#include "gmpbsplinebasiscurve.c"


#endif // BSPLINEBASIS1_H
