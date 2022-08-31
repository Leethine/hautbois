#pragma once
#include "../bar/one_bar.hpp"
namespace hautbois 
{

using ListBar=std::list<std::unique_ptr<OneBar>>;
using TempVoice=std::pair<size_t,ListBar>;
using ListTempVoice=std::vector<TempVoice>;

const size_t _MAX_TEMP_VOICES = 3;

class OneVoice {
protected:
    const Meter meter;
    ListBar bars;
    ListTempVoice temp_voices;

    virtual void assertBarNoteExplode(const ListBar& listbars,
                                      const NoteName& name,
                                      const std::string& duration) const {
        if (listbars.back()->checkBarExplode()) {
            std::cerr << "Error: Bar exploded upon adding "
                << "(" << name << "," << duration << "). "
                << "Aborted." << "\n";
            assert(!listbars.back()->checkBarExplode());
        }
    }

public:
    OneVoice():
    meter { {4,4} }
    {}

    OneVoice (Duration duration):
    meter { duration }
    {}

    OneVoice(const std::string& meter_str):
    meter { note_creator_utils::str2Duration(meter_str) }
    {}

    virtual void addNote(const NoteName& name, const std::string& duration) {
        //TODO REFACTO possible
        if ( bars.empty() ) {
            bars.emplace_back( new OneBar(meter) );
            bars.back()->addNote(name, duration);
            assertBarNoteExplode(bars, name, duration);
        }
        else if (bars.back()->checkBarHasSpace()) {
            bars.back()->addNote(name, duration);
            assertBarNoteExplode(bars, name, duration);
        }
        else {
            assert(bars.back()->checkBarFull());
            bars.emplace_back( new OneBar(meter) );
            bars.back()->addNote(name, duration);
            assertBarNoteExplode(bars, name, duration);
        }
    }

    virtual void newTempVoice(size_t begins_at) {
        if ( !temp_voices.empty() &&
             !temp_voices.back().second.back()->checkBarFull() ) {
            std::cerr << "Error: Cannot create new temporary voice!\n"
                      << "The last bar has not yet been finished.\n";
            assert( temp_voices.back().second.back()->checkBarFull() );
        }
        else {
            temp_voices.emplace_back( std::make_pair(begins_at, ListBar()) );
        }
    }

    virtual void addNoteTempVoice(const NoteName& name,
                                  const std::string& duration) {
        //TODO REFACTO necessary
        if ( temp_voices.empty() ) {
            std::cerr << "Error: Cannot add note to temporary voice!\n"
                      << "Temporary voice is empty.\n";
            assert( !temp_voices.empty() );
        }
        else if ( temp_voices.back().second.empty() ) {
            temp_voices.back().second.emplace_back( new OneBar(meter) );
            temp_voices.back().second.back()->addNote(name, duration);
            assert(!temp_voices.back().second.back()->checkBarExplode());
        }
        else if ( temp_voices.back().second.back()->checkBarFull() ) {
            temp_voices.back().second.emplace_back( new OneBar(meter) );
            temp_voices.back().second.back()->addNote(name, duration);
            assert(!temp_voices.back().second.back()->checkBarExplode());
        }
        else if ( temp_voices.back().second.back()->checkBarHasSpace() ) {
            temp_voices.back().second.back()->addNote(name, duration);
            assert(!temp_voices.back().second.back()->checkBarExplode());
        }
        else {
            std::cerr << "Error: " <<
                         "Adding note to temporary voice failed."
                      << "\n";
            assert(0);
        }
    }

    virtual OneBar& getBar(size_t n) const {
        auto it = bars.begin();
        std::advance(it, n);
        return *(*it);
    }

    virtual OneBar& getLastBar() const {
        auto it = bars.end();
        return *(*it);
    }

    virtual OneNote& getNoteInBar(size_t n_bar, size_t n_note) const {
        OneBar& nthbar = getBar(n_bar);
        return nthbar.getNthNote(n_note);
    }

    virtual OneBar& getBarTempVoice(size_t n_temp_voice, size_t n_bar) const {
        assert(n_temp_voice < temp_voices.size());
        assert(n_bar < temp_voices[n_temp_voice].second.size());
        auto it = temp_voices[n_temp_voice].second.begin();
        std::advance(it, n_bar);
        return *(*it);
    }

    virtual std::string printVoice() const {
        return "";
    }
};


}
