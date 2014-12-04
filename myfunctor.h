#ifndef MYFUNCTOR_H
#define MYFUNCTOR_H
#include <abstractfunctor.h>
#include <cassert>
#include <math.h>

class MyFunctor : public AbstractFunctor<double>
{
public:
    MyFunctor() : AbstractFunctor/*<double>*/(4) {}
    Vector<double> operator () (Vector<double>& X)
    {
        assert(X.size() == dim);
        Vector<double> vals(X.size());

        vals(0) = -X(0)*X(0) + X(1) + X(2)*X(2) + X(3);
        vals(1) = X(0) + X(1) - X(2)*X(2) - 1.0 - X(1)*X(3);
        vals(2) = X(0)*X(0) - 2.0*X(2)*X(2);
        vals(3) = X(0) - sin(X(3));
        return vals;
    }

    RealVec val(RealVec& X)
    {
        assert(X.size() == dim);
        Vector<double> vals(X.size());

        vals(0) = -X(0)*X(0) + X(1) + X(2)*X(2) + X(3);
        vals(1) = X(0) + X(1) - X(2)*X(2) - 1.0 - X(1)*X(3);
        vals(2) = X(0)*X(0) - 2.0*X(2)*X(2);
        vals(3) = X(0) - sin(X(3));
        return vals;
    }

    Matrix<double> JacobyMx(Vector<double>& X)
    {
        assert(X.size() == dim);
        Matrix<double> j(X.size(), X.size());
        j(0,0) = -2.0 * X(0);  j(0,1) = 1.0;  j(0,2) = 2.0*X(2);  j(0,3) = 1.0;
        j(1,0) = 1.0;          j(1,1) = 1.0 - X(3);  j(1,2) = -2.0*X(2)*X(2); j(1,3) = -X(1);
        j(2,0) = 2.0*X(0);     j(2,1) = 0.0;  j(2,2) = -4.0*X(2); j(2,3) = 0.0;
        j(3,0) = 1.0;     j(3,1) = 0.0;  j(3,2) = 0.0; j(3,3) = -cos(X(3));
        return j;
    }
};

#endif // MYFUNCTOR_H
