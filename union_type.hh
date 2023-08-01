#include <type_traits>

template <class U, class V>
class Union final {
private:
    U u;
    V v;
public:
    Union() = default;
    Union(const U& u) {
        this->u = std::move(u);
    }
    Union(const V& v) {
        this->v = std::move(v);
    }
    Union(const Union& s) {
        u = std::move(s.u);
        v = std::move(s.v);
    }
    Union& operator=(const U& u) {
        this->u = std::move(u);
        return *this;
    }
    Union& operator=(const V& v) {
        this->v = std::move(v);
        return *this;
    }
    operator U() const noexcept {
        return u;
    }
    operator V() const noexcept {
        return v;
    }
};
