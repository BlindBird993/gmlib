#include <benchmark/benchmark.h>

#include "../src/curves/gmpcircle.h"
#include "../src/triangles/gmpbeziertriangledecasteljau.h"
using namespace GMlib;



//static void BM_PCircle_Resample(benchmark::State& state)
//{
//  auto pcircle = PCircle<float>();
//  DVector<DVector<Vector<float,3>>> samps;

//  // The test loop
//  while (state.KeepRunning()) {
//    pcircle.resample(samps, state.range(0), state.range(1));
//  }
//}


//BENCHMARK(BM_PCircle_Resample)
//  ->Unit(benchmark::kNanosecond)
//  ->RangeMultiplier(2)
//  ->Ranges({{2, 2 << 15}, {1,2}});

void index(int d,DVector<Vector<float,3>> p)
{
    DVector<DVector<Vector<float,3>>> subs;
    subs.setDim(3);

    DVector<int> index = DVector<int>(3,0);
    index[0] = d;
    for(int i = 1, k=0; i <= 3; i++)
    {
        //Add to sub
        for(int l = 0; l < index.getDim(); l++)
        {
            if(index[l] > 0)
                subs[l].push_back(p[k]);
        }
        if(i == 3)
        {
            if(index[i-1] == d)
                break;
            int j = 1;//n-2
            for(; index[j] == 0 and j >= 0; j--);
            if(j < 0)
                break;
            i = j+1;
            index[i]=index[2];//index[n-1]
            if(i != 2)//n-1
                index[2]=0;//index[n-1]

        }
        index[i]++;
        index[i-1]--;
        k++;
    }
}

static void BM_BezierTriangle_deCasteljau_d1(benchmark::State& state)
{
  DVector<Vector<float,3>> c;
  int d = 1;
  c.push_back(GMlib::Vector<float,3>(0.f,0.f,0.f));
  c.push_back(GMlib::Vector<float,3>(3.0f,0.f,0.f));
  c.push_back(GMlib::Vector<float,3>(1.5f,3.f,0.f));

  auto pbezierTri = PBezierTriangleDeCasteljau<float>(c);

  Vector<float,3> test;

  // The test loop
  while (state.KeepRunning()) {
    test = pbezierTri.DeCasteljau(d,c,Vector<float,3>(1,0,0));
  }

}
BENCHMARK(BM_BezierTriangle_deCasteljau_d1);


static void BM_BezierTriangle_deCasteljau_d2(benchmark::State& state)
{
  DVector<Vector<float,3>> c;
  int d = 2;
  c.push_back(GMlib::Vector<float,3>(0.f,0.f,0.f));
  c.push_back(GMlib::Vector<float,3>(1.5f,0.f,0.f));
  c.push_back(GMlib::Vector<float,3>(0.75f,1.5f,0.f));
  c.push_back(GMlib::Vector<float,3>(3.0f,0.f,0.f));
  c.push_back(GMlib::Vector<float,3>(2.25f,1.5f,0.f));
  c.push_back(GMlib::Vector<float,3>(1.5f,3.f,0.f));

  auto pbezierTri = PBezierTriangleDeCasteljau<float>(c);

  Vector<float,3> test;

  // The test loop
  while (state.KeepRunning()) {
    test = pbezierTri.DeCasteljau(d,c,Vector<float,3>(1,0,0));
  }

}
BENCHMARK(BM_BezierTriangle_deCasteljau_d2);


static void BM_BezierTriangle_deCasteljau_d3(benchmark::State& state)
{
  DVector<Vector<float,3>> c;
  int d = 3;
  c.push_back(GMlib::Vector<float,3>(0.f,0.f,1.f));
  c.push_back(GMlib::Vector<float,3>(1.f,0.f,0.f));
  c.push_back(GMlib::Vector<float,3>(0.5f,1.f,0.f));
  c.push_back(GMlib::Vector<float,3>(2.f,0.f,0.f));
  c.push_back(GMlib::Vector<float,3>(1.5f,1.f,0.f));
  c.push_back(GMlib::Vector<float,3>(1.f,2.f,0.f));
  c.push_back(GMlib::Vector<float,3>(3.0f,0.f,1.f));
  c.push_back(GMlib::Vector<float,3>(2.5f,1.f,0.f));
  c.push_back(GMlib::Vector<float,3>(2.f,2.f,0.f));
  c.push_back(GMlib::Vector<float,3>(1.5f,3.f,1.f));

  auto pbezierTri = PBezierTriangleDeCasteljau<float>(c);

  Vector<float,3> test;

  // The test loop
  while (state.KeepRunning()) {
    test = pbezierTri.DeCasteljau(d,c,Vector<float,3>(1,0,0));
  }

}
BENCHMARK(BM_BezierTriangle_deCasteljau_d3);


static void BM_BezierTriangle_deCasteljau_d4(benchmark::State& state)
{
  DVector<Vector<float,3>> c;
  int d = 4;
  c.push_back(GMlib::Vector<float,3>(0.f,0.f,0.f));
  c.push_back(GMlib::Vector<float,3>(1.f,0.f,0.f));
  c.push_back(GMlib::Vector<float,3>(0.5f,1.f,0.f));
  c.push_back(GMlib::Vector<float,3>(2.f,0.f,0.f));
  c.push_back(GMlib::Vector<float,3>(1.5f,1.f,0.f));
  c.push_back(GMlib::Vector<float,3>(1.f,2.f,0.f));
  c.push_back(GMlib::Vector<float,3>(3.0f,0.f,0.f));
  c.push_back(GMlib::Vector<float,3>(2.5f,1.f,0.f));
  c.push_back(GMlib::Vector<float,3>(2.f,2.f,0.f));
  c.push_back(GMlib::Vector<float,3>(1.5f,3.f,0.f));
  c.push_back(GMlib::Vector<float,3>(4.f,0.f,0.f));
  c.push_back(GMlib::Vector<float,3>(3.5f,1.f,0.f));
  c.push_back(GMlib::Vector<float,3>(3.f,2.f,0.f));
  c.push_back(GMlib::Vector<float,3>(2.5f,3.f,0.f));
  c.push_back(GMlib::Vector<float,3>(2.f,4.f,0.f));

  auto pbezierTri = PBezierTriangleDeCasteljau<float>(c);

  Vector<float,3> test;

  // The test loop
  while (state.KeepRunning()) {
    test = pbezierTri.DeCasteljau(d,c,Vector<float,3>(1,0,0));
  }

}
BENCHMARK(BM_BezierTriangle_deCasteljau_d4);


static void BM_BezierTriangle_deCasteljau_d5(benchmark::State& state)
{
  DVector<Vector<float,3>> c;
  int d = 5;
  c.push_back(GMlib::Vector<float,3>(0.f,0.f,0.f));
  c.push_back(GMlib::Vector<float,3>(1.f,0.f,0.f));
  c.push_back(GMlib::Vector<float,3>(0.5f,1.f,0.f));
  c.push_back(GMlib::Vector<float,3>(2.f,0.f,0.f));
  c.push_back(GMlib::Vector<float,3>(1.5f,1.f,0.f));
  c.push_back(GMlib::Vector<float,3>(1.f,2.f,0.f));
  c.push_back(GMlib::Vector<float,3>(3.0f,0.f,0.f));
  c.push_back(GMlib::Vector<float,3>(2.5f,1.f,0.f));
  c.push_back(GMlib::Vector<float,3>(2.f,2.f,0.f));
  c.push_back(GMlib::Vector<float,3>(1.5f,3.f,0.f));
  c.push_back(GMlib::Vector<float,3>(4.f,0.f,0.f));
  c.push_back(GMlib::Vector<float,3>(3.5f,1.f,0.f));
  c.push_back(GMlib::Vector<float,3>(3.f,2.f,0.f));
  c.push_back(GMlib::Vector<float,3>(2.5f,3.f,0.f));
  c.push_back(GMlib::Vector<float,3>(2.f,4.f,0.f));
  c.push_back(GMlib::Vector<float,3>(1.5f,3.f,0.f));
  c.push_back(GMlib::Vector<float,3>(4.f,0.f,0.f));
  c.push_back(GMlib::Vector<float,3>(3.5f,1.f,0.f));
  c.push_back(GMlib::Vector<float,3>(3.f,2.f,0.f));
  c.push_back(GMlib::Vector<float,3>(2.5f,3.f,0.f));
  c.push_back(GMlib::Vector<float,3>(2.f,4.f,0.f));

  auto pbezierTri = PBezierTriangleDeCasteljau<float>(c);

  Vector<float,3> test;

  // The test loop
  while (state.KeepRunning()) {
    test = pbezierTri.DeCasteljau(d,c,Vector<float,3>(1,0,0));
  }

}
BENCHMARK(BM_BezierTriangle_deCasteljau_d5);


static void BM_BezierTriangle_deCasteljau_d6(benchmark::State& state)
{
  DVector<Vector<float,3>> c;
  int d = 6;
  c.push_back(GMlib::Vector<float,3>(0.f,0.f,0.f));
  c.push_back(GMlib::Vector<float,3>(1.f,0.f,0.f));
  c.push_back(GMlib::Vector<float,3>(0.5f,1.f,0.f));
  c.push_back(GMlib::Vector<float,3>(2.f,0.f,0.f));
  c.push_back(GMlib::Vector<float,3>(1.5f,1.f,0.f));
  c.push_back(GMlib::Vector<float,3>(1.f,2.f,0.f));
  c.push_back(GMlib::Vector<float,3>(3.0f,0.f,0.f));
  c.push_back(GMlib::Vector<float,3>(2.5f,1.f,0.f));
  c.push_back(GMlib::Vector<float,3>(2.f,2.f,0.f));
  c.push_back(GMlib::Vector<float,3>(1.5f,3.f,0.f));
  c.push_back(GMlib::Vector<float,3>(4.f,0.f,0.f));
  c.push_back(GMlib::Vector<float,3>(3.5f,1.f,0.f));
  c.push_back(GMlib::Vector<float,3>(3.f,2.f,0.f));
  c.push_back(GMlib::Vector<float,3>(2.5f,3.f,0.f));
  c.push_back(GMlib::Vector<float,3>(2.f,4.f,0.f));
  c.push_back(GMlib::Vector<float,3>(1.5f,3.f,0.f));
  c.push_back(GMlib::Vector<float,3>(4.f,0.f,0.f));
  c.push_back(GMlib::Vector<float,3>(3.5f,1.f,0.f));
  c.push_back(GMlib::Vector<float,3>(3.f,2.f,0.f));
  c.push_back(GMlib::Vector<float,3>(2.5f,3.f,0.f));
  c.push_back(GMlib::Vector<float,3>(2.f,4.f,0.f));
  c.push_back(GMlib::Vector<float,3>(2.f,4.f,0.f));
  c.push_back(GMlib::Vector<float,3>(1.5f,3.f,0.f));
  c.push_back(GMlib::Vector<float,3>(4.f,0.f,0.f));
  c.push_back(GMlib::Vector<float,3>(3.5f,1.f,0.f));
  c.push_back(GMlib::Vector<float,3>(3.f,2.f,0.f));
  c.push_back(GMlib::Vector<float,3>(2.5f,3.f,0.f));
  c.push_back(GMlib::Vector<float,3>(2.f,4.f,0.f));

  auto pbezierTri = PBezierTriangleDeCasteljau<float>(c);

  Vector<float,3> test;

  // The test loop
  while (state.KeepRunning()) {
    test = pbezierTri.DeCasteljau(d,c,Vector<float,3>(1,0,0));
  }

}
BENCHMARK(BM_BezierTriangle_deCasteljau_d6);


