#ifndef SIMPLEX_H
#define SIMPLEX_H
#include <array>
#include <QPointF>
#include <iostream>
using namespace std;

class Simplex0D : public QPointF {
public:
    Simplex0D(QPointF p) : QPointF(p) {}
};

class Simplex1D {
public:
    const Simplex0D& s1;
    const Simplex0D& s2;
    Simplex1D(const Simplex0D& _s1, const Simplex0D& _s2) : s1(_s1), s2(_s2) {}
};

class Simplex2D {
public:
    const Simplex1D& s1;
    const Simplex1D& s2;
    const Simplex1D& s3;
    Simplex2D(const Simplex1D& _s1, const Simplex1D& _s2, const Simplex1D& _s3)
        : s1(_s1), s2(_s2), s3(_s3)
    {}
};

template <unsigned dim>
class Simplex {
public:
    array<Simplex<dim-1>*, dim+1> edges;
    Simplex<dim> (array<Simplex<dim-1>*, dim+1>& _edges)
        : edges(_edges)
    {}
};

template <>
class Simplex<0> : public QPointF {
public:
    Simplex<0> (QPointF p) : QPointF(p)
    {}
    Simplex<0> (array<Simplex<0>, 1>& a) : QPointF(a[0].x(), a[0].y())
    {
    }
};

#endif // SIMPLEX_H
