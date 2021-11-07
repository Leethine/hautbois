/* Property and ornaments definitions mother class */
#pragma once
#include "../../defs/defs.hpp"
#include <memory>
#include <set>
#include <boost/optional.hpp>
#include <boost/algorithm/string.hpp>

namespace hautbois 
{

using KeyValPair=std::map<std::string,std::string>;

struct NoteProperty {
    KeyValPair entries;
    virtual void addEntry(const std::string&, const std::string&) {
    // to be deleted
    std::cout << "DBGMSG: Parent Class" << "\n";
    };
};

}
