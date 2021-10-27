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
    NoteProperty()=delete;
    InstrumentType instrument;
    TimePropertyValue delay;
    TimePropertyValue duration;
    NoteProperty(InstrumentType instrument):
    instrument { instrument }
    {};
};


}
