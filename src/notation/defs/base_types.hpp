#pragma once

#include<string>
#include<vector>
#include<iostream>

namespace hautbois 
{

using UIntValue=unsigned int;
using Beat=unsigned int;

struct Duration
{
    Beat num;
    Beat denom;

    Duration(): 
    num { 0 },
    denom { 1 }
    {};

    Duration(Beat num, Beat denom): 
    num { num },
    denom { denom }
    {};

    friend bool operator<(const Duration& d1, const Duration& d2) {
        return d1.num * d2.denom < d2.num * d1.denom;
    }

    friend bool operator>(const Duration& d1, const Duration& d2) {
        return d1.num * d2.denom > d2.num * d1.denom;
    }

    friend bool operator==(const Duration& d1, const Duration& d2) {
        return d1.num * d2.denom == d2.num * d1.denom;
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
        Duration d {d1.num*d2.denom - d2.num*d1.denom, d1.denom*d2.denom};
        return d;
    }
};

using NoteIndex=unsigned int;
using NoteName=std::string;
using GroupIndex=std::vector<NoteIndex>;
using GroupName=std::vector<NoteName>;
using GroupDuration=std::vector<Duration>;


}