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
    void test(std::function<A(int)> func, MemberPtr<T, U>... u){
       T t{};int i = 5;
       ((t.*u =  func(i).*u),...);
       ((std::cout <<  t .* u), ...) << std::endl ;
    }
};

int main(){
 //  int A::* p = &A::a;
//   void (A:: *fp)() = &A::e;
   B().test<A, int>([](int a)->A{return A{a++,a++,a++,a++};}, &A::a, &A::b, &A::c, &A::d);
}
