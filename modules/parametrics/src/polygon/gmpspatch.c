
namespace GMlib {

    template <typename T>
    PSPatch<T>::PSPatch(const DVector< Vector<T,3> >& c)
    {
        _sgv = new SelectorGridVisualizer<T>;
    }

    template <typename T>
    PSPatch<T>::~PSPatch()
    {
        delete _sgv;
    }

    template <typename T>
    void PSPatch<T>::eval(T u0, T u1, T u2, T u3, T u4, int d)
    {

    }

    template <typename T>
    DVector< Vector<T,3>> PSPatch<T>::getControlPoints() const
    {
        return _c;
    }

    template <typename T>
    void PSPatch<T>::createPn(T u0, T u1, T u2, T u3, T u4)
    {
        //Jostein's circle trick
        Vector<T,2> circ_eval = [](T t){return Vector<T,2>(std::cos(t), std::sin(t));};

        for(int i = 0; i < 5; i++)
        {
            _p_uv[i] = circ_eval((2*3.14)/5*i);
        }

    }

    template <typename T>
    DVector<T> PSPatch<T>::createAlpha(T p)
    {
        DVector<T> _alpha;
        Vector<Vector<T,3>,3> mat;
        int j;
        _alpha.setDim(_p_uv.getDim());
        for(int i = 0; i < _p_uv.getDim(); i++){
            if((i+1) == _p_uv.getDim())
                j=0;
            else
                j=i;
            mat = (Vector<T,3>{p[0],_p_uv[i][0], _p_uv[j][0]},Vector<T,3>{p[1], _p_uv[i][1], _p_uv[j][1]},Vector<T,3>{T(1),T(1),T(1)});
            _alpha[i] = getDeterminant(mat);
        }
        return _alpha;
    }

    template <typename T>
    DVector<T> PSPatch<T>::createPi(T p)
    {
        DVector<T> _alpha = createAlpha(p);
        
    }
    
    template <typename T>
    DVector<T> PSPatch<T>::createL(T p)
    {

    }

    template <typename T>
    DVector<T> PSPatch<T>::createW(T p)
    {

    }
    
    template <typename T>
    T PSPatch<T>::getDeterminant(const Vector<Vector<T,3>,3>& mat)
    {
        
    }

    template <typename T>
    void PSPatch<T>::hideSelectors() {

      if( !_selectors )
        return;

      // Remove Selector Grid Visualizer
      this->removeVisualizer( _sgv );
      _sgv->reset();

      // Remove selectors
      for( int i = 0; i < _s.getDim(); i++ ) {
        this->remove( _s[i] );
        delete _s[i];
      }

      _selectors = false;
    }

    template <typename T>
    inline
    void PSPatch<T>::showSelectors( bool grid, Color selector_color, Color grid_color ) {

      if( _selectors )
        return;

      _s.setDim( _c.getDim() );
      for( int i = 0, k = 0; i < _s.getDim(); i++ ) {
        Selector<T,3> *sel;
        if( i == 0 )
          sel = new Selector<T,3>( _c[i], k++, this, T(0.2), GMcolor::red() );
        else
          sel = new Selector<T,3>( _c[i], k++, this, T(0.2), selector_color );

        this->insert( sel );
        _s[i] = sel;
      }

      if( grid ) {
        _sgv->setSelectors( _c, 1 );
        this->insertVisualizer( _sgv );
      }

      _selectors = true;
    }
}
