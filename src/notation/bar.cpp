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
#include <string>
#include <vector>
#include <tuple>
#include <boost/algorithm/string.hpp>

#include "note.hpp"

using namespace std;

#if (defined(__cplusplus) && (__cplusplus >= 201703) )
#include <variant>

class Bar {
    string InstrumentName;
    string InstrumentType;
    string InstrumentIndex;
    
    string Clef;
    int ClefNumber; // e.g. 5 for "G-clef"
    // line on the stave at which clef is centred, 1 is the lowest
    int ClefCentre;
    
    string Scale; // "C" "Am" "Ebm" etc
    string RelativeScale;
    // Ref: A. Danhauser, Théorie de la Musique Abrégé (Lesson.4-10)
    int ScaleIndex;    
    int RelativeScaleIndex;
    
    // Key properties
    vector<string> KeySignature;
    vector<tuple<char, int>> KeyRules;
    // Offset at which the Bar will be added in the sheet, as Duration
    int Offset[2];
    
    // Content
    vector<variant<Note, NoteGroup, Break>> ContentFlow;
    
    // TODO Leave Space for more properties
    
    
    
    
    int Clef2Number(string clef);
    int Scale2Index(string scale);
    int GetRelativeScaleIndex(int s_idx);
    
    vector<string> GetKeySignature(); // format: ["#", "L3", "L4", "S2"]
    // Get rules in list of tuple, +1 or -1 semitone
    // [('C',0), ('D',1) .... ]
    vector<tuple<char, int>> GetKeyRules();
    
    // TODO More functions
    
    Bar();
    Bar(string clef);
    Bar(string clef, string scale);
    Bar(string clef, int centre, string scale);
    
};



//#else



#endif

int main()
{
    Bar bar1 (); 
    return 0;

}
