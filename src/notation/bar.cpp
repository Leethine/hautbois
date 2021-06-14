/*

  This file is part of the HAUTBOIS project, which is released under
  the GNU General Public License. You should have received a copy of 
  the GNU General Public License along with Hautbois.  
  If not, see <http://www.gnu.org/licenses/>.

*/


/* bar.cpp
 * This file Defines one Bar in the musical score.
 * This one Bar should contain one voice (see Guide: Voice Separation).
 * Bar defines the clef type, speed, instrument type, key signature, etc.
 * Convertion functions are implemented, which allows converting from
 * different notation system to notation index on a standard keyboard.
 */

#include <iostream>

#include "bar.hpp"

using namespace std;

bool Bar::CheckMetre(string metre) {
    size_t found;
    //int num, denom;
    bool valid;
    // Eliminate white spaces
    while ( (found = metre.find(" ")) != string::npos ) {
        metre.erase(metre.begin() + found);
    }
    
    if ( isdigit(metre[0]) && isdigit(metre[2]) 
            && (metre[1] == '/') ) {
        valid = true;
        
        Metre[0] = metre[0] - '0';
        Metre[1] = metre[2] - '0';
    }
    else if ( metre.length() == 1 && isdigit(metre[0]) ) {
        Metre[0] = metre[0];
        Metre[1] = 4;
        valid = true;
    }
    else { valid = false; }
    
    return valid;
}

bool Bar::AddNote(MusicNote new_note) {
    Note * p = new_note.clone();
    ContentFlow.push_back(p);
    // add check function later
    return true;
}

bool Bar::AddNote(Rest new_note) {
    Note * p = new_note.clone();
    ContentFlow.push_back(p);
    // add check function later
    return true;
}

bool Bar::AddNote(Blank new_note) {
    Note * p = new_note.clone();
    ContentFlow.push_back(p);
    // add check function later
    return true;
}

bool Bar::AddNote(NoteGroup new_note) {
    Note * p = new_note.clone();
    ContentFlow.push_back(p);
    // add check function later
    return true;
}

bool Bar::PopNote() {
    if ( ContentFlow.empty() ) {
        ContentFlow.pop_back();
    }
    
    return true;
}

void Bar::PrintBar() {
    cout << "Clef: " << Clef[0] << "-clef";
    cout << ", Centered at line No." << ClefCentre << endl;
    cout << "Scale: ";
    
    cout << Scale << " " << Mode << endl;
    
    cout << "Metre: " << Metre[0] << "/" << Metre[1] << endl;
    
    if ( !ContentFlow.empty() ) {
        for ( int i = 0; i < ContentFlow.size(); i++ ) {
            if (ContentFlow[0] != NULL) {
                switch(ContentFlow[i]->GetNoteType()) {
                case note_group_:
                    cout << ContentFlow[i]->PrintNoteGroup() << " ";
                    break;
                case music_note_:
                    cout << ContentFlow[i]->PrintNote() << " ";
                    break;
                case blank_:
                    cout << ContentFlow[i]->PrintNote() << " ";
                    break;
                case rest_:
                    cout << ContentFlow[i]->PrintNote() << " ";
                    break;
                default:
                    cout << "Unknown" << " ";
                    break;
                }
            }
            else { cout << "NULL "; }
        }
        cout << endl;
    }
    else {
        cout << "Empty Bar." << endl;
    }
    
}

int Bar::Clef2Number(string clef) {
    string newclef = boost::to_upper_copy<string>(clef);
    // support latin name later
    if ( newclef[0] == 'G' )
        return 5;
    else if ( newclef[0] == 'F' )
        return 4;
    else if ( newclef[0] == 'C' )
        return 1;
    else
        return -1;
}

bool Bar::CheckScale(string scale) {
    // Verify Scale format in Scientific notation: e.g. C, Gm
    bool valid = true;
    //TODO Refinement, complete format check
    if ( scale.length() == 3 )
        Scale = scale.substr(0,2);
    else if ( scale.length() == 2 && scale[1] != 'm' && scale[1] != 'M' )
        Scale = scale;
    else if ( scale.length() == 2 )
        Scale = scale.substr(0,1);
    else if ( scale.length() == 1 )
        Scale = scale;
    else
        valid = false;
    
    if ( scale.back() == 'm' )
        Mode = "Minor";
    else
        Mode = "Major";
    
    return valid;
}

int Bar::Scale2Index(string scale) { 
// Please refer to the svg file, the order is:
// C ==> F# : 0 ==> +12
// C ==> Gb : 0 ==> -12
    string keys1 = "C G D A E B F#C#";
    string keys2 = "C F BbEbAbDbGb";
    string keys3 = "C E#A#D#G#";
    int sidx;
    // concatenate a whitespace for uniformed searching size
    if ( scale.length() == 1 )
        scale += " ";
    
    size_t found1 = keys1.find(scale);
    size_t found2 = keys2.find(scale);
    size_t found3 = keys3.find(scale);
    if ( found1 != string::npos )
        sidx = found1 / 2;
    else if ( found2 != string::npos )
        sidx = - found2 / 2;
    else if ( found3 != string::npos )
        sidx = - found3 / 2;
    else
        sidx = -1000;
    
    return sidx;
}

