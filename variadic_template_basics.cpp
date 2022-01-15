#include <iostream>
#include <iomanip>
#include <string>
#include <vector>

void print(){
    std::cout << std::endl;
}

template<typename T, typename... Types>
void print(T firstArg, Types... args){
//    std::cout << std::setw(100) << std::left << __PRETTY_FUNCTION__ << std::setw(15);
//    std::cout << "size args: " << sizeof...(args) << " sizeof types: " << sizeof...(Types) << " ";
    std::cout << firstArg << " ";
    print(args...);
}

template<typename... T>
auto foldSum(T... s){
    return (... + s);
}

struct Node{
    int value;
    Node* left;
    Node* right;
    Node(const int i = 0): value(i), left(nullptr), right(nullptr){
    }
};

auto left  = &Node::left;
auto right = &Node::right;

template<typename T, typename... TP>
Node* traverse(T np, TP... paths){
    return (np->* ... ->* paths);
}

template<typename... T>
void printDoubled(T const&... args){
    print(args + args...);
}

template<typename... T>
void addOne(T const& ... args){
    print((args + 1)...);
}

template<typename T, typename... TN>
bool isHomogeneus(T, TN...){
    return (std::is_same<T,TN>::value && ...);
}

template<typename T, typename... Idx>
void printElems(T const& coll, Idx... idx){
    print(coll[idx]...);
}

int main(){
    print("Print test:", 132, 32UL, 32.0, 32.0);
    print("Fold test:", foldSum(1,2,3,4), foldSum(1,32.0, 11UL));
    Node* root = new Node{0};
    root->left = new Node{1};
    root->left->right = new Node{2};
    Node* node = traverse(root, left, right);
    print("Tree test: ", node->value);
    printDoubled(123, std::string("asd"), 32.0);
    addOne(12, 0.5);
    std::cout << std::boolalpha << "Homo test: " << isHomogeneus(1,2,3,4) << " " << isHomogeneus(2.3,2) << " " << isHomogeneus("asd", "", "!") << std::endl;
    std::vector<std::string> coll = {"123", "zxcz", "232tgfd", "4t5g"};
    printElems(coll, 0, 1, 3);
}
