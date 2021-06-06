#include <iostream>
#include "../src/notation/note.hpp"

using namespace std;

int main(void) 
{
    MusicNote n1("A5", "2/4");
    MusicNote n2("C6#", "2/4");
    MusicNote n3("E6", "2/4");
    MusicNote n4("C7#", "2/4");
    
    NoteGroup ng1 (n1,n2,n3,n4);
    
    cout << n1.PrintNote() << endl;
    cout << ng1.PrintNoteGroup() << endl;
    
    
    return 0;
}

