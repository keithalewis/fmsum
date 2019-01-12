// um.h - Unified Model
#pragma once
#include <algorithm>
#include <functional>
#include <numeric>

namespace um {

static const char um_doc[] = R"xyzzyx(
The unified models values any derivative security using the formula V_t D_t = E_t (A_u + V_u) D_u.
Both sides are measures on the atoms of the algebra representing information available at time t.
)xyzzyx";

	template<class S, class T>
	inline bool equal(S s, T t)
	{
		while (s && t) {
			if (!(*s == *t))
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
		array(const X* a, size_t n)
			: a(a), n(n)
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

	template<class S>
	inline auto sum(S s, double s0 = 0) // std::iterator_traits<S>::value_type
	{
		while (s) {
			s0 += *s;
			++s;
		}

		return s0;
	}

	template<class F, class S>
	class apply {
		const F& f;
		S s;
	public:
		apply(const F& f, S s)
			: f(f), s(s)
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

	template<class X>
	class iota {
		X b, e, di;
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

	using Atom = std::pair<size_t, size_t>;

	class Atoms {
		size_t n, k, l; // (n,k),...(n,l)
	public:
		Atoms(size_t n, size_t k, size_t l)
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
			return Atom(n, k);
		}
		Atoms& operator++()
		{
			if (k < l)
				++k;

			return *this;
		}
	};

	class Binomial {
		size_t n; // level n
	public:
		using atom = std::pair<size_t, size_t>; // (k,j) 0 <= j <= k
		Binomial(size_t n)
			: n(n)
		{ }
		// Atoms in Binomial(n) containing a
		auto atoms(const atom& a)
		{
			auto[k, j] = a;
			// ensure (j <= k && k <= n)
			
			return Atoms(n, j, j + n - k);
		}
	};

	template<class Measure, class Algebra, class X = double>
	inline auto eval(const Measure& P, const Algebra& A)
	{
		return [](auto a) { return sum(apply(P, A.atoms(a))); };
	}

	template<class Amount, class Deflator>
	inline auto value(const Amount& A, const Deflator& D)
	{
		return [](auto t, auto a) {
			return 0;
		};
	}
		

} // namespace um
