#include <memory>
#include <string>
#include <queue>
#include <iostream>

#include <fmt/core.h>

#if __has_include("lua.hpp")
    #include <lua.hpp>
    #include <lauxlib.h>
#elif __has_include("lua5.4/lua.hpp")
    #include <lua5.4/lua.hpp>
    #include <lua5.4/lauxlib.h>
#else
    #include <lua/lua.hpp>
    #include <lua/lauxlib.h>
#endif

#include <le3.h>
using namespace le3;

class A {
public:
    void foo() { fmt::print("(foo) Class A\n"); }
    virtual void bar() { fmt::print("(bar) Class A\n"); }
};
using APtr = std::shared_ptr<A>;

class B : public A {
public:
    void foo() { fmt::print("(foo) Class B [{}]\n", this->num); }
    virtual void bar() { fmt::print("(bar) Class B\n"); }

    int num = 3;
};
using BPtr = std::shared_ptr<B>;


int main() {
    APtr obj = std::dynamic_pointer_cast<A>(std::make_shared<B>());
    obj->foo();
    obj->bar();

    void* tmp = reinterpret_cast<void*>((APtr*)&obj);
    BPtr* obj_ = reinterpret_cast<BPtr*>(tmp);
    (*obj_)->foo();
    (*obj_)->bar();

    return 0;
}


