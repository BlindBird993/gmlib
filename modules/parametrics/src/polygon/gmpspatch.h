#ifndef GM_PARAMETRICS_POLYGON_PSPATCH_H
#define GM_PARAMETRICS_POLYGON_PSPATCH_H


#include"../gmppolygon.h"

namespace GMlib {

    template <typename T, int n>
    class Selector;

    template <typename T>
    class SelectorGridVisualizer;

    template <typename T>
    class PSPatch : public PPolygon<T,3>
    {
        GM_SCENEOBJECT(PSPatch)
    public:
        PSPatch(const DVector< Vector<T,3> >& c);
        ~PSPatch();

        DVector< Vector<T,3> > getControlPoints() const;

        virtual void hideSelectors();
        bool isSelectorsVisible() const;
        virtual void showSelectors( bool grid, Color selector_color = GMcolor::darkBlue(), Color grid_color = GMcolor::lightGreen() );

    protected:
        DVector< Vector<T,3> > _c;

        bool                        _selectors;
        SelectorGridVisualizer<T>  *_sgv;
        DVector< Selector<T,3>* >   _s;

        void eval(T u0, T u1, T u2, T u3, T u4, int d) override;

    private:
        DVector<T> _p_i, _l, _W;
        Vector<T,2> _p_pos, _p_uv;
        void createPn(T u0, T u1, T u2, T u3, T u4);
        DVector<T> createAlpha(T p);
        DVector<T> createPi(T p);
        DVector<T> createL(T p);
        DVector<T> createW(T p, int d);
        T getDeterminant(const Vector<Vector<T,3>,3>& mat);
        Point<T,3> DeCasteljau(int n, int d, DVector<Point<T,3>> p, DVector<T> b);
        Point<T,3> cornerCutting(DVector<Point<T,3>> q, DVector<T> b);
//        int binom (int n, int d);
//        int factorial(int x);
    };

}

#include "gmpspatch.c"

#endif // GM_PARAMETRICS_POLYGON_PSPATCH_H