static void BM_BezierTriangle_deCasteljau_d7(benchmark::State& state)
{
  DVector<Vector<float,3>> c;
  int d = 7;
  c.push_back(GMlib::Vector<float,3>(0.f,0.f,0.f));
  c.push_back(GMlib::Vector<float,3>(1.f,0.f,0.f));
  c.push_back(GMlib::Vector<float,3>(0.5f,1.f,0.f));
  c.push_back(GMlib::Vector<float,3>(2.f,0.f,0.f));
  c.push_back(GMlib::Vector<float,3>(1.5f,1.f,0.f));
  c.push_back(GMlib::Vector<float,3>(1.f,2.f,0.f));
  c.push_back(GMlib::Vector<float,3>(3.0f,0.f,0.f));
  c.push_back(GMlib::Vector<float,3>(2.5f,1.f,0.f));
  c.push_back(GMlib::Vector<float,3>(2.f,2.f,0.f));
  c.push_back(GMlib::Vector<float,3>(1.5f,3.f,0.f));
  c.push_back(GMlib::Vector<float,3>(4.f,0.f,0.f));
  c.push_back(GMlib::Vector<float,3>(3.5f,1.f,0.f));
  c.push_back(GMlib::Vector<float,3>(3.f,2.f,0.f));
  c.push_back(GMlib::Vector<float,3>(2.5f,3.f,0.f));
  c.push_back(GMlib::Vector<float,3>(2.f,4.f,0.f));
  c.push_back(GMlib::Vector<float,3>(1.5f,3.f,0.f));
  c.push_back(GMlib::Vector<float,3>(4.f,0.f,0.f));
  c.push_back(GMlib::Vector<float,3>(3.5f,1.f,0.f));
  c.push_back(GMlib::Vector<float,3>(3.f,2.f,0.f));
  c.push_back(GMlib::Vector<float,3>(2.5f,3.f,0.f));
  c.push_back(GMlib::Vector<float,3>(2.f,4.f,0.f));
  c.push_back(GMlib::Vector<float,3>(2.f,4.f,0.f));
  c.push_back(GMlib::Vector<float,3>(1.5f,3.f,0.f));
  c.push_back(GMlib::Vector<float,3>(4.f,0.f,0.f));
  c.push_back(GMlib::Vector<float,3>(3.5f,1.f,0.f));
  c.push_back(GMlib::Vector<float,3>(3.f,2.f,0.f));
  c.push_back(GMlib::Vector<float,3>(2.5f,3.f,0.f));
  c.push_back(GMlib::Vector<float,3>(2.f,4.f,0.f));
  c.push_back(GMlib::Vector<float,3>(2.f,4.f,0.f));
  c.push_back(GMlib::Vector<float,3>(2.f,4.f,0.f));
  c.push_back(GMlib::Vector<float,3>(1.5f,3.f,0.f));
  c.push_back(GMlib::Vector<float,3>(4.f,0.f,0.f));
  c.push_back(GMlib::Vector<float,3>(3.5f,1.f,0.f));
  c.push_back(GMlib::Vector<float,3>(3.f,2.f,0.f));
  c.push_back(GMlib::Vector<float,3>(2.5f,3.f,0.f));
  c.push_back(GMlib::Vector<float,3>(2.f,4.f,0.f));

  auto pbezierTri = PBezierTriangleDeCasteljau<float>(c);

  Vector<float,3> test;

  // The test loop
  while (state.KeepRunning()) {
    test = pbezierTri.DeCasteljau(d,c,Vector<float,3>(1,0,0));
  }

}
BENCHMARK(BM_BezierTriangle_deCasteljau_d7);


static void BM_BezierTriangle_deCasteljau_d8(benchmark::State& state)
{
  DVector<Vector<float,3>> c;
  int d = 8;
  c.push_back(GMlib::Vector<float,3>(0.f,0.f,0.f));
  c.push_back(GMlib::Vector<float,3>(1.f,0.f,0.f));
  c.push_back(GMlib::Vector<float,3>(0.5f,1.f,0.f));
  c.push_back(GMlib::Vector<float,3>(2.f,0.f,0.f));
  c.push_back(GMlib::Vector<float,3>(1.5f,1.f,0.f));
  c.push_back(GMlib::Vector<float,3>(1.f,2.f,0.f));
  c.push_back(GMlib::Vector<float,3>(3.0f,0.f,0.f));
  c.push_back(GMlib::Vector<float,3>(2.5f,1.f,0.f));
  c.push_back(GMlib::Vector<float,3>(2.f,2.f,0.f));
  c.push_back(GMlib::Vector<float,3>(1.5f,3.f,0.f));
  c.push_back(GMlib::Vector<float,3>(4.f,0.f,0.f));
  c.push_back(GMlib::Vector<float,3>(3.5f,1.f,0.f));
  c.push_back(GMlib::Vector<float,3>(3.f,2.f,0.f));
  c.push_back(GMlib::Vector<float,3>(2.5f,3.f,0.f));
  c.push_back(GMlib::Vector<float,3>(2.f,4.f,0.f));
  c.push_back(GMlib::Vector<float,3>(1.5f,3.f,0.f));
  c.push_back(GMlib::Vector<float,3>(4.f,0.f,0.f));
  c.push_back(GMlib::Vector<float,3>(3.5f,1.f,0.f));
  c.push_back(GMlib::Vector<float,3>(3.f,2.f,0.f));
  c.push_back(GMlib::Vector<float,3>(2.5f,3.f,0.f));
  c.push_back(GMlib::Vector<float,3>(2.f,4.f,0.f));
  c.push_back(GMlib::Vector<float,3>(2.f,4.f,0.f));
  c.push_back(GMlib::Vector<float,3>(1.5f,3.f,0.f));
  c.push_back(GMlib::Vector<float,3>(4.f,0.f,0.f));
  c.push_back(GMlib::Vector<float,3>(3.5f,1.f,0.f));
  c.push_back(GMlib::Vector<float,3>(3.f,2.f,0.f));
  c.push_back(GMlib::Vector<float,3>(2.5f,3.f,0.f));
  c.push_back(GMlib::Vector<float,3>(2.f,4.f,0.f));
  c.push_back(GMlib::Vector<float,3>(2.f,4.f,0.f));
  c.push_back(GMlib::Vector<float,3>(2.f,4.f,0.f));
  c.push_back(GMlib::Vector<float,3>(1.5f,3.f,0.f));
  c.push_back(GMlib::Vector<float,3>(4.f,0.f,0.f));
  c.push_back(GMlib::Vector<float,3>(3.5f,1.f,0.f));
  c.push_back(GMlib::Vector<float,3>(3.f,2.f,0.f));
  c.push_back(GMlib::Vector<float,3>(2.5f,3.f,0.f));
  c.push_back(GMlib::Vector<float,3>(2.f,4.f,0.f));
  c.push_back(GMlib::Vector<float,3>(2.f,4.f,0.f));
  c.push_back(GMlib::Vector<float,3>(2.f,4.f,0.f));
  c.push_back(GMlib::Vector<float,3>(2.f,4.f,0.f));
  c.push_back(GMlib::Vector<float,3>(1.5f,3.f,0.f));
  c.push_back(GMlib::Vector<float,3>(4.f,0.f,0.f));
  c.push_back(GMlib::Vector<float,3>(3.5f,1.f,0.f));
  c.push_back(GMlib::Vector<float,3>(3.f,2.f,0.f));
  c.push_back(GMlib::Vector<float,3>(2.5f,3.f,0.f));
  c.push_back(GMlib::Vector<float,3>(2.f,4.f,0.f));

  auto pbezierTri = PBezierTriangleDeCasteljau<float>(c);

  Vector<float,3> test;

  // The test loop
  while (state.KeepRunning()) {
    test = pbezierTri.DeCasteljau(d,c,Vector<float,3>(1,0,0));
  }

}
BENCHMARK(BM_BezierTriangle_deCasteljau_d8);


