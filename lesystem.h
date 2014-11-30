#ifndef SLAE_H
#define SLAE_H
#include <matrix.h>
#include <numvector.h>

template <typename Data>
class LESystem
{
    Matrix<Data> m;
    Vector<Data> v;
    Vector<Data> x;
public:
    LESystem();
    void insertCopyMatrix(Matrix<Data> new_m)
    {
        m = new_m;
    }
    void insertCopyFreeVec(Vector<Data> new_v)
    {
        v = new_v;
    }
    void solve()
    {
        if (m.size() != v.size())
            exit(1);
        gauss_fwd();
    }
    void gauss_fwd()
    {
        // iterating over rows we should make column under current diagonal entry all-zeros
        double factor;
        for (unsigned keyRow = 0; keyRow < m.size(); keyRow++)
        {
            for (unsigned row = keyRow+1; row < m.size(); row++) {
                factor = (-1.0)*m(row, keyRow)/m(keyRow, keyRow);
                m.addToRow(row, keyRow, factor);
            }
        }
    }

    void gauss_bwd()
    {
        // backward iteration with sustitution
        for (unsigned keyRow = m.size()-1; keyRow >= 0; keyRow--)
        {

        }
    }

    Vector<Data>& getSolution()
    {
        return v;
    }
};

#endif // SLAE_H
