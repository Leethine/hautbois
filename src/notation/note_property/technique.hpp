#pragma once
#include <set>
#include "../base/base.hpp"
#include <boost/algorithm/string.hpp>

namespace hautbois 
{

struct NoteTechnique {
    std::string key;
    int value;
    void addTechnique(const std::string& key, const std::string& val) {
        std::string lkey { key };
        std::string lval { val };
        boost::to_lower(lkey);
        boost::to_lower(lval);
        
        const std::set<std::string> valid_keys {
            "legato","vibrato","spicatto"
            //TODO more techniques
        };
        auto search = valid_keys.find(lkey);
        if ( search != valid_keys.end() ) {
            this->key = lkey;
            if ( lval.empty() ) 
            this->value = 0;
            else {
                try {
                    this->value = std::stoi(lval);
                }
                catch(std::exception &e) {
                    std::cout << "Warning: " << "Value must be integer."
                            << "\n" << e.what() << "\n";
                    this->value = 0;
                }
            }
        }
        else {
            throw std::domain_error("Not supported technique: " + lkey);
        }
    };
};

}

