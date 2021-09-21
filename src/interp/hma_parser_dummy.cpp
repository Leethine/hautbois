/*

  This file is part of the HAUTBOIS project, which is released under
  the GNU General Public License. You should have received a copy of 
  the GNU General Public License along with Hautbois.  
  If not, see <http://www.gnu.org/licenses/>.

*/

/* hma_parser.cpp
 * Parser for Hautbois Musical Annotation (.hma)

 */

#include <iostream>
#include <stdlib.h>
//#include <regex>
#include <algorithm>
#include <boost/algorithm/string.hpp>
#include "hma_parser_dummy.hpp"

//namespace HmaParser

#define CLEF_UT 0
#define CLEF_FA 1
#define CLEF_SOL 2

using namespace std;

/*******************************************************************/
/* PreDef of Types */

property_enum property_hashit(string property) {
/* Convert from string to enum, for switch(){} */ 

    if ( boost::algorithm::to_lower_copy(property) == "title" )
        return def_title;
    else if ( boost::algorithm::to_lower_copy(property) == "author" )
        return def_author;
    else if ( boost::algorithm::to_lower_copy(property) == "ninstruments" )
        return def_ninstruments;
    else if ( boost::algorithm::to_lower_copy(property) == "instrument" )
        return def_instrument;
    else if ( boost::algorithm::to_lower_copy(property) == "notationsys" )
        return def_notationsys;
    else if ( boost::algorithm::to_lower_copy(property) == "tempo" )
        return def_tempo;
    else if ( boost::algorithm::to_lower_copy(property) == "speed" )
        return def_speed;
    else if ( boost::algorithm::to_lower_copy(property) == "meter" )
        return def_meter;
    else if ( boost::algorithm::to_lower_copy(property) == "nvoices" )
        return def_nvoices;
    else if ( boost::algorithm::to_lower_copy(property) == "voice" )
        return def_voice;
    else if ( boost::algorithm::to_lower_copy(property) == "tonality" )
        return def_tonality;
    else if ( boost::algorithm::to_lower_copy(property) == "fs" )
        return def_fs;
    else if ( boost::algorithm::to_lower_copy(property) == "freq" )
        return def_freq;
    else
        return name_undefined;

}

bool isBarLine(const string line) {
/* Check if this line defines a bar */
    regex e1 ("@I[0-9]V[0-9]:");
    smatch sm;
    regex_search(line, sm, e1);
    
    if ( sm.size() == 0 ) 
        return false;
    else
        return true; 
}

bool isComment(const string line) {
/* Check if this line is comment */
    regex e1 ("%*%");
    smatch sm;
    regex_search(line, sm, e1);
    
    if ( sm.size() == 0 ) 
        return false;
    else
        return true; 
}

/*******************************************************************/
/* Line processor */

line_type_enum get_next_line(string& line, ifstream& myfile) {
/* Get next line from a file stream. 
 * If the line is a bar and is unfinished, 
 * then get the whole line until the bar is finished. 
 */
    
    line = "";
    if ( myfile.eof() ) {
        return line_eof;
    }
    char c;
    while ( myfile.get(c) ) {
        if ( c == '\n' )
            break;
        else
            line += c;
    }
    
    // proceed the same step until barline is finished
    if ( isBarLine(line) && line.find("|;") == string::npos ) {
        // if end of bar notation |; not found
        while ( myfile.get(c) ) {
            if ( c == '\n' )
                ;
            else if ( c == ';' && line[line.length()-1] == '|' ) {
            // end of bar is found
                line += c;
                break;
            }
            else
                line += c;
        }
    }
    
    if ( isBarLine(line) )
        return line_bar;
    else if ( isComment(line) )
        return line_comment;
    else
        return line_def;
};

note_type_enum get_next_token_note(string& token, string& line) {
/* Get next note token as well as its type from a line string. *
 * If no note is found, the resulting token is empty.
 * If note is found, the note will be cut off from the line string. 
 */
    regex e1, e2;
    e1 = regex("\\(.*\\)");
    e2 = regex("\\{.*\\}");
    
    smatch sm;
    regex_search(line, sm, e1);
    
    const int bracket_curly {1};
    const int bracket_round {0};
    int bracket_flag;
    
    int bracket_open, bracket_close;
    
    for ( int i=0; i < line.length(); i++ ) {
        if ( line[i] == '(' ) {
            bracket_flag = bracket_round;
            bracket_open = i;
            break;
        }
        if ( line[i] == '{' ) {
            bracket_flag = bracket_curly;
            bracket_open = i;
            break;
        }
    }
    
    if ( bracket_flag == bracket_round )
        for ( int i=0; i<line.length(); ++i )
            if ( line[i] == ')' ) {
                bracket_close = i;
                break;
            }
    if ( bracket_flag == bracket_curly )
        for ( int i=0; i<line.length(); ++i )
            if ( line[i] == '}' ) {
                bracket_close = i;
                break;
            }
    
    cout << bracket_open << " " << bracket_close << "\n";
    
    /*for (int i=0; i < line.length(); i++ ) {
        if ( line[i] == '(' || line[i] == '{' ) {
            bracket_open = i;
            if ( line[i] == '(' ) {
                for (int j=i; j < line.length(); j++ ) { 
                    if ( line[j] == ')' ) {
                        bracket_close = j;
                        break;
                    }
                }
            }
            else if ( line[i] == '{' ) {
                for (int j=i; j < line.length(); j++ ) { 
                    if ( line[j] == '}' ) {
                        bracket_close = j;
                        break;
                    }
                }
            }
            break;
        }
    }*/
    
    token = line.substr(bracket_open, bracket_close - bracket_open + 1);
    
    // cut off token from line
    line = line.substr(bracket_close+1);
    
    //TODO Continue here
    
};



