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
    
    //cout << b1.rmSpace(string("1/ 2"));
    cout << b1.readDurationFromStr(string("1/16"));
}
