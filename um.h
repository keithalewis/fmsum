// um.h - Unified Model
#pragma once
#define _USE_MATH_DEFINES
#include <math.h>
#include <algorithm>
#include <functional>
#include <numeric>

namespace um {

    static const char um_doc[] = R"xyzzyx(
The unified models values any derivative security using the formula V_t D_t = E_t (A_u + V_u) D_u.
Both sides are measures on the atoms of the algebra representing information available at time t.
)xyzzyx";

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
            if(n != 0) {
                --n;
                ++a;
            }

            return *this;
        }
    };

    template<class S>
    inline auto sum(S s,double s0 = 0) // std::iterator_traits<S>::value_type
    {
        while(s) {
            s0 += *s;
            ++s;
        }

        return s0;
    }

    template<class F,class S>
    class apply {
        const F& f;
        S s;
    public:
        apply(const F& f,S s)
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
        iota(X b = X(0),X e = std::numeric_limits<X>::max(),X di = X(1))
            : b(b),e(e),di(di)
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

    // The set sum_0^k X_i = W_k = j, where X_i is Bernoulli {0,1}.
    using Atom = std::pair<size_t,size_t>;

    // n!/k!(n - k)! = n/1 * (n-1)/2 * ... (n - k + 1)/k
    constexpr size_t choose(size_t n,size_t k)
    {
        // ensure (n >= k)
        if(2 * k > n)
            k = n - k;

        size_t Cnk = 1;
        for(size_t j = 1; j <= k; ++j) {
            Cnk *= n--;
            Cnk /= j;
        }

        return Cnk;
    }
    inline double probability(const Atom& a)
    {
        auto [n,k] = a;

        static double sqrt2pin = sqrt(2 * M_PI *n);
        double z = static_cast<double>(n - 2 * k);

        return exp(-z*z/(2*n))*2/sqrt2pin;

        // return choose(n, k)/std::pow(2., n);
    }

    class Atoms {
        size_t n,k,l; // (n,k),...(n,l)
    public:
        Atoms(size_t n,size_t k,size_t l)
            : n(n),k(k),l(l)
        {
            // ensure (k <= l && l <= n);
        }
        operator bool() const
        {
            return k <= l;
        }
        Atom operator*() const
        {
            return Atom(n,k);
        }
        Atoms& operator++()
        {
            if(k < l)
                ++k;

            return *this;
        }
    };

    class Binomial {
        size_t n; // level n
    public:
        using atom = std::pair<size_t,size_t>; // (k,j) 0 <= j <= k
        Binomial(size_t n)
            : n(n)
        { }
        // Atoms in Binomial(n) containing a
        auto atoms(const atom& a)
        {
            auto[k,j] = a;
            // ensure (j <= k && k <= n)

            return Atoms(n,j,j + n - k);
        }
    };

    template<class Measure,class Algebra,class X = double>
    inline auto evaluate(const Measure& P,const Algebra& A)
    {
        return [](auto a) { return sum(apply(P,A.atoms(a))); };
    }

    // V_t D_t = (A_u + V_u)D_u|A_t
    template<class Amount,class Deflator>
    inline auto value(const Amount& A,const Deflator& D)
    {
        return [](const Atom& a) {
            auto[k,j] = a;
            return ;
        };
    }


} // namespace um
