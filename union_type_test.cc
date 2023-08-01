#include <iostream>
#include <string>
#include "union_type.hh"

void f(int i) {
    std::cout << i << std::endl;
}

void g(std::string s) {
    std::cout << s << std::endl;
}

int main(void)
{
    Union<int, std::string> u;

    u = 1;
    f(u);
    u = "Hello, world!";
    g(u);
}
