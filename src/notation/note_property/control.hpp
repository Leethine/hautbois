#pragma once
#include <set>
#include "../base/base.hpp"
#include "boost/algorithm/string.hpp"

namespace hautbois 
{

using KeyValPair=std::map<std::string,std::string>;

struct NoteControl {
    KeyValPair entries;

    void addEntry(const std::string& key, const std::string& val) {
        std::string lkey { key };
        std::string lval { val };
        boost::to_lower(lkey);
        boost::to_lower(lval);

        const std::set<std::string> valid_keys {
            "waits","lasts","delay",
            "force","stringnbr" //TODO list of keywords
        };
        auto search = valid_keys.find(lkey);
        if ( search != valid_keys.end() )
            entries.emplace(lkey,lval);
        else {
            std::cout << "Not supported Key: " << lkey << "\n";
            throw std::domain_error("Not supported Key: " + lkey);
        }
    }

    std::string getValue(const std::string& key) {
        KeyValPair::iterator it = entries.find(key);
        if ( it != entries.end() ) { return it->second; }
        else { return ""; }
    }
};

}
