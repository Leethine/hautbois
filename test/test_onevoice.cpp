#include "../src/notation/notation.hpp"
#include <iostream>
#include <typeinfo>

using namespace hautbois; 
using namespace std;

int main() {

    /*
    OneBarFacade b1;
    b1.addNote("(C4, 1/8, [force:pp], <appoggiatura>)");
    b1.addNote("(C4, 1/8, <appoggiatura>)");
    b1.addNote("{(C4,1/8,[force:ff],<trillo:3>)(E4,1/8)(G4,1/16)}");
    b1.addNote("{(C4,1/8)(E4)(G4)}");
    b1.addNote("(r, 1/4)");
    b1.addNote("{(C4,1/4)(E4)(G4)}");
    cout << b1 << "\n";
    cout << "Is complete? " << boolalpha << b1.checkBarComplete() << "\n";
    */
    
    OneVoice voice1( "Cm", {4,4} );
    voice1.setInstrument(InstrumentType::LIUTO);
    
    voice1.addNote("(C4, 1/8, [force:pp], <appoggiatura>)");
    voice1.addNote("(C4, 1/8, <appoggiatura>)");
    voice1.addNote("{(C4,1/8,[force:ff],<trillo:3>)(E4,1/8)(G4,1/16)}");
    voice1.addNote("{(C4,1/8)(E4)(G4)}");
    voice1.addNote("(r, 1/4)");
    voice1.addNote("{(C4,1/4)(E4)(G4)}");
    
    voice1.showBars();
    
    // Add again another bar
    voice1.addNote("(C2, 1/8, [force:pp], <appoggiatura>)");
    voice1.addNote("(C2, 1/8, <appoggiatura>)");
    voice1.addNote("{(C2,1/8,[force:ff],<trillo:3>)(E2,1/8)(G2,1/16)}");
    voice1.addNote("{(C2,1/8)(E2)(G2)}");
    voice1.addNote("(r, 1/4)");
    voice1.addNote("{(C2,1/4)(E2)(G2)}");
    
    voice1.showBars();
    
    //while(1) {}
}

