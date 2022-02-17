#include <functional>
#include <string>
#include <iostream>
#include <tuple>
#include <type_traits>
#include "typelist.hpp"

struct T1{};

struct Policies1{
    using Id = T1;
    static T1 test1(T1 a, std::string b = ""){
        std::cout << "P1::"<< __func__ << b << std::endl;
        return a;
    }
    static double test2(int a, std::string b = "", double c = 0.0){
        std::cout << __func__ << c << b << std::endl;
        return a;
    }
    static std::string test3(){
        return __func__;
    }
};

struct T2{};
struct Policies2{
    using Id = T2;
    static T2 test1(T2 a){
        std::cout << "P2::" << __func__ << std::endl;
        return a;
    }
    static uint8_t test2(int a, std::string b = "", double c = 0.0){
        std::cout << __func__ << c << b << std::endl;
        return a;
    }
    static const std::string test3(){
        return __func__;
    }
};

struct T3{};
struct Policies3{
    using Id = T3;
    static T3 test1(T3 a){
        std::cout << "P3::" << __func__ << std::endl;
        return a;
    }
    static uint8_t test2(int a, std::string b = "", double c = 0.0){
        std::cout << __func__ << c << b << std::endl;
        return a;
    }
    static const std::string test3(){
        return __func__;
    }
};

template<typename T, typename List>
struct ContainsIdT: std::conditional_t<
                                   std::is_same<T, typename Front<List>::Id>::value,
                                                std::true_type,
                                                ContainsIdT<T, PopFront<List>>>{
};

template<typename T>
struct ContainsIdT<T, TypeList<>>: std::false_type{
};

template<typename T, typename List>
constexpr bool ContainsId = ContainsIdT<T, List>::value;

//sfinae out types without ::Id
template<typename T, typename List>
struct FindPolicyByIdImplT{
    using Type = std::conditional_t<
                                   std::is_same<T, typename Front<List>::Id>::value,
                                                Front<List>,
                                                typename FindPolicyByIdImplT<T, PopFront<List>>::Type>;
};

template<typename T, typename LastElem>
struct FindPolicyByIdImplT<T, TypeList<LastElem>>{
    using Type = LastElem;
};

template<typename T, typename List>
using FindPolicyByIdImpl = typename FindPolicyByIdImplT<T, List>::Type;

template<typename T, typename List, bool = ContainsId<T, List>>
struct FindPolicyByIdT{
    using Type = FindPolicyByIdImpl<T, List>;
};

template<typename T, typename List>
struct FindPolicyByIdT<T, List, false>{
};

template<typename T, typename List>
using FindPolicyById = typename FindPolicyByIdT<T, List>::Type;

template<typename... Args>
class PolicyDispatcher{
    using policyList = TypeList<Args...>;
    std::tuple<typename Args::Id...> typesStorage;
public:
    template<typename T>
    void dispatch(T arg){
        using policy = FindPolicyById<T, policyList>;
        policy::test1(arg);
    }
};


int main(){
    using GoodList = TypeList<Policies3, Policies1, Policies2>;
    using BadList = TypeList<Policies2, Policies1>;
    PolicyDispatcher<Policies1, Policies2, Policies3> dispatcher;
//    PrintTypes<FindPolicyById<T3, BadList>>();
    PrintTypes<FindPolicyById<T1, GoodList>>();
    PrintTypes<FindPolicyById<T2, GoodList>>();
    PrintTypes<FindPolicyById<T3, GoodList>>();
    T1 a;
    dispatcher.dispatch<T1>(a);
    T2 b;
    dispatcher.dispatch<T2>(b);
    T3 c;
    dispatcher.dispatch<T3>(c);
}
