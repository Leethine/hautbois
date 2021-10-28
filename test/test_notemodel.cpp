#include <map>
#include <iostream>
#include <string>
#include "../src/notation/notation.hpp"

#include <exception>

using namespace std;
using namespace hautbois;

int main() {
    
    Duration d {1,4};
    Duration d2;
    d2 = Duration(d);

    cout << d2 << endl;

    // constructor test 1
    AnyNote a(NoteType::SingleNote, SCI_NAME_INDEX, "C5", 1, 2);
    // constructor test 2
    AnyNote b(NoteType::GroupNote, SCI_NAME_INDEX, {"C5","E5","G5"}, {{1,2},{1,2},{1,4}});
    // constructor test 3
    AnyNote c(NoteType::GroupNote, SCI_NAME_INDEX, {"D5","F5","A5"}, {{1,2},{1,2},{1,2}});
    
    // << operator test 1 
    cout << a << "\n";
    // << operator test 2
    cout << b << "\n";
    // << operator test 3
    cout << c << "\n";
    
    // << operator and group duration constructor test 4
    cout << b.getDuration() << "\n";
    // << operator and group duration constructor test 5
    cout << c.getDuration() << "\n";
    
    // == operator test 1
    AnyNote e(NoteType::SingleNote, SCI_NAME_INDEX, "C5", 1, 1);
    cout << boolalpha << (e == a) << "\n" ;
    // == operator test 2
    cout << boolalpha << (b == c) << "\n" ;
    // == operator test 3
    AnyNote f(NoteType::GroupNote, SCI_NAME_INDEX, {"C5","E5","G5"}, {{1,2},{1,2},{1,4}});
    cout << boolalpha << (f == c) << "\n" ;
    
    // exception handling test 1
    AnyNote g(NoteType::SingleNote, SCI_NAME_INDEX, "dfr2", 1, 2);
    cout << g << "\n";

}
