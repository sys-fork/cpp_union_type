## C++ で使える Union 型です

初期化，代入，暗黙の型変換をサポートしており，Python や TypeScript などの言語で使用できる Union 型と同様に使うことができます．

```cpp
// union_type_test.cc
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
```
実行結果:
```bash
1
f: 1
Hello World!
g: Hello World!
f: 2
h: 4
h: You said: Have a nice day!
```

[`std::visit`](https://cpprefjp.github.io/reference/variant/visit.html) によるオーバーロードされた関数への呼び出しのようなことはできません（未実装）．

## C++ 標準による Union 型
C++ 標準に [`std::variant`](https://cpprefjp.github.io/reference/variant/variant.html) というものがあり，これが標準で用意されている Union 型です．`std::variant` では暗黙の型変換ではなく，`std::get` を使用して値を取得します．
