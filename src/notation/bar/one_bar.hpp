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

    virtual void checkLength() const {
    }

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

    virtual void addNote(const NoteName& name) {
    
    }

    virtual void addNote(const NoteName& name, const std::string& duration) {
    
    }

    virtual void addNote(const NoteName& name, const std::string& duration,
                 const std::string& option, const std::string& content) {
    
    }
    
    virtual void addNote(const NoteName& name, const std::string& duration,
                 const std::string& option1, const std::string& content1,
                 const std::string& option2, const std::string& content2) {
    
    }

    virtual void addNote(const NoteName& name, const std::string& duration,
                 const std::string& option1, const std::string& content1,
                 const std::string& option2, const std::string& content2,
                 const std::string& option3, const std::string& content3) {
    
    }
    
    virtual std::string printNthNote(size_t n) const {
    
    }
    
    virtual OneNote& getNthNote(size_t n) const {
    
    }

    virtual void deleteNthNote(size_t n) {
    
    }

    virtual OneNote& getLastNote() const {
    
    }

    virtual const std::string printBarLine() const {
    
    }
};

}