/*******************************************************************/
/* Note reader */

MusicNote read_token_musicnote(string note_str) {
/* Read music note token */
    //TODO support different notation system
    
    boost::algorithm::erase_all(note_str, " ");
    string s1, s2, s3; // temp string
    regex e1;
    smatch sm;
    // search for note patern
    e1 = regex("([a-zA-Z][#|b]?[0-9]),([0-9]+/[0-9]+)(,\\[.*\\])?");
    regex_search(note_str, sm, e1);
    
    // normally, 4 matches will be found
    if (sm.size() == 4) {
        s1 = sm[1];
        s2 = sm[2];
        s3 = sm[3];
    }
    else {
        MusicNote n1 ("C4", "1/1");
        cerr << "Invalid note encountered!" << endl;
        return n1;
    }
    
    // if no match for ornament
    if ( s3 == "" ) {
        s1 = sm[1];
        s2 = sm[2];
        MusicNote n1 (s1, s2);
        return n1;
    }
    else {
        s1 = sm[1];
        s2 = sm[2];
        s3 = sm[3];
        s3 = s3.substr(1,s3.length()-1);
        MusicNote n1 (s1, s2);
        //TODO interpret the ornaments
        return n1;
    }
}

Rest read_token_restnote (string note_str) {
/* Read rest note token */
    
    boost::algorithm::erase_all(note_str, " ");
    string s1, s2; // temp string
    regex e1;
    smatch sm;
    // search for note patern
    e1 = regex("([r|R]est),([0-9]+/[0-9]+)");
    regex_search(note_str, sm, e1);
    
    // normally 3 matches will be found
    if (sm.size() == 3) {
        s1 = sm[1];
        s2 = sm[2];
        Rest n1 (s2);
        return n1;
    }
    else {
        Rest n1 ("1/1");
        cerr << "Invalid rest note encountered!" << endl;
        return n1;
    }
}

Blank read_token_blanknote(string note_str) {
/* Read blank token */
    
    boost::algorithm::erase_all(note_str, " ");
    string s1, s2; // temp string
    regex e1;
    smatch sm;
    // search for note patern
    e1 = regex("([b|B]lank),([0-9]+/[0-9]+)");
    regex_search(note_str, sm, e1);
    
    // normally 3 matches will be found
    if (sm.size() == 3) {
        s1 = sm[1];
        s2 = sm[2];
        Blank n1 (s2);
        return n1;
    }
    else {
        Blank n1 ("1/1");
        cerr << "Invalid rest note encountered!" << endl;
        return n1;
    }
}

NoteGroup read_token_notegroup(string note_str) {
/* Read notegroup token */
    
    boost::algorithm::erase_all(note_str, " ");
    string s0, s1, s2, s3; // temp string
    regex e1;
    smatch sm;
    // search for the first note
    e1 = regex("([a-zA-Z][#|b]?[0-9]),([0-9]+/[0-9]+)(,\\[.*\\])?");
    regex_search(note_str, sm, e1);
    
    s0 = sm[0];
    s1 = sm[1];
    s2 = sm[2];
    s3 = sm[3];
    if (s3 != "")
        s3 = s3.substr(1,s3.length()-1);
    
    MusicNote n1 (s1, s2);
    //TODO pass ornaments
    // s3 = ...
    NoteGroup ng1 (n1);
    // look for the next notes
    // s1.length()+3 because of ( , ) and {
    note_str = note_str.substr(s0.length()+3, note_str.length()-1);
    e1 = regex("[a-zA-Z][#|b]?[0-9]");
    regex_search(note_str, sm, e1);
    while (sm.size() != 0) {
        s1 = sm[0];
        // s1.length()+2 because of ( and )
        note_str = note_str.substr(s1.length()+2, note_str.length());
        regex_search(note_str, sm, e1);
        ng1.AddNote( MusicNote(s1) );
    }
    return ng1;
}

/*******************************************************************/
/* Parser... */

