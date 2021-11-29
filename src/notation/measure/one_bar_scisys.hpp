#pragma once
#include "../defs/defs.hpp"
#include "../note/any_note.hpp"
#include <exception>
#include <iostream>
#include <cassert>
#include <list>
#include <memory>
#include <string>
#include <exception>

namespace hautbois {

using Meter=Duration;
using ListNote=std::list<std::unique_ptr<AnyNote>>;
using ScaleName=std::string;

class OneBar {
protected:
    const Meter meter;
    const TonalityType scale;
    const TonalityType relativescale;
    
    mutable ListNote notes;
    
    TonalityType tonalityStr2TypeQuery(ScaleName name) const {
        try { return TONALITY_STR_TYPE_TABLE.at(name); }
        catch (std::out_of_range& e) {
            std::cout << "Could not detect tonality: " 
                      << name << " is invalid." << "\n";
            exit(EXIT_FAILURE);
        }
    }

    TonalityType relativeScaleQuery(TonalityType scale) const {
        return CIRCLE_OF_FIFTH.at(scale);
    }

    void checkLength() const {
        Duration d {0,1};
        for (auto it=begin(notes); it != end(notes); it++) {
            d = d + (*it)->getDuration();
        }
        bool valid_length {false};
        if (d < meter || d == meter) {
            valid_length = true;
        }
        else {
            valid_length = false;
            AnyNote& last_note = * ( notes.back() );
            std::cout << "Cannot add " << last_note 
                      << " <== The bar explodes after adding this note." 
                      << "\n";
        }
        assert(valid_length);
        if (valid_length == false) {
            throw std::domain_error("bar length explode!");
        }
    }

    void clearBar() {
        notes.clear();
    }

public:
    bool tied;
    
    OneBar() :
    meter { Duration{4,4} },
    scale { tonalityStr2TypeQuery("C") },
    relativescale { relativeScaleQuery(scale) },
    tied { false }
    {}

    explicit OneBar(const ScaleName& scalename, 
                    Beat num, Beat denom) :
    meter { Duration{num, denom} },
    scale { tonalityStr2TypeQuery(scalename) },
    relativescale { relativeScaleQuery(this->scale) },
    tied { false }
    {}

    AnyNote& getNthNote(size_t n) const {
        try {
            if ( n >= notes.size() )  {
               throw std::out_of_range("Out of range! Getting the last note.");
            }
            else {
                auto it = notes.begin(); 
                std::advance(it, n);
                std::unique_ptr<AnyNote>& recovered_note = *it;
                return *recovered_note;
            }
        }
        catch (std::exception e) {
            std::cout << n << ": " << e.what() << "\n";
            std::unique_ptr<AnyNote>& recovered_note = * notes.end();
            return *recovered_note;
        }
    }

    const std::string printNthNote(size_t n) const {
        AnyNote& recovered_note = getNthNote(n);
        return recovered_note.printNote();
    }

    void appendRestNote(const Duration& d) {
        notes.emplace_back(new AnyNote(d.num, d.denom));
        checkLength();
    }
    
    void appendSingleNote(const ScaleName& name, const Duration& d) {
        notes.emplace_back(new AnyNote(NoteType::SingleNote,
                                       SCI_NAME_INDEX, name, d.num, d.denom));
        checkLength();
    };

    void appendGroupNote(const GroupName& names, const GroupDuration& gd) {
        notes.emplace_back(new AnyNote(NoteType::GroupNote,
                                       SCI_NAME_INDEX, names, gd));
        checkLength();
    };

    void appendGroupNote(const GroupName& names, const Duration& d) {
        GroupDuration gd;
        for (int i=0; i < names.size(); ++i)
            gd.emplace_back(d);
        notes.emplace_back(new AnyNote(NoteType::GroupNote, 
                                       SCI_NAME_INDEX, names, gd ));
        checkLength();
    };
    
    void deleteNthNote(size_t n) {
        try {
            if ( n >= notes.size() )  {
               throw std::out_of_range("Out of range! Nothing to delete.");
            }
            else {
                auto it = notes.begin(); 
                std::advance(it, n);
                notes.erase(it);
            }
        }
        catch (std::exception e) {
            std::cout << n << ": " << e.what() << "\n";
        }
    }

    AnyNote& getLastNote() const {
        if ( !notes.empty() )
            return getNthNote(notes.size() - 1);
        else
            throw std::range_error("Error: Bar is empty");
    }

    const std::string printBarLine() const {
        std::string result;
        for(int i = 0; i < notes.size(); i++) {
            result += getNthNote(i).printNote() + " ";
        }
        return result;
    }
};

}