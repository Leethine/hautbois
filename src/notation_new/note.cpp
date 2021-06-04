/*

  This file is part of the HAUTBOIS project, which is released under
  the GNU General Public License. You should have received a copy of 
  the GNU General Public License along with Hautbois.  
  If not, see <http://www.gnu.org/licenses/>.

*/


/* note.cpp
 * This file Defines one note in the musical score.
 * The Note contains pitch info, duration, properties.
 * Convertion functions are implemented, which allows converting from
 * different notation system to notation index on a standard keyboard.
 */

#include <iostream>
#include <string>
#include <vector>
#include <boost/algorithm/string.hpp>

#include "note.hpp"

using namespace std;

/* Functions in "Note" class */

int Note::DetectNotation(string name) {
// Detection of the notation system.
// Returns 'S' for Scientific; 'L' for latin, 'D' for German. 
    if ( name.length() == 1 )
        return 'D';
    else if ( isalpha(name[1]) )
        return 'L';
    else if ( isdigit(name[1]) )
        return 'S';
    else
        return 'D';
}

bool Note::CheckDuration(string duration) {
// Check Duration validity; if valid, write to class.
    
    size_t found;
    //int num, denom;
    bool valid = false;
    // Eliminate white spaces
    while ( (found = duration.find(" ")) != string::npos ) {
        duration.erase(duration.begin() + found);
    }
    
    if ( isdigit(duration[0]) && isdigit(duration[2]) 
            && (duration[1] == '/') ) {
        valid = true;
        
        Duration[0] = duration[0] - '0';
        Duration[1] = duration[2] - '0';
    }
    else if ( duration.length() == 1 && isdigit(duration[0]) ) {
        Duration[0] = 1;
        Duration[1] = duration[0];
    }
    
    return valid;
}

int Note::SciName2Index(string name) {
// Convert Scientific Name to Index on a standard keyboard. 
    int note_index, dis, postfix, n_name, n_octave;
    
    // name standardisation
    string std_name = boost::to_lower_copy<string>(name);
    
    // get octave index and note name
    n_octave = std_name[1] - '1';
    n_name = std_name[0];
    // calculate the distance from current note to C
    switch(n_name) {
    case 'c':
        dis = 0;
        break;
    case 'd':
        dis = 2;
        break;
    case 'e':
        dis = 4;
        break;
    case 'f':
        dis = 5;
        break;
    case 'g':
        dis = 7;
        break;
    case 'a':
        dis = 9;
        break;
    case 'b':
        dis = 11;
        break;
    default:
        dis = 0;
        break;
    }
    
    // get sharp or flat sign
    switch(std_name[std_name.length()-1]) {
    case '#':
        postfix = +1;
        break;
    case 'b':
        postfix = -1;
        break;
    default:
        postfix = 0;
        break;
    }
    // Calc the index = distance + 4 + octaves + # or b
    // the reason of +4 is dis(C-A) = 3
    note_index = dis + 4 + n_octave * 12 + postfix;
    
    return note_index;
}

int Note::Latin2Index(string name) {
// Convert Latin Name to Index on a standard keyboard.
    int note_index, dis, postfix, name_hash, n_octave;
    
    // name standardisation
    string std_name = boost::to_lower_copy<string>(name);
    
    // remove "-"
    size_t found = std_name.find("-");
    if ( found != string::npos )
        std_name.erase(std_name.begin()+found);
    
    // get sharp or flat sign
    switch(std_name[std_name.length()-1]) {
    // delete the last char if it's a sharp or flat
    case '#':
        postfix = +1;
        std_name.pop_back();
        break;
    case 'b':
        postfix = -1;
        std_name.pop_back();
        break;
    default:
        postfix = 0;
        break;
    }
    
    // in which octave
    n_octave = std_name[std_name.length()-1] - '0';
    std_name.pop_back();
    
    // generate a hash for Latin names,then search by hash value
    name_hash = 0;
    for ( string::iterator it = std_name.begin(); 
            it != std_name.end(); ++it ) {
        name_hash += (*it - 'a');
    }
    // do: 17, ut: 39, re: 21, mi: 20, fa: 5, sol: 43; la: 11, si: 26
    
    switch(name_hash) {
    case 17:
        dis = 0;
        break;
    case 39:
        dis = 0;
        break;
    case 21:
        dis = 2;
        break;
    case 20:
        dis = 4;
        break;
    case 5:
        dis = 5;
        break;
    case 43:
        dis = 7;
        break;
    case 11:
        dis = 9;
        break;
    case 26:
        dis = 11;
        break;
    default:
        dis = 0;
        break;
    }
    note_index = dis + 4 + n_octave * 12 + postfix;
    
    return note_index;
}

