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

bool Note::CheckDuration(string duration) {
// Check Duration validity; if valid, write to class.
    
    size_t found;
    //int num, denom;
    bool valid;
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
        valid = true;
    }
    else {
        valid = false;
    }
    
    return valid;
}

string Note::PrintNote() {
    string output;
    output = "(" + Name + ", " + string(1, Duration[0] + '0')
                 + "/" + string(1, Duration[1] + '0') + ")";
    return output;
}

bool Note::isNote() { return false; }
bool Note::isBlank() { return false; }
bool Note::isRest() { return false; }
bool Note::isNoteGroup() { return false; }
note_type Note::GetNoteType() {return NoteType; }

string Note::GetName() { return Name; }
int Note::GetNoteIndex() { return NoteIndex; }

tuple<int,int> Note::GetDuration() { 
    return make_tuple(Duration[0], Duration[1]);
}

string Note::GetDurationStr() { 
    return string(1,Duration[0]+'0') + "/" + string(1,Duration[1]+'0');
}

string Note::PrintNoteGroup() { return "PrintGroupBasicNoteClass"; }

Note* Note::Modulation(int semi_tones) { return NULL; }

Note* Note::clone() const { return NULL; }

Note::Note() { };
Note::~Note(void) { };

int MusicNote::DetectNotation(string name) {
// Detection of the notation system.
// Returns 'S' for Scientific; 'L' for latin, 'D' for German. 
    if ( name.length() == 1 )
        return 'D';
    else if ( isalpha(name[1]) && name[1] != 'b' )
        return 'L';
    else if ( isalpha(name[0]) && (isdigit(name.back()) || 
               name.back() == '#' || name.back() == 'b' ))
        return 'S';
    else
        return 'D';
}

// TODO
bool MusicNote::CheckNotationName() { 

    return false;
}

