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
    Union<int, std::string, float, std::uint8_t, std::uint32_t> u = 1;
    Union<int> i = 3;

    u = 1;
    f(u);
    // Union の実装の内部で std::is_same_v で場合分けしている
    // 関係で，std::string 型にしないとうまく動かない
    u = std::string("Hello World!");
    g(u);
    // f(u); -> Error
    f(i);
}
