#ifndef MYFUNCTOR_H
#define MYFUNCTOR_H
#include <abstractfunctor.h>
#include <cassert>
#include <math.h>

class MyFunctor : public AbstractFunctor<double>
{
    double I0;
    double U0;
    double Uc0;
    double F = 1.0;
    double t;
    double Dt;
public:
    MyFunctor(double _I0, double _U0, double _Uc0, double _t, double _Dt = 0.1)
        : AbstractFunctor<double>(2), I0{_I0}, U0{_U0}, Uc0{_Uc0}, t{_t}, Dt{_Dt} {}
    RealVec operator () (RealVec& X)
    {
        assert(X.size() == dim);
        Vector<double> vals(X.size());

        vals(0) = I0 + Dt*X(0) + X(0)/Dt - U0/Dt + X(0) - sin(t);
        vals(1) = X(1) / Dt - Uc0/Dt - X(0);
        return vals;
    }

    RealVec val(RealVec& X)
    {
       return operator ()(X);
    }

    RealMat JacobyMx(RealVec& X)
    {
        assert(X.size() == dim);
        RealMat j(X.size(), X.size());
        j(0,0) = Dt + 1.0/Dt + 1.0; j(0,1) = 0.0;
        j(1,0) = 0.0; j(1,1) = 1/Dt;

        return j;
    }
};

#endif // MYFUNCTOR_H
