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

bool Bar::AddNote(Note new_note) {
    ContentFlow.push_back(new_note);
    // add check function later
    return true;
}

bool Bar::AddNote(Break new_note) {
    ContentFlow.push_back(new_note);
    // add check function later
    return true;
}

bool Bar::AddNote(NoteGroup new_note) {
    ContentFlow.push_back(new_note);
    // add check function later
    return true;
}

bool Bar::PopNote() {
    if ( ContentFlow.empty() ) 
        ContentFlow.pop_back();
    
    return true;
}
    
// print info, not PDF
void Bar::PrintBar() {
    if ( !ContentFlow.empty() ) {
        for ( vector<CPP_VARIANT<Note, NoteGroup, Break>>::iterator
              it = ContentFlow.begin();
              it != ContentFlow.end(); it++ ) {
              if(auto pval = get_if<Note>(it))
                cout << pval.PrintNote() << " "; }
        cout << endl;
    }
    else {
        cout << "Empty Bar." << endl;
    }
};

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

vector<CPP_VARIANT<Note,NoteGroup,Break>> Bar::Modulation(int n_semi_tone) {};
vector<CPP_VARIANT<Note,NoteGroup,Break>> Bar::Modulation(string target_tone) {};

Bar::Bar() {
    // default
    Clef = "G-clef";
    ClefNumber = 5;
    ClefCentre = 2;
    Scale = "C";
    ScaleIndex = Scale2Index(Scale);
    
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
}

Bar::Bar(string clef, string scale) {};

Bar::Bar(string clef, string meter, string scale) {};

Bar::Bar(string clef, int centre, string meter, string scale) {};


// TEST THE OBJECT
int main()
{
    Bar bar1;
    bar1 = Bar();
    bar1.AddNote(Note ("C4", "1/4"));
    bar1.PrintBar();
    return 0;

}