int Note::Helm2Index(string name) {
// Convert Helmholtz pitch notation to its Index.
    int note_index, dis, postfix, n_octave;
    
    postfix = 0;
    // Get sharp or flat
    if (  name.length() > 1 &&
         (name[name.length()-1] == '#' || 
          name[name.length()-1] == 'b' ) ) {
        postfix = (name[name.length()-1] == 'b') ? -1 : +1;
        name.pop_back();
    }
    
    size_t found;
    if ( isupper(name[0]) ) {
    // if upper case letter, then it's in the 2nd Octave 
        n_octave = 1; // 2 - 1
        
        while ( (found = name.find(",")) != string::npos ) {
            n_octave -= 1;
            name.erase(name.begin() + found);
        }
    }
    else {
        n_octave = 2;
        while ( (found = name.find("'")) != string::npos ) {
            n_octave += 1;
            name.erase(name.begin() + found);
        }
    }
    
    // calculate the distance from current note to C
    switch(tolower(name[0])) {
    case 'c':
        dis = 0;
        break;
    case 'd':
        dis = 2;
        break;
    case 'e':
        dis = 4;
        break;
    case 'f':
        dis = 5;
        break;
    case 'g':
        dis = 7;
        break;
    case 'a':
        dis = 9;
        break;
    case 'b':
        dis = 11;
        break;
    default:
        dis = 0;
        break;
    }
    
    note_index = dis + 4 + n_octave * 12 + postfix;
    
    return note_index;
}

/*
string Note::Sci2Latin(string name) {
// Convert Scientific name to Latin Name.
    int note_idx = Note::SciName2Index(name);
    return "";
}

string Note::Latin2Sci(string name) {
// Convert Latin name to Scientific name.
    return "";
}

string Note::Sci2Helm(string name) {
// Convert Scientific name to Helmholtz.
    return "";
}

string Note::Helm2Sci(string name) {
// Convert Helmholtz notation to Scientific notation.
    return "";
}

string Note::Helm2Latin(string name) {
// Convert Helmholtz notation to Latin name.
    return "";
}

string Note::Latin2Helm(string name) {
// Convert Latin name to Helmholtz.
    return "";
}
*/

bool Note::isNote() { return true; }
bool Note::isBreak() { return false; }
bool Note::isNoteGroup() { return false; }

void Note::PrintNote() {
    cout << "(" << Name << ", " << Duration[0] 
         << "/" << Duration[1] << ")";
}

Note::Note(string name, string duration) {
// Init    
    int notation_sys;
    
    // Get notation system
    notation_sys = DetectNotation(name);
    Name = name;
    // then notation
    switch (notation_sys) {
    case 'S':
        NoteIndex = SciName2Index(name);
        break;
    case 'L':
        NoteIndex = Latin2Index(name);
        break;
    case 'D':
        NoteIndex = Helm2Index(name);
        break;
    default:
        NoteIndex = 0;
        break;
    }
    
    if ( !CheckDuration(duration) ) {
        Duration[0] = 1;
        Duration[1] = 4;
    }
}

