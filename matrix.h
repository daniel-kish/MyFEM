#ifndef MATRIX_H
#define MATRIX_H
#include <vector>
#include <iostream>
#include <iomanip>
#include <random>
using namespace std;

template <typename Data> class Matrix;
template <typename T> ostream& operator<< (ostream& out, Matrix<T>& m);

template <typename Data>
class Matrix
{
    vector<Data> data;
    unsigned sz;
public:
    Matrix(unsigned new_sz) : data(new_sz*new_sz), sz{new_sz} {}
    Data operator() (unsigned row, unsigned col) const
    {
        return data[row*sz + col];
    }
    Data& operator() (unsigned row, unsigned col)
    {
        return data[row*sz + col];
    }
    vector<Data>& getDataRef() {
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

    void addToRow(unsigned r0, unsigned r1, Data alpha)
    {
        for (unsigned col = 0; col < sz; col++)
            data[r0*sz + col] += alpha*data[r1*sz + col];
    }

    unsigned size() const {
        return sz;
    }
    friend ostream& operator<< <Data> (ostream& out, Matrix<Data>& m);
};

template <typename T>
ostream& operator<< (ostream& out, Matrix<T>& m)
{
    unsigned sz{m.size()};
    out << std::fixed;
    out << std::setprecision(6);
    for (unsigned i = 0; i < sz; i++) {
        for (unsigned j = 0; j < sz; j++)
            out << std::setw(12) << m(i,j) <<' ';
        out << std::endl;
    }
    return out;
}

using RealMat = Matrix<double>;

#endif // MATRIX_H
