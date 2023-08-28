#include "sci_notename_to_index.hpp"
#include "chart_def_types.hpp"

const hautbois::core::notename_str_index_table::StringToIndexMap hautbois::core::notename_str_index_table::SCINAME_STRING_TO_INDEX {
  {"REST", REST_NOTE_INDEX},
  {"SILENCE", SILENCE_NOTE_INDEX},
  {"R", REST_NOTE_INDEX},
  {"S", SILENCE_NOTE_INDEX},
  {"CHORD", CHORD_INDEX},
  {"CH", CHORD_INDEX},

  {"A0",  1},
  {"A#0", 2},
  {"Ax0", 3},
  {"Bbb0",1},
  {"Bb0", 2},
  {"B0",  3},
  {"B#0", 4},
  {"Bx0", 5},

  {"Cbb1",2},
  {"Cb1", 3},
  {"C1",  4},
  {"C#1", 5},
  {"Cx1", 6},
  {"Dbb1",4},
  {"Db1", 5},
  {"D1",  6},
  {"D#1", 7},
  {"Dx1", 8},
  {"Ebb1",6},
  {"Eb1", 7},
  {"E1",  8},
  {"E#1", 9},
  {"Ex1", 10},
  {"Fbb1",7},
  {"Fb1", 8},
  {"F1",  9},
  {"F#1", 10},
  {"Fx1", 11},
  {"Gbb1",9},
  {"Gb1", 10},
  {"G1",  11},
  {"G#1", 12},
  {"Gx1", 13},
  {"Abb1",11},
  {"Ab1", 12},
  {"A1",  13},
  {"A#1", 14},
  {"Ax1", 15},
  {"Bbb1",13},
  {"Bb1", 14},
  {"B1",  15},
  {"B#1", 16},
  {"Bx1", 17},

  {"Cbb2",14},
  {"Cb2", 15}, 
  {"C2",  16},  
  {"C#2", 17}, 
  {"Cx2", 18}, 
  {"Dbb2",16},
  {"Db2", 17}, 
  {"D2",  18},  
  {"D#2", 19}, 
  {"Dx2", 20}, 
  {"Ebb2",18},
  {"Eb2", 19},
  {"E2",  20},
  {"E#2", 21},
  {"Ex2", 22},
  {"Fbb2",19},
  {"Fb2", 20},
  {"F2",  21},
  {"F#2", 22},
  {"Fx2", 23},
  {"Gbb2",21},
  {"Gb2", 22},
  {"G2",  23},
  {"G#2", 24},
  {"Gx2", 25},
  {"Abb2",23},
  {"Ab2", 24},
  {"A2",  25},
  {"A#2", 26},
  {"Ax2", 27},
  {"Bbb2",25},
  {"Bb2", 26},
  {"B2",  27},
  {"B#2", 28},
  {"Bx2", 29},

  {"Cbb3",26},
  {"Cb3", 27}, 
  {"C3",  28},  
  {"C#3", 29}, 
  {"Cx3", 30}, 
  {"Dbb3",28},
  {"Db3", 29}, 
  {"D3",  30},  
  {"D#3", 31}, 
  {"Dx3", 32}, 
  {"Ebb3",30},
  {"Eb3", 31},
  {"E3",  32},
  {"E#3", 33},
  {"Ex3", 34},
  {"Fbb3",31},
  {"Fb3", 32},
  {"F3",  33},
  {"F#3", 34},
  {"Fx3", 35},
  {"Gbb3",33},
  {"Gb3", 34},
  {"G3",  35},
  {"G#3", 36},
  {"Gx3", 37},
  {"Abb3",35},
  {"Ab3", 36},
  {"A3",  37},
  {"A#3", 38},
  {"Ax3", 39},
  {"Bbb3",37},
  {"Bb3", 38},
  {"B3",  39},
  {"B#3", 40},
  {"Bx3", 41},

  {"Cbb4",38},
  {"Cb4", 39}, 
  {"C4",  40},  
  {"C#4", 41}, 
  {"Cx4", 42}, 
  {"Dbb4",40},
  {"Db4", 41}, 
  {"D4",  42},  
  {"D#4", 43}, 
  {"Dx4", 44}, 
  {"Ebb4",42},
  {"Eb4", 43},
  {"E4",  44},
  {"E#4", 45},
  {"Ex4", 46},
  {"Fbb4",43},
  {"Fb4", 44},
  {"F4",  45},
  {"F#4", 46},
  {"Fx4", 47},
  {"Gbb4",45},
  {"Gb4", 46},
  {"G4",  47},
  {"G#4", 48},
  {"Gx4", 49},
  {"Abb4",47},
  {"Ab4", 48},
  {"A4",  49},
  {"A#4", 50},
  {"Ax4", 51},
  {"Bbb4",49},
  {"Bb4", 50},
  {"B4",  51},
  {"B#4", 52},
  {"Bx4", 53},

  {"Cbb5",50},
  {"Cb5", 51},
  {"C5",  52},
  {"C#5", 53},
  {"Cx5", 54},
  {"Dbb5",52},
  {"Db5", 53},
  {"D5",  54},
  {"D#5", 55},
  {"Dx5", 56},
  {"Ebb5",54},
  {"Eb5", 55},
  {"E5",  56},
  {"E#5", 57},
  {"Ex5", 58},
  {"Fbb5",55},
  {"Fb5", 56},
  {"F5",  57},
  {"F#5", 58},
  {"Fx5", 59},
  {"Gbb5",57},
  {"Gb5", 58},
  {"G5",  59},
  {"G#5", 60},
  {"Gx5", 61},
  {"Abb5",59},
  {"Ab5", 60},
  {"A5",  61},
  {"A#5", 62},
  {"Ax5", 63},
  {"Bbb5",61},
  {"Bb5", 62},
  {"B5",  63},
  {"B#5", 64},
  {"Bx5", 65},

  {"Cbb6",62},
  {"Cb6", 63},
  {"C6",  64},
  {"C#6", 65},
  {"Cx6", 66},
  {"Dbb6",64},
  {"Db6", 65},
  {"D6",  66},
  {"D#6", 67},
  {"Dx6", 68},
  {"Ebb6",66},
  {"Eb6", 67},
  {"E6",  68},
  {"E#6", 69},
  {"Ex6", 70},
  {"Fbb6",67},
  {"Fb6", 68},
  {"F6",  69},
  {"F#6", 70},
  {"Fx6", 71},
  {"Gbb6",69},
  {"Gb6", 70},
  {"G6",  71},
  {"G#6", 72},
  {"Gx6", 73},
  {"Abb6",71},
  {"Ab6", 72},
  {"A6",  73},
  {"A#6", 74},
  {"Ax6", 75},
  {"Bbb6",73},
  {"Bb6", 74},
  {"B6",  75},
  {"B#6", 76},
  {"Bx6", 77},

  {"Cbb7",74},
  {"Cb7", 75},
  {"C7",  76},
  {"C#7", 77},
  {"Cx7", 78},
  {"Dbb7",76},
  {"Db7", 77},
  {"D7",  78},
  {"D#7", 79},
  {"Dx7", 80},
  {"Ebb7",78},
  {"Eb7", 79},
  {"E7",  80},
  {"E#7", 81},
  {"Ex7", 82},
  {"Fbb7",79},
  {"Fb7", 80},
  {"F7",  81},
  {"F#7", 82},
  {"Fx7", 83},
  {"Gbb7",81},
  {"Gb7", 82},
  {"G7",  83},
  {"G#7", 84},
  {"Gx7", 85},
  {"Abb7",83},
  {"Ab7", 84},
  {"A7",  85},
  {"A#7", 86},
  {"Ax7", 87},
  {"Bbb7",85},
  {"Bb7", 86},
  {"B7",  87},
  {"B#7", 88},

  {"Cbb8",86},
  {"Cb8", 87},
  {"C8",  88}
};