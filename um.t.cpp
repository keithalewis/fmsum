// um.t.cpp - Unified Model test
#include <cassert>
#include "binomial.h"
#include "functional.h"
#include "sequence.h"
#include "um.h"

void test_apply()
{
    int a[] = {1, 2, 3};
    auto s = um::array(a, 3);

    assert(um::sum(um::apply([](int i) { return i * i; }, s)) == 1 + 4 + 9);
}

void test_array()
{
    int a[] = {1, 2, 3};
    auto s = um::array(a, 3);
    auto s2{s};
    s = s2;
    assert(s);
    assert(*s == a[0]);
    ++s;
    assert(s);
    assert(*s == a[1]);
    assert(++s);
    assert(*s == a[2]);
    assert(!++s);
    assert(!++s);
}

void test_binomial()
{
}

void test_binop()
{
    std::function<int(int)> f = [](int i) { return i; };
    auto ff = operator_binop(std::plus<int>{},f,f);
    assert (ff(2) == 4);
    auto f_plus = f + f;
    assert (f_plus(3) == 6);
    auto f_minus = f - f;
    assert (f_minus(1) == 0);
    auto f_multiplies = f*f;
    assert (f_multiplies(3) == 9);
    auto f_divides = f/f;
    assert (f_divides(5) == 1);
}

void test_choose()
{
    assert(1 == um::choose(7, 0));
    assert(7 == um::choose(7, 1));
    assert(21 == um::choose(7, 2));
    assert(35 == um::choose(7, 3));
    assert(35 == um::choose(7, 4));
    assert(21 == um::choose(7, 5));
    assert(7 == um::choose(7, 6));
    assert(1 == um::choose(7, 7));
}

void test_sum()
{
	int a[] = { 1,2,3 };
	auto s = um::array(a, 3);

	assert(um::sum(s) == a[0] + a[1] + a[2]);
}

void test_probability()
{
    for (size_t n = 0; n < 32; ++n) {
        double s = um::sum(um::apply(um::probability, um::Atoms(n, 0, n)));
        s = s;
    }
}

void test_iota()
{
	um::iota<int> i;
	assert(i);
	assert(*i == 0);
	assert(*++i == 1);

	auto i2 = um::iota(2, 10, 3);
	int a2[] = { 2, 5, 8 };
	assert(um::equal(i2, um::array(a2, 3)));

	auto i3 = um::iota(2, 4 );
	int a3[] = { 2, 3};
	assert(um::equal(i3, um::array(a3, 2)));
}

int main()
{
    test_apply();
    test_array();
    test_binomial();
    test_binop();
    test_choose();
    test_iota();
    test_probability();
    test_sum();
	
	return 0;
}