#include <iostream>
#include "../src/notation/notation.hpp"

using namespace hautbois;
using namespace std;

int main() {
    OneBar bar1;
    bar1.appendRestNote({1,4});
    bar1.appendSingleNote("C4", {1,4});
    bar1.appendGroupNote({"C4", "E4", "G4"}, {{1,4},{1,4},{1,4}});
    bar1.appendGroupNote({"D4", "F#4", "A4"}, {1,4});
    AnyNote& n0 = bar1.getNthNote(0);
    AnyNote& n1 = bar1.getNthNote(1);
    AnyNote& n2 = bar1.getNthNote(2);
    AnyNote& n3 = bar1.getNthNote(3);
    
    cout << n0 << " " << n1 << " " << n2 << " " << n3 << "\n";
    
    cout << bar1.printBarLine() << "\n";
    //AnyNote& n5 = n0.duplicate();
    bar1.tied = true;
    
    cout << bar1.printBarLine() << "\n";
    
    bar1.appendGroupNote({"D6", "F#6", "A6"}, {1,4});
    
    //bar1.printNthNote(0);
}
