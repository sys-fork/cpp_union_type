#include <type_traits>
#include <utility>
#include <iostream>
#include <cstdlib>

template <class...>
struct Union;

template <class U>
struct Union<U> {
private:
    U u;
    bool u_is_set;
public:
    Union() = default;
    Union(const U& u_) : u(u_), u_is_set(true) {}
    Union(U&& u_) : u(std::move(u_)), u_is_set(true) {}

    Union& operator=(const U& u_) {
        u = u_;
        u_is_set = true;
        return *this;
    }
    Union& operator=(U&& u_) {
        u = std::move(u_);
        u_is_set = true;
        return *this;
    }
    // ムーブ代入演算子はデフォルト

    operator U() const noexcept {
        if (!u_is_set) {
            std::cerr
                << "Union Type Error: Required type "
                << typeid(U).name()
                << " is not set." << std::endl;
            std::exit(EXIT_FAILURE);
        }
        return u;
    }

    virtual ~Union() = default;
};

template <class U, class V, class ...Rest>
struct Union<U, V, Rest...> {
private:
    U u;
    Union<V, Rest...> v;
    bool u_is_set = false;
    bool v_is_set = false;

public:
    Union() = default;

    template <class T, std::enable_if_t<!std::is_same_v<T, U>, std::nullptr_t> = nullptr>
    Union(T&& t_) : v(std::forward<T>(t_)) {}

    template <class T, std::enable_if_t<std::is_same_v<T, U>, std::nullptr_t> = nullptr>
    Union(T&& t_) : u(std::forward<T>(t_)), u_is_set(true) {}

    template <class T, std::enable_if_t<!std::is_same_v<std::decay_t<T>, U>, std::nullptr_t> = nullptr>
    Union& operator=(T&& t_) {
        v = std::forward<T>(t_);
        u_is_set = false;
        v_is_set = true;
        return *this;
    }

    template <class T, std::enable_if_t<std::is_same_v<std::decay_t<T>, U>, std::nullptr_t> = nullptr>
    Union& operator=(T&& t_) {
        u = std::forward<T>(t_);
        u_is_set = true;
        v_is_set = false;
        return *this;
    }

    template <class T, std::enable_if_t<!std::is_same<std::decay_t<T>, U>::value, std::nullptr_t> = nullptr>
    operator T() const noexcept {
        if (!v_is_set) {
            std::cerr
                << "Union Type Error: Required type "
                << typeid(T).name()
                << " is not set." << std::endl;
            std::exit(EXIT_FAILURE);
        }
        return static_cast<T>(v);
    }

    template <class T, std::enable_if_t<std::is_same<std::decay_t<T>, U>::value, std::nullptr_t> = nullptr>
    operator T() const noexcept {
        if (!u_is_set) {
            std::cerr
                << "Union Type Error: Required type "
                << typeid(T).name()
                << " is not set." << std::endl;
            std::exit(EXIT_FAILURE);
        }
        return u;
    }

    virtual ~Union() = default;
};

template <class U, class V>
struct Union<U, V> {
protected:
    U u;
    V v;
    bool u_is_set = false;
    bool v_is_set = false;
public:
    Union() = default;
    Union(const U& u_) : u(u_), u_is_set(true) {}
    Union(const V& v_) : v(v_), v_is_set(true) {} 
    // コピーコンストラクタはデフォルト
    Union(U&& u_) : u(std::move(u_)), u_is_set(true) {}
    Union(V&& v_) : v(std::move(v_)), v_is_set(true) {}
    // ムーブコンストラクタはデフォルト
    Union& operator=(const U& u_) {
        u = u_;
        u_is_set = true;
        v_is_set = false;
        return *this;
    }
    Union& operator=(const V& v_) {
        v = v_;
        u_is_set = false;
        v_is_set = true;
        return *this;
    }
    // コピー代入演算子はデフォルト
    Union& operator=(U&& u_) {
        u = std::move(u_);
        u_is_set = true;
        v_is_set = false;
        return *this;
    }
    Union& operator=(V&& v_) {
        v = std::move(v_);
        u_is_set = false;
        v_is_set = true;
        return *this;
    }
    // ムーブ代入演算子はデフォルト
    operator U() const noexcept {
        if (!u_is_set) {
            std::cerr
                << "Union Type Error: Required type "
                << typeid(U).name()
                << " is not set." << std::endl;
            std::exit(EXIT_FAILURE);
        }
        return u;
    }
    operator V() const noexcept {
        if (!v_is_set) {
            std::cerr
                << "Union Type Error: Required type "
                << typeid(V).name()
                << " is not set." << std::endl;
            std::exit(EXIT_FAILURE);
        }
        return v;
    }
    virtual ~Union() = default;
};
