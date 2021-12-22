#pragma once
#include "base_types.hpp"

namespace hautbois 
{

const NoteNameIndexTable _SCI_NAME_NOTE_INDEX_TABLE {
    {"A0",  1},
    {"A#0", 2},
    {"Bb0", 2},
    {"B0",  3},
    {"B#0", 4},

    {"Cb1", 3},
    {"C1",  4},
    {"C#1", 5},
    {"Db1", 5},
    {"D1",  6},
    {"D#1", 7},
    {"Eb1", 7},
    {"E1",  8},
    {"E#1", 9},
    {"Fb1", 8},
    {"F1",  9},
    {"F#1", 10},
    {"Gb1", 10},
    {"G1",  11},
    {"G#1", 12},
    {"Ab1", 12},
    {"A1",  13},
    {"A#1", 14},
    {"Bb1", 14},
    {"B1",  15},
    {"B#1", 16},

    {"Cb2", 15},
    {"C2",  16},
    {"C#2", 17},
    {"Db2", 17},
    {"D2",  18},
    {"D#2", 19},
    {"Eb2", 19},
    {"E2",  20},
    {"E#2", 21},
    {"Fb2", 20},
    {"F2",  21},
    {"F#2", 22},
    {"Gb2", 22},
    {"G2",  23},
    {"G#2", 24},
    {"Ab2", 24},
    {"A2",  25},
    {"A#2", 26},
    {"Bb2", 26},
    {"B2",  27},
    {"B#2", 28},

    {"Cb3", 27},
    {"C3",  28},
    {"C#3", 29},
    {"Db3", 29},
    {"D3",  30},
    {"D#3", 31},
    {"Eb3", 31},
    {"E3",  32},
    {"E#3", 33},
    {"Fb3", 32},
    {"F3",  33},
    {"F#3", 34},
    {"Gb3", 34},
    {"G3",  35},
    {"G#3", 36},
    {"Ab3", 36},
    {"A3",  37},
    {"A#3", 38},
    {"Bb3", 38},
    {"B3",  39},
    {"B#3", 40},

    {"Cb4", 39},
    {"C4",  40},
    {"C#4", 41},
    {"Db4", 41},
    {"D4",  42},
    {"D#4", 43},
    {"Eb4", 43},
    {"E4",  44},
    {"E#4", 45},
    {"Fb4", 44},
    {"F4",  45},
    {"F#4", 46},
    {"Gb4", 46},
    {"G4",  47},
    {"G#4", 48},
    {"Ab4", 48},
    {"A4",  49},
    {"A#4", 50},
    {"Bb4", 50},
    {"B4",  51},
    {"B#4", 52},

    {"Cb5", 51},
    {"C5",  52},
    {"C#5", 53},
    {"Db5", 53},
    {"D5",  54},
    {"D#5", 55},
    {"Eb5", 55},
    {"E5",  56},
    {"E#5", 57},
    {"Fb5", 56},
    {"F5",  57},
    {"F#5", 58},
    {"Gb5", 58},
    {"G5",  59},
    {"G#5", 60},
    {"Ab5", 60},
    {"A5",  61},
    {"A#5", 62},
    {"Bb5", 62},
    {"B5",  63},
    {"B#5", 64},

    {"Cb6", 63},
    {"C6",  64},
    {"C#6", 65},
    {"Db6", 65},
    {"D6",  66},
    {"D#6", 67},
    {"Eb6", 67},
    {"E6",  68},
    {"E#6", 69},
    {"Fb6", 68},
    {"F6",  69},
    {"F#6", 70},
    {"Gb6", 70},
    {"G6",  71},
    {"G#6", 72},
    {"Ab6", 72},
    {"A6",  73},
    {"A#6", 74},
    {"Bb6", 74},
    {"B6",  75},
    {"B#6", 76},

    {"Cb6", 75},
    {"C7",  76},
    {"C#7", 77},
    {"Db7", 77},
    {"D7",  78},
    {"D#7", 79},
    {"Eb7", 79},
    {"E7",  80},
    {"E#7", 81},
    {"Fb7", 80},
    {"F7",  81},
    {"F#7", 82},
    {"Gb7", 82},
    {"G7",  83},
    {"G#7", 84},
    {"Ab7", 84},
    {"A7",  85},
    {"A#7", 86},
    {"Bb7", 86},
    {"B7",  87},
    {"B#7", 88},

    {"Cb8", 87},
    {"C8",  88}
};

const NoteIndexNameTable _NOTE_INDEX_SCI_NAME_TABLE {
/* Conversion from KeyIndex to NoteName: only # is allowed */
    {1,  "A0"},
    {2,  "A#0"},
    //{2, "Bb0"},
    {3, "B0"},

    {4, "C1"},
    {5, "C#1"},
    //{5, "Db1"},
    {6, "D1"},
    {7, "D#1"},
    //{7, "Eb1"},
    {8, "E1"},
    {9, "F1"},
    {10, "F#1"},
    //{10, "Gb1"},
    {11, "G1"},
    {12, "G#1"},
    //{12, "Ab1"},
    {13, "A1"},
    {14, "A#1"},
    //{14, "Bb1"},
    {15, "B1"},

    {16, "C2"},
    {17, "C#2"},
    //{17, "Db2"},
    {18, "D2"},
    {19, "D#2"},
    //{19, "Eb2"},
    {20, "E2"},
    {21, "F2"},
    {22, "F#2"},
    //{22, "Gb2"},
    {23, "G2"},
    {24, "G#2"},
    //{24, "Ab2"},
    {25, "A2"},
    {26, "A#2"},
    //{26, "Bb2"},
    {27, "B2"},

    {28, "C3"},
    {29, "C#3"},
    //{29, "Db3"},
    {30, "D3"},
    {31, "D#3"},
    //{31, "Eb3"},
    {32, "E3"},
    {33, "F3"},
    {34, "F#3"},
    //{34, "Gb3"},
    {35, "G3"},
    {36, "G#3"},
    //{36, "Ab3"},
    {37, "A3"},
    {38, "A#3"},
    //{38, "Bb3"},
    {39, "B3"},

    {40, "C4"},
    {41, "C#4"},
    //{41, "Db4"},
    {42, "D4"},
    {43, "D#4"},
    //{43, "Eb4"},
    {44, "E4"},
    {45, "F4"},
    {46, "F#4"},
    //{46, "Gb4"},
    {47, "G4"},
    {48, "G#4"},
    //{48, "Ab4"},
    {49, "A4"},
    {50, "A#4"},
    //{50, "Bb4"},
    {51, "B4"},

    {52, "C5"},
    {53, "C#5"},
    //{53, "Db5"},
    {54, "D5"},
    {55, "D#5"},
    //{55, "Eb5"},
    {56, "E5"},
    {57, "F5"},
    {58, "F#5"},
    //{58, "Gb5"},
    {59, "G5"},
    {60, "G#5"},
    //{60, "Ab5"},
    {61, "A5"},
    {62, "A#5"},
    //{62, "Bb5"},
    {63, "B5"},

    {64, "C6"},
    {65, "C#6"},
    //{65, "Db6"},
    {66, "D6"},
    {67, "D#6"},
    //{67, "Eb6"},
    {68, "E6"},
    {69, "F6"},
    {70, "F#6"},
    //{70, "Gb6"},
    {71, "G6"},
    {72, "G#6"},
    //{72, "Ab6"},
    {73, "A6"},
    {74, "A#6"},
    //{74, "Bb6"},
    {75, "B6"},

    {76, "C7"},
    {77, "C#7"},
    //{77, "Db7"},
    {78, "D7"},
    {79, "D#7"},
    //{79, "Eb7"},
    {80, "E7"},
    {81, "F7"},
    {82, "F#7"},
    //{82, "Gb7"}
    {83, "G7"},
    {84, "G#7"},
    //{84, "Ab7"},
    {85, "A7"},
    {86, "A#7"},
    //{86, "Bb7"},
    {87, "B7"},

    {88, "C8"}
};

#ifdef _ENABLE_ALL_NOTATION_SYS
const NoteNameIndexTable _LATIN_NAME_NOTE_INDEX_TABLE {
    {"ut0",  4},
    {"do0",  4},
    {"ut0#", 5},
    {"do0#", 5},
    {"re0b", 5},
    {"re0",  6},
    {"re0#", 7},
    {"mi0b", 7},
    {"mi0",  8},
    {"fa0",  9},
    {"fa0#", 10},
    {"sol0b",10},
    {"sol0", 11},
    {"sol0#",12},
    {"la0b", 12},
    {"la0",  13},
    {"la0#", 14},
    {"si0b", 14},
    {"si0",  15},

    {"ut1",  16},
    {"do1",  16},
    {"ut1#", 17},
    {"do1#", 17},
    {"re1b", 17},
    {"re1",  18},
    {"re1#", 19},
    {"mi1b", 19},
    {"mi1",  20},
    {"fa1",  21},
    {"fa1#", 22},
    {"sol1b",22},
    {"sol1", 23},
    {"sol1#",24},
    {"la1b", 24},
    {"la1",  25},
    {"la1#", 26},
    {"si1b", 26},
    {"si1",  27},

    {"ut2",  28},
    {"do2",  28},
    {"ut2#", 29},
    {"do2#", 29},
    {"re2b", 29},
    {"re2",  30},
    {"re2#", 31},
    {"mi2b", 31},
    {"mi2",  32},
    {"fa2",  33},
    {"fa2#", 34},
    {"sol2b",34},
    {"sol2", 35},
    {"sol2#",36},
    {"la2b", 36},
    {"la2",  37},
    {"la2#", 38},
    {"si2b", 38},
    {"si2",  39},

    {"ut3",  40},
    {"do3",  40},
    {"ut3#", 41},
    {"do3#", 41},
    {"re3b", 41},
    {"re3",  42},
    {"re3#", 43},
    {"mi3b", 43},
    {"mi3",  44},
    {"fa3",  45},
    {"fa3#", 46},
    {"sol3b",46},
    {"sol3", 47},
    {"sol3#",48},
    {"la3b", 48},
    {"la3",  49},
    {"la3#", 50},
    {"si3b", 50},
    {"si3",  51},

    {"ut4",  52},
    {"do4",  52},
    {"ut4#", 53},
    {"do4#", 53},
    {"re4b", 53},
    {"re4",  54},
    {"re4#", 55},
    {"mi4b", 55},
    {"mi4",  56},
    {"fa4",  57},
    {"fa4#", 58},
    {"sol4b",58},
    {"sol4", 59},
    {"sol4#",60},
    {"la4b", 60},
    {"la4",  61},
    {"la4#", 62},
    {"si4b", 62},
    {"si4",  63},

    {"ut5",  64},
    {"do5",  64},
    {"ut5#", 65},
    {"do5#", 65},
    {"re5b", 65},
    {"re5",  66},
    {"re5#", 67},
    {"mi5b", 67},
    {"mi5",  68},
    {"fa5",  69},
    {"fa5#", 70},
    {"sol5b",70},
    {"sol5", 71},
    {"sol5#",72},
    {"la5b", 72},
    {"la5",  73},
    {"la5#", 74},
    {"si5b", 74},
    {"si5",  75},

    {"ut6",  76},
    {"do6",  76},
    {"ut6#", 77},
    {"do6#", 77},
    {"re6b", 77},
    {"re6",  78},
    {"re6#", 79},
    {"mi6b", 79},
    {"mi6",  80},
    {"fa6",  81},
    {"fa6#", 82},
    {"sol6b",82},
    {"sol6", 83},
    {"sol6#",84},
    {"la6b", 84},
    {"la6",  85},
    {"la6#", 86},
    {"si6b", 86},
    {"si6",  87},

    {"ut7",  88},
    {"do7",  88}
};

const NoteIndexNameTable _NOTE_INDEX_LATIN_NAME_TABLE {
    {4,  "ut0" },
    {5,  "ut0#"},
    {6,  "re0" },
    {7,  "re0#"},
    {8,  "mi0" },
    {9,  "fa0" },
    {10, "fa0#"},
    {11, "sol0"},
    {12, "sol0#"},
    {13, "la0" },
    {14, "la0#"},
    {15, "si0" },

    {16, "ut1" },
    {17, "ut1#"},
    {18, "re1" },
    {19, "re1#"},
    {20, "mi1" },
    {21, "fa1" },
    {22, "fa1#"},
    {23, "sol1"},
    {24, "sol1#"},
    {25, "la1" },
    {26, "la1#"},
    {27, "si1" },

    {28, "ut2" },
    {29, "ut2#"},
    {30, "re2" },
    {31, "re2#"},
    {32, "mi2" },
    {33, "fa2" },
    {34, "fa2#"},
    {35, "sol2"},
    {36, "sol2#"},
    {37, "la2" },
    {38, "la2#"},
    {39, "si2" },

    {40, "ut3" },
    {41, "ut3#"},
    {42, "re3" },
    {43, "re3#"},
    {44, "mi3" },
    {45, "fa3" },
    {46, "fa3#"},
    {47, "sol3"},
    {48, "sol3#"},
    {49, "la3" },
    {50, "la3#"},
    {51, "si3" },

    {52, "ut4" },
    {53, "ut4#"},
    {54, "re4" },
    {55, "re4#"},
    {56, "mi4" },
    {57, "fa4" },
    {58, "fa4#"},
    {59, "sol4"},
    {60, "sol4#"},
    {61, "la4" },
    {62, "la4#"},
    {63, "si4" },

    {64, "ut5" },
    {65, "ut5#"},
    {66, "re5" },
    {67, "re5#"},
    {68, "mi5" },
    {69, "fa5" },
    {70, "fa5#"},
    {71, "sol5"},
    {72, "sol5#"},
    {73, "la5" },
    {74, "la5#"},
    {75, "si5" },

    {76, "ut6" },
    {77, "ut6#"},
    {78, "re6" },
    {79, "re6#"},
    {80, "mi6" },
    {81, "fa6" },
    {82, "fa6#"},
    {83, "sol6"},
    {84, "sol6#"},
    {85, "la6" },
    {86, "la6#"},
    {87, "si6" },

    {88, "ut7" }
};
#endif

}
