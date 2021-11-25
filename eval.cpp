#include <functional>

#include <iostream>

using std::function;

template<class ReturnType>
struct procedure{

    ReturnType value;
    bool computed;
    function<ReturnType(void)> func;
    procedure(): value{0}, computed(true){ //Identity Case
    }
    procedure(const ReturnType &val): value(val), computed(true){ //Identity Case
    }
    template<class InputType>
    procedure(ReturnType(foo)(InputType), const InputType &in): computed(false),
        func([foo, &in] (){
            return foo(in);
        }) {}
    template<class InputType>
    procedure(ReturnType(foo)(InputType), procedure<InputType> &in): computed(false),
        func([foo, &in] (){
            return foo(in);
        }) {}
    template<class... InputType>
    procedure(ReturnType(foo)(InputType...), procedure<InputType>&... in): computed(false),
        func([foo, &in...] (){
            return foo(in...);
        }) {}
    void compute(){
        std::cout << "Computed\n";
        value = func();
        computed = true;
    }
    operator ReturnType(){
        if(!computed){
            compute();
        }
        return value;
    }
};

int add1(int x){
        std::cout << x << "!\n";
    return x + 1;
}
int add(int x, int y){
    return x + y;
}
int add(int x, int y, int z){
    std::cout << x << "\t" << y <<"\t" << z << "\n";
    return x + y + z;
}
 
int main(int argc, char **argv){
    procedure x{5};
    int val = 5;
    procedure y{add1, val};
    procedure z{add1,y};
    procedure<int> a;
    if(true){
       a = procedure{add1,z};
    }
    else{
        a = procedure{add1,x};
    }

    procedure<int> b{add,a,z,y};
    x = 0;
    std::cout << x << std::endl;
    std::cout << b << std::endl;
    std::cout << b << std::endl;

    //std::cout << y << "\n";
    //std::cout << b<< "\n";
    return y;
}
