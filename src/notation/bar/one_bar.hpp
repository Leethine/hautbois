#pragma once
#include "../base/base.hpp"
#include "../note/note_facade.hpp"
#include <list>

namespace hautbois {

using Meter=Duration;
using ListNote=std::list<std::unique_ptr<OneNote>>;

class OneBar {
protected:
    const Meter meter;
    mutable ListNote notes;

    virtual void addControl(const std::string& ctl_str, const std::string& val) {
    }

    virtual void addOrnament(const std::string& omt_str, const std::string& val) {
    }
    
    virtual void addTechnique(const std::string& tech_str, const std::string& val) {
    }

public:
    OneBar():
    meter { {4,4} }
    {}

    OneBar (Duration duration):
    meter { duration }
    {}

    OneBar(const std::string& meter_str):
    meter { note_creator_utils::str2Duration(meter_str) }
    {}

    virtual bool checkBarExplode() const {
        Duration d (0,1);
        for (auto it=notes.begin(); it != notes.end(); it++) {
            d += (*it)->getPrincipalDuration();
        }
        if (d > meter)
            return true;
        else
            return false;
    }

    virtual bool checkBarFull() const {
        Duration d (0,1);
        for (auto it=notes.begin(); it != notes.end(); it++) {
            d += (*it)->getPrincipalDuration();
        }
        if (d == meter)
            return true;
        else
            return false;
    }

    virtual bool checkBarHasSpace() const {
        Duration d (0,1);
        for (auto it=notes.begin(); it != notes.end(); it++) {
            d += (*it)->getPrincipalDuration();
        }
        if (d < meter)
            return true;
        else
            return false;
    }

    virtual void addNote(const NoteName& name, const std::string& duration) {
        if ( checkBarHasSpace() ) {
            notes.emplace_back(new OneNote(name,duration));
        }
        else {
            std::cerr << "Bar already full. Aborted." << "\n";
            assert(checkBarHasSpace()); //TODO exception
        }
        if (checkBarExplode()) {
            std::cerr << "Bar exploded; Aborted." << "\n";
            assert(!checkBarExplode()); //TODO exception
        }
    }

    virtual void insertNote(size_t n, const NoteName& name, 
                            const std::string& duration) {
        assert(n < notes.size());
        auto it = notes.begin();
        std::advance(it, n);

        if ( checkBarHasSpace() ) {
            notes.emplace(it, new OneNote(name, duration));
        }
        else {
            std::cerr << "Bar already full. Aborted." << "\n";
            assert(checkBarHasSpace()); //TODO exception
        }
        if (checkBarExplode()) {
            std::cerr << "Bar exploded! Aborted." << "\n";
            assert(!checkBarExplode()); //TODO exception
        }
    }

    // TODO handle note properties
    
    virtual Meter getMeter() const {
        return meter;
    }
    
    virtual OneNote& getNthNote(size_t n) const {
        assert(n < notes.size());
        auto it = notes.begin();
        std::advance(it, n);
        return (*(*it));
    }

    virtual std::string printNthNote(size_t n) const {
        OneNote& note1 = this->getNthNote(n);
        return note1.printNote();
    }

    virtual void deleteNthNote(size_t n) {
        auto it = notes.begin();
        std::advance(it, n);
        notes.erase(it);
    }

    virtual OneNote& getFirstNote() const {
        auto it = notes.begin();
        return (*(*it));
    }
    virtual OneNote& getLastNote() const {
        auto it = notes.begin();
        std::advance(it, notes.size()-1);
        return (*(*it));
    }
    virtual const std::string printBarLine() const {
        std::string sout;
        for (auto it=notes.begin(); it != notes.end(); it++) {
            sout += (*it)->printNote() + " ";
        }
        sout.pop_back();
        //TODO decide if the space is necessary
        return sout;
    }
};

}