#pragma once
#include "../notation/base/base_types.hpp"

namespace hautbois 
{

// English table
using NoteNameLilypondNotationTable=std::map<NoteName, NoteName>;

const NoteNameLilypondNotationTable _SCI_NAME_LILYPOND_NOTATION_TABLE_EN {
    {"A0",   "a,,,"},
    {"A#0",  "as,,,"},
    {"Ax0",  "ax,,,"},
    {"Bbb0", "bff,,,"},
    {"Bb0",  "bf,,,"},
    {"B0",   "b,,,"},
    {"B#0",  "bs,,,"},
    {"Bx0",  "bx,,,"},

    {"Cbb1", "cff,,"},
    {"Cb1",  "cf,,"},
    {"C1",   "c,,"},
    {"C#1",  "cs,,"},
    {"Cx1",  "cx,,"},
    {"Dbb1", "dff,,"},
    {"Db1",  "df,,"},
    {"D1",   "d,,"},
    {"D#1",  "ds,,"},
    {"Dx1",  "dx,,"},
    {"Ebb1", "eff,,"},
    {"Eb1",  "ef,,"},
    {"E1",   "e,,"},
    {"E#1",  "es,,"},
    {"Ex1",  "ex,,"},
    {"Fbb1", "fff,,"},
    {"Fb1",  "ff,,"},
    {"F1",   "f,,"},
    {"F#1",  "fs,,"},
    {"Fx1",  "fx,,"},
    {"Gbb1", "gff,,"},
    {"Gb1",  "gf,,"},
    {"G1",   "g,,"},
    {"G#1",  "gs,,"},
    {"Gx1",  "gx,,"},
    {"Abb1", "aff,,"},
    {"Ab1",  "af,,"},
    {"A1",   "a,,"},
    {"A#1",  "as,,"},
    {"Ax1",  "ax,,"},
    {"Bbb1", "bff,,"},
    {"Bb1",  "bf,,"},
    {"B1",   "b,,"},
    {"B#1",  "bs,,"},
    {"Bx1",  "bx,,"},

    {"Cbb2", "cff,"},
    {"Cb2",  "cf,"},
    {"C2",   "c,"},
    {"C#2",  "cs,"},
    {"Cx2",  "cx,"},
    {"Dbb2", "dff,"},
    {"Db2",  "df,"},
    {"D2",   "d,"},
    {"D#2",  "ds,"},
    {"Dx2",  "dx,"},
    {"Ebb2", "eff,"},
    {"Eb2",  "ef,"},
    {"E2",   "e,"},
    {"E#2",  "es,"},
    {"Ex2",  "ex,"},
    {"Fbb2", "fff,"},
    {"Fb2",  "ff,"},
    {"F2",   "f,"},
    {"F#2",  "fs,"},
    {"Fx2",  "fx,"},
    {"Gbb2", "gff,"},
    {"Gb2",  "gf,"},
    {"G2",   "g,"},
    {"G#2",  "gs,"},
    {"Gx2",  "gx,"},
    {"Abb2", "aff,"},
    {"Ab2",  "af,"},
    {"A2",   "a,"},
    {"A#2",  "as,"},
    {"Ax2",  "ax,"},
    {"Bbb2", "bff,"},
    {"Bb2",  "bf,"},
    {"B2",   "b,"},
    {"B#2",  "bs,"},
    {"Bx2",  "bx,"},

    {"Cbb3", "cff"},
    {"Cb3",  "cf"},
    {"C3",   "c"},
    {"C#3",  "cs"},
    {"Cx3",  "cx"},
    {"Dbb3", "dff"},
    {"Db3",  "df"},
    {"D3",   "d"},
    {"D#3",  "ds"},
    {"Dx3",  "dx"},
    {"Ebb3", "eff"},
    {"Eb3",  "ef"},
    {"E3",   "e"},
    {"E#3",  "es"},
    {"Ex3",  "ex"},
    {"Fbb3", "fff"},
    {"Fb3",  "ff"},
    {"F3",   "f"},
    {"F#3",  "fs"},
    {"Fx3",  "fx"},
    {"Gbb3", "gff"},
    {"Gb3",  "gf"},
    {"G3",   "g"},
    {"G#3",  "gs"},
    {"Gx3",  "gx"},
    {"Abb3", "aff"},
    {"Ab3",  "af"},
    {"A3",   "a"},
    {"A#3",  "as"},
    {"Ax3",  "ax"},
    {"Bbb3", "bff"},
    {"Bb3",  "bf"},
    {"B3",   "b"},
    {"B#3",  "bs"},
    {"Bx3",  "bx"},

    {"Cbb4", "cff\'"},
    {"Cb4",  "cf\'"},
    {"C4",   "c\'"},
    {"C#4",  "cs\'"},
    {"Cx4",  "cx\'"},
    {"Dbb4", "dff\'"},
    {"Db4",  "df\'"},
    {"D4",   "d\'"},
    {"D#4",  "ds\'"},
    {"Dx4",  "dx\'"},
    {"Ebb4", "eff\'"},
    {"Eb4",  "ef\'"},
    {"E4",   "e\'"},
    {"E#4",  "es\'"},
    {"Ex4",  "ex\'"},
    {"Fbb4", "fff\'"},
    {"Fb4",  "ff\'"},
    {"F4",   "f\'"},
    {"F#4",  "fs\'"},
    {"Fx4",  "fx\'"},
    {"Gbb4", "gff\'"},
    {"Gb4",  "gf\'"},
    {"G4",   "g\'"},
    {"G#4",  "gs\'"},
    {"Gx4",  "gx\'"},
    {"Abb4", "aff\'"},
    {"Ab4",  "af\'"},
    {"A4",   "a\'"},
    {"A#4",  "as\'"},
    {"Ax4",  "ax\'"},
    {"Bbb4", "bff\'"},
    {"Bb4",  "bf\'"},
    {"B4",   "b\'"},
    {"B#4",  "bs\'"},
    {"Bx4",  "bx\'"},

    {"Cbb5", "cff\'\'"},
    {"Cb5",  "cf\'\'"},
    {"C5",   "c\'\'"},
    {"C#5",  "cs\'\'"},
    {"Cx5",  "cx\'\'"},
    {"Dbb5", "dff\'\'"},
    {"Db5",  "df\'\'"},
    {"D5",   "d\'\'"},
    {"D#5",  "ds\'\'"},
    {"Dx5",  "dx\'\'"},
    {"Ebb5", "eff\'\'"},
    {"Eb5",  "ef\'\'"},
    {"E5",   "e\'\'"},
    {"E#5",  "es\'\'"},
    {"Ex5",  "ex\'\'"},
    {"Fbb5", "fff\'\'"},
    {"Fb5",  "ff\'\'"},
    {"F5",   "f\'\'"},
    {"F#5",  "fs\'\'"},
    {"Fx5",  "fx\'\'"},
    {"Gbb5", "gff\'\'"},
    {"Gb5",  "gf\'\'"},
    {"G5",   "g\'\'"},
    {"G#5",  "gs\'\'"},
    {"Gx5",  "gx\'\'"},
    {"Abb5", "aff\'\'"},
    {"Ab5",  "af\'\'"},
    {"A5",   "a\'\'"},
    {"A#5",  "as\'\'"},
    {"Ax5",  "ax\'\'"},
    {"Bbb5", "bff\'\'"},
    {"Bb5",  "bf\'\'"},
    {"B5",   "b\'\'"},
    {"B#5",  "bs\'\'"},
    {"Bx5",  "bx\'\'"},

    {"Cbb6", "cff\'\'\'"},
    {"Cb6",  "cf\'\'\'"},
    {"C6",   "c\'\'\'"},
    {"C#6",  "cs\'\'\'"},
    {"Cx6",  "cx\'\'\'"},
    {"Dbb6", "dff\'\'\'"},
    {"Db6",  "df\'\'\'"},
    {"D6",   "d\'\'\'"},
    {"D#6",  "ds\'\'\'"},
    {"Dx6",  "dx\'\'\'"},
    {"Ebb6", "eff\'\'\'"},
    {"Eb6",  "ef\'\'\'"},
    {"E6",   "e\'\'\'"},
    {"E#6",  "es\'\'\'"},
    {"Ex6",  "ex\'\'\'"},
    {"Fbb6", "fff\'\'\'"},
    {"Fb6",  "ff\'\'\'"},
    {"F6",   "f\'\'\'"},
    {"F#6",  "fs\'\'\'"},
    {"Fx6",  "fx\'\'\'"},
    {"Gbb6", "gff\'\'\'"},
    {"Gb6",  "gf\'\'\'"},
    {"G6",   "g\'\'\'"},
    {"G#6",  "gs\'\'\'"},
    {"Gx6",  "gx\'\'\'"},
    {"Abb6", "aff\'\'\'"},
    {"Ab6",  "af\'\'\'"},
    {"A6",   "a\'\'\'"},
    {"A#6",  "as\'\'\'"},
    {"Ax6",  "ax\'\'\'"},
    {"Bbb6", "bff\'\'\'"},
    {"Bb6",  "bf\'\'\'"},
    {"B6",   "b\'\'\'"},
    {"B#6",  "bs\'\'\'"},
    {"Bx6",  "bx\'\'\'"},

    {"Cbb7", "cff\'\'\'\'"},
    {"Cb7",  "cf\'\'\'\'"},
    {"C7",   "c\'\'\'\'"},
    {"C#7",  "cs\'\'\'\'"},
    {"Cx7",  "cx\'\'\'\'"},
    {"Dbb7", "dff\'\'\'\'"},
    {"Db7",  "df\'\'\'\'"},
    {"D7",   "d\'\'\'\'"},
    {"D#7",  "ds\'\'\'\'"},
    {"Dx7",  "dx\'\'\'\'"},
    {"Ebb7", "eff\'\'\'\'"},
    {"Eb7",  "ef\'\'\'\'"},
    {"E7",   "e\'\'\'\'"},
    {"E#7",  "es\'\'\'\'"},
    {"Ex7",  "ex\'\'\'\'"},
    {"Fbb7", "fff\'\'\'\'"},
    {"Fb7",  "ff\'\'\'\'"},
    {"F7",   "f\'\'\'\'"},
    {"F#7",  "fs\'\'\'\'"},
    {"Fx7",  "fx\'\'\'\'"},
    {"Gbb7", "gff\'\'\'\'"},
    {"Gb7",  "gf\'\'\'\'"},
    {"G7",   "g\'\'\'\'"},
    {"G#7",  "gs\'\'\'\'"},
    {"Gx7",  "gx\'\'\'\'"},
    {"Abb7", "aff\'\'\'\'"},
    {"Ab7",  "af\'\'\'\'"},
    {"A7",   "a\'\'\'\'"},
    {"A#7",  "as\'\'\'\'"},
    {"Ax7",  "ax\'\'\'\'"},
    {"Bbb7", "bff\'\'\'\'"},
    {"Bb7",  "bf\'\'\'\'"},
    {"B7",   "b\'\'\'\'"},
    {"B#7",  "bs\'\'\'\'"},

    {"Cbb8", "cff\'\'\'\'\'"},
    {"Cb8",  "cf\'\'\'\'\'"},
    {"C8",   "c\'\'\'\'\'"}
};

// Default Dutch table
const NoteNameLilypondNotationTable _SCI_NAME_LILYPOND_NOTATION_TABLE_NL {
    {"A0",   "a,,,"},
    {"A#0",  "ais,,,"},
    {"Ax0",  "aisis,,,"},
    {"Bbb0", "beses,,,"},
    {"Bb0",  "bes,,,"},
    {"B0",   "b,,,"},
    {"B#0",  "bis,,,"},
    {"Bx0",  "bisis,,,"},

    {"Cbb1", "ceses,,"},
    {"Cb1",  "ces,,"},
    {"C1",   "c,,"},
    {"C#1",  "cis,,"},
    {"Cx1",  "cisis,,"},
    {"Dbb1", "deses,,"},
    {"Db1",  "des,,"},
    {"D1",   "d,,"},
    {"D#1",  "dis,,"},
    {"Dx1",  "disis,,"},
    {"Ebb1", "eeses,,"},
    {"Eb1",  "ees,,"},
    {"E1",   "e,,"},
    {"E#1",  "eis,,"},
    {"Ex1",  "eisis,,"},
    {"Fbb1", "feses,,"},
    {"Fb1",  "fes,,"},
    {"F1",   "f,,"},
    {"F#1",  "fis,,"},
    {"Fx1",  "fisis,,"},
    {"Gbb1", "geses,,"},
    {"Gb1",  "ges,,"},
    {"G1",   "g,,"},
    {"G#1",  "gis,,"},
    {"Gx1",  "gisis,,"},
    {"Abb1", "aeses,,"},
    {"Ab1",  "aes,,"},
    {"A1",   "a,,"},
    {"A#1",  "ais,,"},
    {"Ax1",  "aisis,,"},
    {"Bbb1", "beses,,"},
    {"Bb1",  "bes,,"},
    {"B1",   "b,,"},
    {"B#1",  "bis,,"},
    {"Bx1",  "bisis,,"},

    {"Cbb2", "ceses,"},
    {"Cb2",  "ces,"},
    {"C2",   "c,"},
    {"C#2",  "cis,"},
    {"Cx2",  "cisis,"},
    {"Dbb2", "deses,"},
    {"Db2",  "des,"},
    {"D2",   "d,"},
    {"D#2",  "dis,"},
    {"Dx2",  "disis,"},
    {"Ebb2", "eeses,"},
    {"Eb2",  "ees,"},
    {"E2",   "e,"},
    {"E#2",  "eis,"},
    {"Ex2",  "eisis,"},
    {"Fbb2", "feses,"},
    {"Fb2",  "fes,"},
    {"F2",   "f,"},
    {"F#2",  "fis,"},
    {"Fx2",  "fisis,"},
    {"Gbb2", "geses,"},
    {"Gb2",  "ges,"},
    {"G2",   "g,"},
    {"G#2",  "gis,"},
    {"Gx2",  "gisis,"},
    {"Abb2", "aeses,"},
    {"Ab2",  "aes,"},
    {"A2",   "a,"},
    {"A#2",  "ais,"},
    {"Ax2",  "aisis,"},
    {"Bbb2", "beses,"},
    {"Bb2",  "bes,"},
    {"B2",   "b,"},
    {"B#2",  "bis,"},
    {"Bx2",  "bisis,"},

    {"Cbb3", "ceses"},
    {"Cb3",  "ces"},
    {"C3",   "c"},
    {"C#3",  "cis"},
    {"Cx3",  "cisis"},
    {"Dbb3", "deses"},
    {"Db3",  "des"},
    {"D3",   "d"},
    {"D#3",  "dis"},
    {"Dx3",  "disis"},
    {"Ebb3", "eeses"},
    {"Eb3",  "ees"},
    {"E3",   "e"},
    {"E#3",  "eis"},
    {"Ex3",  "eisis"},
    {"Fbb3", "feses"},
    {"Fb3",  "fes"},
    {"F3",   "f"},
    {"F#3",  "fis"},
    {"Fx3",  "fisis"},
    {"Gbb3", "geses"},
    {"Gb3",  "ges"},
    {"G3",   "g"},
    {"G#3",  "gis"},
    {"Gx3",  "gisis"},
    {"Abb3", "aeses"},
    {"Ab3",  "aes"},
    {"A3",   "a"},
    {"A#3",  "ais"},
    {"Ax3",  "aisis"},
    {"Bbb3", "beses"},
    {"Bb3",  "bes"},
    {"B3",   "b"},
    {"B#3",  "bis"},
    {"Bx3",  "bisis"},

    {"Cbb4", "ceses\'"},
    {"Cb4",  "ces\'"},
    {"C4",   "c\'"},
    {"C#4",  "cis\'"},
    {"Cx4",  "cisis\'"},
    {"Dbb4", "deses\'"},
    {"Db4",  "des\'"},
    {"D4",   "d\'"},
    {"D#4",  "dis\'"},
    {"Dx4",  "disis\'"},
    {"Ebb4", "eeses\'"},
    {"Eb4",  "ees\'"},
    {"E4",   "e\'"},
    {"E#4",  "eis\'"},
    {"Ex4",  "eisis\'"},
    {"Fbb4", "feses\'"},
    {"Fb4",  "fes\'"},
    {"F4",   "f\'"},
    {"F#4",  "fis\'"},
    {"Fx4",  "fisis\'"},
    {"Gbb4", "geses\'"},
    {"Gb4",  "ges\'"},
    {"G4",   "g\'"},
    {"G#4",  "gis\'"},
    {"Gx4",  "gisis\'"},
    {"Abb4", "aeses\'"},
    {"Ab4",  "aes\'"},
    {"A4",   "a\'"},
    {"A#4",  "ais\'"},
    {"Ax4",  "aisis\'"},
    {"Bbb4", "beses\'"},
    {"Bb4",  "bes\'"},
    {"B4",   "b\'"},
    {"B#4",  "bis\'"},
    {"Bx4",  "bisis\'"},

    {"Cbb5", "ceses\'\'"},
    {"Cb5",  "ces\'\'"},
    {"C5",   "c\'\'"},
    {"C#5",  "cis\'\'"},
    {"Cx5",  "cisis\'\'"},
    {"Dbb5", "deses\'\'"},
    {"Db5",  "des\'\'"},
    {"D5",   "d\'\'"},
    {"D#5",  "dis\'\'"},
    {"Dx5",  "disis\'\'"},
    {"Ebb5", "eeses\'\'"},
    {"Eb5",  "ees\'\'"},
    {"E5",   "e\'\'"},
    {"E#5",  "eis\'\'"},
    {"Ex5",  "eisis\'\'"},
    {"Fbb5", "feses\'\'"},
    {"Fb5",  "fes\'\'"},
    {"F5",   "f\'\'"},
    {"F#5",  "fis\'\'"},
    {"Fx5",  "fisis\'\'"},
    {"Gbb5", "geses\'\'"},
    {"Gb5",  "ges\'\'"},
    {"G5",   "g\'\'"},
    {"G#5",  "gis\'\'"},
    {"Gx5",  "gisis\'\'"},
    {"Abb5", "aeses\'\'"},
    {"Ab5",  "aes\'\'"},
    {"A5",   "a\'\'"},
    {"A#5",  "ais\'\'"},
    {"Ax5",  "aisis\'\'"},
    {"Bbb5", "beses\'\'"},
    {"Bb5",  "bes\'\'"},
    {"B5",   "b\'\'"},
    {"B#5",  "bis\'\'"},
    {"Bx5",  "bisis\'\'"},

    {"Cbb6", "ceses\'\'\'"},
    {"Cb6",  "ces\'\'\'"},
    {"C6",   "c\'\'\'"},
    {"C#6",  "cis\'\'\'"},
    {"Cx6",  "cisis\'\'\'"},
    {"Dbb6", "deses\'\'\'"},
    {"Db6",  "des\'\'\'"},
    {"D6",   "d\'\'\'"},
    {"D#6",  "dis\'\'\'"},
    {"Dx6",  "disis\'\'\'"},
    {"Ebb6", "eeses\'\'\'"},
    {"Eb6",  "ees\'\'\'"},
    {"E6",   "e\'\'\'"},
    {"E#6",  "eis\'\'\'"},
    {"Ex6",  "eisis\'\'\'"},
    {"Fbb6", "feses\'\'\'"},
    {"Fb6",  "fes\'\'\'"},
    {"F6",   "f\'\'\'"},
    {"F#6",  "fis\'\'\'"},
    {"Fx6",  "fisis\'\'\'"},
    {"Gbb6", "geses\'\'\'"},
    {"Gb6",  "ges\'\'\'"},
    {"G6",   "g\'\'\'"},
    {"G#6",  "gis\'\'\'"},
    {"Gx6",  "gisis\'\'\'"},
    {"Abb6", "aeses\'\'\'"},
    {"Ab6",  "aes\'\'\'"},
    {"A6",   "a\'\'\'"},
    {"A#6",  "ais\'\'\'"},
    {"Ax6",  "aisis\'\'\'"},
    {"Bbb6", "beses\'\'\'"},
    {"Bb6",  "bes\'\'\'"},
    {"B6",   "b\'\'\'"},
    {"B#6",  "bis\'\'\'"},
    {"Bx6",  "bisis\'\'\'"},

    {"Cbb7", "ceses\'\'\'\'"},
    {"Cb7",  "ces\'\'\'\'"},
    {"C7",   "c\'\'\'\'"},
    {"C#7",  "cis\'\'\'\'"},
    {"Cx7",  "cisis\'\'\'\'"},
    {"Dbb7", "deses\'\'\'\'"},
    {"Db7",  "des\'\'\'\'"},
    {"D7",   "d\'\'\'\'"},
    {"D#7",  "dis\'\'\'\'"},
    {"Dx7",  "disis\'\'\'\'"},
    {"Ebb7", "eeses\'\'\'\'"},
    {"Eb7",  "ees\'\'\'\'"},
    {"E7",   "e\'\'\'\'"},
    {"E#7",  "eis\'\'\'\'"},
    {"Ex7",  "eisis\'\'\'\'"},
    {"Fbb7", "feses\'\'\'\'"},
    {"Fb7",  "fes\'\'\'\'"},
    {"F7",   "f\'\'\'\'"},
    {"F#7",  "fis\'\'\'\'"},
    {"Fx7",  "fisis\'\'\'\'"},
    {"Gbb7", "geses\'\'\'\'"},
    {"Gb7",  "ges\'\'\'\'"},
    {"G7",   "g\'\'\'\'"},
    {"G#7",  "gis\'\'\'\'"},
    {"Gx7",  "gisis\'\'\'\'"},
    {"Abb7", "aeses\'\'\'\'"},
    {"Ab7",  "aes\'\'\'\'"},
    {"A7",   "a\'\'\'\'"},
    {"A#7",  "ais\'\'\'\'"},
    {"Ax7",  "aisis\'\'\'\'"},
    {"Bbb7", "beses\'\'\'\'"},
    {"Bb7",  "bes\'\'\'\'"},
    {"B7",   "b\'\'\'\'"},
    {"B#7",  "bis\'\'\'\'"},

    {"Cbb8", "ceses\'\'\'\'\'"},
    {"Cb8",  "ces\'\'\'\'\'"},
    {"C8",   "c\'\'\'\'\'"}
};
}