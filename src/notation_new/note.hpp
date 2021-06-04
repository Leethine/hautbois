/*

  This file is part of the HAUTBOIS project, which is released under
  the GNU General Public License. You should have received a copy of 
  the GNU General Public License along with Hautbois.  
  If not, see <http://www.gnu.org/licenses/>.

*/


/* note.hpp
 * This file Defines one note in the musical score.
 * The Note contains pitch info, duration, properties.
 * Convertion functions are implemented, which allows converting from
 * different notation system to notation index on a standard keyboard.
 */
 
#include <string>
#include <vector>

using namespace std;

/* Definition of the "Note" Class */
class Note {
    public:
    
    // Notation System, Scientific, German, Latin.
    int notationSys; // 'S', 'D', 'L'
    
    // Name of the note and duration.
    int NoteIndex;
    string Name;
    int Duration[2];
    
    // Properties of the note, e.g. Force, Ornaments, etc.
    string Force;
    string OrnamentType;
    string OrnamentParam;
    // TODO Leave spaces for further properties
            
    
    // Functions for handling the notation.
    bool CheckDuration(string duration);
    int DetectNotation(string name);
    int SciName2Index(string name);
    int Latin2Index(string name);
    int Helm2Index(string name);
    /*
    string Sci2Latin(string name);
    string Latin2Sci(string name);
    string Sci2Helm(string name);
    string Helm2Sci(string name);
    string Helm2Latin(string name);
    string Latin2Helm(string name);
    */
    
    // Informative functions
    bool isNote();
    bool isBreak();
    bool isNoteGroup();
    
    void PrintNote();
    
    Note(string name, string duration);
    Note(string name);
};

/* "Break" Class, Rest or Blank */
class Break {
    public:
    
    // Show the break symbol or not
    bool ShowSymbol;
    int Duration[2];
    bool CheckDuration(string duration);

    // Informative functions
    bool isNote();
    bool isBreak();
    bool isNoteGroup();
    
    void PrintNote();
    
    // Avoid using Break Class directly, preferred "Blank" or "Rest" 
    //Break(string duration, bool show);
    Break(string duration) {};
    Break() {};
};

/* Rest symbol class */
class Rest : public Break {
    public:
    
    Rest(string duration);
    Rest();
};

/* Blank class, left blank a block of spaces */
class Blank : public Break {
    public:
    
    Blank(string duration);
    Blank();
};


/* NoteGroup Class, a group of note with the same length */
class NoteGroup {
    // Every Note will follow the properties of the first Note
    public:
    
    vector<Note> NoteList;
            
    void AddNote(Note new_note);
    void DelLastNote();
    void ClearNotes();
    Note GetFirstNote();
    vector<Note> GetNoteList();
        
    // Informative functions
    bool isNote();
    bool isBreak();
    bool isNoteGroup();
    int NbrNotes();
    
    void PrintNote();
    
    NoteGroup();
};