bool parse_defs(string line, hma_sheet &my_sheet) {
/* Parse property definitions (on the top of the annotation file) */

    regex exp_voice("@I[1-9]V[1-9]:");
    regex exp_def("@([a-zA-Z]*)");
    smatch sm;
    
    regex_search(line, sm, exp_voice);
    if ( sm.size() > 0 )
        return false;
    
    regex_search(line, sm, exp_def);
    if ( sm.size() == 0 )
        return false;
        
    string property_name = sm[0];
    string s; // temp string
    int n;    // temp number
    regex e1; // temp regex
    
    // get property name without @
    property_name = property_name.substr(1, property_name.length()-1);
    
    switch(property_hashit(property_name)) {
    
    case def_title:
        // extract the rest of the line
        line = line.substr(property_name.length()-1, line.length());
        // search the properties defined later
        e1 = regex("\"[a-zA-Z].*\"");
        regex_search(line, sm, e1);
        s = sm[0];
        my_sheet.title = s.substr(1,s.length()-2);
        break;
        
    case def_author:
        line = line.substr(property_name.length()-1, line.length());
        e1 = regex("\"[a-zA-Z].*\"");
        regex_search(line, sm, e1);
        s = sm[0];
        my_sheet.author = s.substr(1,s.length()-2);
        break;
        
    case def_ninstruments:
        line = line.substr(property_name.length()-1, line.length());
        // look for digits
        e1 = regex("[0-9]+");
        regex_search(line, sm, e1);
        // convert and save 
        my_sheet.ninstruments = stoi(sm[0]);
        break;
        
    case def_instrument:
        line = line.substr(property_name.length()-1, line.length());
        // search the No. of instrument
        e1 = regex("[0-9]+");
        regex_search(line, sm, e1);
        n = stoi(sm[0]);
        
        // search the name instrument
        e1 = regex("\"[a-zA-Z].*\"");
        regex_search(line, sm, e1);
        s = sm[0];
        s = s.substr(1,s.length()-2);
        // assign the intrument to the correct position
        while ( my_sheet.instruments.size() < n )
            my_sheet.instruments.push_back("");
        my_sheet.instruments[n-1] = s;
        
    case def_notationsys:
        line = line.substr(property_name.length()-1, line.length());
        e1 = regex("\"[a-zA-Z].*\"");
        regex_search(line, sm, e1);
        s = sm[0];
        my_sheet.notationsys = s.substr(1,s.length()-2);
        break;
        
    case def_tempo:
        line = line.substr(property_name.length()-1, line.length());
        e1 = regex("\"[a-zA-Z].*\"");
        regex_search(line, sm, e1);
        s = sm[0];
        my_sheet.tempo = s.substr(1,s.length()-2);
        break;
        
    case def_speed:
        line = line.substr(property_name.length()-1, line.length());
        // look for digits
        e1 = regex("[0-9]+");
        regex_search(line, sm, e1);
        // convert and save 
        my_sheet.speed = stoi(sm[0]);
        break;
        
    case def_meter:
        line = line.substr(property_name.length()-1, line.length());
        // search X/X pattern
        e1 = regex("\"[0-9]*//*[0-9]\"");
        regex_search(line, sm, e1);
        s = sm[0];
        s = s.substr(1,s.length()-2);
        my_sheet.meter[0] = s[0] - '0';
        my_sheet.meter[1] = s[s.length()-1] - '0';
        break;
        
    case def_nvoices:
        line = line.substr(property_name.length()-1, line.length());
        // look for digits
        e1 = regex("[0-9]+");
        regex_search(line, sm, e1);
        // convert and save 
        my_sheet.nvoices = stoi(sm[0]);
        break;
        
    case def_voice:
        line = line.substr(property_name.length()-1, line.length());
        // look digit pair
        e1 = regex("[0-9]+-[0-9]+");
        regex_search(line, sm, e1);
        // convert and save 
        s = sm[0];
        my_sheet.voices.push_back(s);
        
        // look for clef definition
        e1 = regex("-[a-zA-Z]");
        regex_search(line, sm, e1);
        // push to clef vector
        if ( sm[0] == "-C" )
            my_sheet.voice_clef[CLEF_UT].push_back(s);
        else if ( sm[0] == "-F" )
            my_sheet.voice_clef[CLEF_FA].push_back(s);
        else if ( sm[0] == "-G" )
            my_sheet.voice_clef[CLEF_SOL].push_back(s);
        else
            return false;
        
        break;
        
    case def_tonality:
        line = line.substr(property_name.length()-1, line.length());
        e1 = regex("\"[a-zA-Z].*\"");
        regex_search(line, sm, e1);
        s = sm[0];
        my_sheet.tempo = s.substr(1,s.length()-2);
        break;
        
    case def_fs:
        line = line.substr(property_name.length()-1, line.length());
        // look for digits
        e1 = regex("[0-9]+");
        regex_search(line, sm, e1);
        // convert and save 
        my_sheet.fs = stoi(sm[0]);
        break;
        
    case def_freq:
        line = line.substr(property_name.length()-1, line.length());
        // look for digits
        e1 = regex("[0-9]+");
        regex_search(line, sm, e1);
        // convert and save 
        my_sheet.freq = stoi(sm[0]);
        break;
        
    default:
        return false;
    }
    
    return true;
}

//TODO
void parse_bar(string barnbr) {};

