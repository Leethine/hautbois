/*

  This file is part of the HAUTBOIS project, which is released under
  the GNU General Public License. You should have received a copy of 
  the GNU General Public License along with Hautbois.  
  If not, see <http://www.gnu.org/licenses/>.

*/

/* hma_parser.hpp
 * Dummy Parser for Hautbois Musical Annotation (.hma)
 */

//#include "../notation/note.hpp"
#include "../notation/bar.hpp"
#include "hma_defs.h"
#include "tempo.h"

//namespace HmaParser {

using namespace std;

typedef struct _hma_sheet_ {
    string title;
    string author;
    int ninstruments;
    vector<string> instruments;
    string notationsys;
    string tempo;
    int speed;
    int meter[2];
    string tonality;
    int nvoices;
    vector<string> voices;
    // order CLEF_UT => Fa = Sol
    vector<string> voice_clef[3];
    int fs;
    int freq;
} hma_sheet;

enum property_enum {
    def_title,
    def_author,
    def_ninstruments,
    def_instrument,
    def_notationsys,
    def_tempo,
    def_speed,
    def_meter,
    def_nvoices,
    def_voice,
    def_tonality,
    def_fs,
    def_freq,
    name_undefined
};

property_enum property_hashit(string property);

string get_next_token_note(string line);
MusicNote read_token_musicnote(string note_str);
Rest      read_token_restnote (string note_str);
Blank     read_token_blanknote(string note_str);
NoteGroup read_token_notegroup(string note_str);

string get_next_line();
//hma_type get_next_token(string &token, const string input);

bool parse_defs(string line, hma_sheet &my_sheet);
void parse_bar(string barnbr);

//}