static void BM_BezierTriangle_deCasteljau_d9(benchmark::State& state)
{
  DVector<Vector<float,3>> c;
  int d = 9;
  c.push_back(GMlib::Vector<float,3>(0.f,0.f,0.f));
  c.push_back(GMlib::Vector<float,3>(1.f,0.f,0.f));
  c.push_back(GMlib::Vector<float,3>(0.5f,1.f,0.f));
  c.push_back(GMlib::Vector<float,3>(2.f,0.f,0.f));
  c.push_back(GMlib::Vector<float,3>(1.5f,1.f,0.f));
  c.push_back(GMlib::Vector<float,3>(1.f,2.f,0.f));
  c.push_back(GMlib::Vector<float,3>(3.0f,0.f,0.f));
  c.push_back(GMlib::Vector<float,3>(2.5f,1.f,0.f));
  c.push_back(GMlib::Vector<float,3>(2.f,2.f,0.f));
  c.push_back(GMlib::Vector<float,3>(1.5f,3.f,0.f));
  c.push_back(GMlib::Vector<float,3>(4.f,0.f,0.f));
  c.push_back(GMlib::Vector<float,3>(3.5f,1.f,0.f));
  c.push_back(GMlib::Vector<float,3>(3.f,2.f,0.f));
  c.push_back(GMlib::Vector<float,3>(2.5f,3.f,0.f));
  c.push_back(GMlib::Vector<float,3>(2.f,4.f,0.f));
  c.push_back(GMlib::Vector<float,3>(1.5f,3.f,0.f));
  c.push_back(GMlib::Vector<float,3>(4.f,0.f,0.f));
  c.push_back(GMlib::Vector<float,3>(3.5f,1.f,0.f));
  c.push_back(GMlib::Vector<float,3>(3.f,2.f,0.f));
  c.push_back(GMlib::Vector<float,3>(2.5f,3.f,0.f));
  c.push_back(GMlib::Vector<float,3>(2.f,4.f,0.f));
  c.push_back(GMlib::Vector<float,3>(2.f,4.f,0.f));
  c.push_back(GMlib::Vector<float,3>(1.5f,3.f,0.f));
  c.push_back(GMlib::Vector<float,3>(4.f,0.f,0.f));
  c.push_back(GMlib::Vector<float,3>(3.5f,1.f,0.f));
  c.push_back(GMlib::Vector<float,3>(3.f,2.f,0.f));
  c.push_back(GMlib::Vector<float,3>(2.5f,3.f,0.f));
  c.push_back(GMlib::Vector<float,3>(2.f,4.f,0.f));
  c.push_back(GMlib::Vector<float,3>(2.f,4.f,0.f));
  c.push_back(GMlib::Vector<float,3>(2.f,4.f,0.f));
  c.push_back(GMlib::Vector<float,3>(1.5f,3.f,0.f));
  c.push_back(GMlib::Vector<float,3>(4.f,0.f,0.f));
  c.push_back(GMlib::Vector<float,3>(3.5f,1.f,0.f));
  c.push_back(GMlib::Vector<float,3>(3.f,2.f,0.f));
  c.push_back(GMlib::Vector<float,3>(2.5f,3.f,0.f));
  c.push_back(GMlib::Vector<float,3>(2.f,4.f,0.f));
  c.push_back(GMlib::Vector<float,3>(2.f,4.f,0.f));
  c.push_back(GMlib::Vector<float,3>(2.f,4.f,0.f));
  c.push_back(GMlib::Vector<float,3>(2.f,4.f,0.f));
  c.push_back(GMlib::Vector<float,3>(1.5f,3.f,0.f));
  c.push_back(GMlib::Vector<float,3>(4.f,0.f,0.f));
  c.push_back(GMlib::Vector<float,3>(3.5f,1.f,0.f));
  c.push_back(GMlib::Vector<float,3>(3.f,2.f,0.f));
  c.push_back(GMlib::Vector<float,3>(2.5f,3.f,0.f));
  c.push_back(GMlib::Vector<float,3>(2.f,4.f,0.f));
  c.push_back(GMlib::Vector<float,3>(2.f,4.f,0.f));
  c.push_back(GMlib::Vector<float,3>(2.f,4.f,0.f));
  c.push_back(GMlib::Vector<float,3>(2.f,4.f,0.f));
  c.push_back(GMlib::Vector<float,3>(2.f,4.f,0.f));
  c.push_back(GMlib::Vector<float,3>(1.5f,3.f,0.f));
  c.push_back(GMlib::Vector<float,3>(4.f,0.f,0.f));
  c.push_back(GMlib::Vector<float,3>(3.5f,1.f,0.f));
  c.push_back(GMlib::Vector<float,3>(3.f,2.f,0.f));
  c.push_back(GMlib::Vector<float,3>(2.5f,3.f,0.f));
  c.push_back(GMlib::Vector<float,3>(2.f,4.f,0.f));

  auto pbezierTri = PBezierTriangleDeCasteljau<float>(c);

  Vector<float,3> test;

  // The test loop
  while (state.KeepRunning()) {
    test = pbezierTri.DeCasteljau(d,c,Vector<float,3>(1,0,0));
  }

}
BENCHMARK(BM_BezierTriangle_deCasteljau_d9);


static void BM_BezierTriangle_deCasteljau_d10(benchmark::State& state)
{
  DVector<Vector<float,3>> c;
  int d = 10;
  c.push_back(GMlib::Vector<float,3>(0.f,0.f,0.f));
  c.push_back(GMlib::Vector<float,3>(1.f,0.f,0.f));
  c.push_back(GMlib::Vector<float,3>(0.5f,1.f,0.f));
  c.push_back(GMlib::Vector<float,3>(2.f,0.f,0.f));
  c.push_back(GMlib::Vector<float,3>(1.5f,1.f,0.f));
  c.push_back(GMlib::Vector<float,3>(1.f,2.f,0.f));
  c.push_back(GMlib::Vector<float,3>(3.0f,0.f,0.f));
  c.push_back(GMlib::Vector<float,3>(2.5f,1.f,0.f));
  c.push_back(GMlib::Vector<float,3>(2.f,2.f,0.f));
  c.push_back(GMlib::Vector<float,3>(1.5f,3.f,0.f));
  c.push_back(GMlib::Vector<float,3>(4.f,0.f,0.f));
  c.push_back(GMlib::Vector<float,3>(3.5f,1.f,0.f));
  c.push_back(GMlib::Vector<float,3>(3.f,2.f,0.f));
  c.push_back(GMlib::Vector<float,3>(2.5f,3.f,0.f));
  c.push_back(GMlib::Vector<float,3>(2.f,4.f,0.f));
  c.push_back(GMlib::Vector<float,3>(1.5f,3.f,0.f));
  c.push_back(GMlib::Vector<float,3>(4.f,0.f,0.f));
  c.push_back(GMlib::Vector<float,3>(3.5f,1.f,0.f));
  c.push_back(GMlib::Vector<float,3>(3.f,2.f,0.f));
  c.push_back(GMlib::Vector<float,3>(2.5f,3.f,0.f));
  c.push_back(GMlib::Vector<float,3>(2.f,4.f,0.f));
  c.push_back(GMlib::Vector<float,3>(2.f,4.f,0.f));
  c.push_back(GMlib::Vector<float,3>(1.5f,3.f,0.f));
  c.push_back(GMlib::Vector<float,3>(4.f,0.f,0.f));
  c.push_back(GMlib::Vector<float,3>(3.5f,1.f,0.f));
  c.push_back(GMlib::Vector<float,3>(3.f,2.f,0.f));
  c.push_back(GMlib::Vector<float,3>(2.5f,3.f,0.f));
  c.push_back(GMlib::Vector<float,3>(2.f,4.f,0.f));
  c.push_back(GMlib::Vector<float,3>(2.f,4.f,0.f));
  c.push_back(GMlib::Vector<float,3>(2.f,4.f,0.f));
  c.push_back(GMlib::Vector<float,3>(1.5f,3.f,0.f));
  c.push_back(GMlib::Vector<float,3>(4.f,0.f,0.f));
  c.push_back(GMlib::Vector<float,3>(3.5f,1.f,0.f));
  c.push_back(GMlib::Vector<float,3>(3.f,2.f,0.f));
  c.push_back(GMlib::Vector<float,3>(2.5f,3.f,0.f));
  c.push_back(GMlib::Vector<float,3>(2.f,4.f,0.f));
  c.push_back(GMlib::Vector<float,3>(2.f,4.f,0.f));
  c.push_back(GMlib::Vector<float,3>(2.f,4.f,0.f));
  c.push_back(GMlib::Vector<float,3>(2.f,4.f,0.f));
  c.push_back(GMlib::Vector<float,3>(1.5f,3.f,0.f));
  c.push_back(GMlib::Vector<float,3>(4.f,0.f,0.f));
  c.push_back(GMlib::Vector<float,3>(3.5f,1.f,0.f));
  c.push_back(GMlib::Vector<float,3>(3.f,2.f,0.f));
  c.push_back(GMlib::Vector<float,3>(2.5f,3.f,0.f));
  c.push_back(GMlib::Vector<float,3>(2.f,4.f,0.f));
  c.push_back(GMlib::Vector<float,3>(2.f,4.f,0.f));
  c.push_back(GMlib::Vector<float,3>(2.f,4.f,0.f));
  c.push_back(GMlib::Vector<float,3>(2.f,4.f,0.f));
  c.push_back(GMlib::Vector<float,3>(2.f,4.f,0.f));
  c.push_back(GMlib::Vector<float,3>(1.5f,3.f,0.f));
  c.push_back(GMlib::Vector<float,3>(4.f,0.f,0.f));
  c.push_back(GMlib::Vector<float,3>(3.5f,1.f,0.f));
  c.push_back(GMlib::Vector<float,3>(3.f,2.f,0.f));
  c.push_back(GMlib::Vector<float,3>(2.5f,3.f,0.f));
  c.push_back(GMlib::Vector<float,3>(2.f,4.f,0.f));
  c.push_back(GMlib::Vector<float,3>(2.f,4.f,0.f));
  c.push_back(GMlib::Vector<float,3>(2.f,4.f,0.f));
  c.push_back(GMlib::Vector<float,3>(2.f,4.f,0.f));
  c.push_back(GMlib::Vector<float,3>(2.f,4.f,0.f));
  c.push_back(GMlib::Vector<float,3>(2.f,4.f,0.f));
  c.push_back(GMlib::Vector<float,3>(1.5f,3.f,0.f));
  c.push_back(GMlib::Vector<float,3>(4.f,0.f,0.f));
  c.push_back(GMlib::Vector<float,3>(3.5f,1.f,0.f));
  c.push_back(GMlib::Vector<float,3>(3.f,2.f,0.f));
  c.push_back(GMlib::Vector<float,3>(2.5f,3.f,0.f));
  c.push_back(GMlib::Vector<float,3>(2.f,4.f,0.f));

  auto pbezierTri = PBezierTriangleDeCasteljau<float>(c);

  Vector<float,3> test;

  // The test loop
  while (state.KeepRunning()) {
    test = pbezierTri.DeCasteljau(d,c,Vector<float,3>(1,0,0));
  }

}
BENCHMARK(BM_BezierTriangle_deCasteljau_d10);


