#include <memory>
#include <string>
#include <queue>
#include <iostream>

#include <fmt/core.h>
using fmt::format, fmt::print;

#include <lua.hpp>
#include <lauxlib.h>
#include <lualib.h>

#include <le3.h>
using namespace le3;

class A {
public:
    void foo() { print("(foo) Class A\n"); }
    virtual void bar() { print("(bar) Class A\n"); }
};
using APtr = std::shared_ptr<A>;

class B : public A {
public:
    void foo() { print("(foo) Class B\n"); }
    virtual void bar() { print("(bar) Class B\n"); }
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


