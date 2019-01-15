// um.t.cpp - Unified Model test
#include <cassert>
#include "um.h"

void test_array()
{
	int a[] = { 1,2,3 };
	auto s = um::array(a, 3);
	auto s2{ s };
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

void test_sum()
{
	int a[] = { 1,2,3 };
	auto s = um::array(a, 3);

	assert(um::sum(s) == a[0] + a[1] + a[2]);
}

void test_apply()
{
	int a[] = { 1,2,3 };
	auto s = um::array(a, 3);

	assert(um::sum(um::apply([](int i) { return i * i; }, s)) == 1 + 4 + 9);
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

int main()
{
	test_choose();
	test_array();
	test_sum();
	test_apply();
	test_iota();

	return 0;
}