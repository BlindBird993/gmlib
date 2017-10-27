#include <benchmark/benchmark.h>
#include <math.h>

#include "../src/curves/gmpcircle.h"
#include "../src/triangles/gmpbeziertriangledecasteljau.h"
#include "../../core/src/utils/gmutils.h"

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

template <typename T>
Vector<T,3> VSAlgoTriReg3(const DVector<Vector<T,3>>& c,const DVector<T>& bCoord, int d)
{
    Vector<T,3> final = Vector<T,3>(0,0,0);
    int j = 0;
    Vector<T,3> A = c[j];
    for(int i = 1; i<=d; i++)
    {
        Vector<T,3> B = c[j++];
        for(int k = 1; k<=i; k++)
        {
            B = B * (bCoord[1]/bCoord[2])+c[j++];
        }
        A = A * (bCoord[0]/bCoord[2])+B;
    }
    final = A*std::pow(bCoord[2],d);

    return final;
}

template <typename T>
Vector<T,3> VSAlgoPentReg5(const DVector<Vector<T,3>>& c,const DVector<T>& bCoord, int d)
{
    Vector<T,3> final = Vector<T,3>(0,0,0);

    int m = 0;
    Vector<T,3> A = c[m];
    for(int i = 1; i<=d; i++)
    {
        Vector<T,3> B = c[m++];
        for(int j = 1; j<=i; j++)
        {
            Vector<T,3> C = c[m++];
            for(int k = 1; k<=j; k++)
            {
                Vector<T,3> D = c[m++];
                for(int l = 1; l<=k; l++)
                {
                    D = D * (bCoord[3]/bCoord[4]) + c[m++];
                }
                C = C * (bCoord[2]/bCoord[4]) + D;
            }
            B = B * (bCoord[1]/bCoord[4]) + C;
        }
        A = A * (bCoord[0]/bCoord[4]) + B;
    }
    final = A*std::pow(bCoord[4],d);

    return final;
}

template <typename T>
Vector<T,3> cornerCutting(const DVector<Vector<T,3>>& q,const DVector<T>& b)
{
    Vector<T,3> final = Vector<T,3>(0,0,0);

    for(int i = 0; i < q.getDim(); i++)
    {
       final +=  b[i]*q[i];
    }

    return final;
}

//template <typename T>
//Vector<T,3> DeCasteljau(int d, DVector<Vector<T,3>> p, DVector<T> b, int n)
//{

//    if(p.getDim() == n)
//   {
//        return cornerCutting(p, b);
//   }
//    else
//    {
//        DVector<Vector<T,3>> q;
//        q.setDim(n);
//        DVector<DVector<Vector<T,3>>> subs;
//        subs.setDim(n);

//        DVector<int> index = DVector<int>(n,0);
//        index[0] = d;
//        for(int i = 1, k=0; i <= n; i++)
//        {
//            //Add to sub
//            for(int l = 0; l < index.getDim(); l++)
//            {
//                if(index[l] > 0)
//                    subs[l].push_back(p[k]);
//            }
//            if(i == n)
//            {
//                if(index[i-1] == d)
//                    break;
//                int j = n-2;//n-2
//                for(; index[j] == 0 && j >= 0; j--);
//                if(j < 0)
//                    break;
//                i = j+1;
//                index[i]=index[n-1];//index[n-1]
//                if(i != n-1)//n-1
//                    index[n-1]=0;//index[n-1]

//            }
//            index[i]++;
//            index[i-1]--;
//            k++;
//        }

//        for(int i = 0; i < subs.getDim(); i++)
//        {
//            q[i] = DeCasteljau(d-1,subs[i],b,n);
//        }

//        return cornerCutting(q, b);
//    }
//}


//static void BM_triangle_VSalgo_degree1(benchmark::State& state)
//{
//    DVector<Vector<double,3>> c;
//    for(int i = 0; i < 3; i++)
//    {
//      c.push_back(Vector<double,3>(1.0,1.0,0.0));
//    }

//    DVector<double> b;
//    b.push_back(0.0);
//    b.push_back(0.0);
//    b.push_back(1.0);

//    Vector<double,3> test;

//    // The test loop
//    while (state.KeepRunning()) {
//      test = VSAlgoTriReg3(c,b,1);
//    }

//}
//BENCHMARK(BM_triangle_VSalgo_degree1);

//static void BM_triangle_VSalgo_degree2(benchmark::State& state)
//{
//    DVector<Vector<double,3>> c;
//    for(int i = 0; i < 6; i++)
//    {
//      c.push_back(Vector<double,3>(1.0,1.0,0.0));
//    }


//    DVector<double> b;
//    b.push_back(0.0);
//    b.push_back(0.0);
//    b.push_back(1.0);

//    Vector<double,3> test;

//    // The test loop
//    while (state.KeepRunning()) {
//      test = VSAlgoTriReg3(c,b,2);
//    }

//}
//BENCHMARK(BM_triangle_VSalgo_degree2);

//static void BM_triangle_VSalgo_degree3(benchmark::State& state)
//{
//    DVector<Vector<double,3>> c;
//    for(int i = 0; i < 10; i++)
//    {
//      c.push_back(Vector<double,3>(1.0,1.0,0.0));
//    }


//    DVector<double> b;
//    b.push_back(0.0);
//    b.push_back(0.0);
//    b.push_back(1.0);

//    Vector<double,3> test;

//    // The test loop
//    while (state.KeepRunning()) {
//      test = VSAlgoTriReg3(c,b,3);
//    }

//}
//BENCHMARK(BM_triangle_VSalgo_degree3);

//static void BM_triangle_VSalgo_degree4(benchmark::State& state)
//{
//    DVector<Vector<double,3>> c;
//    for(int i = 0; i < 15; i++)
//    {
//      c.push_back(Vector<double,3>(1.0,1.0,0.0));
//    }


//    DVector<double> b;
//    b.push_back(0.0);
//    b.push_back(0.0);
//    b.push_back(1.0);

//    Vector<double,3> test;

//    // The test loop
//    while (state.KeepRunning()) {
//      test = VSAlgoTriReg3(c,b,4);
//    }

//}
//BENCHMARK(BM_triangle_VSalgo_degree4);

//static void BM_triangle_VSalgo_degree5(benchmark::State& state)
//{
//    DVector<Vector<double,3>> c;
//    for(int i = 0; i < 21; i++)
//    {
//      c.push_back(Vector<double,3>(1.0,1.0,0.0));
//    }


//    DVector<double> b;
//    b.push_back(0.0);
//    b.push_back(0.0);
//    b.push_back(1.0);

//    Vector<double,3> test;

//    // The test loop
//    while (state.KeepRunning()) {
//      test = VSAlgoTriReg3(c,b,5);
//    }

//}
//BENCHMARK(BM_triangle_VSalgo_degree5);

//static void BM_triangle_VSalgo_degree6(benchmark::State& state)
//{
//    DVector<Vector<double,3>> c;
//    for(int i = 0; i < 28; i++)
//    {
//      c.push_back(Vector<double,3>(1.0,1.0,0.0));
//    }


//    DVector<double> b;
//    b.push_back(0.0);
//    b.push_back(0.0);
//    b.push_back(1.0);

//    Vector<double,3> test;

//    // The test loop
//    while (state.KeepRunning()) {
//      test = VSAlgoTriReg3(c,b,6);
//    }

//}
//BENCHMARK(BM_triangle_VSalgo_degree6);

//static void BM_triangle_VSalgo_degree7(benchmark::State& state)
//{
//    DVector<Vector<double,3>> c;
//    for(int i = 0; i < 36; i++)
//    {
//      c.push_back(Vector<double,3>(1.0,1.0,0.0));
//    }


//    DVector<double> b;
//    b.push_back(0.0);
//    b.push_back(0.0);
//    b.push_back(1.0);

//    Vector<double,3> test;

//    // The test loop
//    while (state.KeepRunning()) {
//      test = VSAlgoTriReg3(c,b,7);
//    }

//}
//BENCHMARK(BM_triangle_VSalgo_degree7);

//static void BM_triangle_VSalgo_degree8(benchmark::State& state)
//{
//    DVector<Vector<double,3>> c;
//    for(int i = 0; i < 45; i++)
//    {
//      c.push_back(Vector<double,3>(1.0,1.0,0.0));
//    }


//    DVector<double> b;
//    b.push_back(0.0);
//    b.push_back(0.0);
//    b.push_back(1.0);

//    Vector<double,3> test;

//    // The test loop
//    while (state.KeepRunning()) {
//      test = VSAlgoTriReg3(c,b,8);
//    }

//}
//BENCHMARK(BM_triangle_VSalgo_degree8);

//static void BM_triangle_VSalgo_degree9(benchmark::State& state)
//{
//    DVector<Vector<double,3>> c;
//    for(int i = 0; i < 55; i++)
//    {
//      c.push_back(Vector<double,3>(1.0,1.0,0.0));
//    }


//    DVector<double> b;
//    b.push_back(0.0);
//    b.push_back(0.0);
//    b.push_back(1.0);

//    Vector<double,3> test;

//    // The test loop
//    while (state.KeepRunning()) {
//      test = VSAlgoTriReg3(c,b,9);
//    }

//}
//BENCHMARK(BM_triangle_VSalgo_degree9);

//static void BM_triangle_VSalgo_degree10(benchmark::State& state)
//{
//    DVector<Vector<double,3>> c;
//    for(int i = 0; i < 66; i++)
//    {
//      c.push_back(Vector<double,3>(1.0,1.0,0.0));
//    }


//    DVector<double> b;
//    b.push_back(0.0);
//    b.push_back(0.0);
//    b.push_back(1.0);

//    Vector<double,3> test;

//    // The test loop
//    while (state.KeepRunning()) {
//      test = VSAlgoTriReg3(c,b,10);
//    }

//}
//BENCHMARK(BM_triangle_VSalgo_degree10);



//static void BM_pentagon_VSalgo_degree1(benchmark::State& state)
//{
//    DVector<Vector<double,3>> c;
//    for(int i = 0; i < 5; i++)
//    {
//      c.push_back(Vector<double,3>(1.0,1.0,0.0));
//    }

//    DVector<double> b;
//    b.push_back(0.0);
//    b.push_back(0.0);
//    b.push_back(0.0);
//    b.push_back(0.0);
//    b.push_back(1.0);

//    Vector<double,3> test;

//    // The test loop
//    while (state.KeepRunning()) {
//      test = VSAlgoPentReg5(c,b,1);
//    }

//}
//BENCHMARK(BM_pentagon_VSalgo_degree1);

//static void BM_pentagon_VSalgo_degree2(benchmark::State& state)
//{
//    DVector<Vector<double,3>> c;
//    for(int i = 0; i < 15; i++)
//    {
//      c.push_back(Vector<double,3>(1.0,1.0,0.0));
//    }

//    DVector<double> b;
//    b.push_back(0.0);
//    b.push_back(0.0);
//    b.push_back(0.0);
//    b.push_back(0.0);
//    b.push_back(1.0);

//    Vector<double,3> test;

//    // The test loop
//    while (state.KeepRunning()) {
//      test = VSAlgoPentReg5(c,b,2);
//    }

//}
//BENCHMARK(BM_pentagon_VSalgo_degree2);

//static void BM_pentagon_VSalgo_degree3(benchmark::State& state)
//{
//    DVector<Vector<double,3>> c;
//    for(int i = 0; i < 35; i++)
//    {
//      c.push_back(Vector<double,3>(1.0,1.0,0.0));
//    }

//    DVector<double> b;
//    b.push_back(0.0);
//    b.push_back(0.0);
//    b.push_back(0.0);
//    b.push_back(0.0);
//    b.push_back(1.0);

//    Vector<double,3> test;

//    // The test loop
//    while (state.KeepRunning()) {
//      test = VSAlgoPentReg5(c,b,3);
//    }

//}
//BENCHMARK(BM_pentagon_VSalgo_degree3);

//static void BM_pentagon_VSalgo_degree4(benchmark::State& state)
//{
//    DVector<Vector<double,3>> c;
//    for(int i = 0; i < 70; i++)
//    {
//      c.push_back(Vector<double,3>(1.0,1.0,0.0));
//    }

//    DVector<double> b;
//    b.push_back(0.0);
//    b.push_back(0.0);
//    b.push_back(0.0);
//    b.push_back(0.0);
//    b.push_back(1.0);

//    Vector<double,3> test;

//    // The test loop
//    while (state.KeepRunning()) {
//      test = VSAlgoPentReg5(c,b,4);
//    }

//}
//BENCHMARK(BM_pentagon_VSalgo_degree4);

//static void BM_pentagon_VSalgo_degree5(benchmark::State& state)
//{
//    DVector<Vector<double,3>> c;
//    for(int i = 0; i < 126; i++)
//    {
//      c.push_back(Vector<double,3>(1.0,1.0,0.0));
//    }

//    DVector<double> b;
//    b.push_back(0.0);
//    b.push_back(0.0);
//    b.push_back(0.0);
//    b.push_back(0.0);
//    b.push_back(1.0);

//    Vector<double,3> test;

//    // The test loop
//    while (state.KeepRunning()) {
//      test = VSAlgoPentReg5(c,b,5);
//    }

//}
//BENCHMARK(BM_pentagon_VSalgo_degree5);

//static void BM_pentagon_VSalgo_degree6(benchmark::State& state)
//{
//    DVector<Vector<double,3>> c;
//    for(int i = 0; i < 210; i++)
//    {
//      c.push_back(Vector<double,3>(1.0,1.0,0.0));
//    }

//    DVector<double> b;
//    b.push_back(0.0);
//    b.push_back(0.0);
//    b.push_back(0.0);
//    b.push_back(0.0);
//    b.push_back(1.0);

//    Vector<double,3> test;

//    // The test loop
//    while (state.KeepRunning()) {
//      test = VSAlgoPentReg5(c,b,6);
//    }

//}
//BENCHMARK(BM_pentagon_VSalgo_degree6);

//static void BM_pentagon_VSalgo_degree7(benchmark::State& state)
//{
//    DVector<Vector<double,3>> c;
//    for(int i = 0; i < 330; i++)
//    {
//      c.push_back(Vector<double,3>(1.0,1.0,0.0));
//    }

//    DVector<double> b;
//    b.push_back(0.0);
//    b.push_back(0.0);
//    b.push_back(0.0);
//    b.push_back(0.0);
//    b.push_back(1.0);

//    Vector<double,3> test;

//    // The test loop
//    while (state.KeepRunning()) {
//      test = VSAlgoPentReg5(c,b,7);
//    }

//}
//BENCHMARK(BM_pentagon_VSalgo_degree7);

//static void BM_pentagon_VSalgo_degree8(benchmark::State& state)
//{
//    DVector<Vector<double,3>> c;
//    for(int i = 0; i < 495; i++)
//    {
//      c.push_back(Vector<double,3>(1.0,1.0,0.0));
//    }

//    DVector<double> b;
//    b.push_back(0.0);
//    b.push_back(0.0);
//    b.push_back(0.0);
//    b.push_back(0.0);
//    b.push_back(1.0);

//    Vector<double,3> test;

//    // The test loop
//    while (state.KeepRunning()) {
//      test = VSAlgoPentReg5(c,b,8);
//    }

//}
//BENCHMARK(BM_pentagon_VSalgo_degree8);