static void BM_BezierTriangle_index_d2(benchmark::State& state)
{
    int d = 2;
    DVector<Vector<float,3>> c;
    c.push_back(GMlib::Vector<float,3>(0.f,0.f,0.f));
    c.push_back(GMlib::Vector<float,3>(1.5f,0.f,0.f));
    c.push_back(GMlib::Vector<float,3>(0.75f,1.5f,0.f));
    c.push_back(GMlib::Vector<float,3>(3.0f,0.f,0.f));
    c.push_back(GMlib::Vector<float,3>(2.25f,1.5f,0.f));
    c.push_back(GMlib::Vector<float,3>(1.5f,3.f,0.f));
  // The test loop
  while (state.KeepRunning()) {
    index(d,c);
  }

}
BENCHMARK(BM_BezierTriangle_index_d2);


static void BM_BezierTriangle_index_d3(benchmark::State& state)
{
      int d = 3;
      DVector<Vector<float,3>> c;
      c.push_back(GMlib::Vector<float,3>(0.f,0.f,1.f));
      c.push_back(GMlib::Vector<float,3>(1.f,0.f,0.f));
      c.push_back(GMlib::Vector<float,3>(0.5f,1.f,0.f));
      c.push_back(GMlib::Vector<float,3>(2.f,0.f,0.f));
      c.push_back(GMlib::Vector<float,3>(1.5f,1.f,0.f));
      c.push_back(GMlib::Vector<float,3>(1.f,2.f,0.f));
      c.push_back(GMlib::Vector<float,3>(3.0f,0.f,1.f));
      c.push_back(GMlib::Vector<float,3>(2.5f,1.f,0.f));
      c.push_back(GMlib::Vector<float,3>(2.f,2.f,0.f));
      c.push_back(GMlib::Vector<float,3>(1.5f,3.f,1.f));
  // The test loop
  while (state.KeepRunning()) {
    index(d,c);
  }

}
BENCHMARK(BM_BezierTriangle_index_d3);


static void BM_BezierTriangle_index_d4(benchmark::State& state)
{
    int d = 4;
    DVector<Vector<float,3>> c;
    c.push_back(GMlib::Vector<float,3>(0.f,0.f,0.f));
    c.push_back(GMlib::Vector<float,3>(1.f,0.f,0.f));
    c.push_back(GMlib::Vector<float,3>(0.5f,1.f,0.f));
    c.push_back(GMlib::Vector<float,3>(2.f,0.f,0.f));
    c.push_back(GMlib::Vector<float,3>(1.5f,1.f,0.f));
    c.push_back(GMlib::Vector<float,3>(1.f,2.f,0.f));
    c.push_back(GMlib::Vector<float,3>(3.0f,0.f,0.f));
    c.push_back(GMlib::Vector<float,3>(2.5f,1.f,0.f));
    c.push_back(GMlib::Vector<float,3>(2.f,2.f,0.f));
    c.push_back(GMlib::Vector<float,3>(1.5f,3.f,0.f));
    c.push_back(GMlib::Vector<float,3>(4.f,0.f,0.f));
    c.push_back(GMlib::Vector<float,3>(3.5f,1.f,0.f));
    c.push_back(GMlib::Vector<float,3>(3.f,2.f,0.f));
    c.push_back(GMlib::Vector<float,3>(2.5f,3.f,0.f));
    c.push_back(GMlib::Vector<float,3>(2.f,4.f,0.f));
  // The test loop
  while (state.KeepRunning()) {
    index(d,c);
  }

}
BENCHMARK(BM_BezierTriangle_index_d4);


static void BM_BezierTriangle_index_d5(benchmark::State& state)
{
    int d = 5;
    DVector<Vector<float,3>> c;
    c.push_back(GMlib::Vector<float,3>(0.f,0.f,0.f));
    c.push_back(GMlib::Vector<float,3>(1.f,0.f,0.f));
    c.push_back(GMlib::Vector<float,3>(0.5f,1.f,0.f));
    c.push_back(GMlib::Vector<float,3>(2.f,0.f,0.f));
    c.push_back(GMlib::Vector<float,3>(1.5f,1.f,0.f));
    c.push_back(GMlib::Vector<float,3>(1.f,2.f,0.f));
    c.push_back(GMlib::Vector<float,3>(3.0f,0.f,0.f));
    c.push_back(GMlib::Vector<float,3>(2.5f,1.f,0.f));
    c.push_back(GMlib::Vector<float,3>(2.f,2.f,0.f));
    c.push_back(GMlib::Vector<float,3>(1.5f,3.f,0.f));
    c.push_back(GMlib::Vector<float,3>(4.f,0.f,0.f));
    c.push_back(GMlib::Vector<float,3>(3.5f,1.f,0.f));
    c.push_back(GMlib::Vector<float,3>(3.f,2.f,0.f));
    c.push_back(GMlib::Vector<float,3>(2.5f,3.f,0.f));
    c.push_back(GMlib::Vector<float,3>(2.f,4.f,0.f));
    c.push_back(GMlib::Vector<float,3>(1.5f,3.f,0.f));
    c.push_back(GMlib::Vector<float,3>(4.f,0.f,0.f));
    c.push_back(GMlib::Vector<float,3>(3.5f,1.f,0.f));
    c.push_back(GMlib::Vector<float,3>(3.f,2.f,0.f));
    c.push_back(GMlib::Vector<float,3>(2.5f,3.f,0.f));
    c.push_back(GMlib::Vector<float,3>(2.f,4.f,0.f));
  // The test loop
  while (state.KeepRunning()) {
    index(d,c);
  }

}
BENCHMARK(BM_BezierTriangle_index_d5);


static void BM_BezierTriangle_index_d6(benchmark::State& state)
{
    int d = 6;
    DVector<Vector<float,3>> c;
    c.push_back(GMlib::Vector<float,3>(0.f,0.f,0.f));
    c.push_back(GMlib::Vector<float,3>(1.f,0.f,0.f));
    c.push_back(GMlib::Vector<float,3>(0.5f,1.f,0.f));
    c.push_back(GMlib::Vector<float,3>(2.f,0.f,0.f));
    c.push_back(GMlib::Vector<float,3>(1.5f,1.f,0.f));
    c.push_back(GMlib::Vector<float,3>(1.f,2.f,0.f));
    c.push_back(GMlib::Vector<float,3>(3.0f,0.f,0.f));
    c.push_back(GMlib::Vector<float,3>(2.5f,1.f,0.f));
    c.push_back(GMlib::Vector<float,3>(2.f,2.f,0.f));
    c.push_back(GMlib::Vector<float,3>(1.5f,3.f,0.f));
    c.push_back(GMlib::Vector<float,3>(4.f,0.f,0.f));
    c.push_back(GMlib::Vector<float,3>(3.5f,1.f,0.f));
    c.push_back(GMlib::Vector<float,3>(3.f,2.f,0.f));
    c.push_back(GMlib::Vector<float,3>(2.5f,3.f,0.f));
    c.push_back(GMlib::Vector<float,3>(2.f,4.f,0.f));
    c.push_back(GMlib::Vector<float,3>(1.5f,3.f,0.f));
    c.push_back(GMlib::Vector<float,3>(4.f,0.f,0.f));
    c.push_back(GMlib::Vector<float,3>(3.5f,1.f,0.f));
    c.push_back(GMlib::Vector<float,3>(3.f,2.f,0.f));
    c.push_back(GMlib::Vector<float,3>(2.5f,3.f,0.f));
    c.push_back(GMlib::Vector<float,3>(2.f,4.f,0.f));
    c.push_back(GMlib::Vector<float,3>(2.f,4.f,0.f));
    c.push_back(GMlib::Vector<float,3>(1.5f,3.f,0.f));
    c.push_back(GMlib::Vector<float,3>(4.f,0.f,0.f));
    c.push_back(GMlib::Vector<float,3>(3.5f,1.f,0.f));
    c.push_back(GMlib::Vector<float,3>(3.f,2.f,0.f));
    c.push_back(GMlib::Vector<float,3>(2.5f,3.f,0.f));
    c.push_back(GMlib::Vector<float,3>(2.f,4.f,0.f));
  // The test loop
  while (state.KeepRunning()) {
    index(d,c);
  }

}
BENCHMARK(BM_BezierTriangle_index_d6);


static void BM_BezierTriangle_index_d7(benchmark::State& state)
{
    int d = 7;
    DVector<Vector<float,3>> c;
    c.push_back(GMlib::Vector<float,3>(0.f,0.f,0.f));
    c.push_back(GMlib::Vector<float,3>(1.f,0.f,0.f));
    c.push_back(GMlib::Vector<float,3>(0.5f,1.f,0.f));
    c.push_back(GMlib::Vector<float,3>(2.f,0.f,0.f));
    c.push_back(GMlib::Vector<float,3>(1.5f,1.f,0.f));
    c.push_back(GMlib::Vector<float,3>(1.f,2.f,0.f));
    c.push_back(GMlib::Vector<float,3>(3.0f,0.f,0.f));
    c.push_back(GMlib::Vector<float,3>(2.5f,1.f,0.f));
    c.push_back(GMlib::Vector<float,3>(2.f,2.f,0.f));
    c.push_back(GMlib::Vector<float,3>(1.5f,3.f,0.f));
    c.push_back(GMlib::Vector<float,3>(4.f,0.f,0.f));
    c.push_back(GMlib::Vector<float,3>(3.5f,1.f,0.f));
    c.push_back(GMlib::Vector<float,3>(3.f,2.f,0.f));
    c.push_back(GMlib::Vector<float,3>(2.5f,3.f,0.f));
    c.push_back(GMlib::Vector<float,3>(2.f,4.f,0.f));
    c.push_back(GMlib::Vector<float,3>(1.5f,3.f,0.f));
    c.push_back(GMlib::Vector<float,3>(4.f,0.f,0.f));
    c.push_back(GMlib::Vector<float,3>(3.5f,1.f,0.f));
    c.push_back(GMlib::Vector<float,3>(3.f,2.f,0.f));
    c.push_back(GMlib::Vector<float,3>(2.5f,3.f,0.f));
    c.push_back(GMlib::Vector<float,3>(2.f,4.f,0.f));
    c.push_back(GMlib::Vector<float,3>(2.f,4.f,0.f));
    c.push_back(GMlib::Vector<float,3>(1.5f,3.f,0.f));
    c.push_back(GMlib::Vector<float,3>(4.f,0.f,0.f));
    c.push_back(GMlib::Vector<float,3>(3.5f,1.f,0.f));
    c.push_back(GMlib::Vector<float,3>(3.f,2.f,0.f));
    c.push_back(GMlib::Vector<float,3>(2.5f,3.f,0.f));
    c.push_back(GMlib::Vector<float,3>(2.f,4.f,0.f));
    c.push_back(GMlib::Vector<float,3>(2.f,4.f,0.f));
    c.push_back(GMlib::Vector<float,3>(2.f,4.f,0.f));
    c.push_back(GMlib::Vector<float,3>(1.5f,3.f,0.f));
    c.push_back(GMlib::Vector<float,3>(4.f,0.f,0.f));
    c.push_back(GMlib::Vector<float,3>(3.5f,1.f,0.f));
    c.push_back(GMlib::Vector<float,3>(3.f,2.f,0.f));
    c.push_back(GMlib::Vector<float,3>(2.5f,3.f,0.f));
    c.push_back(GMlib::Vector<float,3>(2.f,4.f,0.f));
  // The test loop
  while (state.KeepRunning()) {
    index(d,c);
  }

}
BENCHMARK(BM_BezierTriangle_index_d7);