int Bar::GetRelativeScaleIndex(int sidx) { 
// Refer to the circle of fifth, just turn 
// the circle of fifth by 3 steps, anticlockwise
    int relative_sidx = sidx + 3;
    if ( relative_sidx > 7 )
        relative_sidx = 7 - relative_sidx;
    
    return relative_sidx;
}

vector<Note*> Bar::Modulation(int n_semi_tone, bool rewrite) {
    vector<Note*> new_notes;
    for ( int i = 0; i < ContentFlow.size(); i++ ) {
        new_notes.push_back(ContentFlow[i]->Modulation(n_semi_tone));
    }
    if ( rewrite )
        ContentFlow = new_notes;
    return new_notes;
}

//vector<Note*> Bar::Modulation(string target_tone) {};

vector<Note*> Bar::ToRelativeScale() {};

Bar::Bar() {
    // default
    Clef = "G-clef";
    ClefNumber = 5;
    ClefCentre = 2;
    Scale = "C";
    ScaleIndex = Scale2Index(Scale);
    RelativeScaleIndex = GetRelativeScaleIndex(ScaleIndex);
    Metre[0] = 4;
    Metre[1] = 4; 
}

Bar::Bar(string clef) {
    Clef = clef;
    ClefNumber = Clef2Number(clef);
    ClefCentre = 2;
    // if clef format wrong
    if ( ClefNumber == -1 ) {
        cout << "Wrong format: " << clef << " ...using default" << endl;
        Clef = "G-clef";
        ClefNumber = 5;
    }
    Scale = "C";
    Mode = "Major";
    ScaleIndex = Scale2Index(Scale);
    RelativeScaleIndex = GetRelativeScaleIndex(ScaleIndex);
    Metre[0] = 4;
    Metre[1] = 4; 
}

Bar::Bar(string clef, string scale) {
    Clef = clef;
    ClefNumber = Clef2Number(clef);
    ClefCentre = 2;
    // if clef format wrong
    if ( ClefNumber == -1 ) {
        cout << "Wrong format: " << clef << " ...using default" << endl;
        Clef = "G-clef";
        ClefNumber = 5;
    }
    if ( !CheckScale(scale) ) {
        cout << "Wrong format: " << scale 
             << " ...using default C Major scale." << endl;
        Scale = "C";
        Mode = "Major";
    }
        
    ScaleIndex = Scale2Index(Scale);
    RelativeScaleIndex = GetRelativeScaleIndex(ScaleIndex);
    Metre[0] = 4;
    Metre[1] = 4; 
}


Bar::Bar(string clef, string metre, string scale) {
    Clef = clef;
    ClefNumber = Clef2Number(clef);
    ClefCentre = 2;
    // if clef format wrong
    if ( ClefNumber == -1 ) {
        cout << "Wrong format: " << clef << " ...using default" << endl;
        Clef = "G-clef";
        ClefNumber = 5;
    }
    
    if ( !CheckScale(scale) ) {
        cout << "Wrong format: " << scale 
             << " ...using default C Major scale." << endl;
        Scale = "C";
        Mode = "Major";
    }
    
    ScaleIndex = Scale2Index(Scale);
    RelativeScaleIndex = GetRelativeScaleIndex(ScaleIndex);
    if ( !CheckMetre(metre) ) {
        Metre[0] = 4;
        Metre[1] = 4;
    }
}

Bar::Bar(string clef, int centre, string metre, string scale) {
    Clef = clef;
    ClefNumber = Clef2Number(clef);
    ClefCentre = centre;
    // if clef format wrong
    if ( ClefNumber == -1 ) {
        cout << "Wrong format: " << clef << " ...using default" << endl;
        Clef = "G-clef";
        ClefNumber = 5;
    }
    
    if ( !CheckScale(scale) ) {
        cout << "Wrong format: " << scale 
             << " ...using default C Major scale." << endl;
        Scale = "C";
        Mode = "Major";
    }
    
    ScaleIndex = Scale2Index(Scale);
    RelativeScaleIndex = GetRelativeScaleIndex(ScaleIndex);
    if ( !CheckMetre(metre) ) {
        Metre[0] = 4;
        Metre[1] = 4;
    }
}

Bar::~Bar() {
    if ( !ContentFlow.empty() ) {
        for ( int i; i < ContentFlow.size(); i++ ) {
             // release memory of each note
             delete ContentFlow[i];
        }
    }
}
