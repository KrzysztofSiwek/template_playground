#include<iostream>
#include<cstddef>
#include<utility>

template<typename T>
struct TypeSize{
    static std::size_t const value = sizeof(T);
};

template<typename T>
struct ElementT;

template<typename T, std::size_t N>
struct ElementT<T[N]>{
    using Type = T; //specialization for all tables needed
};

template<typename T>
struct RemoveReferenceT{
    using Type = T;
};

template<typename T>
struct RemoveReferenceT<T&>{
    using Type = T;
};

template<typename T>
struct RemoveReferenceT<T&&>{
    using Type = T;
};

template<typename T1, typename T2>
struct PlusResultTV1{// this is not sfinae friendly
    using Type = decltype(std::declval<T1>() + std::declval<T2>());
};

template<typename T>
struct IsDefaultConstructibleHelper{
private:
    template<typename U, typename = decltype(U())>
        static std::true_type test(void*);
    template<typename>
        static std::false_type test(...);
public:
    using Type = decltype(test<T>(nullptr));
};

template<typename T>
struct IsDefaultConstructible: IsDefaultConstructibleHelper<T>::Type{
};

template<typename ...> using VoidT = void;

template<typename, typename = VoidT<>>
struct IsDefaultConstructibleV2: std::false_type{
};

template<typename T>
struct IsDefaultConstructibleV2<T, VoidT<decltype(T())>>: std::true_type{
};

template<typename, typename, typename = VoidT<>>
struct HasPlusT: std::false_type{
};

template<typename T1, typename T2>
struct HasPlusT<T1, T2, VoidT<decltype(std::declval<T1>()+std::declval<T2>())>>: std::true_type{
};

template<typename T1, typename T2, bool = HasPlusT<T1, T2>::value>
struct PlusResultT{
    using Type = decltype(std::declval<T1>()+std::declval<T2>());  
};

template<typename T1, typename T2>
struct PlusResultT<T1, T2, false>{
};

template<typename FROM, typename TO>
struct IsConvertibleT{
private:
    static void aux(TO);
    template<typename F, typename T, typename = decltype(aux(std::declval<F>()))>
    static std::true_type test(void*);// special cases not handled
    template<typename, typename>
    static std::false_type test(...);
public:
    using Type = decltype(test<FROM, TO>(nullptr));
};

template<typename, typename = VoidT<>>
struct HasTestMemberT: std::false_type{
};

template<typename T>
struct HasTestMemberT<T, VoidT<decltype(&T::test_member)>>: std::true_type{ //typename instead of decltype for detecting traits
};

struct MemberTest{
    int test_member;
//    int test_member(int); - with this trait wont work
};

template<typename, typename = VoidT<>>
struct HasTestFuncMemberT: std::false_type{
};

template<typename T>
struct HasTestFuncMemberT<T, VoidT<decltype(std::declval<T>().Func())>>: std::true_type{ //works with function overloads
};

struct MemberFuncTest{
    int Func();
    int Func(int); 
};

template<bool COND,typename FalseType, typename TrueType>
struct IfThenElseT{
    using Type = TrueType;
};

template<typename FalseType, typename TrueType>
struct IfThenElseT<false, FalseType, TrueType>{
    using Type = FalseType;
};

template<typename T>
struct IsNoThrowConstructibleT: std::bool_constant<noexcept(T(std::declval<T>()))>{
};

struct CtorNoNoThrow{
    CtorNoNoThrow(const CtorNoNoThrow&){};
};

int main(){
    std::cout << IsConvertibleT<int, double>::Type::value <<  " " << IsConvertibleT<char[6], char>::Type::value << std::endl;
    std::cout << "Typesize<int> " << TypeSize<int>::value << std::endl;
    std::cout << "plusresult int+double " << typeid(PlusResultT<int,double>::Type).name() << std::endl;
    std::cout << "ElementT<char[6]> " << typeid(ElementT<char[6]>::Type).name() << std::endl;
    std::cout << "Has Test A: "<< HasTestMemberT<MemberTest>::value << " Has Test int: "<< HasTestMemberT<int>::value << std::endl;
    std::cout << "Has Test Func A: "<< HasTestFuncMemberT<MemberFuncTest>::value << " Has Test Func int: "<< HasTestFuncMemberT<int>::value << std::endl;
    std::cout << "IsNoThrowConstructible Test:" << IsNoThrowConstructibleT<CtorNoNoThrow>::value << IsNoThrowConstructibleT<MemberTest>::value << std::endl;
}
