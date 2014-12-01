#include <matrix.h>
#include <numvector.h>
#include <iostream>
#include <chrono>
#include <lesystem.h>
#include <iomanip>

int main(/*int argc, char * argv[]*/)
{
    using namespace chrono;
    unsigned N{1000};
    Matrix<double> A(N, N);
    Vector<double> B(N);
    A.randomize(0.0, 10.0);
    B.randomize(-1.0, 1.0);

    LESystem<double> s(A,B);
    auto t0 = high_resolution_clock::now();
    s.solve();
    auto t1 = high_resolution_clock::now();
    std::cout << duration_cast<seconds>(t1-t0).count() << " s passed" << std::endl;

    Vector<double> v = s.getSolution();
    v = A*v - B;
    std::cout << std::fixed << std::setprecision(12) <<  v.mag() << std::endl;

    return 0;
}
