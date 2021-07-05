/*

  This file is part of the HAUTBOIS project, which is released under
  the GNU General Public License. You should have received a copy of 
  the GNU General Public License along with Hautbois.  
  If not, see <http://www.gnu.org/licenses/>.

*/

/* hma_parser.hpp
 * Dummy Parser for Hautbois Musical Annotation (.hma)
 */

//TODO STATUS: IN PROGRESS

#include "../notation/Note.hpp"
#include "../notation/Bar.hpp"

namespace HmaParser {


struct hma_sheet {
    string title;
    string author;
    vector<string> instruments;
    string notationsys;
    string tempo;
    int speed;
    int meter[2];
    string tonality;
    vector<string> voices;
    int fs;
    int freq;
}


MusicNote read_token_musicnote(string note_str);
Rest      read_token_restnote (string note_str);
Blank     read_token_blanknote(string note_str);
NoteGroup read_token_notegroup(string note_str);

hma_type get_next_token(string &token, const string input);

void parse_defs();
void parse_properties();
void parse_bar(string barnbr);



}
