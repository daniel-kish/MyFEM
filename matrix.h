#ifndef MATRIX_H
#define MATRIX_H
#include <vector>
#include <iostream>
#include <iomanip>
#include <random>
#include <chrono>
#include <numvector.h>
using namespace std;

template <typename Data> class Matrix;
template <typename T> ostream& operator<< (ostream& out, Matrix<T>& m);

template <typename Data>
class Matrix
{
    vector<Data> data;
    unsigned rowsNo;
    unsigned colsNo;
public:
    enum pos {first, last, diag};
    Matrix(unsigned _r, unsigned _c) : data(_r * _c), rowsNo{_r}, colsNo{_c}
    {}
    // natural positioning
    Data operator() (unsigned row, unsigned col) const
    {
        return data[row*colsNo + col];
    }
    Data& operator() (unsigned row, unsigned col)
    {
        return data[row*colsNo + col];
    }

    // row-pos
    Data operator() (pos p, unsigned col) const
    {
        switch(p)
        {
        case first:
            return data[col];
        case last:
            return data[(rowsNo-1)*colsNo + col];
        case diag:
            return data[col*colsNo + col];
        default:
            return 0.0;
        }
    }
    Data& operator() (pos p, unsigned col)
    {
        switch(p)
        {
        case first:
            return data[col];
        case last:
            return data[(rowsNo-1)*colsNo + col];
        case diag:
            return data[col*colsNo + col];
        default:
            return data[0];
        }
    }

    // col-pos
    Data operator() (unsigned row, pos p) const
    {
        switch(p)
        {
        case first:
            return data[row*colsNo];
        case last:
            return data[row*colsNo + colsNo-1];
        case diag:
            return data[row*colsNo + row];
        default:
            return 0.0;
        }
    }
    Data& operator() (unsigned row, pos p)
    {
        switch(p)
        {
        case first:
            return data[row*colsNo];
        case last:
            return data[row*colsNo + colsNo-1];
        case diag:
            return data[row*colsNo + row];
        default:
            exit(3);
        }
    }

    Vector<Data> operator*(Vector<Data>& v)
    {
        Vector<Data> x(v.size());
        for (int row = 0; row < rowsNo; row++) {
            double a{0.0};
            for (int col = 0; col < colsNo; col++)
                a += data[row*colsNo+col]*v(col);
            x(row) = a;
        }
        return x;
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
        chrono::system_clock::time_point now = chrono::system_clock::now();
        time_t now_c = chrono::system_clock::to_time_t(now);

        std::uniform_real_distribution<Data> unif(lowerBnd, upperBnd);
        std::default_random_engine re(now_c);
        for (auto& elem : data)
            elem = unif(re);
    }

    void addToRow(unsigned r0, unsigned r1, Data alpha)
    {
        for (unsigned col = 0; col < colsNo; col++)
            data[r0*colsNo + col] += alpha*data[r1*colsNo + col];
    }

    unsigned cols() const {
        return colsNo;
    }
    unsigned rows() const {
        return rowsNo;
    }
    friend ostream& operator<< <Data> (ostream& out, Matrix<Data>& m);
};

template <typename T>
ostream& operator<< (ostream& out, Matrix<T>& m)
{
    unsigned cols{m.cols()};
    unsigned rows{m.rows()};

    out << std::fixed;
    out << std::setprecision(6);
    for (unsigned i = 0; i < rows; i++) {
        for (unsigned j = 0; j < cols; j++)
            out << std::setw(12) << m(i,j) <<' ';
        out << std::endl;
    }
    return out;
}

template <typename T>
ostream& operator<< (ostream& out, Matrix<T>&& m)
{
    unsigned cols{m.cols()};
    unsigned rows{m.rows()};

    out << std::fixed;
    out << std::setprecision(6);
    for (unsigned i = 0; i < rows; i++) {
        for (unsigned j = 0; j < cols; j++)
            out << std::setw(12) << m(i,j) <<' ';
        out << std::endl;
    }
    return out;
}


using RealMat = Matrix<double>;
using mpos = Matrix<double>::pos;

#endif // MATRIX_H
