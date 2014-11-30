#include <matrix.h>
#include <iostream>
#include <chrono>

int main(/*int argc, char * argv[]*/)
{
    using namespace chrono;
    Matrix<double> m(10);
    m.fill(10.0);
    m.randomize(0.0, 1.0);

    double factor;
    for (unsigned keyRow = 0; keyRow < m.size(); keyRow++)
    {
        for (unsigned row = keyRow+1; row < m.size(); row++) {
            factor = (-1.0)*m(row, keyRow)/m(keyRow, keyRow);
            m.addToRow(row, keyRow, factor);
        }
    }

    std::cout << m;

    return 0;
}
