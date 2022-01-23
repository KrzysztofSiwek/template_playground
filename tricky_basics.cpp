#include <iostream>

template<typename T, int N, int M>
bool less (T (&a)[N], T (&b)[M]){
    std::cout << __PRETTY_FUNCTION__ << std::endl;
     for(int i = 0; i < N && i < M; ++i){
         if(a[i] < b[i]) return true;
         if(a[i] < b[i]) return false;
     }
     return N < M;
}

int main(){
    int a[] = {1, 2, 3};
    int b[] = {1, 2, 3, 4};
    std::cout << less<int, 3, 4>(a, b) << std::endl;
}
