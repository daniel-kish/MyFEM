#include <iostream>
#include <myfunctor.h>
#include <cmath>
#include <lesystem.h>
using namespace std;

int main(/*int argc, char * argv[]*/)
{    
    MyFunctor f;
    Vector<double> X0(3);
    RealMat m(3,3);
    X0(0) = 1.0;
    X0(1) = 0.5;
    X0(2) = 1.0;

    // TO-DO! Implement Jacoby matrix singularity test
    int n{50};
    while (n-- && f(X0).mag() > 10.0E-12)
    std::cout << (X0 += LESystem<double>(f.JacobyMx(X0), -f(X0)).solve());



    return 0;
}
