## C++ で使える Union 型です

初期化，代入，暗黙の型変換をサポートしており，Python や TypeScript などの言語で使用できる Union 型と同様に使うことができます．

```cpp
// union_type_test.cc
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
```
実行結果:
```bash
1
Hello World!
2
4
You said: Have a nice day!
```

[`std::visit`](https://cpprefjp.github.io/reference/variant/visit.html) によるオーバーロードされた関数への呼び出しのようなことはできません（未実装）．

## C++ 標準による Union 型
C++ 標準に [`std::variant`](https://cpprefjp.github.io/reference/variant/variant.html) というものがあり，これが標準で用意されている Union 型です．`std::variant` では暗黙の型変換ではなく，`std::get` を使用して値を取得します．
