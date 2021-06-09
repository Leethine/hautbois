#include <iostream>
#include "../src/notation/bar.hpp"

using namespace std;

// TEST THE OBJECT
int main()
{
    MusicNote n1 ("C4", "1/4");
    MusicNote n2 ("E4", "1/4");
    NoteGroup n3 (n1, n2);
    NoteGroup n4 (MusicNote("G4", "1/2"), MusicNote("C4", "1/2"), 
                  MusicNote("E4", "1/2"), MusicNote("B4", "1/2"));
    
    Bar bar1;
    bar1.AddNote(n1);
    bar1.AddNote(n2);
    bar1.AddNote(MusicNote("G4", "1/2"));
    bar1.AddNote(n3);
    bar1.AddNote(Rest("1/4"));
    bar1.AddNote(n4);
    bar1.PrintBar();
    
    Bar bar2 ("G-clef", "G#");
    Bar bar3 ("G-clef", "D#");
    Bar bar4 ("G-clef", "D");
    Bar bar5 ("G-clef", "F");

    cout << "Scale Index: " << bar2.Scale2Index(bar2.Scale) << endl; 
    cout << "Scale Index: " << bar3.Scale2Index(bar3.Scale) << endl; 
    cout << "Scale Index: " << bar4.Scale2Index(bar4.Scale) << endl; 
    cout << "Scale Index: " << bar5.Scale2Index(bar5.Scale) << endl; 
    return 0;

}