//static void BM_pentagon_VSalgo_degree9(benchmark::State& state)
//{
//    DVector<Vector<double,3>> c;
//    for(int i = 0; i < 715; i++)
//    {
//      c.push_back(Vector<double,3>(1.0,1.0,0.0));
//    }

//    DVector<double> b;
//    b.push_back(0.0);
//    b.push_back(0.0);
//    b.push_back(0.0);
//    b.push_back(0.0);
//    b.push_back(1.0);

//    Vector<double,3> test;

//    // The test loop
//    while (state.KeepRunning()) {
//      test = VSAlgoPentReg5(c,b,9);
//    }

//}
//BENCHMARK(BM_pentagon_VSalgo_degree9);

//static void BM_pentagon_VSalgo_degree10(benchmark::State& state)
//{
//    DVector<Vector<double,3>> c;
//    for(int i = 0; i < 1001; i++)
//    {
//      c.push_back(Vector<double,3>(1.0,1.0,0.0));
//    }

//    DVector<double> b;
//    b.push_back(0.0);
//    b.push_back(0.0);
//    b.push_back(0.0);
//    b.push_back(0.0);
//    b.push_back(1.0);

//    Vector<double,3> test;

//    // The test loop
//    while (state.KeepRunning()) {
//      test = VSAlgoPentReg5(c,b,10);
//    }

//}
//BENCHMARK(BM_pentagon_VSalgo_degree10);

//static void BM_pentagon_deCasteljauRevised_degree1(benchmark::State& state)
//{
//    DVector<Vector<double,3>> c;
//    c.push_back(GMlib::Vector<double,3>(0.0,0.0,0.0));
//    c.push_back(GMlib::Vector<double,3>(3.0,0.0,0.0));
//    c.push_back(GMlib::Vector<double,3>(1.5,3.0,0.0));
//    c.push_back(GMlib::Vector<double,3>(3.0,0.0,0.0));
//    c.push_back(GMlib::Vector<double,3>(1.5,3.0,0.0));

//    DVector<double> b;
//    b.push_back(0.0);
//    b.push_back(0.0);
//    b.push_back(1.0);
//    b.push_back(0.0);
//    b.push_back(0.0);

//    Vector<double,3> test;

//    // The test loop
//    while (state.KeepRunning()) {
//        for(int i = 0; i < 1; i++)
//          test = cornerCutting(c,b);
//    }

//}
//BENCHMARK(BM_pentagon_deCasteljauRevised_degree1);

//static void BM_pentagon_deCasteljauRevised_degree2(benchmark::State& state)
//{
//    DVector<Vector<double,3>> c;
//    c.push_back(GMlib::Vector<double,3>(0.0,0.0,0.0));
//    c.push_back(GMlib::Vector<double,3>(3.0,0.0,0.0));
//    c.push_back(GMlib::Vector<double,3>(1.5,3.0,0.0));
//    c.push_back(GMlib::Vector<double,3>(3.0,0.0,0.0));
//    c.push_back(GMlib::Vector<double,3>(1.5,3.0,0.0));

//    DVector<double> b;
//    b.push_back(0.0);
//    b.push_back(0.0);
//    b.push_back(1.0);
//    b.push_back(0.0);
//    b.push_back(0.0);

//    Vector<double,3> test;

//    // The test loop
//    while (state.KeepRunning()) {
//        for(int i = 0; i < 6; i++)
//          test = cornerCutting(c,b);
//    }

//}
//BENCHMARK(BM_pentagon_deCasteljauRevised_degree2);

//static void BM_pentagon_deCasteljauRevised_degree3(benchmark::State& state)
//{
//    DVector<Vector<double,3>> c;
//    c.push_back(GMlib::Vector<double,3>(0.0,0.0,0.0));
//    c.push_back(GMlib::Vector<double,3>(3.0,0.0,0.0));
//    c.push_back(GMlib::Vector<double,3>(1.5,3.0,0.0));
//    c.push_back(GMlib::Vector<double,3>(3.0,0.0,0.0));
//    c.push_back(GMlib::Vector<double,3>(1.5,3.0,0.0));

//    DVector<double> b;
//    b.push_back(0.0);
//    b.push_back(0.0);
//    b.push_back(1.0);
//    b.push_back(0.0);
//    b.push_back(0.0);

//    Vector<double,3> test;

//    // The test loop
//    while (state.KeepRunning()) {
//        for(int i = 0; i < 31; i++)
//          test = cornerCutting(c,b);
//    }

//}
//BENCHMARK(BM_pentagon_deCasteljauRevised_degree3);

//static void BM_pentagon_deCasteljauRevised_degree4(benchmark::State& state)
//{
//    DVector<Vector<double,3>> c;
//    c.push_back(GMlib::Vector<double,3>(0.0,0.0,0.0));
//    c.push_back(GMlib::Vector<double,3>(3.0,0.0,0.0));
//    c.push_back(GMlib::Vector<double,3>(1.5,3.0,0.0));
//    c.push_back(GMlib::Vector<double,3>(3.0,0.0,0.0));
//    c.push_back(GMlib::Vector<double,3>(1.5,3.0,0.0));

//    DVector<double> b;
//    b.push_back(0.0);
//    b.push_back(0.0);
//    b.push_back(1.0);
//    b.push_back(0.0);
//    b.push_back(0.0);

//    Vector<double,3> test;

//    // The test loop
//    while (state.KeepRunning()) {
//        for(int i = 0; i < 156; i++)
//          test = cornerCutting(c,b);
//    }

//}
//BENCHMARK(BM_pentagon_deCasteljauRevised_degree4);

//static void BM_pentagon_deCasteljauRevised_degree5(benchmark::State& state)
//{
//    DVector<Vector<double,3>> c;
//    c.push_back(GMlib::Vector<double,3>(0.0,0.0,0.0));
//    c.push_back(GMlib::Vector<double,3>(3.0,0.0,0.0));
//    c.push_back(GMlib::Vector<double,3>(1.5,3.0,0.0));
//    c.push_back(GMlib::Vector<double,3>(3.0,0.0,0.0));
//    c.push_back(GMlib::Vector<double,3>(1.5,3.0,0.0));

//    DVector<double> b;
//    b.push_back(0.0);
//    b.push_back(0.0);
//    b.push_back(1.0);
//    b.push_back(0.0);
//    b.push_back(0.0);

//    Vector<double,3> test;

//    // The test loop
//    while (state.KeepRunning()) {
//        for(int i = 0; i < 781; i++)
//          test = cornerCutting(c,b);
//    }

//}
//BENCHMARK(BM_pentagon_deCasteljauRevised_degree5);

//static void BM_pentagon_deCasteljauRevised_degree6(benchmark::State& state)
//{
//    DVector<Vector<double,3>> c;
//    c.push_back(GMlib::Vector<double,3>(0.0,0.0,0.0));
//    c.push_back(GMlib::Vector<double,3>(3.0,0.0,0.0));
//    c.push_back(GMlib::Vector<double,3>(1.5,3.0,0.0));
//    c.push_back(GMlib::Vector<double,3>(3.0,0.0,0.0));
//    c.push_back(GMlib::Vector<double,3>(1.5,3.0,0.0));

//    DVector<double> b;
//    b.push_back(0.0);
//    b.push_back(0.0);
//    b.push_back(1.0);
//    b.push_back(0.0);
//    b.push_back(0.0);

//    Vector<double,3> test;

//    // The test loop
//    while (state.KeepRunning()) {
//        for(int i = 0; i < 3906; i++)
//          test = cornerCutting(c,b);
//    }

//}
//BENCHMARK(BM_pentagon_deCasteljauRevised_degree6);

//static void BM_pentagon_deCasteljauRevised_degree7(benchmark::State& state)
//{
//    DVector<Vector<double,3>> c;
//    c.push_back(GMlib::Vector<double,3>(0.0,0.0,0.0));
//    c.push_back(GMlib::Vector<double,3>(3.0,0.0,0.0));
//    c.push_back(GMlib::Vector<double,3>(1.5,3.0,0.0));
//    c.push_back(GMlib::Vector<double,3>(3.0,0.0,0.0));
//    c.push_back(GMlib::Vector<double,3>(1.5,3.0,0.0));

//    DVector<double> b;
//    b.push_back(0.0);
//    b.push_back(0.0);
//    b.push_back(1.0);
//    b.push_back(0.0);
//    b.push_back(0.0);

//    Vector<double,3> test;

//    // The test loop
//    while (state.KeepRunning()) {
//        for(int i = 0; i < 19531; i++)
//          test = cornerCutting(c,b);
//    }

//}
//BENCHMARK(BM_pentagon_deCasteljauRevised_degree7);

//static void BM_pentagon_deCasteljauRevised_degree8(benchmark::State& state)
//{
//    DVector<Vector<double,3>> c;
//    c.push_back(GMlib::Vector<double,3>(0.0,0.0,0.0));
//    c.push_back(GMlib::Vector<double,3>(3.0,0.0,0.0));
//    c.push_back(GMlib::Vector<double,3>(1.5,3.0,0.0));
//    c.push_back(GMlib::Vector<double,3>(3.0,0.0,0.0));
//    c.push_back(GMlib::Vector<double,3>(1.5,3.0,0.0));

//    DVector<double> b;
//    b.push_back(0.0);
//    b.push_back(0.0);
//    b.push_back(1.0);
//    b.push_back(0.0);
//    b.push_back(0.0);

//    Vector<double,3> test;

//    // The test loop
//    while (state.KeepRunning()) {
//        for(int i = 0; i < 97656; i++)
//          test = cornerCutting(c,b);
//    }

//}
//BENCHMARK(BM_pentagon_deCasteljauRevised_degree8);

//static void BM_pentagon_deCasteljauRevised_degree9(benchmark::State& state)
//{
//    DVector<Vector<double,3>> c;
//    c.push_back(GMlib::Vector<double,3>(0.0,0.0,0.0));
//    c.push_back(GMlib::Vector<double,3>(3.0,0.0,0.0));
//    c.push_back(GMlib::Vector<double,3>(1.5,3.0,0.0));
//    c.push_back(GMlib::Vector<double,3>(3.0,0.0,0.0));
//    c.push_back(GMlib::Vector<double,3>(1.5,3.0,0.0));

//    DVector<double> b;
//    b.push_back(0.0);
//    b.push_back(0.0);
//    b.push_back(1.0);
//    b.push_back(0.0);
//    b.push_back(0.0);

//    Vector<double,3> test;

//    // The test loop
//    while (state.KeepRunning()) {
//        for(int i = 0; i < 488281; i++)
//          test = cornerCutting(c,b);
//    }

//}
//BENCHMARK(BM_pentagon_deCasteljauRevised_degree9);

//static void BM_pentagon_deCasteljauRevised_degree10(benchmark::State& state)
//{
//    DVector<Vector<double,3>> c;
//    c.push_back(GMlib::Vector<double,3>(0.0,0.0,0.0));
//    c.push_back(GMlib::Vector<double,3>(3.0,0.0,0.0));
//    c.push_back(GMlib::Vector<double,3>(1.5,3.0,0.0));
//    c.push_back(GMlib::Vector<double,3>(3.0,0.0,0.0));
//    c.push_back(GMlib::Vector<double,3>(1.5,3.0,0.0));

//    DVector<double> b;
//    b.push_back(0.0);
//    b.push_back(0.0);
//    b.push_back(1.0);
//    b.push_back(0.0);
//    b.push_back(0.0);

//    Vector<double,3> test;

//    // The test loop
//    while (state.KeepRunning()) {
//        for(int i = 0; i < 2441406; i++)
//          test = cornerCutting(c,b);
//    }

//}
//BENCHMARK(BM_pentagon_deCasteljauRevised_degree10);


//static void BM_pentagon_hardCoded_degree1(benchmark::State& state)
//{
//    double u0 = 0, u1 = 0, u2 = 1, u3 = 0, u4 = 0;
//    DVector<Vector<double,3>> c;
//    for(int i = 0; i < 5; i++)
//    {
//      c.push_back(Vector<double,3>(1.0,1.0,0.0));
//    }

//    Vector<double,3> test;

//  // The test loop
//  while (state.KeepRunning()) {
//    test = c[0]*u0 + c[1]*u1 + c[2]*u2 + c[3]*u3 + c[4]*u4;
//  }

//  Vector<double,3> testing;
//  for(int i = 1; i < test.getLength(); i++)
//      testing[i] = test[i];

//}
//BENCHMARK(BM_pentagon_hardCoded_degree1);


//static void BM_pentagon_hardCoded_degree2(benchmark::State& state)
//{
//    double u0 = 0, u1 = 0, u2 = 1, u3 = 0, u4 = 0;
//    DVector<Vector<double,3>> c;
//    for(int i = 0; i < 15; i++)
//    {
//      c.push_back(Vector<double,3>(1.0,1.0,0.0));
//    }

//    Vector<double,3> test;

//  // The test loop
//  while (state.KeepRunning()) {
//    test = c[0]*(u0*u0) + c[1]*(2*u0*u1) + c[2]*(2*u0*u2) + c[3]*(2*u0*u3)
//         + c[4]*(2*u0*u4) + c[5]*(u1*u1) + c[6]*(2*u1*u2) + c[7]*(2*u1*u3)
//         + c[8]*(2*u1*u4) + c[9]*(u2*u2) + c[10]*(2*u2*u3) + c[11]*(2*u2*u4)
//         + c[12]*(u3*u3) + c[13]*(2*u3*u4) + c[14]*(u4*u4);
//  }

//  Vector<double,3> testing;
//  for(int i = 1; i < test.getLength(); i++)
//      testing[i] = test[i];

//}
//BENCHMARK(BM_pentagon_hardCoded_degree2);


//static void BM_pentagon_hardCoded_degree3(benchmark::State& state)
//{
//    double u0 = 0, u1 = 0, u2 = 1, u3 = 0, u4 = 0;
//    DVector<Vector<double,3>> c;
//    for(int i = 0; i < 35; i++)
//    {
//      c.push_back(Vector<double,3>(1.0,1.0,0.0));
//    }
//    Vector<double,3> test;

//  // The test loop
//  while (state.KeepRunning()) {
//    test = c[0]*(u0*u0*u0) + c[1]*(3*u0*u0*u1) + c[2]*(3*u0*u0*u2) + c[3]*(3*u0*u0*u3)
//         + c[4]*(3*u0*u0*u4) + c[5]*(3*u0*u1*u1) + c[6]*(6*u0*u1*u2) + c[7]*(6*u0*u1*u3)
//         + c[8]*(6*u0*u1*u4) + c[9]*(3*u0*u2*u2) + c[10]*(6*u0*u2*u3) + c[11]*(6*u0*u2*u4)
//         + c[12]*(3*u0*u3*u3) + c[13]*(6*u0*u3*u4) + c[14]*(3*u0*u4*u4) + c[15]*(u1*u1*u1)
//         + c[16]*(3*u1*u1*u2) + c[17]*(3*u1*u1*u3) + c[18]*(3*u1*u1*u4) + c[19]*(3*u1*u2*u2)
//         + c[20]*(6*u1*u2*u3) + c[21]*(6*u1*u2*u4) + c[22]*(3*u1*u3*u3) + c[23]*(6*u1*u3*u4)
//         + c[24]*(3*u1*u4*u4) + c[25]*(u2*u2*u2) + c[26]*(3*u2*u2*u3) + c[27]*(3*u2*u2*u4)
//         + c[28]*(3*u2*u3*u3) + c[29]*(6*u2*u3*u4) + c[30]*(3*u2*u4*u4) + c[31]*(u3*u3*u3)
//         + c[32]*(3*u3*u3*u4) + c[33]*(3*u3*u4*u4) + c[34]*(u4*u4*u4);
//  }

