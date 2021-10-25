/* Property and ornaments definitions mother class */
#pragma once
#include "../defs.hpp"
#include <memory>

namespace hautbois 
{
using ForcePropertyValue=int;
using TimePropertyValue=Duration;
using StringPropertyValue=int;

struct NoteProperty
{
    InstrumentList instrument;
    TimePropertyValue delay;
    TimePropertyValue duration;
    NoteProperty()=default ;
};

}
