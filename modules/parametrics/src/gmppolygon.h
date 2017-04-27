#ifndef GM_PARAMETRICS_PPOLYGON_H
#define GM_PARAMETRICS_PPOLYGON_H

#include "gmparametrics.h"

// gmlib
#include <core/types/gmpoint.h>
#include <core/containers/gmdvector.h>

namespace GMlib {
    template <typename T, int n>
    class PTriangleVisualizer;

    template <typename T, int n>
    class PTriangleDefaultVisualizer;

    template <typename T, int n>
    class PPolygon : public Parametrics<T,2,n>
    {

    public:
        PPolygon();
        ~PPolygon();

        void enableDefaultVisualizer( bool enable = true );
//        const PTriangleVisualizer<T,n>* getDefaultVisualizer() const;
//        void toggleDefaultVisualizer();
//        void insertVisualizer( Visualizer *visualizer );
//        void removeVisualizer( Visualizer *visualizer );

        virtual void replot( int m = 2, int d = 1 );
        virtual void resample( DVector<DVector<Vector<T,n> > > &p, int m, int d );


    protected:
        Array< PTriangleVisualizer<T,n>* >  _ppolygon_visualizers;
        PTriangleVisualizer<T,n> *_default_visualizer;

        int _no_sam;
        DVector< Vector<T,n> > _p;
        T _u0;
        T _u1;
        T _u2;
        T _u3;
        T _u4;
        int _d;

        virtual void  eval( T u0, T u1, T u2, T u3, T u4, int d ) = 0;
        virtual void setSurroundingSphere( const DVector<DVector<Vector<T,n> > > &p );

    private:
        void  _eval( T u0, T u1, T u2, T u3, T u4, int d );
    };

}

#include "gmppolygon.c"

#endif // GM_PARAMETRICS_PPOLYGON_H