static void BM_BezierTriangle_index_d8(benchmark::State& state)
{
    int d = 8;
    DVector<Vector<float,3>> c;
    c.push_back(GMlib::Vector<float,3>(0.f,0.f,0.f));
    c.push_back(GMlib::Vector<float,3>(1.f,0.f,0.f));
    c.push_back(GMlib::Vector<float,3>(0.5f,1.f,0.f));
    c.push_back(GMlib::Vector<float,3>(2.f,0.f,0.f));
    c.push_back(GMlib::Vector<float,3>(1.5f,1.f,0.f));
    c.push_back(GMlib::Vector<float,3>(1.f,2.f,0.f));
    c.push_back(GMlib::Vector<float,3>(3.0f,0.f,0.f));
    c.push_back(GMlib::Vector<float,3>(2.5f,1.f,0.f));
    c.push_back(GMlib::Vector<float,3>(2.f,2.f,0.f));
    c.push_back(GMlib::Vector<float,3>(1.5f,3.f,0.f));
    c.push_back(GMlib::Vector<float,3>(4.f,0.f,0.f));
    c.push_back(GMlib::Vector<float,3>(3.5f,1.f,0.f));
    c.push_back(GMlib::Vector<float,3>(3.f,2.f,0.f));
    c.push_back(GMlib::Vector<float,3>(2.5f,3.f,0.f));
    c.push_back(GMlib::Vector<float,3>(2.f,4.f,0.f));
    c.push_back(GMlib::Vector<float,3>(1.5f,3.f,0.f));
    c.push_back(GMlib::Vector<float,3>(4.f,0.f,0.f));
    c.push_back(GMlib::Vector<float,3>(3.5f,1.f,0.f));
    c.push_back(GMlib::Vector<float,3>(3.f,2.f,0.f));
    c.push_back(GMlib::Vector<float,3>(2.5f,3.f,0.f));
    c.push_back(GMlib::Vector<float,3>(2.f,4.f,0.f));
    c.push_back(GMlib::Vector<float,3>(2.f,4.f,0.f));
    c.push_back(GMlib::Vector<float,3>(1.5f,3.f,0.f));
    c.push_back(GMlib::Vector<float,3>(4.f,0.f,0.f));
    c.push_back(GMlib::Vector<float,3>(3.5f,1.f,0.f));
    c.push_back(GMlib::Vector<float,3>(3.f,2.f,0.f));
    c.push_back(GMlib::Vector<float,3>(2.5f,3.f,0.f));
    c.push_back(GMlib::Vector<float,3>(2.f,4.f,0.f));
    c.push_back(GMlib::Vector<float,3>(2.f,4.f,0.f));
    c.push_back(GMlib::Vector<float,3>(2.f,4.f,0.f));
    c.push_back(GMlib::Vector<float,3>(1.5f,3.f,0.f));
    c.push_back(GMlib::Vector<float,3>(4.f,0.f,0.f));
    c.push_back(GMlib::Vector<float,3>(3.5f,1.f,0.f));
    c.push_back(GMlib::Vector<float,3>(3.f,2.f,0.f));
    c.push_back(GMlib::Vector<float,3>(2.5f,3.f,0.f));
    c.push_back(GMlib::Vector<float,3>(2.f,4.f,0.f));
    c.push_back(GMlib::Vector<float,3>(2.f,4.f,0.f));
    c.push_back(GMlib::Vector<float,3>(2.f,4.f,0.f));
    c.push_back(GMlib::Vector<float,3>(2.f,4.f,0.f));
    c.push_back(GMlib::Vector<float,3>(1.5f,3.f,0.f));
    c.push_back(GMlib::Vector<float,3>(4.f,0.f,0.f));
    c.push_back(GMlib::Vector<float,3>(3.5f,1.f,0.f));
    c.push_back(GMlib::Vector<float,3>(3.f,2.f,0.f));
    c.push_back(GMlib::Vector<float,3>(2.5f,3.f,0.f));
    c.push_back(GMlib::Vector<float,3>(2.f,4.f,0.f));
  // The test loop
  while (state.KeepRunning()) {
    index(d,c);
  }

}
BENCHMARK(BM_BezierTriangle_index_d8);


static void BM_BezierTriangle_index_d9(benchmark::State& state)
{
    int d = 9;
    DVector<Vector<float,3>> c;
    c.push_back(GMlib::Vector<float,3>(0.f,0.f,0.f));
    c.push_back(GMlib::Vector<float,3>(1.f,0.f,0.f));
    c.push_back(GMlib::Vector<float,3>(0.5f,1.f,0.f));
    c.push_back(GMlib::Vector<float,3>(2.f,0.f,0.f));
    c.push_back(GMlib::Vector<float,3>(1.5f,1.f,0.f));
    c.push_back(GMlib::Vector<float,3>(1.f,2.f,0.f));
    c.push_back(GMlib::Vector<float,3>(3.0f,0.f,0.f));
    c.push_back(GMlib::Vector<float,3>(2.5f,1.f,0.f));
    c.push_back(GMlib::Vector<float,3>(2.f,2.f,0.f));
    c.push_back(GMlib::Vector<float,3>(1.5f,3.f,0.f));
    c.push_back(GMlib::Vector<float,3>(4.f,0.f,0.f));
    c.push_back(GMlib::Vector<float,3>(3.5f,1.f,0.f));
    c.push_back(GMlib::Vector<float,3>(3.f,2.f,0.f));
    c.push_back(GMlib::Vector<float,3>(2.5f,3.f,0.f));
    c.push_back(GMlib::Vector<float,3>(2.f,4.f,0.f));
    c.push_back(GMlib::Vector<float,3>(1.5f,3.f,0.f));
    c.push_back(GMlib::Vector<float,3>(4.f,0.f,0.f));
    c.push_back(GMlib::Vector<float,3>(3.5f,1.f,0.f));
    c.push_back(GMlib::Vector<float,3>(3.f,2.f,0.f));
    c.push_back(GMlib::Vector<float,3>(2.5f,3.f,0.f));
    c.push_back(GMlib::Vector<float,3>(2.f,4.f,0.f));
    c.push_back(GMlib::Vector<float,3>(2.f,4.f,0.f));
    c.push_back(GMlib::Vector<float,3>(1.5f,3.f,0.f));
    c.push_back(GMlib::Vector<float,3>(4.f,0.f,0.f));
    c.push_back(GMlib::Vector<float,3>(3.5f,1.f,0.f));
    c.push_back(GMlib::Vector<float,3>(3.f,2.f,0.f));
    c.push_back(GMlib::Vector<float,3>(2.5f,3.f,0.f));
    c.push_back(GMlib::Vector<float,3>(2.f,4.f,0.f));
    c.push_back(GMlib::Vector<float,3>(2.f,4.f,0.f));
    c.push_back(GMlib::Vector<float,3>(2.f,4.f,0.f));
    c.push_back(GMlib::Vector<float,3>(1.5f,3.f,0.f));
    c.push_back(GMlib::Vector<float,3>(4.f,0.f,0.f));
    c.push_back(GMlib::Vector<float,3>(3.5f,1.f,0.f));
    c.push_back(GMlib::Vector<float,3>(3.f,2.f,0.f));
    c.push_back(GMlib::Vector<float,3>(2.5f,3.f,0.f));
    c.push_back(GMlib::Vector<float,3>(2.f,4.f,0.f));
    c.push_back(GMlib::Vector<float,3>(2.f,4.f,0.f));
    c.push_back(GMlib::Vector<float,3>(2.f,4.f,0.f));
    c.push_back(GMlib::Vector<float,3>(2.f,4.f,0.f));
    c.push_back(GMlib::Vector<float,3>(1.5f,3.f,0.f));
    c.push_back(GMlib::Vector<float,3>(4.f,0.f,0.f));
    c.push_back(GMlib::Vector<float,3>(3.5f,1.f,0.f));
    c.push_back(GMlib::Vector<float,3>(3.f,2.f,0.f));
    c.push_back(GMlib::Vector<float,3>(2.5f,3.f,0.f));
    c.push_back(GMlib::Vector<float,3>(2.f,4.f,0.f));
    c.push_back(GMlib::Vector<float,3>(2.f,4.f,0.f));
    c.push_back(GMlib::Vector<float,3>(2.f,4.f,0.f));
    c.push_back(GMlib::Vector<float,3>(2.f,4.f,0.f));
    c.push_back(GMlib::Vector<float,3>(2.f,4.f,0.f));
    c.push_back(GMlib::Vector<float,3>(1.5f,3.f,0.f));
    c.push_back(GMlib::Vector<float,3>(4.f,0.f,0.f));
    c.push_back(GMlib::Vector<float,3>(3.5f,1.f,0.f));
    c.push_back(GMlib::Vector<float,3>(3.f,2.f,0.f));
    c.push_back(GMlib::Vector<float,3>(2.5f,3.f,0.f));
    c.push_back(GMlib::Vector<float,3>(2.f,4.f,0.f));
  // The test loop
  while (state.KeepRunning()) {
    index(d,c);
  }

}
BENCHMARK(BM_BezierTriangle_index_d9);


