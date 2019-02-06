// functional.h - Extend <functional>
#pragma once
#include <functional>

template<class X, class Y, class Binop>
inline auto operator_binop(Binop binop, const std::function<Y(X)>& f, const std::function<Y(X)>& g)
{
    return [binop,&f,&g](auto x) { return binop(f(x), g(x)); };
}

template<class X, class Y>
inline auto operator+(const std::function<Y(X)>& f,const std::function<Y(X)>& g)
{
    return operator_binop(std::plus<Y>{},f,g);
}
template<class X,class Y>
inline auto operator-(const std::function<Y(X)>& f,const std::function<Y(X)>& g)
{
    return operator_binop(std::minus<Y>{},f,g);
}
template<class X,class Y>
inline auto operator*(const std::function<Y(X)>& f,const std::function<Y(X)>& g)
{
    return operator_binop(std::multiplies<Y>{},f,g);
}
template<class X,class Y>
inline auto operator/(const std::function<Y(X)>& f,const std::function<Y(X)>& g)
{
    return operator_binop(std::divides<Y>{},f,g);
}