//  Vector<double,3> testing;
//  for(int i = 1; i < test.getLength(); i++)
//      testing[i] = test[i];

//}
//BENCHMARK(BM_pentagon_hardCoded_degree3);


//static void BM_pentagon_hardCoded_degree4(benchmark::State& state)
//{
//    double u0 = 0, u1 = 0, u2 = 1, u3 = 0, u4 = 0;
//    DVector<Vector<double,3>> c;
//    for(int i = 0; i < 70; i++)
//    {
//      c.push_back(Vector<double,3>(1.0,1.0,0.0));
//    }

//    Vector<double,3> test;

//  // The test loop
//  while (state.KeepRunning()) {
//    test = c[0]*(u0*u0*u0*u0) + c[1]*(4*u0*u0*u0*u1) + c[2]*(4*u0*u0*u0*u2) + c[3]*(4*u0*u0*u0*u3)
//         + c[4]*(4*u0*u0*u0*u4) + c[5]*(6*u0*u0*u1*u1) + c[6]*(12*u0*u0*u1*u2) + c[7]*(12*u0*u0*u1*u3)
//         + c[8]*(12*u0*u0*u1*u4) + c[9]*(6*u0*u0*u2*u2) + c[10]*(12*u0*u0*u2*u3) + c[11]*(12*u0*u0*u2*u4)
//         + c[12]*(6*u0*u0*u3*u3) + c[13]*(12*u0*u0*u3*u4) + c[14]*(6*u0*u0*u4*u4) + c[15]*(4*u0*u1*u1*u1)
//         + c[16]*(12*u0*u1*u1*u2) + c[17]*(12*u0*u1*u1*u3) + c[18]*(12*u0*u1*u1*u4) + c[19]*(12*u0*u1*u2*u2)
//         + c[20]*(24*u0*u1*u2*u3) + c[21]*(24*u0*u1*u2*u4) + c[22]*(12*u0*u1*u3*u3) + c[23]*(24*u0*u1*u3*u4)
//         + c[24]*(12*u0*u1*u4*u4) + c[25]*(4*u0*u2*u2*u2) + c[26]*(12*u0*u2*u2*u3) + c[27]*(12*u0*u2*u2*u4)
//         + c[28]*(12*u0*u2*u3*u3) + c[29]*(24*u0*u2*u3*u4) + c[30]*(12*u0*u2*u4*u4) + c[31]*(4*u0*u3*u3*u3)
//         + c[32]*(12*u0*u3*u3*u4) + c[33]*(12*u0*u3*u4*u4) + c[34]*(4*u0*u4*u4*u4) + c[35]*(u1*u1*u1*u1)
//         + c[36]*(4*u1*u1*u1*u2) + c[37]*(4*u1*u1*u1*u3) + c[38]*(4*u1*u1*u1*u4) + c[39]*(6*u1*u1*u2*u2)
//         + c[40]*(12*u1*u1*u2*u3) + c[41]*(12*u1*u1*u2*u4) + c[42]*(6*u1*u1*u3*u3) + c[43]*(12*u1*u1*u3*u4)
//         + c[44]*(6*u1*u1*u4*4) + c[45]*(4*u1*u2*u2*u2) + c[46]*(12*u1*u2*u2*u3) + c[47]*(12*u1*u2*u2*u4)
//         + c[48]*(12*u1*u2*u3*u3) + c[49]*(24*u1*u2*u3*u4) + c[50]*(12*u1*u2*u4*u4) + c[51]*(4*u1*u3*u3*u3)
//         + c[52]*(12*u1*u3*u3*u4) + c[53]*(12*u1*u3*u4*u4) + c[54]*(4*u1*u4*u4*u4) + c[55]*(u2*u2*u2*u2)
//         + c[56]*(4*u2*u2*u2*u3) + c[57]*(4*u2*u2*u2*u4) + c[58]*(6*u2*u2*u3*u3) + c[59]*(12*u2*u2*u3*u4)
//         + c[60]*(6*u2*u2*u4*u4) + c[61]*(4*u2*u3*u3*u3) + c[62]*(12*u2*u3*u3*u4) + c[63]*(12*u2*u3*u4*u4)
//         + c[64]*(4*u2*u4*u4*u4) + c[65]*(u3*u3*u3*u3) + c[66]*(4*u3*u3*u3*u4) + c[67]*(6*u3*u3*u4*u4)
//         + c[68]*(4*u3*u4*u4*u4) + c[69]*(u4*u4*u4*u4);
//  }

//  Vector<double,3> testing;
//  for(int i = 1; i < test.getLength(); i++)
//      testing[i] = test[i];

//}
//BENCHMARK(BM_pentagon_hardCoded_degree4);

//static void BM_BezierTriangle_deCasteljauRevised_degree1(benchmark::State& state)
//{
//    DVector<Vector<double,3>> c;
//    c.push_back(GMlib::Vector<double,3>(0.0,0.0,0.0));
//    c.push_back(GMlib::Vector<double,3>(3.0,0.0,0.0));
//    c.push_back(GMlib::Vector<double,3>(1.5,3.0,0.0));

//    DVector<double> b;
//    b.push_back(0.0);
//    b.push_back(0.0);
//    b.push_back(1.0);

//    Vector<double,3> test;

//    // The test loop
//    while (state.KeepRunning()) {
//        for(int i = 0; i < 1; i++)
//          test = cornerCutting(c,b);
//    }

//}
//BENCHMARK(BM_BezierTriangle_deCasteljauRevised_degree1);


//static void BM_BezierTriangle_deCasteljauRevised_degree2(benchmark::State& state)
//{
//    DVector<Vector<double,3>> c;
//    c.push_back(GMlib::Vector<double,3>(0.0,0.0,0.0));
//    c.push_back(GMlib::Vector<double,3>(3.0,0.0,0.0));
//    c.push_back(GMlib::Vector<double,3>(1.5,3.0,0.0));

//    DVector<double> b;
//    b.push_back(0.0);
//    b.push_back(0.0);
//    b.push_back(1.0);

//    Vector<double,3> test;

//    // The test loop
//    while (state.KeepRunning()) {
//        for(int i = 0; i < 4; i++)
//          test = cornerCutting(c,b);
//    }
//}
//BENCHMARK(BM_BezierTriangle_deCasteljauRevised_degree2);

//static void BM_BezierTriangle_deCasteljauRevised_degree3(benchmark::State& state)
//{
//    DVector<Vector<double,3>> c;
//    c.push_back(GMlib::Vector<double,3>(0.0,0.0,0.0));
//    c.push_back(GMlib::Vector<double,3>(3.0,0.0,0.0));
//    c.push_back(GMlib::Vector<double,3>(1.5,3.0,0.0));

//    DVector<double> b;
//    b.push_back(0.0);
//    b.push_back(0.0);
//    b.push_back(1.0);

//    Vector<double,3> test;

//    // The test loop
//    while (state.KeepRunning()) {
//        for(int i = 0; i < 13; i++)
//          test = cornerCutting(c,b);
//    }

//}
//BENCHMARK(BM_BezierTriangle_deCasteljauRevised_degree3);


//static void BM_BezierTriangle_deCasteljauRevised_degree4(benchmark::State& state)
//{
//    DVector<Vector<double,3>> c;
//    c.push_back(GMlib::Vector<double,3>(0.0,0.0,0.0));
//    c.push_back(GMlib::Vector<double,3>(3.0,0.0,0.0));
//    c.push_back(GMlib::Vector<double,3>(1.5,3.0,0.0));

//    DVector<double> b;
//    b.push_back(0.0);
//    b.push_back(0.0);
//    b.push_back(1.0);

//    Vector<double,3> test;

//    // The test loop
//    while (state.KeepRunning()) {
//        for(int i = 0; i < 40; i++)
//          test = cornerCutting(c,b);
//    }

//}
//BENCHMARK(BM_BezierTriangle_deCasteljauRevised_degree4);

//static void BM_BezierTriangle_deCasteljauRevised_degree5(benchmark::State& state)
//{
//    DVector<Vector<double,3>> c;
//    c.push_back(GMlib::Vector<double,3>(0.0,0.0,0.0));
//    c.push_back(GMlib::Vector<double,3>(3.0,0.0,0.0));
//    c.push_back(GMlib::Vector<double,3>(1.5,3.0,0.0));

//    DVector<double> b;
//    b.push_back(0.0);
//    b.push_back(0.0);
//    b.push_back(1.0);

//    Vector<double,3> test;

//    // The test loop
//    while (state.KeepRunning()) {
//        for(int i = 0; i < 121; i++)
//          test = cornerCutting(c,b);
//    }

//}
//BENCHMARK(BM_BezierTriangle_deCasteljauRevised_degree5);


//static void BM_BezierTriangle_deCasteljauRevised_degree6(benchmark::State& state)
//{
//    DVector<Vector<double,3>> c;
//    c.push_back(GMlib::Vector<double,3>(0.0,0.0,0.0));
//    c.push_back(GMlib::Vector<double,3>(3.0,0.0,0.0));
//    c.push_back(GMlib::Vector<double,3>(1.5,3.0,0.0));

//    DVector<double> b;
//    b.push_back(0.0);
//    b.push_back(0.0);
//    b.push_back(1.0);

//    Vector<double,3> test;

//    // The test loop
//    while (state.KeepRunning()) {
//        for(int i = 0; i < 364; i++)
//          test = cornerCutting(c,b);
//    }

//}
//BENCHMARK(BM_BezierTriangle_deCasteljauRevised_degree6);

//static void BM_BezierTriangle_deCasteljauRevised_degree7(benchmark::State& state)
//{
//    DVector<Vector<double,3>> c;
//    c.push_back(GMlib::Vector<double,3>(0.0,0.0,0.0));
//    c.push_back(GMlib::Vector<double,3>(3.0,0.0,0.0));
//    c.push_back(GMlib::Vector<double,3>(1.5,3.0,0.0));

//    DVector<double> b;
//    b.push_back(0.0);
//    b.push_back(0.0);
//    b.push_back(1.0);

//    Vector<double,3> test;

//    // The test loop
//    while (state.KeepRunning()) {
//        for(int i = 0; i < 1093; i++)
//          test = cornerCutting(c,b);
//    }
//}
//BENCHMARK(BM_BezierTriangle_deCasteljauRevised_degree7);


//static void BM_BezierTriangle_deCasteljauRevised_degree8(benchmark::State& state)
//{
//    DVector<Vector<double,3>> c;
//    c.push_back(GMlib::Vector<double,3>(0.0,0.0,0.0));
//    c.push_back(GMlib::Vector<double,3>(3.0,0.0,0.0));
//    c.push_back(GMlib::Vector<double,3>(1.5,3.0,0.0));

//    DVector<double> b;
//    b.push_back(0.0);
//    b.push_back(0.0);
//    b.push_back(1.0);

//    Vector<double,3> test;

//    // The test loop
//    while (state.KeepRunning()) {
//        for(int i = 0; i < 3280; i++)
//          test = cornerCutting(c,b);
//    }
//}
//BENCHMARK(BM_BezierTriangle_deCasteljauRevised_degree8);

//static void BM_BezierTriangle_deCasteljauRevised_degree9(benchmark::State& state)
//{
//    DVector<Vector<double,3>> c;
//    c.push_back(GMlib::Vector<double,3>(0.0,0.0,0.0));
//    c.push_back(GMlib::Vector<double,3>(3.0,0.0,0.0));
//    c.push_back(GMlib::Vector<double,3>(1.5,3.0,0.0));

//    DVector<double> b;
//    b.push_back(0.0);
//    b.push_back(0.0);
//    b.push_back(1.0);

//    Vector<double,3> test;

//    // The test loop
//    while (state.KeepRunning()) {
//        for(int i = 0; i < 9841; i++)
//          test = cornerCutting(c,b);
//    }

//}
//BENCHMARK(BM_BezierTriangle_deCasteljauRevised_degree9);


//static void BM_BezierTriangle_deCasteljauRevised_degree10(benchmark::State& state)
//{
//    DVector<Vector<double,3>> c;
//    c.push_back(GMlib::Vector<double,3>(0.0,0.0,0.0));
//    c.push_back(GMlib::Vector<double,3>(3.0,0.0,0.0));
//    c.push_back(GMlib::Vector<double,3>(1.5,3.0,0.0));

//    DVector<double> b;
//    b.push_back(0.0);
//    b.push_back(0.0);
//    b.push_back(1.0);

//    Vector<double,3> test;

//    // The test loop
//    while (state.KeepRunning()) {
//        for(int i = 0; i < 29524; i++)
//          test = cornerCutting(c,b);
//    }

//}
//BENCHMARK(BM_BezierTriangle_deCasteljauRevised_degree10);


//static void BM_BezierTriangle_hardCoded_degree1(benchmark::State& state)
//{
//    double u = 1, v = 0, w = 0;
//    DVector<Vector<double,3>> c;
//    for(int i = 0; i < 3; i++)
//    {
//      c.push_back(Vector<double,3>(1.0,1.0,0.0));
//    }
//    Vector<double,3> test;

//  // The test loop
//  while (state.KeepRunning()) {
//    test = c[0]*u + c[1]*v + c[2]*w;
//  }

//  Vector<double,3> testing;
//  for(int i = 1; i < test.getLength(); i++)
//      testing[i] = test[i];

//}
//BENCHMARK(BM_BezierTriangle_hardCoded_degree1);


//static void BM_BezierTriangle_hardCoded_degree2(benchmark::State& state)
//{
//    double u = 1, v = 0, w = 0;
//    DVector<Vector<double,3>> c;
//    for(int i = 0; i < 6; i++)
//    {
//      c.push_back(Vector<double,3>(1.0,1.0,0.0));
//    }
//    Vector<double,3> test;

//  // The test loop
//  while (state.KeepRunning()) {
//    test = c[0]*(u*u) + c[1]*(2*u*v) + c[2]*(2*u*w)
//         + c[3]*(v*v) + c[4]*(2*v*w) + c[5]*(w*w);
//  }

//  Vector<double,3> testing;
//  for(int i = 1; i < test.getLength(); i++)
//      testing[i] = test[i];

//}
//BENCHMARK(BM_BezierTriangle_hardCoded_degree2);


//static void BM_BezierTriangle_hardCoded_degree3(benchmark::State& state)
//{
//    double u = 1, v = 0, w = 0;
//    DVector<Vector<double,3>> c;
//    for(int i = 0; i < 10; i++)
//    {
//      c.push_back(Vector<double,3>(1.0,1.0,0.0));
//    }
//    Vector<double,3> test;

//  // The test loop
//  while (state.KeepRunning()) {
//    test = c[0]*(u*u*u) + c[1]*(3*u*u*v) + c[2]*(3*u*u*w)
//         + c[3]*(3*u*v*v) + c[4]*(6*u*v*w) + c[5]*(3*u*w*w)
//         + c[6]*(v*v*v) + c[7]*(3*v*v*w) + c[8]*(3*v*w*w) + c[9]*(w*w*w);
//  }

//  Vector<double,3> testing;
//  for(int i = 1; i < test.getLength(); i++)
//      testing[i] = test[i];

//}
//BENCHMARK(BM_BezierTriangle_hardCoded_degree3);


