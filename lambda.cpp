#include <iostream>
#include <vector>
#include <algorithm>

#include <functional>

// Lambda function acts like a class that has a member variables
int main() {
    std::vector<int> vals = {1,2,3,4,5,7,10,20};

    auto is_above_3 = [](int v){ return v > 3;};
    ptrdiff_t num_above_3 = std::count_if(vals.begin(), vals.end(), is_above_3);
    std::cout << num_above_3 << "\n";

    int th = 5;
    //This lambda function uses 'capture by reference'
    auto is_above_threshold = [&th](int v){ return v > th;};
    ptrdiff_t num_above_threshold = std::count_if(vals.begin(), vals.end(), is_above_threshold);
    std::cout << num_above_threshold << "\n\n";

    //Initializing a capture in lambda function
    auto func = [c=std::vector<int>{1,3}](){
        for(auto ci : c){
            std::cout<<ci<< "\n";
        }
    };
    func();

    int v=5;
    //Initializing a lambda function that has mutable capture
    auto func2 = [v]() mutable {
        v++;
        std::cout << "inside func2: v=" << v <<"\n";
    };  
    std::cout << "v=" << v << "\n";
    func2(); 
    func2(); // notice that the v inside func2 becomes 7
    std::cout << "v=" << v << "\n"; // v outside is still 5

    // std::function can hold any function that has the same return type
    // voidFunc hold function that takes in two int and returns void
    std::function<void(int, int)> voidFunc;
    // you can put in any lambda function with matching return type. 
    // This is different from lambda functions that has unique type even if they have same return type

    // lambda fucntions can be called inline (meaning no compiler overhead when calling)
    // std::function can not do that for extra flexibility. This means worse performance

    // Most implementation of std::function allocates it in heap meaning potential cache miss
}

class foo {
    public:
    void memberfunctions() {
        int c = 2;
        //Capture all variables in scope by copy
        auto l1 = [=]() {std::cout << a << b << c;};

        //capture all variables in scope by reference
        auto l2 = [&]() {a++;b++;c++;};

        //capture all member variables by copy
        auto l2 = [*this]() {int A = a;int B = b;std::cout << A << " " << B;}; 
        //a++;b++; causes compiler error because a++ expression needs lvalue
        //in other words, because a and b are copied, it needs to be assigned within the lambda function in order to increment it with ++

        //capture all member variables by reference
        auto l2 = [this]() {a++;b++;};
    }
    private:
    int a = 0;
    int b = 1;
};