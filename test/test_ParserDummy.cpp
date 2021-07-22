#include <iostream>
#include <string>
#include "../src/interp/hma_parser_dummy.hpp"

using namespace std;

int main(void) {
    hma_sheet sheet;
    /*
    string l1 = "@I2V2: | | | |;";
    string l2 = "@title    \"Sonata No.5\"";
    string l3 = "@instrument     1 \"Recorder\"";
    string l4 = "@ninstruments   24";
    string l5 = "@meter          \"2/4\"";
    string l6 = "@instrument     2 \"Luth\"";
    string l7 = "@voice          2-2 \"Clef-F\"";
    parse_defs(l1, sheet);
    parse_defs(l2, sheet);
    parse_defs(l3, sheet);
    parse_defs(l4, sheet);
    parse_defs(l5, sheet);
    parse_defs(l6, sheet);
    parse_defs(l7, sheet);
    //cout << sheet.voice_clef[1][0] << endl;
    
    read_token_musicnote("(C#4, 1/2, [\"trill\":10])");
    read_token_restnote("(rest, 1/2)");
    read_token_blanknote("(blank, 6/1)");
    read_token_notegroup("{(G3,1/8)(B3)(D4)(G4)(D#4)(Ab3)}");
    */
    
    ifstream ifs;
    ifs.open("../sample/sample_annotation.hma", ifstream::in);
    string l;
    while( !ifs.eof() ) {
        get_next_line(l,ifs);
        cout << l << endl;
    }
    
    ifs.close();
    return 0;
}
