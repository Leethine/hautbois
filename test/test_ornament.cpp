#include "../src/notation/notation.hpp"
#include <iostream>
#include <typeinfo>

using namespace hautbois; 
using namespace std;

int main() {

    OneBarFacade b1;
    b1.setInstrument(InstrumentType::LIUTO);
    b1.addNote("(C4, 1/8, [force:pp], <appoggiatura>)");
    b1.addNote("(C4, 1/8, <appoggiatura>)");
    //b1.addNote("(C4, 1/8, <appoggiatura>, [force:pp])");
    //cout << "success" << "\n";
    b1.addNote("{(C4,1/8,[force:ff],<trillo:3>)(E4,1/8)(G4,1/16)}");
    //cout << "success" << "\n";
    b1.addNote("(r, 1/4)");
    //cout << "success" << "\n";
    b1.addNote("{(C4,1/4)(E4)(G4)}");
    //cout << "success" << "\n";
    cout << b1 << "\n";

    AnyNote& n1 = b1.getNthNote(0);
    AnyNote& n2 = b1.getNthNote(1);
    AnyNote& n3 = b1.getNthNote(2);
    AnyNote& n4 = b1.getNthNote(3);
    /*
    auto p1 = n1.property.get();
    auto p2 = n2.property.get();
    
    cout << p1.entries["force"] << "\n";
    cout << p2.entries["force"] << "\n";
    
    if ( ! n3.property.is_initialized() ) {
        cout << "none" << "\n";
    }
    */
    cout << n1.getProperty("force") << "\n";
    cout << n2.getProperty("force") << "\n";
    cout << n3.getProperty("force") << "\n";
    cout << n4.getProperty("force") << "\n";

    cout << n1.getOrnament() << "\n";
    cout << n2.getOrnament() << "\n";
    cout << n3.getOrnament() << "\n";
    cout << n4.getOrnament() << "\n";

}

