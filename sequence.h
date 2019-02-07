// sequence.h - forward iterators with operator bool() const
#pragma once

namespace um {

    // counted array
    template<class X>
    class array {
        const X* a;
        size_t n;
    public:
        array(const X* a = nullptr,size_t n = 0)
            : a(a),n(n)
        { }
        operator bool() const
        {
            return n != 0;
        }
        X operator*() const
        {
            return *a;
        }
        array& operator++()
        {
            if (n != 0) {
                --n;
                ++a;
            }

            return *this;
        }
    };

    template<class X>
    class constant {
        X x;
    public:
        constant(X x = 0)
            : x(x)
        { }
        operator bool() const
        {
            return true;
        }
        X operator*() const
        {
            return x;
        }
        constant& operator++()
        {
            return *this;
        }
    };

    // sequence routines
    template<class S,class T>
    inline bool equal(S s,T t)
    {
        while(s && t) {
            if(!(*s == *t))
                return false;
            ++s;
            ++t;
        }

        return !s && !t;
    }

    template<class S>
    inline auto sum(S s, double s0 = 0) // std::iterator_traits<S>::value_type
    {
        while(s) {
            s0 += *s;
            ++s;
        }

        return s0;
    }

    // apply function to each element
    template<class F,class S>
    class apply {
        F f;
        S s;
    public:
        apply(F f,S s)
            : f(f),s(s)
        { }
        operator bool() const
        {
            return s;
        }
        auto operator*() const
        {
            return f(*s);
        }
        apply& operator++()
        {
            ++s;

            return *this;
        }
    };

    // [b, b + di, ..., e)
    template<class X>
    class iota {
        X b,e,di;
    public:
        iota(X b = X(0), X e = std::numeric_limits<X>::max(), X di = X(1))
            : b(b), e(e), di(di)
        { }
        operator bool() const
        {
            return b < e;
        }
        X operator*() const
        {
            return b;
        }
        iota& operator++()
        {
            b += di;

            return *this;
        }
    };

}
