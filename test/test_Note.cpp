#include <iostream>
#include "../src/notation/note.hpp"

using namespace std;

int main(void) 
{
    MusicNote n1("A5", "2/4");
    MusicNote n2("C#6", "2/4");
    MusicNote n3("E6", "2/4");
    MusicNote n4("C7#", "2/4");
    MusicNote n5("Eb4", "2/4");
    
    NoteGroup ng1 (n1,n2,n3,n4);
    
    cout << n1.PrintNote() << endl;
    cout << ng1.PrintNoteGroup() << endl;
    
    cout << n1.Index2SciName_alt(n1.GetNoteIndex()) << endl;
    cout << n2.Index2SciName_alt(n2.GetNoteIndex()) << endl;
    cout << n3.Index2SciName_alt(n3.GetNoteIndex()) << endl;
    cout << n4.Index2SciName_alt(n4.GetNoteIndex()) << endl;
    cout << n5.Index2SciName_alt(n5.GetNoteIndex()) << endl;
    return 0;
}

