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
    
    // test modulation
    cout << n4.PrintNote() << endl;
    Note* n6 = n4.Modulation(+1);
    if ( n6->GetNoteType() == music_note_ )
        cout << n6->PrintNote() << endl;
    else
        cout << "Type incorrect" << endl;
    cout << n4.PrintNote() << endl;
    
    cout << ng1.PrintNoteGroup() << endl;
    Note* ng2 = ng1.Modulation(+1);
    if ( ng2->GetNoteType() == note_group_ )
        cout << ng2->PrintNoteGroup() << endl;
    else
        cout << "Type incorrect" << endl;
    cout << ng1.PrintNoteGroup() << endl;
    
    /*
    // test conversion
    cout << n1.Index2SciName_alt(n1.GetNoteIndex()) << endl;
    cout << n2.Index2SciName_alt(n2.GetNoteIndex()) << endl;
    cout << n3.Index2SciName_alt(n3.GetNoteIndex()) << endl;
    cout << n4.Index2SciName_alt(n4.GetNoteIndex()) << endl;
    cout << n5.Index2SciName_alt(n5.GetNoteIndex()) << endl;
    */
    return 0;
}

