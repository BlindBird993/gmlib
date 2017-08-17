

#include <gtest/gtest.h>

#include "../src/curves/gmpcircle.h"
using namespace GMlib;


namespace {

template <typename T>
inline
void testPCurveStandardMethodCalls( PCurve<T,3>& curve ) {
  curve.evaluate( curve.getParStart() + curve.getParDelta() * 0.5, 0 );
}


TEST(Parametrics_Curves, CompileTest) {

  auto pcircle = PCircle<float>();
  testPCurveStandardMethodCalls(pcircle);
}



}

























