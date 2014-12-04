#include <iostream>
#include <myfunctor.h>
#include <cmath>
#include <lesystem.h>
#include <iomanip>
#include <nesystem.h>
using namespace std;

class MyClass {
    int* d;
    size_t sz;
public:
    MyClass() : d(new int[1]), sz(1)
    {
        std::cout << "MyClass() called\n";
    }
    MyClass(size_t _sz) : d(new int[_sz]), sz(_sz)
    {
        std::cout << "Myclass(size_t) called\n";
    }
    // copy
    MyClass(const MyClass& obj)
    {
        d = new int[obj.sz];
        sz = obj.sz;
        for (size_t i = 0; i < sz; i++)
            d[i] = obj.d[i];
        std::cout << "Myclass(const MyClass&) called\n";
    }
    MyClass& operator =(const MyClass& obj)
    {
        if (d != nullptr)
            delete d;
        d = new int[obj.sz];
        sz = obj.sz;
        for (size_t i = 0; i < sz; i++)
            d[i] = obj.d[i];
        std::cout << "MyClass& operator =(const MyClass&) called\n";

        return *this;
    }
    //move
    MyClass(MyClass&& obj)
    {
        sz = obj.sz;
        d = obj.d;

        obj.d = nullptr;
        obj.sz = 0;
        std::cout << "Myclass(MyClass&&) called\n";
    }
    MyClass& operator =(MyClass&& obj)
    {
        if (d != nullptr)
            delete d;
        d = obj.d;
        sz = obj.sz;

        obj.d = nullptr;
        obj.sz = 0;
        std::cout << "MyClass& operator =(MyClass&&) called\n";

        return *this;
    }


    int get(size_t i) const {
        return d[i];
    }
    int& get(size_t i) {
        return d[i];
    }

    size_t size() const {
        return sz;
    }
};

MyClass& f(MyClass& m)
{
    if (m.size() >= 3) {
        m.get(0) = 1;
        m.get(1) = 2;
        m.get(2) = 3;
    }
    std::cout << "MyClass& f(MyClass& m) called\n";
    return m;
}

MyClass f(MyClass m)
{
    if (m.size() >= 3) {
        m.get(0) = 1;
        m.get(1) = 2;
        m.get(2) = 3;
    }
    std::cout << "MyClass f(MyClass m) called\n";
    return m;
}

MyClass f()
{
    MyClass m(3);
    if (m.size() >= 3) {
        m.get(0) = 1;
        m.get(1) = 2;
        m.get(2) = 3;
    }
    std::cout << "MyClass f() called\n";
    return m;
}


int main(/*int argc, char * argv[]*/)
{    
    AbstractFunctor<double>* f = new MyFunctor;
    RealVec X0(4);
    RealMat m(4,4);
    X0(0) = -0.7+1.0;
    X0(1) = 1.098;
    X0(2) = 0.52;
    X0(3) = -0.82;

    RealNESystem s(f);
    RealVec v = s.solve(X0);

    std::cout << v;
    std::cout << std::endl << std::setprecision(16) << f->val(v).mag() << std::endl;



    return 0;
}
