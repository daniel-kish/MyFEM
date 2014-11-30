#ifndef VECTOR_H
#define VECTOR_H
#include <vector>
#include <random>
#include <iostream>
#include <iomanip>
using namespace std;

template <typename Data> class Vector;
template <typename T> ostream& operator<< (ostream& out, Vector<T>& m);


template <typename Data>
class Vector
{
    std::vector<Data> data;
public:
    Vector(unsigned new_sz) : data(new_sz) {}
    Data operator() (unsigned ind) const
    {
        return data.at(ind);
    }
    Data& operator() (unsigned ind)
    {
        return data.at(ind);
    }
    std::vector<Data>& getDataRef() {
        return data;
    }
    void fill (Data filler)
    {
        for (auto& elem : data)
            elem = filler;
    }
    void randomize(Data lowerBnd, Data upperBnd)
    {
        std::uniform_real_distribution<Data> unif(lowerBnd, upperBnd);
        std::default_random_engine re;
        for (auto& elem : data)
            elem = unif(re);
    }
    unsigned size() const {
        return data.size();
    }

    friend ostream& operator<< <Data> (ostream& out, Vector<Data>& m);
};

template <typename T>
ostream& operator<< (ostream& out, Vector<T>& v)
{
    unsigned sz{v.size()};
    out << std::fixed;
    out << std::setprecision(6);
    for (unsigned j = 0; j < sz; j++)
        out << std::setw(12) << v(j) << std::endl;
    out << std::endl;
    return out;
}

#endif // VECTOR_H