//static void BM_BezierTriangle_hardCoded_degree4(benchmark::State& state)
//{
//    double u = 1, v = 0, w = 0;
//    DVector<Vector<double,3>> c;
//    for(int i = 0; i < 15; i++)
//    {
//      c.push_back(Vector<double,3>(1.0,1.0,0.0));
//    }
//    Vector<double,3> test;

//  // The test loop
//  while (state.KeepRunning()) {
//    test = c[0]*(u*u*u*u) + c[1]*(4*u*u*u*v) + c[2]*(4*u*u*u*w)
//         + c[3]*(6*u*u*v*v) + c[4]*(12*u*u*v*w) + c[5]*(6*u*u*w*w)
//         + c[6]*(4*u*v*v*v) + c[7]*(12*u*v*v*w) + c[8]*(12*u*v*w*w)
//         + c[9]*(4*u*w*w*w) + c[10]*(v*v*v*v) + c[11]*(4*v*v*v*w)
//         + c[12]*(6*v*v*w*w) + c[13]*(4*v*w*w*w) + c[14]*(w*w*w*w);
//  }

//  Vector<double,3> testing;
//  for(int i = 1; i < test.getLength(); i++)
//      testing[i] = test[i];

//}
//BENCHMARK(BM_BezierTriangle_hardCoded_degree4);


//static void BM_BezierTriangle_hardCoded_degree5(benchmark::State& state)
//{
//    double u = 1, v = 0, w = 0;
//    DVector<Vector<double,3>> c;
//    for(int i = 0; i < 21; i++)
//    {
//      c.push_back(Vector<double,3>(1.0,1.0,0.0));
//    }
//    Vector<double,3> test;

//  // The test loop
//  while (state.KeepRunning()) {
//    test = c[0]*(u*u*u*u*u) + c[1]*(5*u*u*u*u*v) + c[2]*(5*u*u*u*u*w)
//         + c[3]*(10*u*u*u*v*v) + c[4]*(20*u*u*u*v*w) + c[5]*(10*u*u*u*w*w)
//         + c[6]*(10*u*u*v*v*v) + c[7]*(30*u*u*v*v*w) + c[8]*(30*u*u*v*w*w)
//         + c[9]*(10*u*u*w*w*w) + c[10]*(5*u*v*v*v*v) + c[11]*(20*u*v*v*v*w)
//         + c[12]*(30*u*v*v*w*w) + c[13]*(20*u*v*w*w*w) + c[14]*(5*u*w*w*w*w)
//         + c[15]*(v*v*v*v*v) + c[16]*(5*v*v*v*v*w) + c[17]*(10*v*v*v*w*w)
//         + c[18]*(10*v*v*w*w*w) + c[19]*(5*v*w*w*w*w) + c[20]*(w*w*w*w*w);
//  }

//  Vector<double,3> testing;
//  for(int i = 1; i < test.getLength(); i++)
//      testing[i] = test[i];

//}
//BENCHMARK(BM_BezierTriangle_hardCoded_degree5);


//static void BM_BezierTriangle_hardCoded_degree6(benchmark::State& state)
//{
//    double u = 1, v = 0, w = 0;
//    DVector<Vector<double,3>> c;
//    for(int i = 0; i < 28; i++)
//    {
//      c.push_back(Vector<double,3>(1.0,1.0,0.0));
//    }
//    Vector<double,3> test;

//  // The test loop
//  while (state.KeepRunning()) {
//    test = c[0]*(u*u*u*u*u*u) + c[1]*(6*u*u*u*u*u*v) + c[2]*(6*u*u*u*u*u*w)
//         + c[3]*(15*u*u*u*u*v*v) + c[4]*(30*u*u*u*u*v*w) + c[5]*(15*u*u*u*u*w*w)
//         + c[6]*(20*u*u*u*v*v*v) + c[7]*(60*u*u*u*v*v*w) + c[8]*(60*u*u*u*v*w*w)
//         + c[9]*(20*u*u*u*w*w*w) + c[10]*(15*u*u*v*v*v*v) + c[11]*(60*u*u*v*v*v*w)
//         + c[12]*(90*u*u*v*v*w*w) + c[13]*(60*u*u*v*w*w*w) + c[14]*(15*u*u*w*w*w*w)
//         + c[15]*(6*u*v*v*v*v*v) + c[16]*(30*u*v*v*v*v*w) + c[17]*(60*u*v*v*v*w*w)
//         + c[18]*(60*u*v*v*w*w*w) + c[19]*(30*u*v*w*w*w*w) + c[20]*(6*u*w*w*w*w*w)
//         + c[21]*(v*v*v*v*v*v) + c[22]*(6*v*v*v*v*v*w) + c[23]*(15*v*v*v*v*w*w)
//         + c[24]*(20*v*v*v*w*w*w) + c[25]*(15*v*v*w*w*w*w) + c[26]*(6*v*w*w*w*w*w)
//         + c[27]*(w*w*w*w*w*w);
//  }

//  Vector<double,3> testing;
//  for(int i = 1; i < test.getLength(); i++)
//      testing[i] = test[i];

//}
//BENCHMARK(BM_BezierTriangle_hardCoded_degree6);


//static void BM_BezierTriangle_hardCoded_degree7(benchmark::State& state)
//{
//    double u = 1, v = 0, w = 0;
//    DVector<Vector<double,3>> c;
//    for(int i = 0; i < 36; i++)
//    {
//      c.push_back(Vector<double,3>(1.0,1.0,0.0));
//    }

//    Vector<double,3> test;

//  // The test loop
//  while (state.KeepRunning()) {
//    test = c[0]*(u*u*u*u*u*u*u) + c[1]*(7*u*u*u*u*u*u*v) + c[2]*(7*u*u*u*u*u*u*w)
//         + c[3]*(21*u*u*u*u*u*v*v) + c[4]*(42*u*u*u*u*u*v*w) + c[5]*(21*u*u*u*u*u*w*w)
//         + c[6]*(35*u*u*u*u*v*v*v) + c[7]*(105*u*u*u*u*v*v*w) + c[8]*(105*u*u*u*u*v*w*w)
//         + c[9]*(35*u*u*u*u*w*w*w) + c[10]*(35*u*u*u*v*v*v*v) + c[11]*(140*u*u*u*v*v*v*w)
//         + c[12]*(210*u*u*u*v*v*w*w) + c[13]*(140*u*u*u*v*w*w*w) + c[14]*(35*u*u*u*w*w*w*w)
//         + c[15]*(21*u*u*v*v*v*v*v) + c[16]*(105*u*u*v*v*v*v*w) + c[17]*(210*u*u*v*v*v*w*w)
//         + c[18]*(210*u*u*v*v*w*w*w) + c[19]*(105*u*u*v*w*w*w*w) + c[20]*(21*u*u*w*w*w*w*w)
//         + c[21]*(7*u*v*v*v*v*v*v) + c[22]*(42*u*v*v*v*v*v*w) + c[23]*(105*u*v*v*v*v*w*w)
//         + c[24]*(140*u*v*v*v*w*w*w) + c[25]*(105*u*v*v*w*w*w*w) + c[26]*(42*u*v*w*w*w*w*w)
//         + c[27]*(7*u*w*w*w*w*w*w) + c[28]*(v*v*v*v*v*v*v) + c[29]*(7*v*v*v*v*v*v*w)
//         + c[30]*(21*v*v*v*v*v*w*w) + c[31]*(35*v*v*v*v*w*w*w) + c[32]*(35*v*v*v*w*w*w*w)
//         + c[33]*(21*v*v*w*w*w*w*w) + c[34]*(7*v*w*w*w*w*w*w) + c[35]*(w*w*w*w*w*w*w);
//  }

//  Vector<double,3> testing;
//  for(int i = 1; i < test.getLength(); i++)
//      testing[i] = test[i];

//}
//BENCHMARK(BM_BezierTriangle_hardCoded_degree7);


//static void BM_BezierTriangle_hardCoded_degree8(benchmark::State& state)
//{
//    double u = 1, v = 0, w = 0;
//    DVector<Vector<double,3>> c;
//    for(int i = 0; i < 45; i++)
//    {
//      c.push_back(Vector<double,3>(1.0,1.0,0.0));
//    }

//    Vector<double,3> test;

//  // The test loop
//  while (state.KeepRunning()) {
//    test = c[0]*(u*u*u*u*u*u*u*u) + c[1]*(8*u*u*u*u*u*u*u*v) + c[2]*(8*u*u*u*u*u*u*u*w)
//         + c[3]*(28*u*u*u*u*u*u*v*v) + c[4]*(56*u*u*u*u*u*u*v*w) + c[5]*(28*u*u*u*u*u*u*w*w)
//         + c[6]*(56*u*u*u*u*u*v*v*v) + c[7]*(168*u*u*u*u*u*v*v*w) + c[8]*(168*u*u*u*u*u*v*w*w)
//         + c[9]*(56*u*u*u*u*u*w*w*w) + c[10]*(70*u*u*u*u*v*v*v*v) + c[11]*(280*u*u*u*u*v*v*v*w)
//         + c[12]*(420*u*u*u*u*v*v*w*w) + c[13]*(280*u*u*u*u*v*w*w*w) + c[14]*(70*u*u*u*u*w*w*w*w)
//         + c[15]*(56*u*u*u*v*v*v*v*v) + c[16]*(280*u*u*u*v*v*v*v*w) + c[17]*(560*u*u*u*v*v*v*w*w)
//         + c[18]*(560*u*u*u*v*v*w*w*w) + c[19]*(280*u*u*u*v*w*w*w*w) + c[20]*(56*u*u*u*w*w*w*w*w)
//         + c[21]*(28*u*u*v*v*v*v*v*v) + c[22]*(168*u*u*v*v*v*v*v*w) + c[23]*(420*u*u*v*v*v*v*w*w)
//         + c[24]*(560*u*u*v*v*v*w*w*w) + c[25]*(420*u*u*v*v*w*w*w*w) + c[26]*(168*u*u*v*w*w*w*w*w)
//         + c[27]*(28*u*u*w*w*w*w*w*w) + c[28]*(8*u*v*v*v*v*v*v*v) + c[29]*(56*u*v*v*v*v*v*v*w)
//         + c[30]*(168*u*v*v*v*v*v*w*w) + c[31]*(280*u*v*v*v*v*w*w*w) + c[32]*(280*u*v*v*v*w*w*w*w)
//         + c[33]*(168*u*v*v*w*w*w*w*w) + c[34]*(56*u*v*w*w*w*w*w*w) + c[35]*(8*u*w*w*w*w*w*w*w)
//         + c[36]*(v*v*v*v*v*v*v*v) + c[37]*(8*v*v*v*v*v*v*v*w) + c[38]*(28*v*v*v*v*v*v*w*w)
//         + c[39]*(56*v*v*v*v*v*w*w*w) + c[40]*(70*v*v*v*v*w*w*w*w) + c[41]*(56*v*v*v*w*w*w*w*w)
//         + c[42]*(28*v*v*w*w*w*w*w*w) + c[43]*(8*v*w*w*w*w*w*w*w) + c[44]*(w*w*w*w*w*w*w*w);
//  }

//  Vector<double,3> testing;
//  for(int i = 1; i < test.getLength(); i++)
//      testing[i] = test[i];

//}
//BENCHMARK(BM_BezierTriangle_hardCoded_degree8);


//static void BM_BezierTriangle_hardCoded_degree9(benchmark::State& state)
//{
//    double u = 1, v = 0, w = 0;
//    DVector<Vector<double,3>> c;
//    for(int i = 0; i < 55; i++)
//    {
//      c.push_back(Vector<double,3>(1.0,1.0,0.0));
//    }

//    Vector<double,3> test;

//  // The test loop
//  while (state.KeepRunning()) {
//    test = c[0]*(u*u*u*u*u*u*u*u*u) + c[1]*(9*u*u*u*u*u*u*u*u*v) + c[2]*(9*u*u*u*u*u*u*u*u*w)
//         + c[3]*(36*u*u*u*u*u*u*u*v*v) + c[4]*(72*u*u*u*u*u*u*u*v*w) + c[5]*(36*u*u*u*u*u*u*u*w*w)
//         + c[6]*(84*u*u*u*u*u*u*v*v*v) + c[7]*(252*u*u*u*u*u*u*v*v*w) + c[8]*(252*u*u*u*u*u*u*v*w*w)
//         + c[9]*(84*u*u*u*u*u*u*w*w*w) + c[10]*(126*u*u*u*u*u*v*v*v*v) + c[11]*(504*u*u*u*u*u*v*v*v*w)
//         + c[12]*(756*u*u*u*u*u*v*v*w*w) + c[13]*(504*u*u*u*u*u*v*w*w*w) + c[14]*(126*u*u*u*u*u*w*w*w*w)
//         + c[15]*(126*u*u*u*u*v*v*v*v*v) + c[16]*(630*u*u*u*u*v*v*v*v*w) + c[17]*(1260*u*u*u*u*v*v*v*w*w)
//         + c[18]*(1260*u*u*u*u*v*v*w*w*w) + c[19]*(630*u*u*u*u*v*w*w*w*w) + c[20]*(126*u*u*u*u*w*w*w*w*w)
//         + c[21]*(84*u*u*u*v*v*v*v*v*v) + c[22]*(504*u*u*u*v*v*v*v*v*w) + c[23]*(1260*u*u*u*v*v*v*v*w*w)
//         + c[24]*(1680*u*u*u*v*v*v*w*w*w) + c[25]*(1260*u*u*u*v*v*w*w*w*w) + c[26]*(504*u*u*u*v*w*w*w*w*w)
//         + c[27]*(84*u*u*u*w*w*w*w*w*w) + c[28]*(36*u*u*v*v*v*v*v*v*v) + c[29]*(252*u*u*v*v*v*v*v*v*w)
//         + c[30]*(756*u*u*v*v*v*v*v*w*w) + c[31]*(1260*u*u*v*v*v*v*w*w*w) + c[32]*(1260*u*u*v*v*v*w*w*w*w)
//         + c[33]*(756*u*u*v*v*w*w*w*w*w) + c[34]*(252*u*u*v*w*w*w*w*w*w) + c[35]*(36*u*u*w*w*w*w*w*w*w)
//         + c[36]*(9*u*v*v*v*v*v*v*v*v) + c[37]*(72*u*v*v*v*v*v*v*v*w) + c[38]*(252*u*v*v*v*v*v*v*w*w)
//         + c[39]*(504*u*v*v*v*v*v*w*w*w) + c[40]*(630*u*v*v*v*v*w*w*w*w) + c[41]*(504*u*v*v*v*w*w*w*w*w)
//         + c[42]*(252*u*v*v*w*w*w*w*w*w) + c[43]*(72*u*v*w*w*w*w*w*w*w) + c[44]*(9*u*w*w*w*w*w*w*w*w)
//         + c[45]*(v*v*v*v*v*v*v*v*v) + c[46]*(9*v*v*v*v*v*v*v*v*w) + c[47]*(36*v*v*v*v*v*v*v*w*w)
//         + c[48]*(84*v*v*v*v*v*v*w*w*w) + c[49]*(126*v*v*v*v*v*w*w*w*w) + c[50]*(126*v*v*v*v*w*w*w*w*w)
//         + c[51]*(84*v*v*v*w*w*w*w*w*w) + c[52]*(36*v*v*w*w*w*w*w*w*w) + c[53]*(9*v*w*w*w*w*w*w*w*w)
//         + c[54]*(w*w*w*w*w*w*w*w*w);
//  }

