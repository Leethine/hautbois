#pragma once
#include <cassert>
#include <iostream>
#include <algorithm>
#include "../defs.hpp"
#include <memory>
#include "property.hpp"
#include "ornaments.hpp"

namespace hautbois 
{

const NoteIndex REST_NOTE_INDEX {101};
const NoteIndex GROUP_NOTE_INDEX {103};

enum class NoteType {
    RestNote,
    SingleNote,
    GroupNote
};

class AnyNote {
protected:
    const NoteType type;
    const Duration duration;
    const NoteName name;
    const NoteIndex index;
    const GroupName groupname;
    const GroupIndex groupindex;
    const GroupDuration groupduration;
    
    AnyNote& operator=(const AnyNote&)=delete;
    AnyNote(const AnyNote&);
    NoteIndex singleName2IndexQuery(const NameIndexTable& name_index_table,
                         const NoteName& name) const {
        NoteIndex index;
        try {
            index = name_index_table.at(name);
            return index;
        }
        catch (std::out_of_range& e) {
            std::cout << "Error encountered while processing "
             << "\"" << name << "\"" << ": "
             << "Invalid Note Value!" << "\n";
             exit(EXIT_FAILURE);
        }
    }

    GroupIndex groupName2IndexQuery(const NameIndexTable& name_index_table, 
                               const GroupName& names) const {
        GroupIndex indices;
        try {
            for (auto it {begin(names)}; it != end(names); ++it)
                indices.push_back(name_index_table.at(*it));
            return indices;
        }
        catch (std::out_of_range& e) {
            std::cout << "Error encountered while processing "
             << "chord: "
             << "Invalid Note Value!" << "\n";
            exit(EXIT_FAILURE);
        }
    }
    bool isSimpleChord(const GroupDuration durations) const {
        Duration d { durations.front() };

        for (auto it {begin(durations)}; it != end(durations); ++it)
            if ( d.num != it->num || d.denom != it->denom )
                return false;
        
        return true;
    }

    void displaySingleNote(std::ostream& o) const noexcept {
        o << "(\"" << name << "\", " << duration.num
          << "/" << duration.denom << ")";
    }
    void displayRestNote(std::ostream& o) const noexcept {
        o << "(\"" << "p" << "\", " << duration.num
          << "/" << duration.denom << ")";
    }
    void displayGroupNote(std::ostream& o) const noexcept {
        std::string s { "" };
        std::string d { "" };

        for (auto it {begin(groupname)}; it != end(groupname); it++) {
            s += "\"" + *it + "\"";
            s += "+";
        }
        s.pop_back(); // remove the last '+' symbol
        for (auto it {begin(groupduration)}; it != end(groupduration); it++) {
            d += std::to_string(it->num) + "/" + std::to_string(it->denom);
            d += "+";
        }
        d.pop_back();

        if ( isSimpleChord(groupduration) ) {
            o << "(" << 
            s
            << ", " << groupduration.front().num
            << "/" << groupduration.front().denom << ")";
        }
        else {
            o << "(" << 
            s
            << ", " << d << ")";
        }
    }

    bool verifySingleNote(const NameIndexTable& name_index_table) const {
        if ( index != name_index_table.at(name) )
            return false;
        return true;
    }
    
    bool verifyGroupNote(const NameIndexTable& name_index_table) const {
        if ( groupname.empty()  || 
             groupindex.empty() || 
             groupduration.empty() )
            return false;

        if ( groupname.size()  != groupduration.size() ||
             groupname.size()  != groupindex.size()    ||
             groupindex.size() != groupduration.size() )
             return false;
        
        for ( int i { 0 }; i < groupname.size(); ++i )
            if ( groupindex[i] != name_index_table.at(groupname[i]) )
                return false;
        
        return true;
    }
    
    bool verifyRestNote() const {
        if ( index != REST_NOTE_INDEX )
            return false;
        return true;
    }
    
    bool verifyNote(const NameIndexTable& name_index_table) const  {
        switch (type)
        {
        case NoteType::RestNote :
            return verifyRestNote();
            break;
        case NoteType::GroupNote :
            return verifyGroupNote(name_index_table);
            break;
        case NoteType::SingleNote :
            return verifySingleNote(name_index_table);
            break;
        default:
            return false;
            break;
        }
        return false;
    }
    
public:

    std::unique_ptr<NoteProperty> property;
    std::unique_ptr<NoteOrnament> ornament;

    AnyNote()=delete;
    ~AnyNote()=default;

    // Rest note initialiser
    explicit AnyNote( const Beat num, const Beat denom ) :
    type { NoteType::RestNote },
    name { "rest" },
    index { REST_NOTE_INDEX },
    duration { num, denom }
    {
        assert( verifyRestNote() );
    }

    // Single Note initialiser
    explicit AnyNote( const NoteType type,
               const NameIndexTable& name_index_table,
               const NoteName& name,
               const Beat num, const Beat denom ) :
    type { type },
    name { name },
    index { singleName2IndexQuery(name_index_table, name) },
    duration { num, denom }
    {
        assert( verifyNote(name_index_table) );
    }

    // Chord initialiser
    explicit AnyNote( const NoteType type,
               const NameIndexTable& name_index_table,
               const GroupName& names,
               const GroupDuration& durations ) :
    type { type },
    name { "chord" },
    index { GROUP_NOTE_INDEX },
    duration { * std::max_element(begin(durations),end(durations)) },
    groupname { names },
    groupindex { groupName2IndexQuery(name_index_table, names) },
    groupduration { durations }
    {
        assert( verifyNote(name_index_table) );
    }

    NoteName getName() const {
        return name;
    }
    NoteIndex getIndex() const {
        return index;
    }
    Beat getDurationNum() const {
        return duration.num;
    }
    Beat getDurationDenom() const {
        return duration.denom;
    }
    Duration getDuration() const {
        return duration;
    }

    AnyNote duplicate() const {
        AnyNote n { AnyNote(*this) };
        return n;
    }

    friend std::ostream& operator<<(std::ostream& o, const AnyNote& n) {
        switch (n.type)
        {
        case NoteType::RestNote :
            n.displayRestNote(o);
            break;
        case NoteType::SingleNote :
            n.displaySingleNote(o);
            break;
        case NoteType::GroupNote :
            n.displayGroupNote(o);
            break;
        default:
            break;
        }
        return o;
    }

    bool operator==(const AnyNote& n) {
        if ( this->type != n.type )
            return false;
        else if ( this->type == NoteType::GroupNote && 
                  this->groupname.size() == n.groupname.size() ) {
            for ( int i {0}; i < this->groupname.size() ; i++) {
                if ( this->groupindex[i] != n.groupindex[i] ||
                     this->groupduration[i].num != n.groupduration[i].num ||
                     this->groupduration[i].denom != n.groupduration[i].denom )
                     return false;
            }
        }
        else {
            if ( this->index != n.index || 
                 this->duration.num != n.duration.num ||
                 this->duration.denom != n.duration.denom ) 
                 return false;
        }
        return true;
    }
};

}
