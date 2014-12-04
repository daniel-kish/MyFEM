#ifndef VECTOR_H
#define VECTOR_H
#include <vector>
#include <random>
#include <iostream>
#include <iomanip>
#include <chrono>
using namespace std;

template <typename Data> class Vector;
template <typename T> ostream& operator<< (ostream& out, Vector<T>& m);


template <typename Data>
class Vector
{
    std::vector<Data> data;
public:
    enum pos {first, last};

    Vector(unsigned new_sz) : data(new_sz) {}
    // natural positioning
    Data operator() (unsigned ind) const
    {
        return data.at(ind);
    }
    Data& operator() (unsigned ind)
    {
        return data.at(ind);
    }

    // pos
    Data operator() (pos p) const
    {
        if (p == first)
            return data.front();
        return data.back();
    }
    Data& operator() (pos p)
    {
        if (p == first)
            return data.front();
        return data.back();
    }
    std::vector<Data>& getDataRef() {
        return data;
    }

    Vector<Data> operator+(Vector<Data> v)
    {
        Vector<Data> r(v.size());
        for (int i = 0; i < v.size(); i++)
            r(i) = data[i] + v(i);
        return r;
    }

    Vector<Data> operator-(Vector<Data> v)
    {
        Vector<Data> r(v.size());
        for (int i = 0; i < v.size(); i++)
            r(i) = data[i] - v(i);
        return r;
    }
    Vector<Data> operator*(Data v) {
        Vector<Data> res(data.size());
        for (unsigned i = 0; i < data.size(); i++)
            res(i) = v*data[i];
        return res;
    }

    Vector<Data> operator += (Vector<Data>& v)
    {
        for (unsigned i = 0; i < v.size(); i++)
            data[i] += v(i);
        return *this;
    }

    Vector<Data> operator += (Vector<Data>&& v)
    {
        for (unsigned i = 0; i < v.size(); i++)
            data[i] += v(i);
        return *this;
    }

    void fill (Data filler)
    {
        for (auto& elem : data)
            elem = filler;
    }
    void randomize(Data lowerBnd, Data upperBnd)
    {
        chrono::system_clock::time_point now = chrono::system_clock::now();
        time_t now_c = chrono::system_clock::to_time_t(now);

        std::uniform_real_distribution<Data> unif(lowerBnd, upperBnd);
        std::default_random_engine re(now_c);
        for (auto& elem : data)
            elem = unif(re);
    }
    unsigned size() const {
        return data.size();
    }

    Data mag()
    {
        double m{0.0};
        for (auto& elem : data)
            m += elem*elem;
        return sqrt(m);
    }

    friend ostream& operator<< <Data> (ostream& out, Vector<Data>& m);
};

using vpos = Vector<double>::pos;

const int outPrec{9};
template <typename T>
ostream& operator<< (ostream& out, Vector<T>& v)
{
    unsigned sz{v.size()};
    out << std::fixed;
    out << std::setprecision(outPrec);
    for (unsigned j = 0; j < sz; j++)
        out << std::setw(12) << v(j) << std::endl;
    out << std::endl;
    return out;
}

template <typename T>
ostream& operator<< (ostream& out, Vector<T>&& v)
{
    unsigned sz{v.size()};
    out << std::fixed;
    out << std::setprecision(6);
    for (unsigned j = 0; j < sz; j++)
        out << std::setw(12) << v(j) << std::endl;
    out << std::endl;
    return out;
}

template <typename T>
Vector<T> operator -(Vector<T> v)
{
    Vector<T> res(v.size());
    for (unsigned i = 0; i < v.size(); i++)
        res(i) = -v(i);
    return res;
}

using RealVec = Vector<double>;

#endif // VECTOR_H