Note::Note(string name) {
// Init    
    int notation_sys;
    
    // Get notation system
    notation_sys = DetectNotation(name);
    Name = name;
    // then notation
    switch (notation_sys) {
    case 'S':
        NoteIndex = SciName2Index(name);
        break;
    case 'L':
        NoteIndex = Latin2Index(name);
        break;
    case 'D':
        NoteIndex = Helm2Index(name);
        break;
    default:
        NoteIndex = 0;
        break;
    }
    
    Duration[0] = 1;
    Duration[1] = 4;
}

/* Break class */

bool Break::CheckDuration(string duration) {
// Check Duration validity; if valid, write to class.
    
    size_t found;
    //int num, denom;
    bool valid = false;
    // Eliminate white spaces
    while ( (found = duration.find(" ")) != string::npos ) {
        duration.erase(duration.begin() + found);
    }
    
    if ( isdigit(duration[0]) && isdigit(duration[2]) 
            && (duration[1] == '/') ) {
        valid = true;
        
        Duration[0] = duration[0] - '0';
        Duration[1] = duration[2] - '0';
    }
    else if ( duration.length() == 1 && isdigit(duration[0]) ) {
        Duration[0] = 1;
        Duration[1] = duration[0];
    }
    
    return valid;
}

bool Break::isNote() { return false; }
bool Break::isBreak() { return true; }
bool Break::isNoteGroup() { return false; }

void Break::PrintNote() {

    string name;
    if ( ShowSymbol )
        name = "rest";
    else
        name = "blank";
    
    cout << "(" << name << ", " << Duration[0] 
         << "/" << Duration[1] << ")";
}

/*
Break::Break(string duration, bool show) {
    if ( !CheckDuration(duration) ) {
    // set as 1/1 by default
        ShowSymbol = show;
        Duration[0] = 1;
        Duration[1] = 1;
    }
}
*/

Rest::Rest(string duration) {
    ShowSymbol = true;
    if ( !CheckDuration(duration) ) {
    // set as 1/4 by default
        Duration[0] = 1;
        Duration[1] = 4;
    }
}

Rest::Rest() {
    ShowSymbol = true;
    Duration[0] = 1;
    Duration[1] = 4;
}

Blank::Blank(string duration) {
    ShowSymbol = false;
    if ( !CheckDuration(duration) ) {
    // set as 1/1 by default
        Duration[0] = 1;
        Duration[1] = 1;
    }
}

Blank::Blank() {
    ShowSymbol = false;
    Duration[0] = 1;
    Duration[1] = 1;
}

/* NoteGroup class */

void NoteGroup::AddNote(Note new_note) {
    NoteList.push_back(new_note);
}

void NoteGroup::DelLastNote() {
    if ( !NoteList.empty() )
        NoteList.pop_back();
}
        
void NoteGroup::ClearNotes() {
    while ( !NoteList.empty() )
        NoteList.pop_back();
}
        
Note NoteGroup::GetFirstNote() {
    if ( !NoteList.empty() ) {
        return NoteList.front();
    }
    else {
        cerr << "Note list is empty!" << endl;
        return Note("A4","");
    }
}
        
vector<Note> NoteGroup::GetNoteList() { 
    if ( !NoteList.empty() ) {
        return NoteList;
    }
    else {
        cerr << "Note list still Empty!" << endl;
        return vector<Note> () ;
    }
}
        
bool NoteGroup::isNote() { return false; }
bool NoteGroup::isBreak() { return false; }
bool NoteGroup::isNoteGroup() { return true; }

void NoteGroup::PrintNote() {
    if ( !NoteList.empty() ) {
        cout << "[ ";
        for ( vector<Note>::iterator it = NoteList.begin();
              it != NoteList.end(); it++ ) {
            it->PrintNote();
            cout << " ";
        }
        cout << "]";
    }
    else {
        cout << "[EmptyGroup]";
    }
}
   
int NoteGroup::NbrNotes() {
    return NoteList.size();
}
        
NoteGroup::NoteGroup() {}


