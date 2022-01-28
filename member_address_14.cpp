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
    template<typename T, typename X>
    void test(std::function<T(int)> func, MemberPtr<T, X> firstMember){
       int i = 5;
       std::get<T>(Types).*firstMember =  func(i).*firstMember;
    }

    template<typename T, typename  X, typename... U>
    void test(std::function<T(int)> func,  MemberPtr<T, X> firstMember, MemberPtr<T, U>... u){
        int i = 5;
       std::get<T>(Types).*firstMember =  func(i).*firstMember;
       test(func, u...);
    }
    
    std::tuple<Ts...> Types;
};

int main(){
 //  int A::* p = &A::a;
//   void (A:: *fp)() = &A::e;
   Test<A,B,C> b;
   std::cout << "NEW MEMBER:\n";
   b.test<A>([](int a)->A{return A{a++,a++,a++,a++};}, &A::a, &A::b, &A::c, &A::d);
   std::cout << "Now assigned: " << std::get<A>(b.Types).a<< std::get<A>(b.Types).b<< std::get<A>(b.Types).c<< std::get<A>(b.Types).d << std::endl;
   std::cout << "NEW MEMBER:\n";
   b.test<B>([](int a)->B{return B{0.0, a++,a++};}, &B::a, &B::b, &B::padding);
   std::cout << "Now assigned: " << std::get<B>(b.Types).a<< std::get<B>(b.Types).b<< std::get<B>(b.Types).padding << std::endl;
   std::cout << "NEW MEMBER:\n";
   b.test<C>([](int a)->C{return C{{}, a--,a--,a--,a--};}, &C::a, &C::b, &C::c, &C::d);
   std::cout << "Now assigned: " << std::get<C>(b.Types).a<< std::get<C>(b.Types).b<< std::get<C>(b.Types).c<< std::get<C>(b.Types).d << std::endl;
}
