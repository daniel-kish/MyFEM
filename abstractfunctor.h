#ifndef ABSTRACTFUNCTOR_H
#define ABSTRACTFUNCTOR_H
#include <numvector.h>
#include <matrix.h>

template <typename Data>
class AbstractFunctor
{
protected:
    unsigned dim; // dimension of a function domain
public:
    AbstractFunctor(unsigned d) : dim{d} {}
    virtual Vector<Data> operator () (Vector<Data>& X) = 0;
    virtual Vector<Data> val(Vector<Data>& X) = 0;
    virtual Matrix<Data> JacobyMx(Vector<Data>& X) = 0;
    unsigned dimension() const {
        return dim;
    }
};

#endif // ABSTRACTFUNCTOR_H