int MusicNote::SciName2Index(string name) {
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
        dis = -500;
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

int MusicNote::SciName2Index_alt(string name) {
// Convert Scientific Name to Index on a standard keyboard. 
// Alternative format e.g. "A#2". 
    int note_index, dis, postfix, n_name, n_octave;
    // get octave index and note name
    n_octave = name[name.length()-1] - '1';
    n_name = name[0];
    // calculate the distance from current note to C
    switch(toupper(n_name)) {
    case 'C':
        dis = 0;
        break;
    case 'D':
        dis = 2;
        break;
    case 'E':
        dis = 4;
        break;
    case 'F':
        dis = 5;
        break;
    case 'G':
        dis = 7;
        break;
    case 'A':
        dis = 9;
        break;
    case 'B':
        dis = 11;
        break;
    default:
        dis = -500;
        break;
    }
    
    // get sharp or flat sign
    if ( name.length() > 2 ) {
        switch(name[1]) {
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
    }
    else { postfix = 0; }
    // Calc the index = distance + 4 + octaves + # or b
    // the reason of +4 is dis(C-A) = 3
    note_index = dis + 4 + n_octave * 12 + postfix;
    return note_index;
}


string MusicNote::Index2SciName(int idx) {
// Convert index to scientific notation name
    
    if ( idx < 1 || idx > 108 ) {
        cout << "Index must be within range [1,108]" << endl;
        return "";
    }
    
    idx = idx - 1;
    char note_name[3];
    note_name[2] = ' ';
    note_name[0] = idx % 12 + 1;
    
    char temp = note_name[0];
    switch(temp) {
    // do nothing for white keys
    case 1:
        note_name[0] = 'A';
        break;
    case 3:
        note_name[0] = 'B';
        break;
    case 4:
        note_name[0] = 'C';
        break;
    case 6:
        note_name[0] = 'D';
        break;
    case 8:
        note_name[0] = 'E';
        break;
    case 9:
        note_name[0] = 'F';
        break;
    case 11:
        note_name[0] = 'G';
        break;
    default:
        note_name[2] = '#';
        temp -= 1;
        break;
    }
    
    switch(temp) {
    // do nothing for white keys
    case 1:
        note_name[0] = 'A';
        break;
    case 3:
        note_name[0] = 'B';
        break;
    case 4:
        note_name[0] = 'C';
        break;
    case 6:
        note_name[0] = 'D';
        break;
    case 8:
        note_name[0] = 'E';
        break;
    case 9:
        note_name[0] = 'F';
        break;
    case 11:
        note_name[0] = 'G';
        break;
    default:
        note_name[2] = ' ';
        note_name[0] = ' ';
        break;
    }
    
    note_name[1] = (idx + 9) / 12;
    if ( note_name[1] < 0 ) 
        note_name[1] = 0;
    
    note_name[1] += '0';
    
    if ( note_name[2] == ' ' )
        return string(note_name, 2);
    else
        return string(note_name, 3);
}

string MusicNote::Index2SciName_alt(int idx) {
// Convert index to scientific notation name
    
    if ( idx < 1 || idx > 108 ) {
        cout << "Index must be within range [1,108]" << endl;
        return "";
    }
    
    idx = idx - 1;
    char note_name[3];
    note_name[2] = ' ';
    note_name[0] = idx % 12 + 1;
    
    char temp = note_name[0];
    switch(temp) {
    // do nothing for white keys
    case 1:
        note_name[0] = 'A';
        break;
    case 3:
        note_name[0] = 'B';
        break;
    case 4:
        note_name[0] = 'C';
        break;
    case 6:
        note_name[0] = 'D';
        break;
    case 8:
        note_name[0] = 'E';
        break;
    case 9:
        note_name[0] = 'F';
        break;
    case 11:
        note_name[0] = 'G';
        break;
    default:
        note_name[2] = '#';
        temp -= 1;
        break;
    }
    
    switch(temp) {
    // do nothing for white keys
    case 1:
        note_name[0] = 'A';
        break;
    case 3:
        note_name[0] = 'B';
        break;
    case 4:
        note_name[0] = 'C';
        break;
    case 6:
        note_name[0] = 'D';
        break;
    case 8:
        note_name[0] = 'E';
        break;
    case 9:
        note_name[0] = 'F';
        break;
    case 11:
        note_name[0] = 'G';
        break;
    default:
        note_name[2] = ' ';
        note_name[0] = ' ';
        break;
    }
    
    note_name[1] = (idx + 9) / 12;
    if ( note_name[1] < 0 ) 
        note_name[1] = 0;
    
    note_name[1] += '0';
    
    if ( note_name[2] == ' ' ) {
        return string(note_name, 2);
    }
    else {
        temp = note_name[2];
        note_name[2] = note_name[1];
        note_name[1] = temp;
        return string(note_name, 3);
    }
}

int MusicNote::Latin2Index(string name) {
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

int MusicNote::Helm2Index(string name) {
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
string MusicNote::Sci2Latin(string name) {
// Convert Scientific name to Latin Name.
    int note_idx = Note::SciName2Index(name);
    return "";
}

string MusicNote::Latin2Sci(string name) {
// Convert Latin name to Scientific name.
    return "";
}

string MusicNote::Sci2Helm(string name) {
// Convert Scientific name to Helmholtz.
    return "";
}

string MusicNote::Helm2Sci(string name) {
// Convert Helmholtz notation to Scientific notation.
    return "";
}

string MusicNote::Helm2Latin(string name) {
// Convert Helmholtz notation to Latin name.
    return "";
}

string MusicNote::Latin2Helm(string name) {
// Convert Latin name to Helmholtz.
    return "";
}
*/

string MusicNote::PrintNote() {
    string output;
    output = "(" + Name + ", " + string(1, Duration[0] + '0')
                 + "/" + string(1, Duration[1] + '0') + ")";
    return output;
}

bool MusicNote::isNote() { return true; }
bool MusicNote::isBlank() { return false; }
bool MusicNote::isRest() { return false; }
bool MusicNote::isNoteGroup() { return false; }

Note* MusicNote::Modulation(int semi_tones) {
    // save the note info
    string old_name = Name;
    int old_index = NoteIndex;
    
    // temporary change
    NoteIndex += semi_tones;
    Name = Index2SciName_alt(NoteIndex);
    
    // clone a new note
    Note* NewNote = clone();
    
    // restore the current note
    NoteIndex = old_index;
    Name = old_name;
    
    return NewNote;
}

Note* MusicNote::clone() const { return new MusicNote(*this); }

MusicNote::MusicNote(string name, string duration) {
// Init    
    int notation_sys;
    NoteType = music_note_;
    
    // Get notation system
    notation_sys = DetectNotation(name);
    Name = name;
    // then notation
    switch (notation_sys) {
    case 'S':
        if ( name.length() > 2 && (name[1] == '#' || name[1] == 'b') )
            NoteIndex = SciName2Index_alt(name);
        else
            NoteIndex = SciName2Index(name);
        break;
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
        cout << "Wrong format of Duration: " << duration << endl;
        cout << "Using default 1/4" << endl;
        Duration[0] = 1;
        Duration[1] = 4;
    }
}

MusicNote::MusicNote(string name) {
// Init
    int notation_sys;
    NoteType = music_note_;
    
    // Get notation system
    notation_sys = DetectNotation(name);
    Name = name;
    // then notation
    switch (notation_sys) {
    case 'S':
        if ( name.length() > 2 && (name[1] == '#' || name[1] == 'b') )
            NoteIndex = SciName2Index_alt(name);
        else
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



/* Rest and Blank class */
string Rest::PrintNote() {
    string output;
    output = "(" + Name + ", " + string(1, Duration[0] + '0')
                 + "/" + string(1, Duration[1] + '0') + ")";
    return output;
}
bool Rest::isNote() { return false; }
bool Rest::isBlank() { return false; }
bool Rest::isRest() { return true; }
bool Rest::isNoteGroup() { return false; }

Note* Rest::Modulation(int semi_tones) { return clone(); }

Note* Rest::clone() const { return new Rest(*this); }

Rest::Rest(string duration) {
    Name = "rest";
    NoteType = rest_;
    
    if ( !CheckDuration(duration) ) {
        cout << "Wrong format of Duration: " << duration << endl;
        cout << "Using default 1/4" << endl;
        
        Duration[0] = 1;
        Duration[1] = 4;
    }
    NoteIndex = 0;
}

Rest::Rest() {
    Name = "rest";
    NoteType = rest_;
    
    Duration[0] = 1;
    Duration[1] = 4;
    NoteIndex = 0;
}

string Blank::PrintNote() {
    string output;
    output = "(" + Name + ", " + string(1, Duration[0] + '0')
                 + "/" + string(1, Duration[1] + '0') + ")";
    return output;
}

bool Blank::isNote() { return false; }
bool Blank::isBlank() { return true; }
bool Blank::isRest() { return false; }
bool Blank::isNoteGroup() { return false; }

Note* Blank::Modulation(int semi_tones) { return clone(); }

Note* Blank::clone() const { return new Blank(*this); }

Blank::Blank(string duration) {
    Name = "blank";
    NoteType = blank_;
    
    if ( !CheckDuration(duration) ) {
        cout << "Wrong format of Duration: " << duration << endl;
        cout << "Using default 4/4" << endl;
        Duration[0] = 4;
        Duration[1] = 4;
    }
    NoteIndex = -1;
}

Blank::Blank() {
    Name = "blank";
    NoteType = blank_;
    
    Duration[0] = 4;
    Duration[1] = 4;
    NoteIndex = -1;
}

/* NoteGroup class */

void NoteGroup::AddNote(MusicNote new_note) {
    NoteList.push_back(new_note);
}

void NoteGroup::DelLastNote() {
    if ( !NoteList.empty() )
        NoteList.pop_back();
}

Note NoteGroup::PopLastNote() {
    Note last_note;
    if ( !NoteList.empty() ) {
        last_note = NoteList.back();
        NoteList.pop_back();
    }
    else {
        cerr << "Note list is empty!" << endl;
    }
    return last_note;
}
        
void NoteGroup::ClearNotes() {
    while ( !NoteList.empty() )
        NoteList.pop_back();
}
        
Note NoteGroup::GetFirstNote() {
    Note first_note;
    if ( !NoteList.empty() ) {
        first_note = NoteList.front();
    }
    else {
        cerr << "Note list is empty!" << endl;
    }
    return first_note;
}
        
vector<MusicNote> NoteGroup::GetNoteList() { 
    if ( !NoteList.empty() ) {
        return NoteList;
    }
    else {
        cerr << "Note list still Empty!" << endl;
        return vector<MusicNote> () ;
    }
}

bool NoteGroup::isNote() { return false; }
bool NoteGroup::isBlank() { return false; }
bool NoteGroup::isRest() { return false; }
bool NoteGroup::isNoteGroup() { return true; }
int NoteGroup::NbrNotes() { return NoteList.size(); }

string NoteGroup::PrintNoteGroup() {
    string output = "";
    if ( !NoteList.empty() ) {
        output += "[";
        for ( vector<MusicNote>::iterator it = NoteList.begin();
              it != NoteList.end(); it++ ) {
            output += it->PrintNote();
            output += " ";
        }
        output = output.substr(0,output.length()-1);
        output += "]";
    }
    else {
        output += "[EmptyGroup]";
    }
    return output;
}

Note* NoteGroup::Modulation(int semi_tones) {
    // create a copy of original notes
    vector<MusicNote> old_notes = NoteList;
    Note* temp_note;
    // clear current notes
    ClearNotes();
    string duration;
    for ( int i = 0; i < old_notes.size(); i++ ) {
        temp_note = old_notes[i].Modulation(semi_tones);
        AddNote(MusicNote(temp_note->GetName(), temp_note->GetDurationStr()));
    }
    Note* NewGroup = this->clone();
    ClearNotes();
    // restore the previous note list
    NoteList = old_notes;
    
    return NewGroup;
}

Note* NoteGroup::clone() const { return new NoteGroup(*this); }

NoteGroup::NoteGroup(MusicNote note1) {
    Name = "Group2Notes";
    NoteType = note_group_;
    
    Duration[0] = get<0>(note1.GetDuration());
    Duration[1] = get<1>(note1.GetDuration());
    NoteIndex = -2;
    AddNote(note1);
}

NoteGroup::NoteGroup(MusicNote note1, MusicNote note2) {
    Name = "Group2Notes";
    NoteType = note_group_;
    
    Duration[0] = get<0>(note1.GetDuration());
    Duration[1] = get<1>(note1.GetDuration());
    NoteIndex = -2;
    AddNote(note1);
    AddNote(note2);
}

NoteGroup::NoteGroup(MusicNote note1, MusicNote note2, MusicNote note3) {
    Name = "Group3Notes";
    NoteType = note_group_;
    
    Duration[0] = get<0>(note1.GetDuration());
    Duration[1] = get<1>(note1.GetDuration());
    NoteIndex = -2;
    AddNote(note1);
    AddNote(note2);
    AddNote(note3);
}

NoteGroup::NoteGroup(MusicNote note1, MusicNote note2, 
                     MusicNote note3, MusicNote note4) {
    Name = "Group4Notes";
    NoteType = note_group_;
    
    Duration[0] = get<0>(note1.GetDuration());
    Duration[1] = get<1>(note1.GetDuration());
    NoteIndex = -2;
    AddNote(note1);
    AddNote(note2);
    AddNote(note3);
    AddNote(note4);
}


