/* Property and ornaments definitions mother class */
#pragma once
#include "../../defs/defs.hpp"
#include <memory>
#include <boost/optional.hpp>

namespace hautbois 
{

struct NoteProperty
{
    // wait how long to get in ?
    boost::optional<Duration> waits;
    // lasts how long ?
    boost::optional<Duration> lasts;

    NoteProperty() {
        waits = boost::none;
        lasts = boost::none;
    }
};

}
