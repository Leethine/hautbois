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

    std::regex rx;
    switch (type)
    {
    case NoteType::RestNote:
        rx = std::regex(RXPTN_RESTNOTE);
        break;
    case NoteType::SingleNote:
        rx = std::regex(RXPTN_SINGLENOTE);
        break;
    case NoteType::GroupNote:
        rx = std::regex(RXPTN_CHORD);
        break;
    default:
        break;
    }

    if ( std::regex_match(token_ns, rx) )
        return true;
    else 
        return false;
}
}

int main() {
    ParserUtl p;

    TokenString s1 = "(C4,1/2)";
    TokenString s2 = "(R,1/2)";
    TokenString s3 = "(r,1/2)";
    TokenString s4 = "(rest,1/4)";
    TokenString s5 = "(Rest,1/8)";
    TokenString s6 = "(E#5,1/16)";
    TokenString s7 = "(Bb5,1/32)";
    TokenString s8 = "{(Gb5,1/16)(E#5,1/16)(Bb5,1/32)}";
    TokenString s9 = "{(Gb5,1/16)(E#5)(Bb5)}";
    
    cout <<  boolalpha << s1 << " " << MyTest::checkFormatting(p, p.checkType(s1), s1) << "\n";
    cout <<  boolalpha << s2 << " " << MyTest::checkFormatting(p, p.checkType(s2), s2) << "\n";
    cout <<  boolalpha << s3 << " " << MyTest::checkFormatting(p, p.checkType(s3), s3) << "\n";
    cout <<  boolalpha << s4 << " " << MyTest::checkFormatting(p, p.checkType(s4), s4) << "\n";
    cout <<  boolalpha << s5 << " " << MyTest::checkFormatting(p, p.checkType(s5), s5) << "\n";
    cout <<  boolalpha << s6 << " " << MyTest::checkFormatting(p, p.checkType(s6), s7) << "\n";
    cout <<  boolalpha << s7 << " " << MyTest::checkFormatting(p, p.checkType(s7), s7) << "\n";
    cout <<  boolalpha << s8 << " " << MyTest::checkFormatting(p, p.checkType(s8), s8) << "\n";
    cout <<  boolalpha << s9 << " " << MyTest::checkFormatting(p, p.checkType(s9), s9) << "\n";
}