//  Vector<double,3> testing;
//  for(int i = 1; i < test.getLength(); i++)
//      testing[i] = test[i];

//}
//BENCHMARK(BM_BezierTriangle_hardCoded_degree9);


//static void BM_BezierTriangle_hardCoded_degree10(benchmark::State& state)
//{
//    double u = 1, v = 0, w = 0;
//    DVector<Vector<double,3>> c;
//    for(int i = 0; i < 66; i++)
//    {
//      c.push_back(Vector<double,3>(1.0,1.0,0.0));
//    }

//    Vector<double,3> test;

//  // The test loop
//  while (state.KeepRunning()) {
//    test = c[0]*(u*u*u*u*u*u*u*u*u*u) + c[1]*(10*u*u*u*u*u*u*u*u*u*v) + c[2]*(10*u*u*u*u*u*u*u*u*u*w)
//         + c[3]*(45*u*u*u*u*u*u*u*u*v*v) + c[4]*(90*u*u*u*u*u*u*u*u*v*w) + c[5]*(45*u*u*u*u*u*u*u*u*w*w)
//         + c[6]*(120*u*u*u*u*u*u*u*v*v*v) + c[7]*(360*u*u*u*u*u*u*u*v*v*w) + c[8]*(360*u*u*u*u*u*u*u*v*w*w)
//         + c[9]*(120*u*u*u*u*u*u*u*w*w*w) + c[10]*(210*u*u*u*u*u*u*v*v*v*v) + c[11]*(840*u*u*u*u*u*u*v*v*v*w)
//         + c[12]*(1260*u*u*u*u*u*u*v*v*w*w) + c[13]*(840*u*u*u*u*u*u*v*w*w*w) + c[14]*(210*u*u*u*u*u*u*w*w*w*w)
//         + c[15]*(252*u*u*u*u*u*v*v*v*v*v) + c[16]*(1260*u*u*u*u*u*v*v*v*v*w) + c[17]*(2520*u*u*u*u*u*v*v*v*w*w)
//         + c[18]*(2520*u*u*u*u*u*v*v*w*w*w) + c[19]*(1260*u*u*u*u*u*v*w*w*w*w) + c[20]*(252*u*u*u*u*u*w*w*w*w*w)
//         + c[21]*(210*u*u*u*u*v*v*v*v*v*v) + c[22]*(1260*u*u*u*u*v*v*v*v*v*w) + c[23]*(3150*u*u*u*u*v*v*v*v*w*w)
//         + c[24]*(4200*u*u*u*u*v*v*v*w*w*w) + c[25]*(3150*u*u*u*u*v*v*w*w*w*w) + c[26]*(1260*u*u*u*u*v*w*w*w*w*w)
//         + c[27]*(210*u*u*u*u*w*w*w*w*w*w) + c[28]*(120*u*u*u*v*v*v*v*v*v*v) + c[29]*(840*u*u*u*v*v*v*v*v*v*w)
//         + c[30]*(2520*u*u*u*v*v*v*v*v*w*w) + c[31]*(4200*u*u*u*v*v*v*v*w*w*w) + c[32]*(4200*u*u*u*v*v*v*w*w*w*w)
//         + c[33]*(2520*u*u*u*v*v*w*w*w*w*w) + c[34]*(840*u*u*u*v*w*w*w*w*w*w) + c[35]*(120*u*u*u*w*w*w*w*w*w*w)
//         + c[36]*(45*u*u*v*v*v*v*v*v*v*v) + c[37]*(360*u*u*v*v*v*v*v*v*v*w) + c[38]*(1260*u*u*v*v*v*v*v*v*w*w)
//         + c[39]*(2520*u*u*v*v*v*v*v*w*w*w) + c[40]*(3150*u*u*v*v*v*v*w*w*w*w) + c[41]*(2520*u*u*v*v*v*w*w*w*w*w)
//         + c[42]*(1260*u*u*v*v*w*w*w*w*w*w) + c[43]*(360*u*u*v*w*w*w*w*w*w*w) + c[44]*(45*u*u*w*w*w*w*w*w*w*w)
//         + c[45]*(10*u*v*v*v*v*v*v*v*v*v) + c[46]*(90*u*v*v*v*v*v*v*v*v*w) + c[47]*(360*u*v*v*v*v*v*v*v*w*w)
//         + c[48]*(840*u*v*v*v*v*v*v*w*w*w) + c[49]*(1260*u*v*v*v*v*v*w*w*w*w) + c[50]*(1260*u*v*v*v*v*w*w*w*w*w)
//         + c[51]*(840*u*v*v*v*w*w*w*w*w*w) + c[52]*(360*u*v*v*w*w*w*w*w*w*w) + c[53]*(90*u*v*w*w*w*w*w*w*w*w)
//         + c[54]*(10*u*w*w*w*w*w*w*w*w*w) + c[55]*(v*v*v*v*v*v*v*v*v*v) + c[56]*(10*v*v*v*v*v*v*v*v*v*w)
//         + c[57]*(45*v*v*v*v*v*v*v*v*w*w) + c[58]*(120*v*v*v*v*v*v*v*w*w*w) + c[59]*(210*v*v*v*v*v*v*w*w*w*w)
//         + c[60]*(252*v*v*v*v*v*w*w*w*w*w) + c[61]*(210*v*v*v*v*w*w*w*w*w*w) + c[62]*(120*v*v*v*w*w*w*w*w*w*w)
//         + c[63]*(45*v*v*w*w*w*w*w*w*w*w) + c[64]*(10*v*w*w*w*w*w*w*w*w*w) + c[65]*(w*w*w*w*w*w*w*w*w*w);
//  }

//  Vector<double,3> testing;
//  for(int i = 1; i < test.getLength(); i++)
//      testing[i] = test[i];

//}
//BENCHMARK(BM_BezierTriangle_hardCoded_degree10);

//static void BM_BezierTriangle_deCasteljau_matrix_degree1(benchmark::State& state)
//{
//  int d = 3;
//  DVector<Vector<double,3>> c(10);
//  c[0] = GMlib::Vector<double,3>(0.0,0.0,1.0);
//  c[1] = GMlib::Vector<double,3>(1.0,0.0,0.0);
//  c[2] = GMlib::Vector<double,3>(0.5,1.0,0.0);


//  DVector<double> up(3);
//  up[0] = 0.5;
//  up[1] = 0.3;
//  up[2] = 0.2;
//  auto T1 = GMPutils::computeT(d-1,1, up);

//  DVector<Vector<double,3>> V;

//  // The test loop
//  while (state.KeepRunning()) {
//    V = T1 * c;
//  }

//  Vector<double,3> res;
//  for (int i=0; i < 3; ++i)
//    res[i] = V(0)(i);

//}
//BENCHMARK(BM_BezierTriangle_deCasteljau_matrix_degree1);

//static void BM_BezierTriangle_deCasteljau_matrix_degree2(benchmark::State& state)
//{
//  int d = 3;
//  DVector<Vector<double,3>> c(10);
//  c[0] = GMlib::Vector<double,3>(0.0,0.0,1.0);
//  c[1] = GMlib::Vector<double,3>(1.0,0.0,0.0);
//  c[2] = GMlib::Vector<double,3>(0.5,1.0,0.0);
//  c[3] = GMlib::Vector<double,3>(2.0,0.0,0.0);
//  c[4] = GMlib::Vector<double,3>(1.5,1.0,0.0);
//  c[5] = GMlib::Vector<double,3>(1.0,2.0,0.0);


//  DVector<double> up(3);
//  up[0] = 0.5;
//  up[1] = 0.3;
//  up[2] = 0.2;
//  auto T1 = GMPutils::computeT(d-1,1, up);
//  auto T2 = GMPutils::computeT(d-1,2, up);

//  DVector<Vector<double,3>> V;

//  // The test loop
//  while (state.KeepRunning()) {
//    auto a = T2 * c;
//    V = T1 * a;
//  }

//  Vector<double,3> res;
//  for (int i=0; i < 3; ++i)
//    res[i] = V(0)(i);

//}
//BENCHMARK(BM_BezierTriangle_deCasteljau_matrix_degree2);

//static void BM_BezierTriangle_deCasteljau_matrix_degree3(benchmark::State& state)
//{
//  int d = 3;
//  DVector<Vector<double,3>> c(10);
//  c[0] = GMlib::Vector<double,3>(0.0,0.0,1.0);
//  c[1] = GMlib::Vector<double,3>(1.0,0.0,0.0);
//  c[2] = GMlib::Vector<double,3>(0.5,1.0,0.0);
//  c[3] = GMlib::Vector<double,3>(2.0,0.0,0.0);
//  c[4] = GMlib::Vector<double,3>(1.5,1.0,0.0);
//  c[5] = GMlib::Vector<double,3>(1.0,2.0,0.0);
//  c[6] = GMlib::Vector<double,3>(3.0,0.0,1.0);
//  c[7] = GMlib::Vector<double,3>(2.5,1.0,0.0);
//  c[8] = GMlib::Vector<double,3>(2.0,2.0,0.0);
//  c[9] = GMlib::Vector<double,3>(1.5,3.0,1.0);


//  DVector<double> up(3);
//  up[0] = 0.5;
//  up[1] = 0.3;
//  up[2] = 0.2;
//  auto T1 = GMPutils::computeT(d-1,1, up);
//  auto T2 = GMPutils::computeT(d-1,2, up);
//  auto T3 = GMPutils::computeT(d-1,3, up);

//  DVector<Vector<double,3>> V;

//  // The test loop
//  while (state.KeepRunning()) {
//    auto a = T3 * c;
//    auto b = T2 * a;
//    V = T1 * b;
//  }

//  Vector<double,3> res;
//  for (int i=0; i < 3; ++i)
//    res[i] = V(0)(i);

//}
//BENCHMARK(BM_BezierTriangle_deCasteljau_matrix_degree3);

//static void BM_BezierTriangle_deCasteljau_matrix_degree4(benchmark::State& state)
//{
//    DVector<Vector<double,3>> c;
//    c.push_back(Vector<double,3>(1.0,1.0,0.0));
//    c.push_back(Vector<double,3>(5.0,1.0,0.0));
//    c.push_back(Vector<double,3>(6.0,4.0,0.0));
//    c.push_back(Vector<double,3>(3.0,6.0,0.0));
//    c.push_back(Vector<double,3>(0.0,4.0,0.0));
//    c.push_back(Vector<double,3>(1.0,1.0,0.0));
//    c.push_back(Vector<double,3>(6.0,4.0,0.0));
//    c.push_back(Vector<double,3>(3.0,6.0,0.0));
//    c.push_back(Vector<double,3>(0.0,4.0,0.0));
//    c.push_back(Vector<double,3>(1.0,1.0,0.0));
//    c.push_back(Vector<double,3>(1.0,1.0,0.0));
//    c.push_back(Vector<double,3>(6.0,4.0,0.0));
//    c.push_back(Vector<double,3>(3.0,6.0,0.0));
//    c.push_back(Vector<double,3>(0.0,4.0,0.0));
//    c.push_back(Vector<double,3>(1.0,1.0,0.0));


//    DVector<double> b;
//    b.push_back(0.0);
//    b.push_back(0.0);
//    b.push_back(1.0);

//    auto T1 = GMPutils::computeT(2,1, b);
//    auto T2 = GMPutils::computeT(2,2, b);
//    auto T3 = GMPutils::computeT(2,3, b);
//    auto T4 = GMPutils::computeT(2,4, b);

//    DVector<Vector<double,3>> test;

//    // The test loop
//    while (state.KeepRunning()) {
//      auto a = T4 * c;
//      auto b = T3 * a;
//      auto cc = T2 * b;
//      test = T1 * cc;
//    }

//}
//BENCHMARK(BM_BezierTriangle_deCasteljau_matrix_degree4);

//static void BM_BezierTriangle_deCasteljau_matrix_degree5(benchmark::State& state)
//{
//    DVector<Vector<double,3>> c;
//    c.push_back(Vector<double,3>(1.0,1.0,0.0));
//    c.push_back(Vector<double,3>(5.0,1.0,0.0));
//    c.push_back(Vector<double,3>(6.0,4.0,0.0));
//    c.push_back(Vector<double,3>(3.0,6.0,0.0));
//    c.push_back(Vector<double,3>(0.0,4.0,0.0));
//    c.push_back(Vector<double,3>(1.0,1.0,0.0));
//    c.push_back(Vector<double,3>(6.0,4.0,0.0));
//    c.push_back(Vector<double,3>(3.0,6.0,0.0));
//    c.push_back(Vector<double,3>(0.0,4.0,0.0));
//    c.push_back(Vector<double,3>(1.0,1.0,0.0));
//    c.push_back(Vector<double,3>(1.0,1.0,0.0));
//    c.push_back(Vector<double,3>(6.0,4.0,0.0));
//    c.push_back(Vector<double,3>(3.0,6.0,0.0));
//    c.push_back(Vector<double,3>(0.0,4.0,0.0));
//    c.push_back(Vector<double,3>(1.0,1.0,0.0));
//    c.push_back(Vector<double,3>(1.0,1.0,0.0));
//    c.push_back(Vector<double,3>(1.0,1.0,0.0));
//    c.push_back(Vector<double,3>(6.0,4.0,0.0));
//    c.push_back(Vector<double,3>(3.0,6.0,0.0));
//    c.push_back(Vector<double,3>(0.0,4.0,0.0));
//    c.push_back(Vector<double,3>(1.0,1.0,0.0));


//    DVector<double> b;
//    b.push_back(0.0);
//    b.push_back(0.0);
//    b.push_back(1.0);


//    auto T1 = GMPutils::computeT(2,1, b);
//    auto T2 = GMPutils::computeT(2,2, b);
//    auto T3 = GMPutils::computeT(2,3, b);
//    auto T4 = GMPutils::computeT(2,4, b);
//    auto T5 = GMPutils::computeT(2,5, b);

//    DVector<Vector<double,3>> test;

//    // The test loop
//    while (state.KeepRunning()) {
//      auto a = T5 * c;
//      auto b = T4 * a;
//      auto cc = T3 * b;
//      auto d = T2 * cc;
//      test = T1 * d;
//    }

//}
//BENCHMARK(BM_BezierTriangle_deCasteljau_matrix_degree5);

//static void BM_BezierTriangle_deCasteljau_matrix_degree6(benchmark::State& state)
//{
//    DVector<Vector<double,3>> c;
//    for(int i = 0; i < 28; i++)
//    {
//      c.push_back(Vector<double,3>(1.0,4.0,0.0));
//    }

//    DVector<double> b;
//    b.push_back(0.0);
//    b.push_back(0.0);
//    b.push_back(1.0);

//    auto T1 = GMPutils::computeT(2,1, b);
//    auto T2 = GMPutils::computeT(2,2, b);
//    auto T3 = GMPutils::computeT(2,3, b);
//    auto T4 = GMPutils::computeT(2,4, b);
//    auto T5 = GMPutils::computeT(2,5, b);
//    auto T6 = GMPutils::computeT(2,6, b);

//    DVector<Vector<double,3>> test;

//    // The test loop
//    while (state.KeepRunning()) {
//      auto a = T6 * c;
//      auto b = T5 * a;
//      auto cc = T4 * b;
//      auto d = T3 * cc;
//      auto e = T2 * d;
//      test = T1 * e;
//    }

//}
//BENCHMARK(BM_BezierTriangle_deCasteljau_matrix_degree6);

