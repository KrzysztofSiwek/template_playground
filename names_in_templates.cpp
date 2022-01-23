template<typename T>
struct Shell{
    template<int N>
    struct In{
        template<int M>
        struct Deep{
            virtual void f();
        };      
    };
};

template<typename T, int N>
struct Weird{
    void case1(typename Shell<T>::template In<N>::template Deep<N>* p){
        p->template Deep<N>::f();    
    }
    void case2 (typename Shell<T>::template In<N>::template Deep<N>& p) {
        p.template Deep<N>::f();
    }
};

int main()
{
    Weird<int, 6> a;
}
