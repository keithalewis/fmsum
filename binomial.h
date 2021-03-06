// binomial.h - Binomial measure
#pragma once
#define _USE_MATH_DEFINES
#include <cmath>
#include <functional>
#include <utility>

namespace um {

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
	// Standard normal cumulative distribution.
    inline double normal_cdf(double z)
    {
        return 0.5 * erfc(-z * M_SQRT1_2);
    }
	// n choose k / 2^n
    inline double probability0(size_t n, size_t k)
    {
        return ::ldexp(choose(n, k), -static_cast<int>(n));
    }
    // Wn ~= sqrt(n)/2 Z + n/2 where Z is standard normal
    inline double probability1(size_t n, size_t k)
    {
        auto z_ = (k + 0.5 - n/2.)*2/sqrt(1.*n);
        auto _z = (k - 0.5 - n/2.)*2/sqrt(1.*n);

        return k == 0 ? normal_cdf(z_) :
               k == n ? 1 - normal_cdf(_z) :
                        normal_cdf(z_) - normal_cdf(_z);
    }
    inline double probability2(size_t n, size_t k, size_t cutoff = 52)
    {
        return n <= cutoff ? probability0(n, k) : probability1(n, k);
    }

    /*
    Measure
    Measure::Atom
    Measure::Atoms(Measure::Atom) - atoms at time U containing atom at time T <= U.
    */
    class Binomial {
    public:
        // { W_n = k }
        class Atom {
            size_t n, k;
        public:
            Atom(size_t n, size_t k)
                : n(n), k(k)
            {
                // ensure (k <= n)
            }
            size_t time() const
            {
                return n;
            }
            operator size_t() const
            {
                return k;
            }
            double probability() const
            {
                return probability2(n, k);
            }
        };
		double operator()(const Atom& a)
        {
            return a.probability();
        }
		using measure = std::function<double(const Atom&)>;
		// Sub-atoms at time m
        class Atoms {
            size_t m, k, l;
        public:
            Atoms(size_t m, const Atom& atom)
                : m(m), k(atom), l(atom + (m - atom.time()))
            {
                // ensure (a.time() <= m);
            }
            operator bool() const
            {
                return k <= l;
            }
            Atom operator*() const
            {
                return Atom{m, k};
            }
            Atoms& operator++()
            {
                if (k <= l)
                    ++k;

                return *this;
            }
        };

    };

}
