// RestNote: ("r", "Num / Denom")
// RestNote: ("R", "Num / Denom")
// RestNote: ("p", "Num / Denom")
// RestNote: ("P", "Num / Denom")
// RestNote: ("rest", "Num / Denom")
// RestNote: ("Rest", "Num / Denom")

// SingleNote: ("Note", "Num / Denom")
// SingleNote: ("Note", "Num / Denom", ["Property1": "Value1", ...])
// SingleNote: ("Note", "Num / Denom", ["Property1": "Value1", ...], ["Ornament": "Value"])

// GroupNote: {SingleNote, SingleNote, ...}

#include "barline.hpp"

using namespace hautbois;
using namespace std;

namespace MyTest {

bool checkFormatting(ParserUtl& p, NoteType type, const TokenString& token_ns) {

    std::regex rx { "\\([C|D|E|F|G|A|B][#|b]?[0-7],[0-9]+/[1-9]+\\)"s };
    //std::smatch sm;
    if ( std::regex_match(token_ns, rx) )
        return true;
    else 
        return false;
}

}

int main() {
    ParserUtl p;

    TokenString s1 = "(C4, 1/2)";
    TokenString s2 = "(R, 1/2)";
    TokenString s3 = "(r, 1/2)";
    TokenString s4 = "(rest, 1/4)";
    TokenString s5 = "(rest, 1/8)";

    cout <<  boolalpha << s1 << " " << MyTest::checkFormatting(p, p.checkType(s1), s1) << "\n";
}