#include <type_traits>
#include <iostream>
#include <string>
template <typename T>
std::enable_if_t<std::is_trivially_default_constructible_v<T>> construct(T* p){
    std::cout << __PRETTY_FUNCTION__ << std::endl << "Trivially default constructible" << std::endl;
}

template <typename T>
std::enable_if_t<!std::is_trivially_default_constructible_v<T>> construct(T* p){
    std::cout << __PRETTY_FUNCTION__ << std::endl << "non-trivially default constructible" << std::endl;
}

template<typename T, typename... Args>
std::enable_if_t<std::is_constructible_v<T, Args&&...>> construct(T* p, Args&&... args){
    std::cout << __PRETTY_FUNCTION__ << std::endl << "multiarg constructible" << std::endl;
}

template<typename T>
void destroy(T*, std::enable_if_t<std::is_trivially_destructible_v<T>, bool> = true){
    std::cout << __PRETTY_FUNCTION__ << std::endl << "Trivially destructible" << std::endl;
}

template<typename T>
void destroy(T*, std::enable_if_t<!std::is_trivially_destructible_v<T> &&
                                   (std::is_class_v<T> || std::is_union_v<T>),
                                   bool> = true){
    std::cout << __PRETTY_FUNCTION__ << std::endl << "non-trivially destructible" << std::endl;
}

template<typename T, typename Enable = void>// void_t?
struct A{
   void a () {std::cout << __PRETTY_FUNCTION__ << std::endl << " non float " << std::endl;}
};

template<typename T>
struct A<T, std::enable_if_t<std::is_floating_point_v<T>>>{
   void a () {std::cout << __PRETTY_FUNCTION__ << std::endl << " float " << std::endl;}
};

int main(){
    int* i = nullptr;
    std::string* s = nullptr;
    char a[5];
    construct(i);
    construct(s);
    construct(a);
    construct(s, "asd");
    destroy(i);
    destroy(s);
    A<int> a1;
    A<std::string> a2;
    A<double> a3;
    A<float>  a4;
    a1.a(); a2.a(); a3.a(); a4.a();
}
