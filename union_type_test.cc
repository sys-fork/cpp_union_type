#include <iostream>
#include <string>
#include "union_type.hh"

void f(int i)
{
    std::cout << i << std::endl;
}

void g(std::string s)
{
    std::cout << s << std::endl;
}

void h(union_type::Union<int, std::string> u)
{
    if (union_type::has_type<int>(u)) {
        std::cout << static_cast<int>(u) + 1 << std::endl;
    } else {
        std::cout << "You said: " + static_cast<std::string>(u) << std::endl;
    }
}

int main(void)
{
    union_type::Union<int, std::string, float,
        std::uint8_t, std::uint32_t> u = 1;
    union_type::Union<int> i = 2;

    u = 1;
    f(u);
    u = std::string("Hello World!");
    g(u);
    // f(u); -> Error
    f(i);
    h(3);
    h(std::string("Have a nice day!"));
}
