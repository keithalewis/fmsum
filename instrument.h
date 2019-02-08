// instrument.h - sequence of amounts
#pragma once
#include <functional>

namespace um {

    template<class A>
    class european {
        A amount;
        size_t count;
    public:
        european(A a)
            : amount(a), count(0)
        { }
        bool done() const
        {
            return count >= 1;
        }
        A& next()
        {
            ++count;

            return amount;
        }
    };

    template<class A>
    inline auto done(const european<A>& i)
    {
        return i.done();
    }
    template<class A>
    inline auto next(european<A>& i)
    {
        return i.next();
    }
}
