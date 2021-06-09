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

enum note_type { music_note_, note_group_, rest_, blank_ };

/* Definition of the "Note" Class *
 * Parent class, not to be used   */
class Note {
  protected:
    // Name of the note and duration.
    int NoteIndex;
    string Name;
    int Duration[2];
    
    note_type NoteType;
    
    // Functions for handling the duration.
    bool CheckDuration(string duration);
    
  public:
    virtual string PrintNote();
    
    virtual string PrintNoteGroup();
    // Informative functions
    virtual bool isNote();
    virtual bool isBlank();
    virtual bool isRest();
    virtual bool isNoteGroup();
    virtual note_type GetNoteType();
    
    string GetName();
    int GetNoteIndex();
    tuple<int,int> GetDuration();
    
    virtual Note* clone() const;
    
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
    int SciName2Index_alt(string name);
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
    string PrintNote();
    bool isNote();
    bool isBlank();
    bool isRest();
    bool isNoteGroup();
    int GetNotationSys();
    
    // Utility functions
    string Index2SciName(int idx);
    string Index2SciName_alt(int idx);
    
    
    Note* clone() const;
    
    MusicNote(string name);
    MusicNote(string name, string duration);
};


/* Rest symbol class */
class Rest: public Note {
  
  public:
    // Informative functions
    string PrintNote();
    bool isNote();
    bool isBlank();
    bool isRest();
    bool isNoteGroup();
    
    Note* clone() const;
    
    Rest();
    Rest(string duration);
};

/* Blank class, left blank a block of spaces */
class Blank: public Note {
  
  public:
    // Informative functions
    string PrintNote();
    bool isNote();
    bool isBlank();
    bool isRest();
    bool isNoteGroup();
    
    Note* clone() const;
    
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
    
    string PrintNoteGroup() override;
    
    Note* clone() const;
    
    NoteGroup(MusicNote note1, MusicNote note2);
    NoteGroup(MusicNote note1, MusicNote note2, MusicNote note3);
    NoteGroup(MusicNote note1, MusicNote note2, 
              MusicNote note3, MusicNote note4);
};

