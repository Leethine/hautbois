/* Property and ornaments definitions mother class */
#pragma once
#include "../../defs/defs.hpp"
#include <memory>

namespace hautbois 
{
using ForcePropertyValue=int;
using TimePropertyValue=Duration;
using StringPropertyValue=int;
using PropertyPtr=std::unique_ptr<NoteProperty>;

struct NoteProperty
{
    InstrumentType instrument;
    TimePropertyValue delay;
    TimePropertyValue duration;
    NoteProperty() {};
    NoteProperty(InstrumentType instrument):
    instrument { instrument }
    {};
};

}
