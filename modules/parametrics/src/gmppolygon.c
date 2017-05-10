// local
#include "visualizers/gmptriangledefaultvisualizer.h"

namespace GMlib {

    template <typename T, int n>
    PPolygon<T,n>::PPolygon()
    {
        _d      = -1;
        _no_sam = 20;
        _ppolygon_visualizers.setSize(5);

    }

    template <typename T, int n>
    PPolygon<T,n>::~PPolygon()
    {
        enableDefaultVisualizer( false );
        if( _default_visualizer )
          delete _default_visualizer;
    }

    template <typename T, int n>
    void PPolygon<T,n>::_eval(T u0, T u1, T u2, T u3, T u4, int d)
    {
        if(!(u0 == _u0 and u1 == _u1 and u2 == _u2 and u3 == _u3 and u4 == _u4 and d <= _d))
        {
          _u0 = u0;
          _u1 = u1;
          _u2 = u2;
          _u3 = u3;
          _u4 = u4;
          _d = d;
          eval(u0, u1, u2, u3, u4, d);
        }

    }

    template <typename T, int n>
    void PPolygon<T,n>::toggleDefaultVisualizer() {
        if( !_pp_v.exist( _default_visualizer) )
          enableDefaultVisualizer( true );
        else
          enableDefaultVisualizer( false );
    }

    template <typename T, int n>
    void PPolygon<T,n>::enableDefaultVisualizer( bool enable )
    {
        if( !enable )
        {
          removeVisualizer( _default_visualizer);
        }
        else
        {
          if( !_default_visualizer)
              _default_visualizer = new PTriangleDefaultVisualizer<T,n>();

          insertVisualizer( _default_visualizer );
        }
    }

    template <typename T, int n>
    void PPolygon<T,n>::insertVisualizer( Visualizer *visualizer )
    {
        PTriangleVisualizer<T,n> *visu = dynamic_cast<PTriangleVisualizer<T,n>*>( visualizer );

        if( !visu ) {

          insertVis( visualizer );
          return;
        }

        if( _pp_v.exist( visu ) )
          return;

        _pp_v += visu;

    }

    template <typename T, int n>
    void PPolygon<T,n>::removeVisualizer(Visualizer *visualizer)
    {
        PTriangleVisualizer<T,n> *visu = dynamic_cast<PTriangleVisualizer<T,n>*>( visualizer );

        if( !visu ) {

          removeVis( visualizer );
          return;
        }

        if( !_pp_v.exist(visu) )
          return;

        _pp_v.remove(visu);
    }

    template <typename T, int n>
    void PPolygon<T,n>::insertVis(Visualizer *visualizer)
    {
        Parametrics<T,2,n>::insertVisualizer( visualizer );

    }

    template <typename T, int n>
    void PPolygon<T,n>::removeVis(Visualizer *visualizer)
    {

        Parametrics<T,2,n>::removeVisualizer( visualizer );
    }

    template <typename T, int n>
    inline
    void PPolygon<T,n>::replot( int m, int d )
    {
        if( m < 2 )        m = _no_sam;
        else         _no_sam = m;

        // Sample Positions and related Derivatives
        DVector< DVector< DVector< Vector<T,n> > > > p;
        resample( p, m, d );

        setSurroundingSphere( p );

        // Clean up "visualizers"
        for( int i = 0; i < _ppolygon_visualizers.size(); ++i )
           for( int j = 0; j < _ppolygon_visualizers[i]->visus.getSize(); ++j )
               removeVis( _ppolygon_visualizers[i]->visus[j] );

        for( int i = 0; i < _ppolygon_visualizers.size(); ++i ) {

          // Update sub-visualizer set
          _ppolygon_visualizers[i]->updateVisualizerSet(_pp_v);

          const Array< PTriangleVisualizer<T,n>* >  &sub_visus  = _ppolygon_visualizers[i]->visus;

          for( int j = 0; j < sub_visus.getSize(); ++j )
          {
            insertVis( sub_visus(j) );


            sub_visus(j)->replot( p[j], m);
          }
        }
    }

    template <typename T, int n>
    void PPolygon<T,n>::resample( DVector< DVector< DVector< Vector<T,n> > > >& p, int m, int d )
    {
        int num = 5;
        int sum_m = _sum(m);
        DVector<DVector<T>> cornerAndCenter_p;
        fillCornersAndCenter(num, cornerAndCenter_p);

        p.setDim(num);

        for(int l = 2, k = 1, i = 0; i < num; i++)
        {
            p[i].setDim(sum_m);
            if(l == num+1)
                l = 1;
            p[i] = createTriangleSamples(m, num, cornerAndCenter_p[0],cornerAndCenter_p[k++],cornerAndCenter_p[l++], d);
        }
    }

    template <typename T, int n>
    void PPolygon<T,n>::fillCornersAndCenter( int num, DVector<DVector<T>> &cornerAndCenter_p)
    {
        cornerAndCenter_p.setDim(num+1);

        cornerAndCenter_p[0].setDim(num);

        for(int i = 1; i < num+1; i++)
        {
            cornerAndCenter_p[0][i-1]=T(1)/num;
            cornerAndCenter_p[i].setDim(num);
            for(int j = 0; j < num; j++)
            {
                if((i-1)==j)
                    cornerAndCenter_p[i][j] = T(1);
                else
                    cornerAndCenter_p[i][j] = T(0);
            }
        }
    }

    template <typename T, int n>
    DVector<DVector<Vector<T,n>>> PPolygon<T,n>::createTriangleSamples(int m, int num, DVector<T> corner_pw, DVector<T> corner_pu, DVector<T> corner_pv, int d)
    {
           DVector<DVector<Vector<T,n>>> tri_samples;
           DVector<T> tri_p;
           T u,v,w,du = T(1)/(m-1);
           tri_samples.setDim(_sum(m));
           tri_p.setDim(num);
           int i,j,k;
           for(k=0,i=0; i<m; i++) {
             for( j=0; j<=i; j++ )
             {
               v = j*du;
               u = (i-j)*du;
               w = 1-u-v;
               tri_p = corner_pw*w + corner_pu*u + corner_pv*v;
               eval(tri_p,d);
               tri_samples[k++] = _p;
             }
           }
           return tri_samples;

    }

    template <typename T, int n>
    int PPolygon<T,n>::_sum(int i)
    {
        int r = 0;
        for(; i>0; i--) r += i;
        return r;
    }

    template <typename T, int n>
    void PPolygon<T,n>::eval(const DVector<T> &corner_p, int d)
    {
        eval(corner_p(0), corner_p(1), corner_p(2), corner_p(3), corner_p(4), d);
    }

    template <typename T, int n>
    inline
    void PPolygon<T,n>::setSurroundingSphere( const DVector< DVector< DVector< Vector<T,n> > > >& p ) {

      Sphere<float,3>  s( p(0)(0)(0) );

      for( int i = 0; i < p.getDim(); i++ )
          for(int j = 0; j < p(i).getDim(); j++)
            s += p(i)(j)(0);

      Parametrics<T,2,n>::setSurroundingSphere(s.template toType<float>());
    }

}
