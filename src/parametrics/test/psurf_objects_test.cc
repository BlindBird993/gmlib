
#include <gtest/gtest.h>

#include <gmTestUtilsModule>
#include <gmParametricsModule>
using namespace GMlib;


namespace {




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
//    GMtest::createDestroyObject< PHermiteSurface<T> >();
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


  TEST(PSurf, ObjectCreation) {

    createAndDestroyBasicSurfaces<float>();
    createAndDestroyBasicSurfaces<double>();
    createAndDestroyBasicSurfaces<int>();
  }

}
