#include <functional>
#include <iostream>
#include <tuple>

struct A{
    int a;
    int b;
    int c;
    int d;
    void e(){};
};

struct B{
    double padding;
    int a;
    int b;
    void e(){};
};

struct C{
    char x[50];
    int a;
    int b;
    int c;
    int d;
    void e(){};
};

template<typename T, typename U>
using MemberPtr = U T::*;

template<typename... Ts>
struct Test{
    template<typename T, typename... U>
    void test(std::function<T(int)> func, MemberPtr<T, U>... u){
       T t{};int i = 5;
       std::cout << "NEW MEMBER:\n";
       ((t.*u =  func(i).*u),...);
       ((std::cout <<  t.* u), ...) << std::endl << "Now assigned: " << std::endl;
       std::get<T>(Types) = t;
       ((std::cout << std::get<T>(Types).* u), ...) << std::endl ;
    }
    
    std::tuple<Ts...> Types;
};

int main(){
 //  int A::* p = &A::a;
//   void (A:: *fp)() = &A::e;
   Test<A,B,C> b;
   b.test<A>([](int a)->A{return A{a++,a++,a++,a++};}, &A::a, &A::b, &A::c, &A::d);
   b.test<B>([](int a)->B{return B{0.0, a++,a++};}, &B::a, &B::b, &B::padding);
   b.test<C>([](int a)->C{return C{{}, a--,a--,a--,a--};}, &C::a, &C::b, &C::c, &C::d);
}
