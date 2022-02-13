#include<iostream>

template<typename T>
class ObjCounter{
public:
    ObjCounter() {++count;};
    ObjCounter(const ObjCounter<T>&) {++count;};
    ObjCounter(const ObjCounter<T>&&) {++count;};
    virtual  ~ObjCounter() {--count;};
    static int count;
};

template<typename T>
int ObjCounter<T>::count = 0;


struct A : ObjCounter<A>
{
};

int main()
{
    for(int i = 0; i< 100; ++i)
    {
        A a;
        A b = a;
    }
    std::cout << ObjCounter<A>::count << std::endl;
}
