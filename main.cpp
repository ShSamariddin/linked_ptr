#include <iostream>
#include "linked_ptr.h"
using namespace std;
struct B {
    int b = 9;

    B(int b) : b(b) {}
};
struct A {
    int a = 5;
    B b = 9;

    A(int a) : a(a), b(9) {}
    A(){}
};
int main() {

    A b(6);
    A c = 7;
    linked_ptr<A> l1(&b);
    cout << l1.get()->a;
}