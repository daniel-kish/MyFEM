#ifndef NESYSTEM_H
#define NESYSTEM_H
#include <abstractfunctor.h>
#include <matrix.h>
#include <numvector.h>
#include <assert.h>
#include <lesystem.h>
#include <iostream>

template <typename Data>
class NESystem
{
    AbstractFunctor<Data> *f;
    const double prec;
public:
    NESystem(AbstractFunctor<Data>* _f, double p = 10.0E-16) : f(_f), prec(p) {}
    Vector<Data> solve(Vector<Data>& X0)
    {
        assert(X0.size() == f->dimension());
        LESystem<Data> s(f->JacobyMx(X0), -f->val(X0));
        int n{100};
        int cnt{0};
        std::cout << std::fixed << std::setprecision(32);
        while (n--)
        {
            X0 += s.solve();
            if (f->val(X0).mag() < prec) {
//                std::cout << cnt <<" : "<< f->val(X0).mag() << std::endl;
                return X0;
            }
            s.insertCopyMatrix(f->JacobyMx(X0));
            s.insertCopyRight(-f->val(X0));
            ++cnt;
        }
//        std::cout << cnt <<" : "<< f->val(X0).mag() << std::endl;
        return X0;
    }

};

using RealNESystem = NESystem<double>;
#endif // NESYSTEM_H
