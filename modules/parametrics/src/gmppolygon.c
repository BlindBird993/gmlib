

namespace GMlib {

    template <typename T, int n>
    PPolygon<T,n>::PPolygon()
    {
        _d      = -1;
        _no_sam = 20;

        _default_visualizer = 0x0;
    }

    template <typename T, int n>
    PPolygon<T,n>::~PPolygon()
    {
//        enableDefaultVisualizer( false );
//        if( _default_visualizer )
//          delete _default_visualizer;
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
    void PPolygon<T,n>::enableDefaultVisualizer( bool enable ) {

      if( !enable )
        removeVisualizer( _default_visualizer );
      else {

        if( !_default_visualizer )
          _default_visualizer = new PTriangleDefaultVisualizer<T,n>();

        insertVisualizer( _default_visualizer );
      }
    }

//    template <typename T, int n>
//    inline
//    const PTriangleVisualizer<T, n>* PPolygon<T,n>::getDefaultVisualizer() const {

//      return _default_visualizer;
//    }

//    template <typename T, int n>
//    inline
//    void PPolygon<T,n>::insertVisualizer( Visualizer *visualizer ) {

//      Parametrics<T,2,n>::insertVisualizer( visualizer );

//      PTriangleVisualizer<T,n> *visu = dynamic_cast<PTriangleVisualizer<T,n>*>( visualizer );

//      if( !visu )
//        return;

//      if( _ppolygon_visualizers.exist( visu ) )
//        return;

//      _ppolygon_visualizers += visu;


//    }

//    template <typename T, int n>
//    inline
//    void PPolygon<T,n>::removeVisualizer( Visualizer *visualizer ) {

//      PTriangleVisualizer<T,n> *visu = dynamic_cast<PTriangleVisualizer<T,n>*>( visualizer );
//      if( visu )
//        _ppolygon_visualizers.remove( visu );

//      Parametrics<T,2,n>::removeVisualizer( visualizer );
//    }

//    template <typename T, int n>
//    void PPolygon<T,n>::toggleDefaultVisualizer() {

//      if( !_ppolygon_visualizers.exist( _default_visualizer ) )
//        enableDefaultVisualizer( true );
//      else
//        enableDefaultVisualizer( false );
//    }

    template <typename T, int n>
    inline
    void PPolygon<T,n>::replot( int m, int d )
    {
      if( m < 2 )        m = _no_sam;
      else         _no_sam = m;

      // Sample Positions and related Derivatives
      DVector< DVector< Vector<T,n> > > p;
      resample( p, m, d );

      setSurroundingSphere( p );

      // Replot Visaulizers
//      for( int i = 0; i < this->_ppolygon_visualizers.getSize(); i++ )
//        this->_ppolygon_visualizers[i]->replot( p, m);
    }

    template <typename T, int n>
    void PPolygon<T,n>::resample( DVector< DVector < Vector<T,n> > >& p, int m, int d )
    {

    }

    template <typename T, int n>
    inline
    void PPolygon<T,n>::setSurroundingSphere( const DVector<DVector<Vector<T,n> > >& p ) {

      Sphere<float,3>  s( p(0)(0) );

      s += p( p.getDim()-1)(0);
      for( int i = 1; i < p.getDim() - 1; i++ )
        s += p(i)(0);

      Parametrics<T,2,n>::setSurroundingSphere(s.template toType<float>());
    }

}
