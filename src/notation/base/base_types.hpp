#pragma once

#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <iostream>
#include <memory>
#include <cmath>
#include <cassert>
#include <iterator>

namespace hautbois
{

using UIntValue=unsigned int;
using Beat=unsigned int;
using NoteIndex=unsigned int;
using NoteName=std::string;
using ScaleName=std::string;
using TonalityName=std::string;
using InstrumentName=std::string;
using GroupNoteName=std::vector<NoteName>;
using GroupNoteIndex=std::vector<NoteIndex>;
using TokenVector=std::vector<std::string>;

using NoteNameIndexTable=std::map<NoteName, NoteIndex>;
using NoteIndexNameTable=std::map<NoteIndex, NoteName>;

/* Instrument family types */
enum class InstrumentFamilyType
{
    ARPA,
    LIUTO,
    OTTONI,
    PERCUSSIONE,
    CLAVICEMBALO,
    FLAUTO,
    FLAUTO_DOLCE,
    OBOE,
    CLARINETTO,
    ORGANO,
    PIANOFORTE,
    // Abstract field
    NONE,
    BASSO_CONTINUOTO,
};

/* Tonality types */
enum class TonalityType {
    // Majors
    C, G, D, A, E, B,
    Fs, Gb, Cs, Db, Ab, Eb, Bb, F,

    // Minors
    a, e, b, fs, cs, gs, ds,
    eb, bb, f, c, g, d,

    // Unset
    UNKNOWN
};

}
