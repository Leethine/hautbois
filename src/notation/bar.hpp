/*
  This file is part of the HAUTBOIS project, which is released under
  the GNU General Public License. You should have received a copy of 
  the GNU General Public License along with Hautbois.  
  If not, see <http://www.gnu.org/licenses/>.

*/


/* bar.hpp
 * This file Defines one Bar in the musical score.
 * This one Bar should contain one voice (see Guide: Voice Separation).
 * Bar defines the clef type, speed, instrument type, key signature, etc.
 * Convertion functions are implemented, which allows converting from
 * different notation system to notation index on a standard keyboard.
 */


#include <string>
#include <vector>
#include <tuple>
#include <boost/algorithm/string.hpp>

#include "note.hpp"

using namespace std;

#if (defined(__cplusplus) && (__cplusplus >= 201703) )

  #include <variant>
  #define CPP_VARIANT variant

#else

  #include <boost/variant.hpp>
  #define CPP_VARIANT boost::variant

#endif

class Bar {
    public:
    
    string InstrumentName;
    string InstrumentType;
    string InstrumentIndex;
    
    string Clef;
    int ClefNumber; // e.g. 5 for "G-clef"
    // line on the stave at which clef is centred, 1 to 5
    int ClefCentre;
    
    string Scale; // "C" "Am" "Ebm" etc
    string Mode;
    string RelativeScale;
    // Ref: A. Danhauser, Théorie de la Musique Abrégé (Lesson.4-10)
    int ScaleIndex;    
    int RelativeScaleIndex;
    
    int Metre[2];
    string Speed;
    string SpeedChangeFunc; // e.g. = "CONSTANT", "Linear", etc.
    double SpeedBegin; // 1/4 = ?
    double SpeedEnd;   // 1/4 = ?
    
    // Offset at which the Bar will be added in the sheet, as Duration
    int Offset[2];
    
    // Content
    vector<Note*> ContentFlow;
    
    // TODO Leave Space for more properties
    // Key properties
    //vector<string> KeySignature; // format: ["#", "L3", "L4", "S2"]
    //vector<tuple<char, char>> KeyRules; // format [('C','#'),('D', 'b')]
    
    
    
    bool CheckMetre(string metre);
    bool AddNote(MusicNote new_note);
    bool AddNote(Rest new_note);
    bool AddNote(Blank new_note);
    bool AddNote(NoteGroup new_note);
    bool PopNote();
    
    // print bar info, not PDF
    void PrintBar();
    
    int Clef2Number(string clef);
    bool CheckScale(string scale);
    int Scale2Index(string scale);
    int GetRelativeScaleIndex(int sidx);
    
    vector<Note*> Modulation(int n_semi_tone, bool = false);
    //vector<Note*> Modulation(string target_tone);
    
    vector<Note*> ToRelativeScale();
    
    
    // TODO More functions
    //vector<string> GetKeySignature(); // format: ["#", "L3", "L4", "S2"]
    // Get rules in list of tuple, +1 or -1 semitone
    // [('C','N'), ('D','#') .... ]
    //vector<tuple<char, char>> GetKeyRules();
    
    
    
    
    Bar();
    Bar(string clef);
    Bar(string clef, string scale);
    Bar(string clef, string metre, string scale);
    Bar(string clef, int centre, string metre, string scale);
    ~Bar();
};

