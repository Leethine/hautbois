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

bool Bar::AddNote(Note new_note) {
    ContentFlow.push_back(new_note);
    // add check function later
    return true;
}

bool Bar::PopNote() {
    if ( ContentFlow.empty() ) 
        ContentFlow.pop_back();
    
    return true;
}

void Bar::PrintBar() {
    cout << "Clef: " << Clef[0] << "-clef";
    cout << ", Centered at line No." << ClefCentre << endl;
    cout << "Scale: ";
    if ( Scale.length() == 3 )
        cout << Scale[0] << Scale[1];
    else if ( Scale.length() == 2 && Scale[1] != 'm' )
        cout << Scale[0] << Scale[1];
    else
        cout << Scale[0];
        
    if ( Scale.back() == 'm' )
        cout << " Minor";
    else
        cout << " Minor";
    cout << endl;
    
    cout << "Metre: " << Metre[0] << "/" << Metre[1] << endl;
    
    if ( !ContentFlow.empty() ) {
        for ( vector<Note>::iterator
              it = ContentFlow.begin();
              it != ContentFlow.end(); it++ ) {
            switch(it->GetNoteType()) {
            case note_group_:
                cout << it->PrintNoteGroup() << " ";
                break;
            case music_note_:
                cout << it->PrintNote() << " ";
                break;
            case blank_:
                cout << it->PrintNote() << " ";
                break;
            case rest_:
                cout << it->PrintNote() << " ";
                break;
            default:
                cout << "Unknown" << " ";
                break;
            }
        }
        cout << endl;
    }
    else {
        cout << "Empty Bar." << endl;
    }
}


/*
void Bar::PrintBar() {
    cout << "Clef: " << Clef[0] << "-clef";
    cout << ", Centered at line No." << ClefCentre << endl;
    cout << "Scale: ";
    if ( Scale.length() == 3 )
        cout << Scale[0] << Scale[1];
    else if ( Scale.length() == 2 && Scale[1] != 'm' )
        cout << Scale[0] << Scale[1];
    else
        cout << Scale[0];
        
    if ( Scale.back() == 'm' )
        cout << " Minor";
    else
        cout << " Minor";
    cout << endl;
    
    cout << "Metre: " << Metre[0] << "/" << Metre[1] << endl;
    
    //string temp;
    //vector<Note> tempnotelist;
    NoteGroup * tempg; // (MusicNote("A4"),MusicNote("A4"));
    if ( !ContentFlow.empty() ) {
        for ( vector<Note>::iterator
              it = ContentFlow.begin();
              it != ContentFlow.end(); it++ ) {
            //temp = "";
            switch(it->GetNoteType()) {
            case note_group_:
                //temp = it->PrintNoteGroup();
                // No idea why it doesn't work, whatever...
                tempg = dynamic_cast<NoteGroup *> (*it);
                cout << tempg->PrintNoteGroup() << " ";
                break;
            case music_note_:
                cout << it->PrintNote() << " ";
                break;
            case blank_:
                cout << it->PrintNote() << " ";
                break;
            case rest_:
                cout << it->PrintNote() << " ";
                break;
            default:
                cout << "Unknown" << " ";
                break;
            }
        }
        cout << endl;
    }
    else {
        cout << "Empty Bar." << endl;
    }
}
*/
/*
void Bar::PrintBar() {
    cout << "Clef: " << Clef[0] << "-clef";
    cout << ", Centered at line No." << ClefCentre << endl;
    cout << "Scale: ";
    if ( Scale.length() == 3 )
        cout << Scale[0] << Scale[1];
    else if ( Scale.length() == 2 && Scale[1] != 'm' )
        cout << Scale[0] << Scale[1];
    else
        cout << Scale[0];
        
    if ( Scale.back() == 'm' )
        cout << " Minor";
    else
        cout << " Minor";
    cout << endl;
    
    cout << "Metre: " << Metre[0] << "/" << Metre[1] << endl;
    
    if ( !ContentFlow.empty() ) {
        for ( int i=0; i < ContentFlow.size(); i++ ) {
            switch(ContentFlow.at(i).GetNoteType()) {
            case note_group_:
                //temp = it->PrintNoteGroup();
                // No idea why it doesn't work, whatever...
                NoteGroup & temp_ng = dynamic_cast<NoteGroup &> (ContentFlow.at(i));
                cout << temp_ng.PrintNoteGroup() << " ";
                break;
                
            default:
                cout << "Unknown" << " ";
                break;
            }
        }
        cout << endl;
    }
    else {
        cout << "Empty Bar." << endl;
    }
}
*/

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

int Bar::Scale2Index(string scale) { return 0; }
int Bar::GetRelativeScaleIndex(int s_idx) { return 0; };

vector<Note> Bar::Modulation(int n_semi_tone) {};
vector<Note> Bar::Modulation(string target_tone) {};

vector<Note> Bar::ToRelativeScale() {};

Bar::Bar() {
    // default
    Clef = "G-clef";
    ClefNumber = 5;
    ClefCentre = 2;
    Scale = "C";
    ScaleIndex = Scale2Index(Scale);
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
    ScaleIndex = Scale2Index(Scale);
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
    
    ScaleIndex = Scale2Index(Scale);
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
    
    ScaleIndex = Scale2Index(Scale);
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
    
    ScaleIndex = Scale2Index(Scale);
    if ( !CheckMetre(metre) ) {
        Metre[0] = 4;
        Metre[1] = 4;
    }
}