//static void BM_BezierTriangle_deCasteljau_matrix_degree7(benchmark::State& state)
//{
//    DVector<Vector<double,3>> c;
//    for(int i = 0; i < 36; i++)
//    {
//      c.push_back(Vector<double,3>(1.0,4.0,0.0));
//    }

//    DVector<double> b;
//    b.push_back(0.0);
//    b.push_back(0.0);
//    b.push_back(1.0);

//    auto T1 = GMPutils::computeT(2,1, b);
//    auto T2 = GMPutils::computeT(2,2, b);
//    auto T3 = GMPutils::computeT(2,3, b);
//    auto T4 = GMPutils::computeT(2,4, b);
//    auto T5 = GMPutils::computeT(2,5, b);
//    auto T6 = GMPutils::computeT(2,6, b);
//    auto T7 = GMPutils::computeT(2,7, b);


//    DVector<Vector<double,3>> test;

//    // The test loop
//    while (state.KeepRunning()) {
//      auto a = T7 * c;
//      auto b = T6 * a;
//      auto cc = T5 * b;
//      auto d = T4 * cc;
//      auto e = T3 * d;
//      auto f = T2 * e;
//      test = T1 * f;
//    }

//}
//BENCHMARK(BM_BezierTriangle_deCasteljau_matrix_degree7);

//static void BM_BezierTriangle_deCasteljau_matrix_degree8(benchmark::State& state)
//{
//    DVector<Vector<double,3>> c;
//    for(int i = 0; i < 45; i++)
//    {
//      c.push_back(Vector<double,3>(1.0,4.0,0.0));
//    }

//    DVector<double> b;
//    b.push_back(0.0);
//    b.push_back(0.0);
//    b.push_back(1.0);

//    auto T1 = GMPutils::computeT(2,1, b);
//    auto T2 = GMPutils::computeT(2,2, b);
//    auto T3 = GMPutils::computeT(2,3, b);
//    auto T4 = GMPutils::computeT(2,4, b);
//    auto T5 = GMPutils::computeT(2,5, b);
//    auto T6 = GMPutils::computeT(2,6, b);
//    auto T7 = GMPutils::computeT(2,7, b);
//    auto T8 = GMPutils::computeT(2,8, b);


//    DVector<Vector<double,3>> test;

//    // The test loop
//    while (state.KeepRunning()) {
//      auto a = T8 * c;
//      auto b = T7 * a;
//      auto cc = T6 * b;
//      auto d = T5 * cc;
//      auto e = T4 * d;
//      auto f = T3 * e;
//      auto g = T2 * f;
//      test = T1 * g;
//    }

//}
//BENCHMARK(BM_BezierTriangle_deCasteljau_matrix_degree8);

//static void BM_BezierTriangle_deCasteljau_matrix_degree9(benchmark::State& state)
//{
//    DVector<Vector<double,3>> c;
//    for(int i = 0; i < 55; i++)
//    {
//      c.push_back(Vector<double,3>(1.0,4.0,0.0));
//    }

//    DVector<double> b;
//    b.push_back(0.0);
//    b.push_back(0.0);
//    b.push_back(1.0);

//    auto T1 = GMPutils::computeT(2,1, b);
//    auto T2 = GMPutils::computeT(2,2, b);
//    auto T3 = GMPutils::computeT(2,3, b);
//    auto T4 = GMPutils::computeT(2,4, b);
//    auto T5 = GMPutils::computeT(2,5, b);
//    auto T6 = GMPutils::computeT(2,6, b);
//    auto T7 = GMPutils::computeT(2,7, b);
//    auto T8 = GMPutils::computeT(2,8, b);
//    auto T9 = GMPutils::computeT(2,9, b);


//    DVector<Vector<double,3>> test;

//    // The test loop
//    while (state.KeepRunning()) {
//      auto a = T9 * c;
//      auto b = T8 * a;
//      auto cc = T7 * b;
//      auto d = T6 * cc;
//      auto e = T5 * d;
//      auto f = T4 * e;
//      auto g = T3 * f;
//      auto h = T2 * g;
//      test = T1 * h;
//    }

//}
//BENCHMARK(BM_BezierTriangle_deCasteljau_matrix_degree9);

//static void BM_BezierTriangle_deCasteljau_matrix_degree10(benchmark::State& state)
//{
//    DVector<Vector<double,3>> c;
//    for(int i = 0; i < 66; i++)
//    {
//      c.push_back(Vector<double,3>(1.0,4.0,0.0));
//    }

//    DVector<double> b;
//    b.push_back(0.0);
//    b.push_back(0.0);
//    b.push_back(1.0);

//    auto T1 = GMPutils::computeT(2,1, b);
//    auto T2 = GMPutils::computeT(2,2, b);
//    auto T3 = GMPutils::computeT(2,3, b);
//    auto T4 = GMPutils::computeT(2,4, b);
//    auto T5 = GMPutils::computeT(2,5, b);
//    auto T6 = GMPutils::computeT(2,6, b);
//    auto T7 = GMPutils::computeT(2,7, b);
//    auto T8 = GMPutils::computeT(2,8, b);
//    auto T9 = GMPutils::computeT(2,9, b);
//    auto T10 = GMPutils::computeT(2,10, b);


//    DVector<Vector<double,3>> test;

//    // The test loop
//    while (state.KeepRunning()) {
//      auto a = T10 * c;
//      auto b = T9 * a;
//      auto cc = T8 * b;
//      auto d = T7 * cc;
//      auto e = T6 * d;
//      auto f = T5 * e;
//      auto g = T4 * f;
//      auto h = T3 * g;
//      auto i = T2 * h;
//      test = T1 * i;
//    }

//}
//BENCHMARK(BM_BezierTriangle_deCasteljau_matrix_degree10);

static void BM_BezierTriangle_deBoorCox_matrix_degree1(benchmark::State& state)
{
  int d = 3;
  DVector<Vector<double,3>> c(10);
  c[0] = GMlib::Vector<double,3>(0.0,0.0,1.0);
  c[1] = GMlib::Vector<double,3>(1.0,0.0,0.0);
  c[2] = GMlib::Vector<double,3>(0.5,1.0,0.0);



  DVector<double> up(3);
  up[0] = 0.5;
  up[1] = 0.3;
  up[2] = 0.2;
  auto T1 = GMPutils::computeT(d-1,1, up);

  DVector<Vector<double,3>> V;

  // The test loop
  while (state.KeepRunning()) {
    V = T1 * c;
  }

  Vector<double,3> res;
  for (int i=0; i < 3; ++i)
    res[i] = V(0)(i);

}
BENCHMARK(BM_BezierTriangle_deBoorCox_matrix_degree1);

static void BM_BezierTriangle_deBoorCox_matrix_degree2(benchmark::State& state)
{
  int d = 3;
  DVector<Vector<double,3>> c(10);
  c[0] = GMlib::Vector<double,3>(0.0,0.0,1.0);
  c[1] = GMlib::Vector<double,3>(1.0,0.0,0.0);
  c[2] = GMlib::Vector<double,3>(0.5,1.0,0.0);
  c[3] = GMlib::Vector<double,3>(2.0,0.0,0.0);
  c[4] = GMlib::Vector<double,3>(1.5,1.0,0.0);
  c[5] = GMlib::Vector<double,3>(1.0,2.0,0.0);


  DVector<double> up(3);
  up[0] = 0.5;
  up[1] = 0.3;
  up[2] = 0.2;
  auto T1 = GMPutils::computeT(d-1,1, up);
  auto T2 = GMPutils::computeT(d-1,2, up);

  DVector<Vector<double,3>> V;

  // The test loop
  while (state.KeepRunning()) {
    auto a = T1 * T2;
    V = a * c;
  }

  Vector<double,3> res;
  for (int i=0; i < 3; ++i)
    res[i] = V(0)(i);

}
BENCHMARK(BM_BezierTriangle_deBoorCox_matrix_degree2);

static void BM_BezierTriangle_deBoorCox_matrix_degree3(benchmark::State& state)
{
  int d = 3;
  DVector<Vector<double,3>> c(10);
  c[0] = GMlib::Vector<double,3>(0.0,0.0,1.0);
  c[1] = GMlib::Vector<double,3>(1.0,0.0,0.0);
  c[2] = GMlib::Vector<double,3>(0.5,1.0,0.0);
  c[3] = GMlib::Vector<double,3>(2.0,0.0,0.0);
  c[4] = GMlib::Vector<double,3>(1.5,1.0,0.0);
  c[5] = GMlib::Vector<double,3>(1.0,2.0,0.0);
  c[6] = GMlib::Vector<double,3>(3.0,0.0,1.0);
  c[7] = GMlib::Vector<double,3>(2.5,1.0,0.0);
  c[8] = GMlib::Vector<double,3>(2.0,2.0,0.0);
  c[9] = GMlib::Vector<double,3>(1.5,3.0,1.0);


  DVector<double> up(3);
  up[0] = 0.5;
  up[1] = 0.3;
  up[2] = 0.2;
  auto T1 = GMPutils::computeT(d-1,1, up);
  auto T2 = GMPutils::computeT(d-1,2, up);
  auto T3 = GMPutils::computeT(d-1,3, up);

  DVector<Vector<double,3>> V;

  // The test loop
  while (state.KeepRunning()) {
    auto a = T1 * T2;
    auto b = a * T3;
    V = b * c;
  }

  Vector<double,3> res;
  for (int i=0; i < 3; ++i)
    res[i] = V(0)(i);

}
BENCHMARK(BM_BezierTriangle_deBoorCox_matrix_degree3);

static void BM_BezierTriangle_deBoorCox_matrix_degree4(benchmark::State& state)
{
    DVector<Vector<double,3>> c;
    c.push_back(Vector<double,3>(1.0,1.0,0.0));
    c.push_back(Vector<double,3>(5.0,1.0,0.0));
    c.push_back(Vector<double,3>(6.0,4.0,0.0));
    c.push_back(Vector<double,3>(3.0,6.0,0.0));
    c.push_back(Vector<double,3>(0.0,4.0,0.0));
    c.push_back(Vector<double,3>(1.0,1.0,0.0));
    c.push_back(Vector<double,3>(6.0,4.0,0.0));
    c.push_back(Vector<double,3>(3.0,6.0,0.0));
    c.push_back(Vector<double,3>(0.0,4.0,0.0));
    c.push_back(Vector<double,3>(1.0,1.0,0.0));
    c.push_back(Vector<double,3>(1.0,1.0,0.0));
    c.push_back(Vector<double,3>(6.0,4.0,0.0));
    c.push_back(Vector<double,3>(3.0,6.0,0.0));
    c.push_back(Vector<double,3>(0.0,4.0,0.0));
    c.push_back(Vector<double,3>(1.0,1.0,0.0));


    DVector<double> b;
    b.push_back(0.0);
    b.push_back(0.0);
    b.push_back(1.0);


    auto T1 = GMPutils::computeT(2,1, b);
    auto T2 = GMPutils::computeT(2,2, b);
    auto T3 = GMPutils::computeT(2,3, b);
    auto T4 = GMPutils::computeT(2,4, b);

    DVector<Vector<double,3>> test;

    // The test loop
    while (state.KeepRunning()) {
      auto a = T1 * T2;
      auto b = a * T3;
      auto cc = b * T4;
      test = cc * c;
    }

}
BENCHMARK(BM_BezierTriangle_deBoorCox_matrix_degree4);

static void BM_BezierTriangle_deBoorCox_matrix_degree5(benchmark::State& state)
{
    DVector<Vector<double,3>> c;
    c.push_back(Vector<double,3>(1.0,1.0,0.0));
    c.push_back(Vector<double,3>(5.0,1.0,0.0));
    c.push_back(Vector<double,3>(6.0,4.0,0.0));
    c.push_back(Vector<double,3>(3.0,6.0,0.0));
    c.push_back(Vector<double,3>(0.0,4.0,0.0));
    c.push_back(Vector<double,3>(1.0,1.0,0.0));
    c.push_back(Vector<double,3>(6.0,4.0,0.0));
    c.push_back(Vector<double,3>(3.0,6.0,0.0));
    c.push_back(Vector<double,3>(0.0,4.0,0.0));
    c.push_back(Vector<double,3>(1.0,1.0,0.0));
    c.push_back(Vector<double,3>(1.0,1.0,0.0));
    c.push_back(Vector<double,3>(6.0,4.0,0.0));
    c.push_back(Vector<double,3>(3.0,6.0,0.0));
    c.push_back(Vector<double,3>(0.0,4.0,0.0));
    c.push_back(Vector<double,3>(1.0,1.0,0.0));
    c.push_back(Vector<double,3>(1.0,1.0,0.0));
    c.push_back(Vector<double,3>(1.0,1.0,0.0));
    c.push_back(Vector<double,3>(6.0,4.0,0.0));
    c.push_back(Vector<double,3>(3.0,6.0,0.0));
    c.push_back(Vector<double,3>(0.0,4.0,0.0));
    c.push_back(Vector<double,3>(1.0,1.0,0.0));


    DVector<double> b;
    b.push_back(0.0);
    b.push_back(0.0);
    b.push_back(1.0);


    auto T1 = GMPutils::computeT(2,1, b);
    auto T2 = GMPutils::computeT(2,2, b);
    auto T3 = GMPutils::computeT(2,3, b);
    auto T4 = GMPutils::computeT(2,4, b);
    auto T5 = GMPutils::computeT(2,5, b);

    DVector<Vector<double,3>> test;

    // The test loop
    while (state.KeepRunning()) {
      auto a = T1 * T2;
      auto b = a * T3;
      auto cc = b * T4;
      auto d = cc * T5;
      test = d * c;
    }

}
BENCHMARK(BM_BezierTriangle_deBoorCox_matrix_degree5);

static void BM_BezierTriangle_deBoorCox_matrix_degree6(benchmark::State& state)
{
    DVector<Vector<double,3>> c;
    for(int i = 0; i < 28; i++)
    {
      c.push_back(Vector<double,3>(1.0,4.0,0.0));
    }


    DVector<double> b;
    b.push_back(0.0);
    b.push_back(0.0);
    b.push_back(1.0);


    auto T1 = GMPutils::computeT(2,1, b);
    auto T2 = GMPutils::computeT(2,2, b);
    auto T3 = GMPutils::computeT(2,3, b);
    auto T4 = GMPutils::computeT(2,4, b);
    auto T5 = GMPutils::computeT(2,5, b);
    auto T6 = GMPutils::computeT(2,6, b);

    DVector<Vector<double,3>> test;

    // The test loop
    while (state.KeepRunning()) {
      auto a = T1 * T2;
      auto b = a * T3;
      auto cc = b * T4;
      auto d = cc * T5;
      auto e = d * T6;
      test = e * c;
    }

}
BENCHMARK(BM_BezierTriangle_deBoorCox_matrix_degree6);

static void BM_BezierTriangle_deBoorCox_matrix_degree7(benchmark::State& state)
{
    DVector<Vector<double,3>> c;
    for(int i = 0; i < 36; i++)
    {
      c.push_back(Vector<double,3>(1.0,4.0,0.0));
    }


    DVector<double> b;
    b.push_back(0.0);
    b.push_back(0.0);
    b.push_back(1.0);


    auto T1 = GMPutils::computeT(2,1, b);
    auto T2 = GMPutils::computeT(2,2, b);
    auto T3 = GMPutils::computeT(2,3, b);
    auto T4 = GMPutils::computeT(2,4, b);
    auto T5 = GMPutils::computeT(2,5, b);
    auto T6 = GMPutils::computeT(2,6, b);
    auto T7 = GMPutils::computeT(2,7, b);

    DVector<Vector<double,3>> test;

    // The test loop
    while (state.KeepRunning()) {
      auto a = T1 * T2;
      auto b = a * T3;
      auto cc = b * T4;
      auto d = cc * T5;
      auto e = d * T6;
      auto f = e * T7;
      test = f * c;
    }

}
BENCHMARK(BM_BezierTriangle_deBoorCox_matrix_degree7);