static void BM_BezierTriangle_index_d10(benchmark::State& state)
{
    int d = 10;
    DVector<Vector<float,3>> c;
    c.push_back(GMlib::Vector<float,3>(0.f,0.f,0.f));
    c.push_back(GMlib::Vector<float,3>(1.f,0.f,0.f));
    c.push_back(GMlib::Vector<float,3>(0.5f,1.f,0.f));
    c.push_back(GMlib::Vector<float,3>(2.f,0.f,0.f));
    c.push_back(GMlib::Vector<float,3>(1.5f,1.f,0.f));
    c.push_back(GMlib::Vector<float,3>(1.f,2.f,0.f));
    c.push_back(GMlib::Vector<float,3>(3.0f,0.f,0.f));
    c.push_back(GMlib::Vector<float,3>(2.5f,1.f,0.f));
    c.push_back(GMlib::Vector<float,3>(2.f,2.f,0.f));
    c.push_back(GMlib::Vector<float,3>(1.5f,3.f,0.f));
    c.push_back(GMlib::Vector<float,3>(4.f,0.f,0.f));
    c.push_back(GMlib::Vector<float,3>(3.5f,1.f,0.f));
    c.push_back(GMlib::Vector<float,3>(3.f,2.f,0.f));
    c.push_back(GMlib::Vector<float,3>(2.5f,3.f,0.f));
    c.push_back(GMlib::Vector<float,3>(2.f,4.f,0.f));
    c.push_back(GMlib::Vector<float,3>(1.5f,3.f,0.f));
    c.push_back(GMlib::Vector<float,3>(4.f,0.f,0.f));
    c.push_back(GMlib::Vector<float,3>(3.5f,1.f,0.f));
    c.push_back(GMlib::Vector<float,3>(3.f,2.f,0.f));
    c.push_back(GMlib::Vector<float,3>(2.5f,3.f,0.f));
    c.push_back(GMlib::Vector<float,3>(2.f,4.f,0.f));
    c.push_back(GMlib::Vector<float,3>(2.f,4.f,0.f));
    c.push_back(GMlib::Vector<float,3>(1.5f,3.f,0.f));
    c.push_back(GMlib::Vector<float,3>(4.f,0.f,0.f));
    c.push_back(GMlib::Vector<float,3>(3.5f,1.f,0.f));
    c.push_back(GMlib::Vector<float,3>(3.f,2.f,0.f));
    c.push_back(GMlib::Vector<float,3>(2.5f,3.f,0.f));
    c.push_back(GMlib::Vector<float,3>(2.f,4.f,0.f));
    c.push_back(GMlib::Vector<float,3>(2.f,4.f,0.f));
    c.push_back(GMlib::Vector<float,3>(2.f,4.f,0.f));
    c.push_back(GMlib::Vector<float,3>(1.5f,3.f,0.f));
    c.push_back(GMlib::Vector<float,3>(4.f,0.f,0.f));
    c.push_back(GMlib::Vector<float,3>(3.5f,1.f,0.f));
    c.push_back(GMlib::Vector<float,3>(3.f,2.f,0.f));
    c.push_back(GMlib::Vector<float,3>(2.5f,3.f,0.f));
    c.push_back(GMlib::Vector<float,3>(2.f,4.f,0.f));
    c.push_back(GMlib::Vector<float,3>(2.f,4.f,0.f));
    c.push_back(GMlib::Vector<float,3>(2.f,4.f,0.f));
    c.push_back(GMlib::Vector<float,3>(2.f,4.f,0.f));
    c.push_back(GMlib::Vector<float,3>(1.5f,3.f,0.f));
    c.push_back(GMlib::Vector<float,3>(4.f,0.f,0.f));
    c.push_back(GMlib::Vector<float,3>(3.5f,1.f,0.f));
    c.push_back(GMlib::Vector<float,3>(3.f,2.f,0.f));
    c.push_back(GMlib::Vector<float,3>(2.5f,3.f,0.f));
    c.push_back(GMlib::Vector<float,3>(2.f,4.f,0.f));
    c.push_back(GMlib::Vector<float,3>(2.f,4.f,0.f));
    c.push_back(GMlib::Vector<float,3>(2.f,4.f,0.f));
    c.push_back(GMlib::Vector<float,3>(2.f,4.f,0.f));
    c.push_back(GMlib::Vector<float,3>(2.f,4.f,0.f));
    c.push_back(GMlib::Vector<float,3>(1.5f,3.f,0.f));
    c.push_back(GMlib::Vector<float,3>(4.f,0.f,0.f));
    c.push_back(GMlib::Vector<float,3>(3.5f,1.f,0.f));
    c.push_back(GMlib::Vector<float,3>(3.f,2.f,0.f));
    c.push_back(GMlib::Vector<float,3>(2.5f,3.f,0.f));
    c.push_back(GMlib::Vector<float,3>(2.f,4.f,0.f));
    c.push_back(GMlib::Vector<float,3>(2.f,4.f,0.f));
    c.push_back(GMlib::Vector<float,3>(2.f,4.f,0.f));
    c.push_back(GMlib::Vector<float,3>(2.f,4.f,0.f));
    c.push_back(GMlib::Vector<float,3>(2.f,4.f,0.f));
    c.push_back(GMlib::Vector<float,3>(2.f,4.f,0.f));
    c.push_back(GMlib::Vector<float,3>(1.5f,3.f,0.f));
    c.push_back(GMlib::Vector<float,3>(4.f,0.f,0.f));
    c.push_back(GMlib::Vector<float,3>(3.5f,1.f,0.f));
    c.push_back(GMlib::Vector<float,3>(3.f,2.f,0.f));
    c.push_back(GMlib::Vector<float,3>(2.5f,3.f,0.f));
    c.push_back(GMlib::Vector<float,3>(2.f,4.f,0.f));
  // The test loop
  while (state.KeepRunning()) {
    index(d,c);
  }

}
BENCHMARK(BM_BezierTriangle_index_d10);


static void BM_BezierTriangle_hardCoded_d1(benchmark::State& state)
{
    float u = 1, v = 0, w = 0;
    DVector<Vector<float,3>> c;
    c.push_back(GMlib::Vector<float,3>(0.f,0.f,0.f));
    c.push_back(GMlib::Vector<float,3>(3.0f,0.f,0.f));
    c.push_back(GMlib::Vector<float,3>(1.5f,3.f,0.f));
    Vector<float,3> test;

  // The test loop
  while (state.KeepRunning()) {
    test = c[0]*u + c[1]*v + c[2]*w;
  }

}
BENCHMARK(BM_BezierTriangle_hardCoded_d1);


static void BM_BezierTriangle_hardCoded_d2(benchmark::State& state)
{
    float u = 1, v = 0, w = 0;
    DVector<Vector<float,3>> c;
    c.push_back(GMlib::Vector<float,3>(0.f,0.f,0.f));
    c.push_back(GMlib::Vector<float,3>(1.5f,0.f,0.f));
    c.push_back(GMlib::Vector<float,3>(0.75f,1.5f,0.f));
    c.push_back(GMlib::Vector<float,3>(3.0f,0.f,0.f));
    c.push_back(GMlib::Vector<float,3>(2.25f,1.5f,0.f));
    c.push_back(GMlib::Vector<float,3>(1.5f,3.f,0.f));
    Vector<float,3> test;

  // The test loop
  while (state.KeepRunning()) {
    test = c[0]*(u*u) + c[1]*(2*u*v) + c[2]*(2*u*w)
         + c[3]*(v*v) + c[4]*(2*v*w) + c[5]*(w*w);
  }

}
BENCHMARK(BM_BezierTriangle_hardCoded_d2);


static void BM_BezierTriangle_hardCoded_d3(benchmark::State& state)
{
    float u = 1, v = 0, w = 0;
    DVector<Vector<float,3>> c;
    c.push_back(GMlib::Vector<float,3>(0.f,0.f,1.f));
    c.push_back(GMlib::Vector<float,3>(1.f,0.f,0.f));
    c.push_back(GMlib::Vector<float,3>(0.5f,1.f,0.f));
    c.push_back(GMlib::Vector<float,3>(2.f,0.f,0.f));
    c.push_back(GMlib::Vector<float,3>(1.5f,1.f,0.f));
    c.push_back(GMlib::Vector<float,3>(1.f,2.f,0.f));
    c.push_back(GMlib::Vector<float,3>(3.0f,0.f,1.f));
    c.push_back(GMlib::Vector<float,3>(2.5f,1.f,0.f));
    c.push_back(GMlib::Vector<float,3>(2.f,2.f,0.f));
    c.push_back(GMlib::Vector<float,3>(1.5f,3.f,1.f));
    Vector<float,3> test;

  // The test loop
  while (state.KeepRunning()) {
    test = c[0]*(u*u*u) + c[1]*(3*u*u*v) + c[2]*(3*u*u*w)
         + c[3]*(3*u*v*v) + c[4]*(6*u*v*w) + c[5]*(3*u*w*w)
         + c[6]*(v*v*v) + c[7]*(3*v*v*w) + c[8]*(3*v*w*w) + c[9]*(w*w*w);
  }

}
BENCHMARK(BM_BezierTriangle_hardCoded_d3);


static void BM_BezierTriangle_hardCoded_d4(benchmark::State& state)
{
    float u = 1, v = 0, w = 0;
    DVector<Vector<float,3>> c;
    c.push_back(GMlib::Vector<float,3>(0.f,0.f,0.f));
    c.push_back(GMlib::Vector<float,3>(1.f,0.f,0.f));
    c.push_back(GMlib::Vector<float,3>(0.5f,1.f,0.f));
    c.push_back(GMlib::Vector<float,3>(2.f,0.f,0.f));
    c.push_back(GMlib::Vector<float,3>(1.5f,1.f,0.f));
    c.push_back(GMlib::Vector<float,3>(1.f,2.f,0.f));
    c.push_back(GMlib::Vector<float,3>(3.0f,0.f,0.f));
    c.push_back(GMlib::Vector<float,3>(2.5f,1.f,0.f));
    c.push_back(GMlib::Vector<float,3>(2.f,2.f,0.f));
    c.push_back(GMlib::Vector<float,3>(1.5f,3.f,0.f));
    c.push_back(GMlib::Vector<float,3>(4.f,0.f,0.f));
    c.push_back(GMlib::Vector<float,3>(3.5f,1.f,0.f));
    c.push_back(GMlib::Vector<float,3>(3.f,2.f,0.f));
    c.push_back(GMlib::Vector<float,3>(2.5f,3.f,0.f));
    c.push_back(GMlib::Vector<float,3>(2.f,4.f,0.f));
    Vector<float,3> test;

  // The test loop
  while (state.KeepRunning()) {
    test = c[0]*(u*u*u*u) + c[1]*(4*u*u*u*v) + c[2]*(4*u*u*u*w)
         + c[3]*(6*u*u*v*v) + c[4]*(12*u*u*v*w) + c[5]*(6*u*u*w*w)
         + c[6]*(4*u*v*v*v) + c[7]*(12*u*v*v*w) + c[8]*(12*u*v*w*w)
         + c[9]*(4*u*w*w*w) + c[10]*(v*v*v*v) + c[11]*(4*v*v*v*w)
         + c[12]*(6*v*v*w*w) + c[13]*(4*v*w*w*w) + c[14]*(w*w*w*w);
  }

}
BENCHMARK(BM_BezierTriangle_hardCoded_d4);


