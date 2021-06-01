#include <iostream>
#include <string>
#include "note.hpp"

using namespace std;
int main()
{
    Note n1 ("A5", "1/4");
    cout << n1.Name << endl;
    cout << n1.NoteIndex << endl;
    
    return 0;
}
