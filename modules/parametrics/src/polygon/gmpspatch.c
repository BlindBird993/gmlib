
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
        DVector<T> _pi;
        _pi.setDim(_alpha.getDim());
        for(int i = 0, k = 0; i < _pi.getDim(); i++)
        {
            if(i == 0)
                k = _pi.getDim()-1;
            else
                k = i-1;
            for(int j = 0; j < _alpha.getDim(); j++){
                if(j != i && j != k)
                    _pi[i] *= _alpha[j];
            }
        }
        
    }
    
    template <typename T>
    DVector<T> PSPatch<T>::createL(T p)
    {
        DVector<T> _pi = createPi(p);
        T _sumPi = 0;
        for(int i = 0; i < _pi.getDim(); i++)
            _sumPi += _pi[i];

        DVector<T> _l;
        _l.setDim(_pi.getDim());
        for(int j = 0; j < _l.getDim(); j++)
            _l[j] = _pi[j]/_sumPi;

        return _l;
    }

    template <typename T>
    DVector<T> PSPatch<T>::createW(T p, int d)
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

    template <typename T>
    Point<T,3> PSPatch<T>::DeCasteljau(int n, int d, DVector<Point<T,3>> p, DVector<T> b)
    {
        if(p.getDim == n)
            return cornerCutting(p, b);
        else
            {
                DVector<Point<T,3>> q;
                q.setDim(n);
                DVector<DVector<Point<T,3>>> subs;
                subs.setDim(n);

                DVector<int> index = DVector<int>(n,0);
                index[0] = d;
                for(int i = 1, k=0; i <= n; i++)
                {
                    //Add to sub
                    for(int l = 0; l < index.getDim(); l++)
                    {
                        if(index[l] > 0)
                            subs[l].push_back(p[k]);
                    }
                    if(i == n)
                    {
                        if(index[i-1] == d)
                            break;
                        int j = n-2;
                        for(; index[j] == 0 and j >= 0; j--);
                        if(j < 0)
                            break;
                        i = j+1;
                        index[i]=index[n-1];
                        if(i != n-1)
                            index[n-1]=0;

                    }
                    index[i]++;
                    index[i-1]--;
                    k++;
                }

                for(int i = 0; i < subs.getDim(); i++)
                {
                    q[i] = DeCasteljau(n,d-1,subs[i],b);
                }
                return cornerCutting(q, b);
            }
    }

//    template <typename T>
//    int PSPatch<T>::binom (int n, int d)
//    {
//        int m = n + d - 1;
//        return factorial(m)/(factorial(d)*factorial(m-d));
//    }

//    template <typename T>
//    int PSPatch<T>::factorial(int x)
//    {
//        if(x == 0)
//            return 1;
//        else
//            return x*factorial(x-1);
//    }

    template <typename T>
    Point<T,3> PSPatch<T>::cornerCutting(DVector<Point<T,3>> q, DVector<T> b)
    {
        //Use l(p)
    }
}
