#ifndef GM_PARAMETRICS_PPOLYGON_H
#define GM_PARAMETRICS_PPOLYGON_H

#include "gmparametrics.h"

// gmlib
#include <core/types/gmpoint.h>
#include <core/containers/gmdvector.h>

namespace GMlib {
    template <typename T, int n>
    class PTriangleVisualizer;

//    template <typename T, int n>
//    class PTriangleDefaultVisualizer;

    template <typename T, int n>
    class PPolygonVisualizerSet {
    public:
      PPolygonVisualizerSet() {}
      PPolygonVisualizerSet( const Array<PTriangleVisualizer<T,n>*>& skel ) { updateVisualizerSet(skel); }

      void    updateVisualizerSet( const Array<PTriangleVisualizer<T,n>*>& skel ) {

        // Delete visualizers
        for( int i = 0; i < visus.getSize(); ++i )
          delete visus[i];
        visus.clear();

        // Create new ones
        for( int i = 0; i < skel.getSize(); ++i )
          visus += static_cast<PTriangleVisualizer<T,n>*>(skel(i)->makeCopy());
      }

      Array< PTriangleVisualizer<T,n>* >    visus;
    };

    template <typename T, int n>
    class PPolygon : public Parametrics<T,2,n>
    {

    public:
        PPolygon();
        ~PPolygon();

        void enableDefaultVisualizer( bool enable = true );
        void toggleDefaultVisualizer();
        void insertVisualizer( Visualizer *visualizer );
        void removeVisualizer( Visualizer *visualizer );

        virtual void replot( int m = 2, int d = 1 );
        virtual void resample( DVector< DVector< DVector< Vector<T,n> > > >& p, int m, int d );


    protected:
        Array< PPolygonVisualizerSet<T,n> *>  _ppolygon_visualizers;
        Array< PTriangleVisualizer<T,n>*> _pp_v;
        PTriangleVisualizer<T,n> * _default_visualizer;

        int _no_sam;
        DVector< Vector<T,n> > _p;
        T _u0;
        T _u1;
        T _u2;
        T _u3;
        T _u4;
        int _d;

        virtual void  eval( T u0, T u1, T u2, T u3, T u4, int d ) = 0;
        virtual void setSurroundingSphere( const DVector< DVector< DVector< Vector<T,n> > > >& p );

    private:
        void  _eval( T u0, T u1, T u2, T u3, T u4, int d );
        void eval(const DVector<T> &corner_p, int d );
        void fillCornersAndCenter( int num, DVector<DVector<T>> &cornerAndCenter_p);
        DVector<DVector<Vector<T,n>>> createTriangleSamples(int m, int num, DVector<T> corner_pw, DVector<T> corner_pu, DVector<T> corner_pv, int d);
        int _sum(int i);
        void insertVis(Visualizer *visualizer);
        void removeVis(Visualizer *visualizer);
    };

}

#include "gmppolygon.c"

#endif // GM_PARAMETRICS_PPOLYGON_H
