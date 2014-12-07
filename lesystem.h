#ifndef SLAE_H
#define SLAE_H
#include <matrix.h>
#include <numvector.h>
#include <exception>
#include <utility>

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
    LESystem(Matrix<Data> _m, Vector<Data> v) : m(_m.rows(), _m.cols()+1), x(_m.cols())
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

    void insertCopyMatrix(const Matrix<Data>& new_m)
    {
        assert(new_m.cols() == m.cols()-1 && new_m.rows() == m.rows());
        for (unsigned i = 0; i < new_m.rows(); i++)
            for (unsigned j = 0; j < new_m.cols(); j++)
                m(i,j) = new_m(i,j);
    }

    void insertCopyRight(const Vector<Data>& new_v)
    {
        assert(new_v.size() == m.rows());
        for (unsigned i = 0; i < new_v.size(); i++)
            m(i, mpos::last) = new_v(i);
    }

    bool isSingular()
    {
        for (unsigned row = 0; row < m.rows(); row++)
            if (fabs(m(row, row)) < 10.0E-10) {
                std::cerr << "!:" << row << std::endl;
                return true;
            }
        return false;
    }
    void swapRows(unsigned i, unsigned j)
    {
        for (unsigned col = 0; col < m.cols(); col++)
        {
            std::swap(m(i,col), m(j,col));
        }
    }
    unsigned findSafeRow(unsigned origin)
    {
        for (unsigned i = origin+1; i < m.rows(); i++)
            if (fabs(m(i,i)) > 10.0E-16)
                return i;
        return -1;
    }

    Vector<Data> solve()
    {
        if (m.rows() == 1)
        {
            x.fill(m(0,1)/m(0,0));
            return x;
        }
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
            if (fabs(m(keyRow,keyRow)) < 10.0E-16)
            {
                unsigned safeRow = findSafeRow(keyRow);
                assert(safeRow > 0);
                swapRows(keyRow, safeRow);
            }
            for (unsigned row = keyRow+1; row < m.rows(); row++) {
                if (fabs(m(row,keyRow)) > 10.0E-16) {
                    factor = (-1.0)*m(row, keyRow)/m(keyRow, keyRow);
                    m.addToRow(row, keyRow, factor);
                }
            }
        }

//        for (unsigned keyRow = 0; keyRow <= m.rows(); keyRow++)
//        {
//            for (unsigned row = keyRow+1; row < m.rows(); row++)
//            {
//                if (fabs(m(row,keyRow)) > 10.0E-16) {
//                    factor = (-1.0)*m(row, keyRow)/m(keyRow, keyRow);
//                    for (unsigned col = 0; col < m.cols(); col++)
//                        if ( fabs(m(keyRow,col)) > 10.0E-16)
//                            m(row,col) += m(keyRow,col) * factor;
//                }
//            }
//        }
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