static void BM_BezierTriangle_hardCoded_d5(benchmark::State& state)
{
    float u = 1, v = 0, w = 0;
    DVector<Vector<float,3>> c;
    c.push_back(GMlib::Vector<float,3>(0.f,0.f,0.f));
    c.push_back(GMlib::Vector<float,3>(1.f,0.f,0.f));
    c.push_back(GMlib::Vector<float,3>(0.5f,1.f,0.f));
    c.push_back(GMlib::Vector<float,3>(2.f,0.f,0.f));
    c.push_back(GMlib::Vector<float,3>(1.5f,1.f,0.f));
    c.push_back(GMlib::Vector<float,3>(1.f,2.f,0.f));
    c.push_back(GMlib::Vector<float,3>(3.0f,0.f,0.f));
    c.push_back(GMlib::Vector<float,3>(2.5f,1.f,0.f));
    c.push_back(GMlib::Vector<float,3>(2.f,2.f,0.f));
    c.push_back(GMlib::Vector<float,3>(1.5f,3.f,0.f));
    c.push_back(GMlib::Vector<float,3>(4.f,0.f,0.f));
    c.push_back(GMlib::Vector<float,3>(3.5f,1.f,0.f));
    c.push_back(GMlib::Vector<float,3>(3.f,2.f,0.f));
    c.push_back(GMlib::Vector<float,3>(2.5f,3.f,0.f));
    c.push_back(GMlib::Vector<float,3>(2.f,4.f,0.f));
    c.push_back(GMlib::Vector<float,3>(1.5f,3.f,0.f));
    c.push_back(GMlib::Vector<float,3>(4.f,0.f,0.f));
    c.push_back(GMlib::Vector<float,3>(3.5f,1.f,0.f));
    c.push_back(GMlib::Vector<float,3>(3.f,2.f,0.f));
    c.push_back(GMlib::Vector<float,3>(2.5f,3.f,0.f));
    c.push_back(GMlib::Vector<float,3>(2.f,4.f,0.f));
    Vector<float,3> test;

  // The test loop
  while (state.KeepRunning()) {
    test = c[0]*(u*u*u*u*u) + c[1]*(5*u*u*u*u*v) + c[2]*(5*u*u*u*u*w)
         + c[3]*(10*u*u*u*v*v) + c[4]*(20*u*u*u*v*w) + c[5]*(10*u*u*u*w*w)
         + c[6]*(10*u*u*v*v*v) + c[7]*(30*u*u*v*v*w) + c[8]*(30*u*u*v*w*w)
         + c[9]*(10*u*u*w*w*w) + c[10]*(5*u*v*v*v*v) + c[11]*(20*u*v*v*v*w)
         + c[12]*(30*u*v*v*w*w) + c[13]*(20*u*v*w*w*w) + c[14]*(5*u*w*w*w*w)
         + c[15]*(v*v*v*v*v) + c[16]*(5*v*v*v*v*w) + c[17]*(10*v*v*v*w*w)
         + c[18]*(10*v*v*w*w*w) + c[19]*(5*v*w*w*w*w) + c[20]*(w*w*w*w*w);
  }

}
BENCHMARK(BM_BezierTriangle_hardCoded_d5);


static void BM_BezierTriangle_hardCoded_d6(benchmark::State& state)
{
    float u = 1, v = 0, w = 0;
    DVector<Vector<float,3>> c;
    c.push_back(GMlib::Vector<float,3>(0.f,0.f,0.f));
    c.push_back(GMlib::Vector<float,3>(1.f,0.f,0.f));
    c.push_back(GMlib::Vector<float,3>(0.5f,1.f,0.f));
    c.push_back(GMlib::Vector<float,3>(2.f,0.f,0.f));
    c.push_back(GMlib::Vector<float,3>(1.5f,1.f,0.f));
    c.push_back(GMlib::Vector<float,3>(1.f,2.f,0.f));
    c.push_back(GMlib::Vector<float,3>(3.0f,0.f,0.f));
    c.push_back(GMlib::Vector<float,3>(2.5f,1.f,0.f));
    c.push_back(GMlib::Vector<float,3>(2.f,2.f,0.f));
    c.push_back(GMlib::Vector<float,3>(1.5f,3.f,0.f));
    c.push_back(GMlib::Vector<float,3>(4.f,0.f,0.f));
    c.push_back(GMlib::Vector<float,3>(3.5f,1.f,0.f));
    c.push_back(GMlib::Vector<float,3>(3.f,2.f,0.f));
    c.push_back(GMlib::Vector<float,3>(2.5f,3.f,0.f));
    c.push_back(GMlib::Vector<float,3>(2.f,4.f,0.f));
    c.push_back(GMlib::Vector<float,3>(1.5f,3.f,0.f));
    c.push_back(GMlib::Vector<float,3>(4.f,0.f,0.f));
    c.push_back(GMlib::Vector<float,3>(3.5f,1.f,0.f));
    c.push_back(GMlib::Vector<float,3>(3.f,2.f,0.f));
    c.push_back(GMlib::Vector<float,3>(2.5f,3.f,0.f));
    c.push_back(GMlib::Vector<float,3>(2.f,4.f,0.f));
    c.push_back(GMlib::Vector<float,3>(2.f,4.f,0.f));
    c.push_back(GMlib::Vector<float,3>(1.5f,3.f,0.f));
    c.push_back(GMlib::Vector<float,3>(4.f,0.f,0.f));
    c.push_back(GMlib::Vector<float,3>(3.5f,1.f,0.f));
    c.push_back(GMlib::Vector<float,3>(3.f,2.f,0.f));
    c.push_back(GMlib::Vector<float,3>(2.5f,3.f,0.f));
    c.push_back(GMlib::Vector<float,3>(2.f,4.f,0.f));
    Vector<float,3> test;

  // The test loop
  while (state.KeepRunning()) {
    test = c[0]*(u*u*u*u*u*u) + c[1]*(6*u*u*u*u*u*v) + c[2]*(6*u*u*u*u*u*w)
         + c[3]*(15*u*u*u*u*v*v) + c[4]*(30*u*u*u*u*v*w) + c[5]*(15*u*u*u*u*w*w)
         + c[6]*(20*u*u*u*v*v*v) + c[7]*(60*u*u*u*v*v*w) + c[8]*(60*u*u*u*v*w*w)
         + c[9]*(20*u*u*u*w*w*w) + c[10]*(15*u*u*v*v*v*v) + c[11]*(60*u*u*v*v*v*w)
         + c[12]*(90*u*u*v*v*w*w) + c[13]*(60*u*u*v*w*w*w) + c[14]*(15*u*u*w*w*w*w)
         + c[15]*(6*u*v*v*v*v*v) + c[16]*(30*u*v*v*v*v*w) + c[17]*(60*u*v*v*v*w*w)
         + c[18]*(60*u*v*v*w*w*w) + c[19]*(30*u*v*w*w*w*w) + c[20]*(6*u*w*w*w*w*w)
         + c[21]*(v*v*v*v*v*v) + c[22]*(6*v*v*v*v*v*w) + c[23]*(15*v*v*v*v*w*w)
         + c[24]*(20*v*v*v*w*w*w) + c[25]*(15*v*v*w*w*w*w) + c[26]*(6*v*w*w*w*w*w)
         + c[27]*(w*w*w*w*w*w);
  }

}
BENCHMARK(BM_BezierTriangle_hardCoded_d6);


