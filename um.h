// um.h - Unified Model
#pragma once
#include <algorithm>
#include <functional>
#include <numeric>
#include "binomial.h"
#include "functional.h"

namespace um {

    static const char um_doc[] = R"xyzzyx(
The unified models values any derivative security using the formula 
    V_t D_t = E_t (A_u + V_u) D_u
where u is the next non-zero value of A_u.
Both sides are measures on the atoms of the algebra representing information available at time t.
)xyzzyx";

    // V_t D_t = (A_u + V_u)D_u|A_t
    template<class Instrument, class Deflator, class Atom>
    inline auto value(const Instrument& I, const Deflator& D)
    {
        return [&I, &D](const Atom& a) {
            return done(I) ? 0 : ((next(I) + value(I, D))*D)(a)/D(a);
        };
    }

} // namespace um
