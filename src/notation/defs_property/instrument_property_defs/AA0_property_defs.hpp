/* Property and ornaments definitions mother class */
#pragma once
#include "../../defs/defs.hpp"
#include <memory>

namespace hautbois 
{
using ForcePropertyValue=int;
using TimePropertyValue=Duration;
using StringPropertyValue=int;

struct NoteProperty
{
    // wait how long to get in?
    TimePropertyValue waits;
    // lasts how long ?
    TimePropertyValue lasts;

    NoteProperty()=default;
};


}
