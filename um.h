// um.h - Unified Model
#pragma once
#include <algorithm>
#include <functional>
#include <numeric>
#include "binomial.h" // !!! remove
#include "functional.h" // !!! remove

namespace um {

    static const char um_doc[] = R"xyzzyx(
The unified models values any derivative security using the formula 
    V_t D_t = E_t (A_u + V_u) D_u
where u is the next non-zero value of A_u.
Both sides are measures on the atoms of the algebra representing information available at time t.
)xyzzyx";

    // V_t D_t = (A_u + V_u)D_u|A_t
    template<class Instrument/*, class Deflator, class Atom*/>
    inline std::function<double(const Binomial::Atom&)> value(Instrument& I/*, const Deflator& D*/)
    {
        return [&I/*, &D*/](const Binomial::Atom& a) {
            if (I.done()) {
                0.;
            }
            std::pair<size_t, std::function<double(const Binomial::Atom&)>> p = I.next();
            
            return ((p.second) + value(I/*, D*/))(a);///* *D*/)(a)/* /D(a)*/;
        };
    }

} // namespace um
