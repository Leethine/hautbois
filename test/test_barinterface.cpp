#include "../src/notation/Interface/barline.hpp"
#include <iostream>

using namespace hautbois; 
using namespace std;

int main() {
    BarLine b1;
    
    /*
    b1.appendRestNote({1,4});
    b1.appendSingleNote("C4", {1,4});
    b1.appendGroupNote({"C4", "E4", "G4"}, {{1,4},{1,4},{1,4}});
    b1.appendGroupNote({"D4", "F#4", "A4"}, {1,4});
    cout << boolalpha << b1.checkBarComplete() << endl;
    */
    
    ParserUtl b2;
    cout << b2.rmSpace(string("1/ 2")) << "\n";
    cout << b2.readDurationFromStr(string("1/16")) << "\n";
    cout << b2.deBracket("(\"C4\",\"1/2\")") << "\n";
    cout << b2.deBracket("{(\"C4\",\"1/2\")}") << "\n";
    cout << b2.deBracket("{(\"C4\",\"1/2\"),(\"E4\",\"1/2\")}") << "\n";
    cout << b2.rmBracket("{(\"C4\",\"1/2\"),(\"E4\",\"1/2\")}") << "\n";
    
}
