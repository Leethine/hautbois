#include "../src/notation/notation.hpp"
#include <iostream>
#include <typeinfo>

using namespace hautbois; 
using namespace std;

int main() {

    OneBarInterface b1;
    b1.instrument = InstrumentType::LIUTO;
    b1.addNote("(C4, 1/4, [force:pp])");
    //cout << "success" << "\n";
    b1.addNote("{(C4,1/4,[force:pp])(E4,1/8)(G4,1/16)}");
    //cout << "success" << "\n";
    b1.addNote("(r, 1/4)");
    //cout << "success" << "\n";
    b1.addNote("{(C4,1/4)(E4)(G4)}");
    //cout << "success" << "\n";
    cout << b1 << "\n";
    /*
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
    */
}
