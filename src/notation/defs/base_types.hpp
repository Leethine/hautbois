#pragma once

#include<string>
#include<vector>
#include<iostream>

namespace hautbois 
{

using Beat=unsigned int;

struct Duration
{
    Beat num;
    Beat denom;

    friend bool operator<(const Duration& d1, const Duration& d2) {
        return d1.num * d2.denom < d2.denom * d1.num;
    }

    friend bool operator>(const Duration& d1, const Duration& d2) {
        return d1.num * d2.denom > d2.denom * d1.num;
    }

    friend std::ostream& operator<<(std::ostream& o, const Duration& d) {
        o << d.num << "/" << d.denom;
        return o;
    }
};

using NoteIndex=unsigned int;
using NoteName=std::string;
using GroupIndex=std::vector<NoteIndex>;
using GroupName=std::vector<NoteName>;
using GroupDuration=std::vector<Duration>;


}