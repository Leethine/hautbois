#include "../src/notation/notation.hpp"
#include <iostream>
#include <typeinfo>

using namespace hautbois; 
using namespace std;

int main() {

    // create a 4-voiced sheet
    BasicSheet sheet1(4);
    
    // Should at least set Scale and Meter
    sheet1.setScale("Cm");
    sheet1.setMeter("4/4");
    sheet1.initializeSheet();
    
    OneVoice& v1 = sheet1.getVoiceN(0);
    OneVoice& v2 = sheet1.getVoiceN(1);
    OneVoice& v3 = sheet1.getVoiceN(2);
    OneVoice& v4 = sheet1.getVoiceN(3);

    v1.addNote("(C4, 1/8, [force:pp], <appoggiatura>)");
    v1.addNote("(C4, 1/8, <appoggiatura>)");
    v1.addNote("{(C4,1/8,[force:ff],<trillo:3>)(E4,1/8)(G4,1/16)}");
    v1.addNote("{(C4,1/8)(E4)(G4)}");
    v1.addNote("(r, 1/4)");
    v1.addNote("{(C4,1/4)(E4)(G4)}");
    
    v2.addNote("(C2, 1/8, [force:pp], <appoggiatura>)");
    v2.addNote("(C2, 1/8, <appoggiatura>)");
    v2.addNote("{(C2,1/8,[force:ff],<trillo:3>)(E2,1/8)(G2,1/16)}");
    v2.addNote("{(C2,1/8)(E2)(G2)}");
    v2.addNote("(r, 1/4)");
    v2.addNote("{(C2,1/4)(E2)(G2)}");
    v2.addNote("(C2, 1/8, [force:pp], <appoggiatura>)");
    v2.addNote("(C2, 1/8, <appoggiatura>)");
    v2.addNote("{(C2,1/8,[force:ff],<trillo:3>)(E2,1/8)(G2,1/16)}");
    v2.addNote("{(C2,1/8)(E2)(G2)}");
    v2.addNote("(r, 1/4)");
    v2.addNote("{(C2,1/4)(E2)(G2)}");
    
    v1.showBars();
    v2.showBars();
}