static void BM_BezierTriangle_deBoorCox_matrix_degree8(benchmark::State& state)
{
    DVector<Vector<double,3>> c;
    for(int i = 0; i < 45; i++)
    {
      c.push_back(Vector<double,3>(1.0,4.0,0.0));
    }


    DVector<double> b;
    b.push_back(0.0);
    b.push_back(0.0);
    b.push_back(1.0);


    auto T1 = GMPutils::computeT(2,1, b);
    auto T2 = GMPutils::computeT(2,2, b);
    auto T3 = GMPutils::computeT(2,3, b);
    auto T4 = GMPutils::computeT(2,4, b);
    auto T5 = GMPutils::computeT(2,5, b);
    auto T6 = GMPutils::computeT(2,6, b);
    auto T7 = GMPutils::computeT(2,7, b);
    auto T8 = GMPutils::computeT(2,8, b);

    DVector<Vector<double,3>> test;

    // The test loop
    while (state.KeepRunning()) {
      auto a = T1 * T2;
      auto b = a * T3;
      auto cc = b * T4;
      auto d = cc * T5;
      auto e = d * T6;
      auto f = e * T7;
      auto g = f * T8;
      test = g * c;
    }

}
BENCHMARK(BM_BezierTriangle_deBoorCox_matrix_degree8);

static void BM_BezierTriangle_deBoorCox_matrix_degree9(benchmark::State& state)
{
    DVector<Vector<double,3>> c;
    for(int i = 0; i < 55; i++)
    {
      c.push_back(Vector<double,3>(1.0,4.0,0.0));
    }


    DVector<double> b;
    b.push_back(0.0);
    b.push_back(0.0);
    b.push_back(1.0);


    auto T1 = GMPutils::computeT(2,1, b);
    auto T2 = GMPutils::computeT(2,2, b);
    auto T3 = GMPutils::computeT(2,3, b);
    auto T4 = GMPutils::computeT(2,4, b);
    auto T5 = GMPutils::computeT(2,5, b);
    auto T6 = GMPutils::computeT(2,6, b);
    auto T7 = GMPutils::computeT(2,7, b);
    auto T8 = GMPutils::computeT(2,8, b);
    auto T9 = GMPutils::computeT(2,9, b);

    DVector<Vector<double,3>> test;

    // The test loop
    while (state.KeepRunning()) {
      auto a = T1 * T2;
      auto b = a * T3;
      auto cc = b * T4;
      auto d = cc * T5;
      auto e = d * T6;
      auto f = e * T7;
      auto g = f * T8;
      auto h = g * T9;
      test = h * c;
    }

}
BENCHMARK(BM_BezierTriangle_deBoorCox_matrix_degree9);

static void BM_BezierTriangle_deBoorCox_matrix_degree10(benchmark::State& state)
{
    DVector<Vector<double,3>> c;
    for(int i = 0; i < 55; i++)
    {
      c.push_back(Vector<double,3>(1.0,4.0,0.0));
    }


    DVector<double> b;
    b.push_back(0.0);
    b.push_back(0.0);
    b.push_back(1.0);


    auto T1 = GMPutils::computeT(2,1, b);
    auto T2 = GMPutils::computeT(2,2, b);
    auto T3 = GMPutils::computeT(2,3, b);
    auto T4 = GMPutils::computeT(2,4, b);
    auto T5 = GMPutils::computeT(2,5, b);
    auto T6 = GMPutils::computeT(2,6, b);
    auto T7 = GMPutils::computeT(2,7, b);
    auto T8 = GMPutils::computeT(2,8, b);
    auto T9 = GMPutils::computeT(2,9, b);
    auto T10 = GMPutils::computeT(2,10, b);

    DVector<Vector<double,3>> test;

    // The test loop
    while (state.KeepRunning()) {
      auto a = T1 * T2;
      auto b = a * T3;
      auto cc = b * T4;
      auto d = cc * T5;
      auto e = d * T6;
      auto f = e * T7;
      auto g = f * T8;
      auto h = g * T9;
      auto i = h * T10;
      test = i * c;
    }

}
BENCHMARK(BM_BezierTriangle_deBoorCox_matrix_degree10);

//static void BM_Pentagon_deCasteljau_matrix_degree1(benchmark::State& state)
//{
//  int d = 5;
//  DVector<Vector<double,3>> c(5);
//  c[0] = GMlib::Vector<double,3>(0.0,0.0,1.0);
//  c[1] = GMlib::Vector<double,3>(1.0,0.0,0.0);
//  c[2] = GMlib::Vector<double,3>(0.5,1.0,0.0);
//  c[3] = GMlib::Vector<double,3>(1.0,0.0,0.0);
//  c[4] = GMlib::Vector<double,3>(0.5,1.0,0.0);


//  DVector<double> up(5);
//  up[0] = 0.2;
//  up[1] = 0.2;
//  up[2] = 0.2;
//  up[3] = 0.2;
//  up[4] = 0.2;
//  auto T1 = GMPutils::computeT(d-1,1, up);

//  DVector<Vector<double,3>> V;

//  // The test loop
//  while (state.KeepRunning()) {
//    V = T1 * c;
//  }

//  Vector<double,3> res;
//  for (int i=0; i < 5; ++i)
//    res[i] = V(0)(i);

//}
//BENCHMARK(BM_Pentagon_deCasteljau_matrix_degree1);

//static void BM_Pentagon_deCasteljau_matrix_degree2(benchmark::State& state)
//{
//  int d = 5;
//  DVector<Vector<double,3>> c(15);
//  c[0] = GMlib::Vector<double,3>(0.0,0.0,1.0);
//  c[1] = GMlib::Vector<double,3>(1.0,0.0,0.0);
//  c[2] = GMlib::Vector<double,3>(0.5,1.0,0.0);
//  c[3] = GMlib::Vector<double,3>(2.0,0.0,0.0);
//  c[4] = GMlib::Vector<double,3>(1.5,1.0,0.0);
//  c[5] = GMlib::Vector<double,3>(1.0,2.0,0.0);
//  c[6] = GMlib::Vector<double,3>(0.0,0.0,1.0);
//  c[7] = GMlib::Vector<double,3>(1.0,0.0,0.0);
//  c[8] = GMlib::Vector<double,3>(0.5,1.0,0.0);
//  c[9] = GMlib::Vector<double,3>(2.0,0.0,0.0);
//  c[10] = GMlib::Vector<double,3>(1.5,1.0,0.0);
//  c[11] = GMlib::Vector<double,3>(1.0,2.0,0.0);
//  c[12] = GMlib::Vector<double,3>(2.0,0.0,0.0);
//  c[13] = GMlib::Vector<double,3>(1.5,1.0,0.0);
//  c[14] = GMlib::Vector<double,3>(1.0,2.0,0.0);


//  DVector<double> up(5);
//  up[0] = 0.2;
//  up[1] = 0.2;
//  up[2] = 0.2;
//  up[3] = 0.2;
//  up[4] = 0.2;
//  auto T1 = GMPutils::computeT(d-1,1, up);
//  auto T2 = GMPutils::computeT(d-1,2, up);

//  DVector<Vector<double,3>> V;

//  // The test loop
//  while (state.KeepRunning()) {
//    auto a = T2 * c;
//    V = T1 * a;
//  }

//  Vector<double,3> res;
//  for (int i=0; i < 5; ++i)
//    res[i] = V(0)(i);

//}
//BENCHMARK(BM_Pentagon_deCasteljau_matrix_degree2);

//static void BM_Pentagon_deCasteljau_matrix_degree3(benchmark::State& state)
//{
//  int d = 5;
//  DVector<Vector<double,3>> c;
//  for(int i = 0; i < 35; i++)
//  {
//    c.push_back(Vector<double,3>(1.0,1.0,2.0));
//  }

//  DVector<double> up(5);
//  up[0] = 0.2;
//  up[1] = 0.2;
//  up[2] = 0.2;
//  up[3] = 0.2;
//  up[4] = 0.2;
//  auto T1 = GMPutils::computeT(d-1,1, up);
//  auto T2 = GMPutils::computeT(d-1,2, up);
//  auto T3 = GMPutils::computeT(d-1,3, up);

//  DVector<Vector<double,3>> V;

//  // The test loop
//  while (state.KeepRunning()) {
//    auto a = T3 * c;
//    auto b = T2 * a;
//    V = T1 * b;
//  }

//  Vector<double,3> res;
//  for (int i=0; i < 5; ++i)
//    res[i] = V(0)(i);

//}
//BENCHMARK(BM_Pentagon_deCasteljau_matrix_degree3);

//static void BM_Pentagon_deCasteljau_matrix_degree4(benchmark::State& state)
//{
//    DVector<Vector<double,3>> c;
//    for(int i = 0; i < 70; i++)
//    {
//      c.push_back(Vector<double,3>(1.0,1.0,2.0));
//    }

//    DVector<double> b;
//    b.push_back(0.2);
//    b.push_back(0.2);
//    b.push_back(0.2);
//    b.push_back(0.2);
//    b.push_back(0.2);

//    auto T1 = GMPutils::computeT(4,1, b);
//    auto T2 = GMPutils::computeT(4,2, b);
//    auto T3 = GMPutils::computeT(4,3, b);
//    auto T4 = GMPutils::computeT(4,4, b);

//    DVector<Vector<double,3>> test;

//    // The test loop
//    while (state.KeepRunning()) {
//      auto a = T4 * c;
//      auto b = T3 * a;
//      auto cc = T2 * b;
//      test = T1 * cc;
//    }

//}
//BENCHMARK(BM_Pentagon_deCasteljau_matrix_degree4);

//static void BM_Pentagon_deCasteljau_matrix_degree5(benchmark::State& state)
//{
//    DVector<Vector<double,3>> c;
//    for(int i = 0; i < 126; i++)
//    {
//      c.push_back(Vector<double,3>(1.0,1.0,2.0));
//    }

//    DVector<double> b;
//    b.push_back(0.2);
//    b.push_back(0.2);
//    b.push_back(0.2);
//    b.push_back(0.2);
//    b.push_back(0.2);


//    auto T1 = GMPutils::computeT(4,1, b);
//    auto T2 = GMPutils::computeT(4,2, b);
//    auto T3 = GMPutils::computeT(4,3, b);
//    auto T4 = GMPutils::computeT(4,4, b);
//    auto T5 = GMPutils::computeT(4,5, b);

//    DVector<Vector<double,3>> test;

//    // The test loop
//    while (state.KeepRunning()) {
//      auto a = T5 * c;
//      auto b = T4 * a;
//      auto cc = T3 * b;
//      auto d = T2 * cc;
//      test = T1 * d;
//    }

//}
//BENCHMARK(BM_Pentagon_deCasteljau_matrix_degree5);

//static void BM_Pentagon_deCasteljau_matrix_degree6(benchmark::State& state)
//{
//    DVector<Vector<double,3>> c;
//    for(int i = 0; i < 210; i++)
//    {
//      c.push_back(Vector<double,3>(1.0,1.0,2.0));
//    }

//    DVector<double> b;
//    b.push_back(0.2);
//    b.push_back(0.2);
//    b.push_back(0.2);
//    b.push_back(0.2);
//    b.push_back(0.2);

//    auto T1 = GMPutils::computeT(4,1, b);
//    auto T2 = GMPutils::computeT(4,2, b);
//    auto T3 = GMPutils::computeT(4,3, b);
//    auto T4 = GMPutils::computeT(4,4, b);
//    auto T5 = GMPutils::computeT(4,5, b);
//    auto T6 = GMPutils::computeT(4,6, b);

//    DVector<Vector<double,3>> test;

//    // The test loop
//    while (state.KeepRunning()) {
//      auto a = T6 * c;
//      auto b = T5 * a;
//      auto cc = T4 * b;
//      auto d = T3 * cc;
//      auto e = T2 * d;
//      test = T1 * e;
//    }

//}
//BENCHMARK(BM_Pentagon_deCasteljau_matrix_degree6);

//static void BM_Pentagon_deCasteljau_matrix_degree7(benchmark::State& state)
//{
//    DVector<Vector<double,3>> c;
//    for(int i = 0; i < 330; i++)
//    {
//      c.push_back(Vector<double,3>(1.0,1.0,2.0));
//    }

//    DVector<double> b;
//    b.push_back(0.2);
//    b.push_back(0.2);
//    b.push_back(0.2);
//    b.push_back(0.2);
//    b.push_back(0.2);

//    auto T1 = GMPutils::computeT(4,1, b);
//    auto T2 = GMPutils::computeT(4,2, b);
//    auto T3 = GMPutils::computeT(4,3, b);
//    auto T4 = GMPutils::computeT(4,4, b);
//    auto T5 = GMPutils::computeT(4,5, b);
//    auto T6 = GMPutils::computeT(4,6, b);
//    auto T7 = GMPutils::computeT(4,7, b);


//    DVector<Vector<double,3>> test;

//    // The test loop
//    while (state.KeepRunning()) {
//      auto a = T7 * c;
//      auto b = T6 * a;
//      auto cc = T5 * b;
//      auto d = T4 * cc;
//      auto e = T3 * d;
//      auto f = T2 * e;
//      test = T1 * f;
//    }

//}
//BENCHMARK(BM_Pentagon_deCasteljau_matrix_degree7);

//static void BM_Pentagon_deCasteljau_matrix_degree8(benchmark::State& state)
//{
//    DVector<Vector<double,3>> c;
//    for(int i = 0; i < 495; i++)
//    {
//      c.push_back(Vector<double,3>(1.0,1.0,2.0));
//    }

//    DVector<double> b;
//    b.push_back(0.2);
//    b.push_back(0.2);
//    b.push_back(0.2);
//    b.push_back(0.2);
//    b.push_back(0.2);

//    auto T1 = GMPutils::computeT(4,1, b);
//    auto T2 = GMPutils::computeT(4,2, b);
//    auto T3 = GMPutils::computeT(4,3, b);
//    auto T4 = GMPutils::computeT(4,4, b);
//    auto T5 = GMPutils::computeT(4,5, b);
//    auto T6 = GMPutils::computeT(4,6, b);
//    auto T7 = GMPutils::computeT(4,7, b);
//    auto T8 = GMPutils::computeT(4,8, b);


//    DVector<Vector<double,3>> test;

//    // The test loop
//    while (state.KeepRunning()) {
//      auto a = T8 * c;
//      auto b = T7 * a;
//      auto cc = T6 * b;
//      auto d = T5 * cc;
//      auto e = T4 * d;
//      auto f = T3 * e;
//      auto g = T2 * f;
//      test = T1 * g;
//    }

//}
//BENCHMARK(BM_Pentagon_deCasteljau_matrix_degree8);

//static void BM_Pentagon_deCasteljau_matrix_degree9(benchmark::State& state)
//{
//    DVector<Vector<double,3>> c;
//    for(int i = 0; i < 715; i++)
//    {
//      c.push_back(Vector<double,3>(1.0,1.0,2.0));
//    }

