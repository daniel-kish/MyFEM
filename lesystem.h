#ifndef SLAE_H
#define SLAE_H
#include <matrix.h>
#include <numvector.h>

template <typename Data> class LESystem;
template <typename T> ostream& operator<< (ostream& out, LESystem<T>& m);

template <typename Data>
class LESystem
{
    Matrix<Data> m;
    Vector<Data> x;
public:
    LESystem(Matrix<Data>& _m, Vector<Data>& v) : m(_m.rows(), _m.cols()+1), x(_m.cols())
    {
        if (_m.cols() != _m.rows() || _m.rows() != v.size()) {
            std::cerr << "You do it wrong!: Matrix should be"
                         " square and vector size equal to m.cols()\n";
            exit(1);
        }

        for (unsigned row = 0; row < m.rows(); row++) {
            for (unsigned col = 0; col < m.cols(); col++)
                m(row,col) = _m(row,col);
            m(row, m.cols()-1) =  v(row);
        }
    }
    LESystem(Matrix<Data>&& _m, Vector<Data>&& v) : m(_m.rows(), _m.cols()+1), x(_m.cols())
    {
        if (_m.cols() != _m.rows() || _m.rows() != v.size()) {
            std::cerr << "You do it wrong!: Matrix should be"
                         " square and vector size equal to m.cols()\n";
            exit(1);
        }

        for (unsigned row = 0; row < m.rows(); row++) {
            for (unsigned col = 0; col < m.cols(); col++)
                m(row,col) = _m(row,col);
            m(row, m.cols()-1) =  v(row);
        }
    }
    Vector<Data> solve()
    {
        gauss_fwd();
        gauss_bwd();
        return x;
    }

    void gauss_fwd()
    {
        // iterating over rows we should make column under current diagonal entry all-zeros
        double factor;
        for (unsigned keyRow = 0; keyRow < m.rows(); keyRow++)
        {
            for (unsigned row = keyRow+1; row < m.rows(); row++) {
                factor = (-1.0)*m(row, keyRow)/m(keyRow, keyRow);
                m.addToRow(row, keyRow, factor);
            }
        }
    }

    void gauss_bwd()
    {
        Data scp{0.0};
        // backward iteration with sustitution
        for (int keyRow = m.rows()-1; keyRow >= 0; keyRow--)
        {
            scp = 0.0;
            for (int col = keyRow+1; col < m.cols()-1; col++) {
                scp += m(keyRow, col) * x(col);
            }
            x(keyRow) = (m(keyRow, m.cols()-1) - scp)/m(keyRow, keyRow);
        }
    }

    Vector<Data>& getSolution()
    {
        return x;
    }

    friend ostream& operator<< <Data> (ostream& out, LESystem<Data>& m);
};

template <typename T>
ostream& operator<< (ostream& out, LESystem<T>& m)
{
    return (out << m.m << std::endl);
}


#endif // SLAE_H
