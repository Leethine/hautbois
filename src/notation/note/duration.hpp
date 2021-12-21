#pragma once

#include "../base/base.hpp"
namespace hautbois 
{

class Duration
{
    const Beat num;
    const Beat denom;

public:
    Duration(): 
    num { 0 },
    denom { 1 }
    {}

    Duration(Beat num, Beat denom): 
    num { num },
    denom { denom }
    {}

    Beat getNum() const {
        return num;
    }

    Beat getDenom() const {
        return denom;
    }
    
    std::string printDuration() const {
        return std::to_string(num) + "/" + std::to_string(denom);
    }

    friend bool operator<(const Duration& d1, const Duration& d2) {
        return d1.num * d2.denom < d2.num * d1.denom;
    }

    friend bool operator>(const Duration& d1, const Duration& d2) {
        return d1.num * d2.denom > d2.num * d1.denom;
    }

    friend bool operator==(const Duration& d1, const Duration& d2) {
        return d1.num * d2.denom == d2.num * d1.denom;
    }

    friend bool operator!=(const Duration& d1, const Duration& d2) {
        return d1.num * d2.denom != d2.num * d1.denom;
    }

    friend std::ostream& operator<<(std::ostream& o, const Duration& d) {
        o << d.num << "/" << d.denom;
        return o;
    }

    friend Duration operator+(const Duration& d1, const Duration& d2) {
        Duration d {d1.num*d2.denom + d2.num*d1.denom, d1.denom*d2.denom};
        return d;
    }

    friend Duration operator-(const Duration& d1, const Duration& d2) {
        Duration d { d1.num*d2.denom > d2.num*d1.denom ? 
                     d1.num*d2.denom - d2.num*d1.denom : 
                     d2.num*d1.denom - d1.num*d2.denom, 
                     d1.denom*d2.denom };
        return d;
    }
};

using GroupDuration=std::vector<Duration>;

}
