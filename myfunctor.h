#ifndef MYFUNCTOR_H
#define MYFUNCTOR_H
#include <abstractfunctor.h>
#include <cassert>
#include <math.h>

class MyFunctor : public AbstractFunctor<double>
{
    double x0;
    double v0;
    double Dt = 0.01;
public:
    MyFunctor(double _x0, double _v0)
        : AbstractFunctor(2), x0{_x0}, v0{_v0}/*, Dt{0.1}*/ {}
    RealVec operator () (RealVec& X)
    {
        assert(X.size() == dim);
        Vector<double> vals(X.size());

        vals(0) = X(0) - X(1)*Dt - x0;
        vals(1) = X(1) + Dt*X(0)*fabs(X(0)) + 0*Dt*0.1*X(1) - v0;
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
        j(0,0) = 1.0; j(0,1) = -Dt;
        j(1,0) = Dt * ( fabs(X(0)) + X(0)*( (X(0)>0)? 1.0:-1.0 ) );
        j(1,1) = 1.0 + 0*Dt*0.1;
        return j;
    }
};

#endif // MYFUNCTOR_H
