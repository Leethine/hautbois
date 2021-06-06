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
#include <tuple>

using namespace std;

//enum note_type { MusicNote, NoteGroup, Rest, Blank };

/* Definition of the "Note" Class *
 * Parent class, not to be used   */
class Note {
  protected:
    // Name of the note and duration.
    int NoteIndex;
    string Name;
    int Duration[2];
    
    //note_type NoteType;
    
    // Functions for handling the duration.
    bool CheckDuration(string duration);
    
  public:
    string PrintNote();
    
    virtual string PrintNoteGroup();
    // Informative functions
    virtual bool isNote();
    virtual bool isBlank();
    virtual bool isRest();
    virtual bool isNoteGroup();
    
    string GetName();
    string GetType();
    int GetNoteIndex();
    tuple<int,int> GetDuration();
    
    Note();
    virtual ~Note();
};


class MusicNote: public Note {
  private:
    // Notation System, Scientific, German, Latin.
    int notationSys; // 'S', 'D', 'L'
    
    // Functions for handling the notation.
    int DetectNotation(string name);
    bool CheckNotationName();
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
    
  public:
    // Properties of the note, e.g. Force, Ornaments, etc.
    string Force;
    string OrnamentType;
    string OrnamentParam;
    // TODO Leave spaces for further properties
    
    
    
    // Informative functions
    bool isNote();
    bool isBlank();
    bool isRest();
    bool isNoteGroup();
    
    int GetNotationSys();
    
    MusicNote(string name);
    MusicNote(string name, string duration);
};


/* Rest symbol class */
class Rest: public Note {
  
  public:
    // Informative functions
    bool isNote();
    bool isBlank();
    bool isRest();
    bool isNoteGroup();
    
    Rest();
    Rest(string duration);
};

/* Blank class, left blank a block of spaces */
class Blank: public Note {
  
  public:
    // Informative functions
    bool isNote();
    bool isBlank();
    bool isRest();
    bool isNoteGroup();
    
    Blank();
    Blank(string duration);
};


/* NoteGroup Class, a group of note with the same length */
class NoteGroup: public Note {
  private:
    // Every Note will follow the properties of the first Note
    vector<Note> NoteList;
  public:
    void AddNote(Note new_note);
    void DelLastNote();
    Note PopLastNote();
    void ClearNotes();
    Note GetFirstNote();
    vector<Note> GetNoteList();
        
    // Informative functions
    bool isNote();
    bool isBlank();
    bool isRest();
    bool isNoteGroup();
    int NbrNotes();
    
    string PrintNoteGroup();
    
    NoteGroup(MusicNote note1, MusicNote note2);
    NoteGroup(MusicNote note1, MusicNote note2, MusicNote note3);
    NoteGroup(MusicNote note1, MusicNote note2, 
              MusicNote note3, MusicNote note4);
};

