// instrument.h - sequence of amounts
#pragma once
#include <functional>
#include <utility>

namespace um {

    // Option paying amount a at expiration t.
    template<class T, class A>
    class european {
        std::pair<T, std::function<double(const A&)>> ta;
        mutable bool b;
    public:
        european(T t , const std::function<double(const A&)>& a)
            : ta{t, a}, b(false)
        { }
        bool done() const
        {
            return b;
        }
        const std::pair<T, std::function<double(const A&)>>& next() const
        {
            // ensure(!b);
            b = true;

            return ta;
        }
    };

    template<class T, class A>
    inline auto done(const european<T,A>& i)
    {
        return i.done();
    }
    template<class T, class A>
    inline auto next(const european<T,A>& i)
    {
        return i.next();
    }

    // !!!instrument should be parameterized by the time and algebra
}
