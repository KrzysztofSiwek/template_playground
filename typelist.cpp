#include<iostream>
#include<utility>
template<typename... Args>
void PrintTypes(){
    std::cout << __PRETTY_FUNCTION__ << std::endl;
}

template<typename... Args>
struct TypeList{
};

template<typename... Args>
struct PopFrontT;

template<typename T, typename... Args>
struct PopFrontT<TypeList<T, Args...>>{
    using Head = T;
    using Type = TypeList<Args...>;
};

template<>
struct PopFrontT<TypeList<>>{
};

template<typename... Args>
struct PushFrontT;

template<typename T, typename... Args>
struct PushFrontT<TypeList<Args...>, T>{
    using Type = TypeList<T, Args...>;
};

template<typename T, typename... Args>
struct PushBackT;

template<typename T, typename... Args>
struct PushBackT<TypeList<Args...>, T>{
    using Type = TypeList<Args..., T>;
};

template<typename... Args>
struct IsEmptyT;

template<typename... Args>
struct IsEmptyT<TypeList<Args...>> : public std::false_type{
};

template<>
struct IsEmptyT<TypeList<>> : public std::true_type{
};

template<typename... Args>
struct ReverseT;

template<typename... Args>
struct ReverseT<TypeList<Args...>>{
private:
    using Head = typename PopFrontT<TypeList<Args...>>::Head;
    using Tmp = typename ReverseT<typename PopFrontT<TypeList<Args...>>::Type>::Type;
public:
    using Type = typename PushBackT<Tmp, Head>::Type; // compare with answers in boook
};

template<>
struct ReverseT<TypeList<>>{
    using Type = TypeList<>;
};
using TestList = TypeList<double, int&, double, const char*>;
int main(){
    PrintTypes<TestList>();
    PrintTypes<PopFrontT<TestList>::Head>();
    PrintTypes<PopFrontT<TestList>::Type>();
    PrintTypes<PushFrontT<TestList, short>::Type>();
    PrintTypes<PushBackT<TestList, unsigned>::Type>();
    PrintTypes<IsEmptyT<TestList>::type>();
    PrintTypes<IsEmptyT<TypeList<>>::type>();
    PrintTypes<ReverseT<TestList>::Type>();
}