//    DVector<double> b;
//    b.push_back(0.2);
//    b.push_back(0.2);
//    b.push_back(0.2);
//    b.push_back(0.2);
//    b.push_back(0.2);

//    auto T1 = GMPutils::computeT(4,1, b);
//    auto T2 = GMPutils::computeT(4,2, b);
//    auto T3 = GMPutils::computeT(4,3, b);
//    auto T4 = GMPutils::computeT(4,4, b);
//    auto T5 = GMPutils::computeT(4,5, b);
//    auto T6 = GMPutils::computeT(4,6, b);
//    auto T7 = GMPutils::computeT(4,7, b);
//    auto T8 = GMPutils::computeT(4,8, b);
//    auto T9 = GMPutils::computeT(4,9, b);


//    DVector<Vector<double,3>> test;

//    // The test loop
//    while (state.KeepRunning()) {
//      auto a = T9 * c;
//      auto b = T8 * a;
//      auto cc = T7 * b;
//      auto d = T6 * cc;
//      auto e = T5 * d;
//      auto f = T4 * e;
//      auto g = T3 * f;
//      auto h = T2 * g;
//      test = T1 * h;
//    }

//}
//BENCHMARK(BM_Pentagon_deCasteljau_matrix_degree9);

//static void BM_Pentagon_deCasteljau_matrix_degree10(benchmark::State& state)
//{
//    DVector<Vector<double,3>> c;
//    for(int i = 0; i < 1001; i++)
//    {
//      c.push_back(Vector<double,3>(1.0,1.0,2.0));
//    }

//    DVector<double> b;
//    b.push_back(0.2);
//    b.push_back(0.2);
//    b.push_back(0.2);
//    b.push_back(0.2);
//    b.push_back(0.2);

//    auto T1 = GMPutils::computeT(4,1, b);
//    auto T2 = GMPutils::computeT(4,2, b);
//    auto T3 = GMPutils::computeT(4,3, b);
//    auto T4 = GMPutils::computeT(4,4, b);
//    auto T5 = GMPutils::computeT(4,5, b);
//    auto T6 = GMPutils::computeT(4,6, b);
//    auto T7 = GMPutils::computeT(4,7, b);
//    auto T8 = GMPutils::computeT(4,8, b);
//    auto T9 = GMPutils::computeT(4,9, b);
//    auto T10 = GMPutils::computeT(4,10, b);


//    DVector<Vector<double,3>> test;

//    // The test loop
//    while (state.KeepRunning()) {
//      auto a = T10 * c;
//      auto b = T9 * a;
//      auto cc = T8 * b;
//      auto d = T7 * cc;
//      auto e = T6 * d;
//      auto f = T5 * e;
//      auto g = T4 * f;
//      auto h = T3 * g;
//      auto i = T2 * h;
//      test = T1 * i;
//    }

//}
//BENCHMARK(BM_Pentagon_deCasteljau_matrix_degree10);

//static void BM_Pentagon_deBoorCox_matrix_degree1(benchmark::State& state)
//{
//  int d = 5;
//  DVector<Vector<double,3>> c(5);
//  c[0] = GMlib::Vector<double,3>(0.0,0.0,1.0);
//  c[1] = GMlib::Vector<double,3>(1.0,0.0,0.0);
//  c[2] = GMlib::Vector<double,3>(0.5,1.0,0.0);
//  c[1] = GMlib::Vector<double,3>(1.0,0.0,0.0);
//  c[2] = GMlib::Vector<double,3>(0.5,1.0,0.0);



//  DVector<double> up(5);
//  up[0] = 0.2;
//  up[1] = 0.2;
//  up[2] = 0.2;
//  up[3] = 0.2;
//  up[4] = 0.2;
//  auto T1 = GMPutils::computeT(d-1,1, up);

//  DVector<Vector<double,3>> V;

//  // The test loop
//  while (state.KeepRunning()) {
//    V = T1 * c;
//  }

//  Vector<double,3> res;
//  for (int i=0; i < 5; ++i)
//    res[i] = V(0)(i);

//}
//BENCHMARK(BM_Pentagon_deBoorCox_matrix_degree1);

//static void BM_Pentagon_deBoorCox_matrix_degree2(benchmark::State& state)
//{
//  int d = 5;
//  DVector<Vector<double,3>> c;
//  for(int i = 0; i < 15; i++)
//  {
//    c.push_back(Vector<double,3>(1.0,1.0,2.0));
//  }


//  DVector<double> up(5);
//  up[0] = 0.2;
//  up[1] = 0.2;
//  up[2] = 0.2;
//  up[3] = 0.2;
//  up[4] = 0.2;
//  auto T1 = GMPutils::computeT(d-1,1, up);
//  auto T2 = GMPutils::computeT(d-1,2, up);

//  DVector<Vector<double,3>> V;

//  // The test loop
//  while (state.KeepRunning()) {
//    auto a = T1 * T2;
//    V = a * c;
//  }

//  Vector<double,3> res;
//  for (int i=0; i < 5; ++i)
//    res[i] = V(0)(i);

//}
//BENCHMARK(BM_Pentagon_deBoorCox_matrix_degree2);

//static void BM_Pentagon_deBoorCox_matrix_degree3(benchmark::State& state)
//{
//  int d = 5;
//  DVector<Vector<double,3>> c;
//  for(int i = 0; i < 35; i++)
//  {
//    c.push_back(Vector<double,3>(1.0,1.0,2.0));
//  }


//  DVector<double> up(5);
//  up[0] = 0.2;
//  up[1] = 0.2;
//  up[2] = 0.2;
//  up[3] = 0.2;
//  up[4] = 0.2;
//  auto T1 = GMPutils::computeT(d-1,1, up);
//  auto T2 = GMPutils::computeT(d-1,2, up);
//  auto T3 = GMPutils::computeT(d-1,3, up);

//  DVector<Vector<double,3>> V;

//  // The test loop
//  while (state.KeepRunning()) {
//    auto a = T1 * T2;
//    auto b = a * T3;
//    V = b * c;
//  }

//  Vector<double,3> res;
//  for (int i=0; i < 5; ++i)
//    res[i] = V(0)(i);

//}
//BENCHMARK(BM_Pentagon_deBoorCox_matrix_degree3);

//static void BM_Pentagon_deBoorCox_matrix_degree4(benchmark::State& state)
//{
//    DVector<Vector<double,3>> c;
//    for(int i = 0; i < 70; i++)
//    {
//      c.push_back(Vector<double,3>(1.0,1.0,2.0));
//    }

//    DVector<double> b;
//    b.push_back(0.2);
//    b.push_back(0.2);
//    b.push_back(0.2);
//    b.push_back(0.2);
//    b.push_back(0.2);


//    auto T1 = GMPutils::computeT(4,1, b);
//    auto T2 = GMPutils::computeT(4,2, b);
//    auto T3 = GMPutils::computeT(4,3, b);
//    auto T4 = GMPutils::computeT(4,4, b);

//    DVector<Vector<double,3>> test;

//    // The test loop
//    while (state.KeepRunning()) {
//      auto a = T1 * T2;
//      auto b = a * T3;
//      auto cc = b * T4;
//      test = cc * c;
//    }

//}
//BENCHMARK(BM_Pentagon_deBoorCox_matrix_degree4);

//static void BM_Pentagon_deBoorCox_matrix_degree5(benchmark::State& state)
//{
//    DVector<Vector<double,3>> c;
//    for(int i = 0; i < 126; i++)
//    {
//      c.push_back(Vector<double,3>(1.0,1.0,2.0));
//    }

//    DVector<double> b;
//    b.push_back(0.2);
//    b.push_back(0.2);
//    b.push_back(0.2);
//    b.push_back(0.2);
//    b.push_back(0.2);

//    auto T1 = GMPutils::computeT(4,1, b);
//    auto T2 = GMPutils::computeT(4,2, b);
//    auto T3 = GMPutils::computeT(4,3, b);
//    auto T4 = GMPutils::computeT(4,4, b);
//    auto T5 = GMPutils::computeT(4,5, b);

//    DVector<Vector<double,3>> test;

//    // The test loop
//    while (state.KeepRunning()) {
//      auto a = T1 * T2;
//      auto b = a * T3;
//      auto cc = b * T4;
//      auto d = cc * T5;
//      test = d * c;
//    }

//}
//BENCHMARK(BM_Pentagon_deBoorCox_matrix_degree5);

//static void BM_Pentagon_deBoorCox_matrix_degree6(benchmark::State& state)
//{
//    DVector<Vector<double,3>> c;
//    for(int i = 0; i < 210; i++)
//    {
//      c.push_back(Vector<double,3>(1.0,1.0,2.0));
//    }

//    DVector<double> b;
//    b.push_back(0.2);
//    b.push_back(0.2);
//    b.push_back(0.2);
//    b.push_back(0.2);
//    b.push_back(0.2);


//    auto T1 = GMPutils::computeT(4,1, b);
//    auto T2 = GMPutils::computeT(4,2, b);
//    auto T3 = GMPutils::computeT(4,3, b);
//    auto T4 = GMPutils::computeT(4,4, b);
//    auto T5 = GMPutils::computeT(4,5, b);
//    auto T6 = GMPutils::computeT(4,6, b);

//    DVector<Vector<double,3>> test;

//    // The test loop
//    while (state.KeepRunning()) {
//      auto a = T1 * T2;
//      auto b = a * T3;
//      auto cc = b * T4;
//      auto d = cc * T5;
//      auto e = d * T6;
//      test = e * c;
//    }

//}
//BENCHMARK(BM_Pentagon_deBoorCox_matrix_degree6);

//static void BM_Pentagon_deBoorCox_matrix_degree7(benchmark::State& state)
//{
//    DVector<Vector<double,3>> c;
//    for(int i = 0; i < 330; i++)
//    {
//      c.push_back(Vector<double,3>(1.0,1.0,2.0));
//    }

//    DVector<double> b;
//    b.push_back(0.2);
//    b.push_back(0.2);
//    b.push_back(0.2);
//    b.push_back(0.2);
//    b.push_back(0.2);


//    auto T1 = GMPutils::computeT(4,1, b);
//    auto T2 = GMPutils::computeT(4,2, b);
//    auto T3 = GMPutils::computeT(4,3, b);
//    auto T4 = GMPutils::computeT(4,4, b);
//    auto T5 = GMPutils::computeT(4,5, b);
//    auto T6 = GMPutils::computeT(4,6, b);
//    auto T7 = GMPutils::computeT(4,7, b);

//    DVector<Vector<double,3>> test;

//    // The test loop
//    while (state.KeepRunning()) {
//      auto a = T1 * T2;
//      auto b = a * T3;
//      auto cc = b * T4;
//      auto d = cc * T5;
//      auto e = d * T6;
//      auto f = e * T7;
//      test = f * c;
//    }

//}
//BENCHMARK(BM_Pentagon_deBoorCox_matrix_degree7);

//static void BM_Pentagon_deBoorCox_matrix_degree8(benchmark::State& state)
//{
//    DVector<Vector<double,3>> c;
//    for(int i = 0; i < 495; i++)
//    {
//      c.push_back(Vector<double,3>(1.0,1.0,2.0));
//    }

//    DVector<double> b;
//    b.push_back(0.2);
//    b.push_back(0.2);
//    b.push_back(0.2);
//    b.push_back(0.2);
//    b.push_back(0.2);


//    auto T1 = GMPutils::computeT(4,1, b);
//    auto T2 = GMPutils::computeT(4,2, b);
//    auto T3 = GMPutils::computeT(4,3, b);
//    auto T4 = GMPutils::computeT(4,4, b);
//    auto T5 = GMPutils::computeT(4,5, b);
//    auto T6 = GMPutils::computeT(4,6, b);
//    auto T7 = GMPutils::computeT(4,7, b);
//    auto T8 = GMPutils::computeT(4,8, b);

//    DVector<Vector<double,3>> test;

//    // The test loop
//    while (state.KeepRunning()) {
//      auto a = T1 * T2;
//      auto b = a * T3;
//      auto cc = b * T4;
//      auto d = cc * T5;
//      auto e = d * T6;
//      auto f = e * T7;
//      auto g = f * T8;
//      test = g * c;
//    }

//}
//BENCHMARK(BM_Pentagon_deBoorCox_matrix_degree8);

//static void BM_Pentagon_deBoorCox_matrix_degree9(benchmark::State& state)
//{
//    DVector<Vector<double,3>> c;
//    for(int i = 0; i < 715; i++)
//    {
//      c.push_back(Vector<double,3>(1.0,1.0,2.0));
//    }

//    DVector<double> b;
//    b.push_back(0.2);
//    b.push_back(0.2);
//    b.push_back(0.2);
//    b.push_back(0.2);
//    b.push_back(0.2);


//    auto T1 = GMPutils::computeT(4,1, b);
//    auto T2 = GMPutils::computeT(4,2, b);
//    auto T3 = GMPutils::computeT(4,3, b);
//    auto T4 = GMPutils::computeT(4,4, b);
//    auto T5 = GMPutils::computeT(4,5, b);
//    auto T6 = GMPutils::computeT(4,6, b);
//    auto T7 = GMPutils::computeT(4,7, b);
//    auto T8 = GMPutils::computeT(4,8, b);
//    auto T9 = GMPutils::computeT(4,9, b);

//    DVector<Vector<double,3>> test;

//    // The test loop
//    while (state.KeepRunning()) {
//      auto a = T1 * T2;
//      auto b = a * T3;
//      auto cc = b * T4;
//      auto d = cc * T5;
//      auto e = d * T6;
//      auto f = e * T7;
//      auto g = f * T8;
//      auto h = g * T9;
//      test = h * c;
//    }

//}
//BENCHMARK(BM_Pentagon_deBoorCox_matrix_degree9);

//static void BM_Pentagon_deBoorCox_matrix_degree10(benchmark::State& state)
//{
//    DVector<Vector<double,3>> c;
//    for(int i = 0; i < 1001; i++)
//    {
//      c.push_back(Vector<double,3>(1.0,1.0,2.0));
//    }

//    DVector<double> b;
//    b.push_back(0.2);
//    b.push_back(0.2);
//    b.push_back(0.2);
//    b.push_back(0.2);
//    b.push_back(0.2);


//    auto T1 = GMPutils::computeT(4,1, b);
//    auto T2 = GMPutils::computeT(4,2, b);
//    auto T3 = GMPutils::computeT(4,3, b);
//    auto T4 = GMPutils::computeT(4,4, b);
//    auto T5 = GMPutils::computeT(4,5, b);
//    auto T6 = GMPutils::computeT(4,6, b);
//    auto T7 = GMPutils::computeT(4,7, b);
//    auto T8 = GMPutils::computeT(4,8, b);
//    auto T9 = GMPutils::computeT(4,9, b);
//    auto T10 = GMPutils::computeT(4,10, b);

//    DVector<Vector<double,3>> test;

//    // The test loop
//    while (state.KeepRunning()) {
//      auto a = T1 * T2;
//      auto b = a * T3;
//      auto cc = b * T4;
//      auto d = cc * T5;
//      auto e = d * T6;
//      auto f = e * T7;
//      auto g = f * T8;
//      auto h = g * T9;
//      auto i = h * T10;
//      test = i * c;
//    }

//}
//BENCHMARK(BM_Pentagon_deBoorCox_matrix_degree10);


BENCHMARK_MAIN()

