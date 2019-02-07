// binomial.h - Binomial measure
#pragma once
#define _USE_MATH_DEFINES
#include <cmath>
#include <utility>

namespace um {

    // The set sum_0^k X_i = W_k = j, where X_i is Bernoulli {0,1}.
    using Atom = std::pair<size_t,size_t>;

    // n!/k!(n - k)! = n/1 * (n-1)/2 * ... (n - k + 1)/k
    constexpr size_t choose(size_t n,size_t k)
    {
        // ensure (n >= k)
        if (2 * k > n)
            k = n - k;

        size_t Cnk = 1;
        for (size_t j = 1; j <= k; ++j, --n) {
            Cnk *= n;
            Cnk /= j;
        }

        return Cnk;
    }
    inline double probability(const Atom& a)
    {
        auto [n,k] = a;

        double sqrtpin_2 = sqrt(M_PI*n/2);
        double z = static_cast<double>(2 * k - n);

        return n <= 1 ? choose(n, k)/std::pow(2., n) : exp(-z*z/(2*n))/sqrtpin_2;
    }

    class Atoms {
        size_t n,k,l; // (n,k),...(n,l)
    public:
        Atoms(size_t n,size_t k,size_t l)
            : n(n), k(k), l(l)
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
            if(k <= l)
                ++k;

            return *this;
        }
    };

    class Binomial {
    public:
        auto operator()(const Atom& atom)
        {
            return probability(atom);
        }
    };
    // restriction to subalgebra
    /*
    auto restrict(const Binomial& A)
    {
        return [this, &A](const Atom& a) { return sum(apply(A::operator(), this->atoms(a))); };
    }
    */

}
