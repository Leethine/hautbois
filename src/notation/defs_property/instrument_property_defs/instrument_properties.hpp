#pragma once
#include "property_defs.hpp"

namespace hautbois 
{

struct HarpsichordNoteProperty : NoteProperty {
    void addEntry(const std::string& key, const std::string& val) override {
        std::string lkey { key };
        std::string lval { val };
        boost::to_lower(lkey);
        boost::to_lower(lval);
        
        std::set<std::string> valid_keys {
            "waits","lasts","delay"
        };
        auto search = valid_keys.find(lkey);
        if ( search != valid_keys.end() )
            entries.emplace(lkey,lval);
        else {
            std::cout << "Not supported Key: " << lkey << "\n";
            throw std::domain_error("Not supported Key: " + lkey);
        }
    }
};

struct LuthNoteProperty : NoteProperty {
    void addEntry(const std::string& key, const std::string& val) override {
        std::string lkey { key };
        std::string lval { val };
        boost::to_lower(lkey);
        boost::to_lower(lval);

        std::set<std::string> valid_keys {
            "waits","lasts","delay","force","stringnbr"
        };
        auto search = valid_keys.find(lkey);
        if ( search != valid_keys.end() )
            entries.emplace(lkey,lval);
        else {
            std::cout << "Not supported Key: " << lkey << "\n";
            throw std::domain_error("Not supported Key: " + lkey);
        }
    }
};

struct SineWaveNoteProperty : NoteProperty {
    void addEntry(const std::string& key, const std::string& val) override {
        std::string lkey { key };
        std::string lval { val };
        boost::to_lower(lkey);
        boost::to_lower(lval);
        
        std::set<std::string> valid_keys {
            "waits","lasts"
        };
        auto search = valid_keys.find(lkey);
        if ( search != valid_keys.end() )
            entries.emplace(lkey,lval);
        else {
            std::cout << "Not supported Key: " << lkey << "\n";
            throw std::domain_error("Not supported Key: " + lkey);
        }
    }
};

}