static void BM_BezierTriangle_hardCoded_d7(benchmark::State& state)
{
    float u = 1, v = 0, w = 0;
    DVector<Vector<float,3>> c;
    c.push_back(GMlib::Vector<float,3>(0.f,0.f,0.f));
    c.push_back(GMlib::Vector<float,3>(1.f,0.f,0.f));
    c.push_back(GMlib::Vector<float,3>(0.5f,1.f,0.f));
    c.push_back(GMlib::Vector<float,3>(2.f,0.f,0.f));
    c.push_back(GMlib::Vector<float,3>(1.5f,1.f,0.f));
    c.push_back(GMlib::Vector<float,3>(1.f,2.f,0.f));
    c.push_back(GMlib::Vector<float,3>(3.0f,0.f,0.f));
    c.push_back(GMlib::Vector<float,3>(2.5f,1.f,0.f));
    c.push_back(GMlib::Vector<float,3>(2.f,2.f,0.f));
    c.push_back(GMlib::Vector<float,3>(1.5f,3.f,0.f));
    c.push_back(GMlib::Vector<float,3>(4.f,0.f,0.f));
    c.push_back(GMlib::Vector<float,3>(3.5f,1.f,0.f));
    c.push_back(GMlib::Vector<float,3>(3.f,2.f,0.f));
    c.push_back(GMlib::Vector<float,3>(2.5f,3.f,0.f));
    c.push_back(GMlib::Vector<float,3>(2.f,4.f,0.f));
    c.push_back(GMlib::Vector<float,3>(1.5f,3.f,0.f));
    c.push_back(GMlib::Vector<float,3>(4.f,0.f,0.f));
    c.push_back(GMlib::Vector<float,3>(3.5f,1.f,0.f));
    c.push_back(GMlib::Vector<float,3>(3.f,2.f,0.f));
    c.push_back(GMlib::Vector<float,3>(2.5f,3.f,0.f));
    c.push_back(GMlib::Vector<float,3>(2.f,4.f,0.f));
    c.push_back(GMlib::Vector<float,3>(2.f,4.f,0.f));
    c.push_back(GMlib::Vector<float,3>(1.5f,3.f,0.f));
    c.push_back(GMlib::Vector<float,3>(4.f,0.f,0.f));
    c.push_back(GMlib::Vector<float,3>(3.5f,1.f,0.f));
    c.push_back(GMlib::Vector<float,3>(3.f,2.f,0.f));
    c.push_back(GMlib::Vector<float,3>(2.5f,3.f,0.f));
    c.push_back(GMlib::Vector<float,3>(2.f,4.f,0.f));
    c.push_back(GMlib::Vector<float,3>(2.f,4.f,0.f));
    c.push_back(GMlib::Vector<float,3>(2.f,4.f,0.f));
    c.push_back(GMlib::Vector<float,3>(1.5f,3.f,0.f));
    c.push_back(GMlib::Vector<float,3>(4.f,0.f,0.f));
    c.push_back(GMlib::Vector<float,3>(3.5f,1.f,0.f));
    c.push_back(GMlib::Vector<float,3>(3.f,2.f,0.f));
    c.push_back(GMlib::Vector<float,3>(2.5f,3.f,0.f));
    c.push_back(GMlib::Vector<float,3>(2.f,4.f,0.f));

    Vector<float,3> test;

  // The test loop
  while (state.KeepRunning()) {
    test = c[0]*(u*u*u*u*u*u*u) + c[1]*(7*u*u*u*u*u*u*v) + c[2]*(7*u*u*u*u*u*u*w)
         + c[3]*(21*u*u*u*u*u*v*v) + c[4]*(42*u*u*u*u*u*v*w) + c[5]*(21*u*u*u*u*u*w*w)
         + c[6]*(35*u*u*u*u*v*v*v) + c[7]*(105*u*u*u*u*v*v*w) + c[8]*(105*u*u*u*u*v*w*w)
         + c[9]*(35*u*u*u*u*w*w*w) + c[10]*(35*u*u*u*v*v*v*v) + c[11]*(140*u*u*u*v*v*v*w)
         + c[12]*(210*u*u*u*v*v*w*w) + c[13]*(140*u*u*u*v*w*w*w) + c[14]*(35*u*u*u*w*w*w*w)
         + c[15]*(21*u*u*v*v*v*v*v) + c[16]*(105*u*u*v*v*v*v*w) + c[17]*(210*u*u*v*v*v*w*w)
         + c[18]*(210*u*u*v*v*w*w*w) + c[19]*(105*u*u*v*w*w*w*w) + c[20]*(21*u*u*w*w*w*w*w)
         + c[21]*(7*u*v*v*v*v*v*v) + c[22]*(42*u*v*v*v*v*v*w) + c[23]*(105*u*v*v*v*v*w*w)
         + c[24]*(140*u*v*v*v*w*w*w) + c[25]*(105*u*v*v*w*w*w*w) + c[26]*(42*u*v*w*w*w*w*w)
         + c[27]*(7*u*w*w*w*w*w*w) + c[28]*(v*v*v*v*v*v*v) + c[29]*(7*v*v*v*v*v*v*w)
         + c[30]*(21*v*v*v*v*v*w*w) + c[31]*(35*v*v*v*v*w*w*w) + c[32]*(35*v*v*v*w*w*w*w)
         + c[33]*(21*v*v*w*w*w*w*w) + c[34]*(7*v*w*w*w*w*w*w) + c[35]*(w*w*w*w*w*w*w);
  }

}
BENCHMARK(BM_BezierTriangle_hardCoded_d7);


static void BM_BezierTriangle_hardCoded_d8(benchmark::State& state)
{
    float u = 1, v = 0, w = 0;
    DVector<Vector<float,3>> c;
    c.push_back(GMlib::Vector<float,3>(0.f,0.f,0.f));
    c.push_back(GMlib::Vector<float,3>(1.f,0.f,0.f));
    c.push_back(GMlib::Vector<float,3>(0.5f,1.f,0.f));
    c.push_back(GMlib::Vector<float,3>(2.f,0.f,0.f));
    c.push_back(GMlib::Vector<float,3>(1.5f,1.f,0.f));
    c.push_back(GMlib::Vector<float,3>(1.f,2.f,0.f));
    c.push_back(GMlib::Vector<float,3>(3.0f,0.f,0.f));
    c.push_back(GMlib::Vector<float,3>(2.5f,1.f,0.f));
    c.push_back(GMlib::Vector<float,3>(2.f,2.f,0.f));
    c.push_back(GMlib::Vector<float,3>(1.5f,3.f,0.f));
    c.push_back(GMlib::Vector<float,3>(4.f,0.f,0.f));
    c.push_back(GMlib::Vector<float,3>(3.5f,1.f,0.f));
    c.push_back(GMlib::Vector<float,3>(3.f,2.f,0.f));
    c.push_back(GMlib::Vector<float,3>(2.5f,3.f,0.f));
    c.push_back(GMlib::Vector<float,3>(2.f,4.f,0.f));
    c.push_back(GMlib::Vector<float,3>(1.5f,3.f,0.f));
    c.push_back(GMlib::Vector<float,3>(4.f,0.f,0.f));
    c.push_back(GMlib::Vector<float,3>(3.5f,1.f,0.f));
    c.push_back(GMlib::Vector<float,3>(3.f,2.f,0.f));
    c.push_back(GMlib::Vector<float,3>(2.5f,3.f,0.f));
    c.push_back(GMlib::Vector<float,3>(2.f,4.f,0.f));
    c.push_back(GMlib::Vector<float,3>(2.f,4.f,0.f));
    c.push_back(GMlib::Vector<float,3>(1.5f,3.f,0.f));
    c.push_back(GMlib::Vector<float,3>(4.f,0.f,0.f));
    c.push_back(GMlib::Vector<float,3>(3.5f,1.f,0.f));
    c.push_back(GMlib::Vector<float,3>(3.f,2.f,0.f));
    c.push_back(GMlib::Vector<float,3>(2.5f,3.f,0.f));
    c.push_back(GMlib::Vector<float,3>(2.f,4.f,0.f));
    c.push_back(GMlib::Vector<float,3>(2.f,4.f,0.f));
    c.push_back(GMlib::Vector<float,3>(2.f,4.f,0.f));
    c.push_back(GMlib::Vector<float,3>(1.5f,3.f,0.f));
    c.push_back(GMlib::Vector<float,3>(4.f,0.f,0.f));
    c.push_back(GMlib::Vector<float,3>(3.5f,1.f,0.f));
    c.push_back(GMlib::Vector<float,3>(3.f,2.f,0.f));
    c.push_back(GMlib::Vector<float,3>(2.5f,3.f,0.f));
    c.push_back(GMlib::Vector<float,3>(2.f,4.f,0.f));
    c.push_back(GMlib::Vector<float,3>(2.f,4.f,0.f));
    c.push_back(GMlib::Vector<float,3>(2.f,4.f,0.f));
    c.push_back(GMlib::Vector<float,3>(2.f,4.f,0.f));
    c.push_back(GMlib::Vector<float,3>(1.5f,3.f,0.f));
    c.push_back(GMlib::Vector<float,3>(4.f,0.f,0.f));
    c.push_back(GMlib::Vector<float,3>(3.5f,1.f,0.f));
    c.push_back(GMlib::Vector<float,3>(3.f,2.f,0.f));
    c.push_back(GMlib::Vector<float,3>(2.5f,3.f,0.f));
    c.push_back(GMlib::Vector<float,3>(2.f,4.f,0.f));

    Vector<float,3> test;

  // The test loop
  while (state.KeepRunning()) {
    test = c[0]*(u*u*u*u*u*u*u*u) + c[1]*(8*u*u*u*u*u*u*u*v) + c[2]*(8*u*u*u*u*u*u*u*w)
         + c[3]*(28*u*u*u*u*u*u*v*v) + c[4]*(56*u*u*u*u*u*u*v*w) + c[5]*(28*u*u*u*u*u*u*w*w)
         + c[6]*(56*u*u*u*u*u*v*v*v) + c[7]*(168*u*u*u*u*u*v*v*w) + c[8]*(168*u*u*u*u*u*v*w*w)
         + c[9]*(56*u*u*u*u*u*w*w*w) + c[10]*(70*u*u*u*u*v*v*v*v) + c[11]*(280*u*u*u*u*v*v*v*w)
         + c[12]*(420*u*u*u*u*v*v*w*w) + c[13]*(280*u*u*u*u*v*w*w*w) + c[14]*(70*u*u*u*u*w*w*w*w)
         + c[15]*(56*u*u*u*v*v*v*v*v) + c[16]*(280*u*u*u*v*v*v*v*w) + c[17]*(560*u*u*u*v*v*v*w*w)
         + c[18]*(560*u*u*u*v*v*w*w*w) + c[19]*(280*u*u*u*v*w*w*w*w) + c[20]*(56*u*u*u*w*w*w*w*w)
         + c[21]*(28*u*u*v*v*v*v*v*v) + c[22]*(168*u*u*v*v*v*v*v*w) + c[23]*(420*u*u*v*v*v*v*w*w)
         + c[24]*(560*u*u*v*v*v*w*w*w) + c[25]*(420*u*u*v*v*w*w*w*w) + c[26]*(168*u*u*v*w*w*w*w*w)
         + c[27]*(28*u*u*w*w*w*w*w*w) + c[28]*(8*u*v*v*v*v*v*v*v) + c[29]*(56*u*v*v*v*v*v*v*w)
         + c[30]*(168*u*v*v*v*v*v*w*w) + c[31]*(280*u*v*v*v*v*w*w*w) + c[32]*(280*u*v*v*v*w*w*w*w)
         + c[33]*(168*u*v*v*w*w*w*w*w) + c[34]*(56*u*v*w*w*w*w*w*w) + c[35]*(8*u*w*w*w*w*w*w*w)
         + c[36]*(v*v*v*v*v*v*v*v) + c[37]*(8*v*v*v*v*v*v*v*w) + c[38]*(28*v*v*v*v*v*v*w*w)
         + c[39]*(56*v*v*v*v*v*w*w*w) + c[40]*(70*v*v*v*v*w*w*w*w) + c[41]*(56*v*v*v*w*w*w*w*w)
         + c[42]*(28*v*v*w*w*w*w*w*w) + c[43]*(8*v*w*w*w*w*w*w*w) + c[44]*(w*w*w*w*w*w*w*w);
  }

}
BENCHMARK(BM_BezierTriangle_hardCoded_d8);


BENCHMARK_MAIN()
