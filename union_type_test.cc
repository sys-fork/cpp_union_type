#include <iostream>
#include <string>
#include "union_type.hh"

using namespace union_type;

void f(int);
void g(std::string);
void h(Union<int, std::string>);

int main(void)
{
    Union<int, std::string, float, double> u = 1;
    Union<int> i = 2;

    std::cout << u << std::endl;
    f(u);
    u = std::string("Hello World!");
    std::cout << u << std::endl;
    g(u);
    // f(u); -> Error
    f(i);
    h(3);
    h(std::string("Have a nice day!"));
}

void f(int i)
{
    std::cout << "f: " << i << std::endl;
}

void g(std::string s)
{
    std::cout << "g: " << s << std::endl;
}

void h(Union<int, std::string> u)
{
    std::cout << "h: ";
    if (has_type<int>(u)) {
        std::cout << static_cast<int>(u) + 1 << std::endl;
    } else {
        std::cout << "You said: " << u << std::endl;
    }
}
