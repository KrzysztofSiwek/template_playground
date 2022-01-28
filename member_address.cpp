#include <functional>
#include <iostream>

struct A{
    int a;
    int b;
    int c;
    int d;
    void e(){};
};

template<typename T, typename U>
using MemberPtr = U T::*;

struct B{

    template<typename T, typename... U>
    void test(int a, MemberPtr<T, U>... u){
       T t{};
       ((t .*  u=  a++),...);
       ((std::cout <<  t .* u), ...) << std::endl ;
    }
};

int main(){
   int A::* p = &A::a;
   void (A:: *fp)() = &A::e;
   B().test<A, int>(2, &A::a, &A::b, &A::c, &A::d);
}
