#include <type_traits>
#include <utility>
#include <iostream>
#include <cstdlib>

namespace union_type {
    template <class...>
    struct Union;

    template <class U>
    struct Union<U> {
    private:
        U u;
        bool u_is_set = false;
    public:
        Union() = default;
        Union(const U& u_) : u(u_), u_is_set(true) {}
        // コピーコンストラクタはデフォルト
        Union(U&& u_) : u(std::move(u_)), u_is_set(true) {}
        // ムーブコンストラクタはデフォルト

        Union& operator=(const U& u_) {
            u = u_;
            u_is_set = true;
            return *this;
        }
        // コピー代入演算子はデフォルト
        Union& operator=(U&& u_) {
            u = std::move(u_);
            u_is_set = true;
            return *this;
        }
        // ムーブ代入演算子はデフォルト

        operator U() const {
            if (!u_is_set) {
                std::cerr
                    << "Union Type Error: Required type "
                    << typeid(U).name()
                    << " is not set." << std::endl;
                std::exit(EXIT_FAILURE);
            }
            return u;
        }

        template <class T>
        friend std::ostream& operator<<(std::ostream&, Union<T>&);

        template <class T, class S>
        friend auto has_type(const Union<S>&) noexcept
            -> std::enable_if_t<!std::is_same_v<T, S>, bool>;

        template <class T, class S>
        friend auto has_type(const Union<S>&) noexcept
            -> std::enable_if_t<std::is_same_v<T, S>, bool>;

        virtual ~Union() = default;
    };

    template <class U>
    std::ostream& operator<<(std::ostream& os, Union<U>& u) {
        if (u.u_is_set) {
            os << static_cast<U>(u);
        } else {
            std::cerr
                << "Union Type Error: operator<< was called "
                << "even though nothing was set for the Union instance."
                << std::endl;
            std::exit(EXIT_FAILURE);
        }

        return os;
    }

    template <class T, class U>
    auto has_type(const Union<U>&) noexcept
        -> std::enable_if_t<!std::is_same_v<T, U>, bool> {
        return false;
    }

    template <class T, class U>
    auto has_type(const Union<U>& u) noexcept
        -> std::enable_if_t<std::is_same_v<T, U>, bool> {
        return u.u_is_set;
    }

    template <class U, class V, class ...Rest>
    struct Union<U, V, Rest...> {
    private:
        U u;
        Union<V, Rest...> v;
        bool u_is_set = false;
        bool v_is_set = false;

    public:
        Union() = default;

        template <class T>
        Union(T&& t_) : v(std::forward<T>(t_)), v_is_set(true) {}

        Union(const U& u_) : u(u_), u_is_set(true) {}

        Union(U&& u_) : u(std::move(u_)), u_is_set(true) {}

        template <class T>
        Union& operator=(T&& t_) {
            v = std::forward<T>(t_);
            u_is_set = false;
            v_is_set = true;
            return *this;
        }

        Union& operator=(const U& u_) {
            u = u_;
            u_is_set = true;
            v_is_set = false;
            return *this;
        }

        Union& operator=(U&& u_) {
            u = std::move(u_);
            u_is_set = true;
            v_is_set = false;
            return *this;
        }

        template <class T>
        operator T() const {
            if (!v_is_set) {
                std::cerr
                    << "Union Type Error: Required type "
                    << typeid(T).name()
                    << " is not set." << std::endl;
                std::exit(EXIT_FAILURE);
            }
            // ここで static_cast<T>(v) としてもよいが，operator T() の戻り値は
            // T なので，このまま v を返しても暗黙の型変換により T 型の値に変換される．
            return v;
        }

        operator U() const {
            if (!u_is_set) {
                std::cerr
                    << "Union Type Error: Required type "
                    << typeid(U).name()
                    << " is not set." << std::endl;
                std::exit(EXIT_FAILURE);
            }
            return u;
        }

        template <class T, class S, class ...Rest_Types>
        friend std::ostream& operator<<(std::ostream&, Union<T, S, Rest_Types...>&);

        template <class T, class S, class W, class ...Rest_types>
        friend auto has_type(const Union<S, W, Rest_types...>&) noexcept
            -> std::enable_if_t<!std::is_same_v<T, S>, bool>;

        template <class T, class S, class W, class ...Rest_types>
        friend auto has_type(const Union<S, W, Rest_types...>&) noexcept
            -> std::enable_if_t<std::is_same_v<T, S>, bool>;

        virtual ~Union() = default;
    };

    template <class U, class V, class ...Rest>
    std::ostream& operator<<(std::ostream& os, Union<U, V, Rest...>& u) {
        if (u.u_is_set) {
            os << static_cast<U>(u);
        } else if (u.v_is_set) {
            os << u.v;
        } else {
            std::cerr
                << "Union Type Error: operator<< was called "
                << "even though nothing was set for the Union instance."
                << std::endl;
            std::exit(EXIT_FAILURE);
        }

        return os;
    }

    template <class T, class U, class V, class ...Rest>
    auto has_type(const Union<U, V, Rest...>& u) noexcept
        -> std::enable_if_t<!std::is_same_v<T, U>, bool> {
        return u.v_is_set && has_type<T>(u.v);
    }

    template <class T, class U, class V, class ...Rest>
    auto has_type(const Union<U, V, Rest...>& u) noexcept
        -> std::enable_if_t<std::is_same_v<T, U>, bool> {
        return u.u_is_set;
    }

} // namespace union_type
