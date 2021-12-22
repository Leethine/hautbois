#include "note_facade.hpp"

using namespace hautbois;

int main() {
/*
    OneNote * n1 = note_creator_utils::newOneNote("rest","1/4");
    OneNote * n2 = note_creator_utils::newOneNote("C#4","1/4");
    OneNote * n3 = note_creator_utils::newOneNote("C#4+E#4","1/4");
    OneNote * n4 = note_creator_utils::newOneNote("D5-E5-D5","1/2");
    OneNote * n5 = note_creator_utils::newOneNote("C#4+E#4+G5","1/4+1/4+1/8");
    
    std::cout << n1->printNote() << "\n";
    std::cout << n2->printNote() << "\n";
    std::cout << n3->printNote() << "\n";
    std::cout << n4->printNote() << "\n";
    std::cout << n5->printNote() << "\n";
    
    std::unique_ptr<OneNote> ptr1 = note_creator_utils::newOneNote("C#4+E#4+G5","1/4+1/4+1/8");
*/
    Note n1 ("rest","1/4");
    Note n2 ("C#4","1/4");
    Note n3 ("C#4+E#4","1/4");
    Note n4 ("D5-E5-D5","1/2");
    Note n5 ("C#4+E#4+G5","1/4+1/4+1/8");
    std::cout << n1.printNote() << "\n";
    std::cout << n2.printNote() << "\n";
    std::cout << n3.printNote() << "\n";
    std::cout << n5.printNote() << "\n";
    std::cout << n4.printNote() << "\n";
    return 0;
}
