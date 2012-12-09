
#include <gtest/gtest.h>

#include <gmTestUtilsModule>
#include <gmParametricsModule>
using namespace GMlib;



//#define PSURF_OBJECT_CREATE_TEST( CNAME, T ) \
//  TEST( ObjectCreation, CNAME ) { \
//    GMtest::createDestroyObject< CNAME<T> >(); \
//  }



namespace {

//  PSURF_OBJECT_CREATE_TEST(PApple,float)


  template <typename T>
  void createAndDestroyBasicCurves() {

//    GMtest::createDestroyObject< PArc<T> >();
    GMtest::createDestroyObject< PBasisCurve<T> >();
    GMtest::createDestroyObject< PButterfly<T> >();
    GMtest::createDestroyObject< PChrysanthemumCurve<T> >();
    GMtest::createDestroyObject< PCircle<T> >();
    GMtest::createDestroyObject< PHelicoid<T> >();
    GMtest::createDestroyObject< PRoseCurve<T> >();
  }


  template <typename T>
  void createAndDestroyBasicSurfaces() {

    GMtest::createDestroyObject< PApple<T> >();
    GMtest::createDestroyObject< PApple2<T> >();
    GMtest::createDestroyObject< PAsteroidalSphere<T> >();
    GMtest::createDestroyObject< PBentHorns<T> >();
    GMtest::createDestroyObject< PBohemianDome<T> >();
    GMtest::createDestroyObject< PBoysSurface<T> >();
    GMtest::createDestroyObject< PCircularSurface<T> >();
    GMtest::createDestroyObject< PCone<T> >();
    GMtest::createDestroyObject< PCrossCap<T> >();
    GMtest::createDestroyObject< PCylinder<T> >();
    GMtest::createDestroyObject< PDiniSurface<T> >();
    GMtest::createDestroyObject< PEightSurface<T> >();
    GMtest::createDestroyObject< PEnnepersSurface<T> >();
    GMtest::createDestroyObject< PHeart<T> >();
    GMtest::createDestroyObject< PInsideOutTorus<T> >();
    GMtest::createDestroyObject< PKleinsBottle<T> >();
    GMtest::createDestroyObject< PMoebiusStrip<T> >();
    GMtest::createDestroyObject< PSeashell<T> >();
    GMtest::createDestroyObject< PSlippersSurface<T> >();
    GMtest::createDestroyObject< PSphere<T> >();
    GMtest::createDestroyObject< PSteinerSurf<T> >();
    GMtest::createDestroyObject< PSwallowTail<T> >();
    GMtest::createDestroyObject< PTorus<T> >();
    GMtest::createDestroyObject< PTrianguloidTrefoil<T> >();
    GMtest::createDestroyObject< PWhitneyUmbrella<T> >();
  }


  TEST(ObjectCreation, PCurves) {

    createAndDestroyBasicCurves<float>();
    createAndDestroyBasicCurves<double>();
    createAndDestroyBasicCurves<int>();
  }

  TEST(ObjectCreation, PSurfs) {

    createAndDestroyBasicSurfaces<float>();
    createAndDestroyBasicSurfaces<double>();
    createAndDestroyBasicSurfaces<int>();
  }


}
