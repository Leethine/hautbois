#include "../src/notation/notation.hpp"
#include <iostream>
#include <typeinfo>

using namespace hautbois; 
using namespace std;

int main() {
    OneBarInterface b1;
    
    /*
    b1.appendRestNote({1,4});
    b1.appendSingleNote("C4", {1,4});
    b1.appendGroupNote({"C4", "E4", "G4"}, {{1,4},{1,4},{1,4}});
    b1.appendGroupNote({"D4", "F#4", "A4"}, {1,4});
    cout << boolalpha << b1.checkBarComplete() << endl;
    */
    
    /*
    ParserUtl b2;
    cout << b2.rmSpace(string("1/ 2")) << "\n";
    cout << b2.readDurationFromStr(string("1/16")) << "\n";
    cout << b2.deBracket("C4,1/2") << "\n";
    cout << b2.deBracket("{(C4,1/2)}") << "\n";
    cout << b2.deBracket("{(C4,1/2),(E4,1/2)}") << "\n";
    cout << b2.rmBracket("{(C4,1/2),(E4,1/2)}") << "\n";
    
    cout << b2.splitToken("(C4,1/2)", ",")[0] << "\n";
    */

   //b1.tokenAddGroupNote("{(C4,1/4)(E4)(G4)}");
   //b1.tokenAddGroupNote("{(C4,1/4)(E4,1/8)(G4,1/16)}");

    b1.addNote("(C4,1/4)");
    b1.addNote("{(C4,1/4)(E4,1/8)(G4,1/16)}");
    b1.addNote("(r, 1/4)");
    b1.addNote("{(C4,1/4)(E4)(G4)}");
    
    cout << b1 << "\n";
    cout << "Object size: " << sizeof(b1) << "\n";

    OneBarInterface b2;
    b2.addNote("(C4,1/8)");
    b2.addNote("(C#4,1/8)");
    b2.addNote("(r, 1/8)");
    b2.addNote("(rest, 1/8)");
    b2.addNote("{(C#4,1/8)(Eb4,1/8)}");
    b2.addNote("{(C#4,1/8)(Eb4,1/8)(G#4,1/16)}");
    b2.addNote("{(C#4,1/8)(Eb4,1/8)(G#4,1/16)(Bb4,1/32)}");
    b2.addNote("{(C#4,1/8)(Eb4,1/8)(G#4,1/16)(Bb4,1/32)}");
    
    cout << b2 << "\n";
    cout << "Bar Object size: " << sizeof(b2) << "\n";
    for (int i = 0; i < 8; ++i) {
        AnyNote& n1 = b2.getNthNote(i);
        cout << "Note Object size: " << sizeof(n1) << "\n";
    }
    

    b1.addNote("(r, 1/4)");

}
