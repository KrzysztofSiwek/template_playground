#include <functional>
#include <iostream>

struct A{
    int i;
    void a(){};
};

template<typename T, typename U>
using MemberPtr = U T::*;

struct B{

    template<typename T, typename U>
    void test(int a,U T::* u){
       T t{};
       t.*u = a;
       std::cout << t.*u << std::endl;
    }
};

int main(){
   int A::* p = &A::i;
   void (A:: *fp)() = &A::a;
   B().test<A, int>(2, &A::i);
}
