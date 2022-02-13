#include <utility>
#include <iostream>

template<typename Signature>
class FunctionPtr;

template<typename R, typename... Args>
class FunctorBridge{
public:
    virtual ~FunctorBridge() = default;
    virtual FunctorBridge* clone() const = 0;
    virtual R invoke(Args... args) const = 0;
};

template<typename Functor, typename R, typename... Args>
class SpecificFunctorBridge: public FunctorBridge<R, Args...>{
    Functor functor;
public:
    template<typename FunctorFwd>
    SpecificFunctorBridge(FunctorFwd&& functor): functor(std::forward<FunctorFwd>(functor)){ std::cout << __PRETTY_FUNCTION__ << std::endl;}
    SpecificFunctorBridge* clone() const override {return new SpecificFunctorBridge(functor);}
    R invoke(Args... args) const override {return functor(std::forward<Args>(args)...);}
};

template<typename R, typename... Args>
class FunctionPtr<R(Args...)>
{
    FunctorBridge<R, Args...>* bridge;
public:
    FunctionPtr():bridge(nullptr){};
    FunctionPtr(const FunctionPtr& other);
    FunctionPtr(FunctionPtr& other) : FunctionPtr(static_cast<const FunctionPtr&>(other)){}
    FunctionPtr(FunctionPtr&& other) : bridge(other.bridge){other.bridge = nullptr;}
    template<typename F> FunctionPtr(F&& f){
        using Functor = std::decay_t<F>;
        using Bridge  = SpecificFunctorBridge<Functor, R, Args...>;
        bridge = new Bridge(std::forward<F>(f));
    }
    // Assign operators etc...

   ~ FunctionPtr(){delete bridge;};
    explicit operator bool() const {return bridge != nullptr;}
    R operator() (Args... args) const {return bridge->invoke(std::forward<Args>(args)...);}
};

int a (int x){
    std::cout << "a" << std::endl;
    return 3;
}


struct B{
    bool  operator()() const{std::cout << "b" << std::endl; return false;}
};

int main()
{
    FunctionPtr<int(int)> x(&a);
    B tmp;
    FunctionPtr<bool()> y(tmp);
    FunctionPtr<void()> z([](){std::cout << "lambda" << std::endl;});
    x(5); y(); z();

}
