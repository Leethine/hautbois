#pragma once
#include "base_types.hpp"
#include <map>

namespace hautbois
{

using TonalityStrTypeTable=std::map<ScaleName, TonalityType>;
const TonalityStrTypeTable _TONALITY_STR_TYPE_TABLE {
    // Majors
    { "C", TonalityType::C },
    { "G", TonalityType::G },
    { "D", TonalityType::D },
    { "A", TonalityType::A },
    { "E", TonalityType::E },
    { "B", TonalityType::B },
    { "F#", TonalityType::Fs },
    { "Gb", TonalityType::Gb },
    { "C#", TonalityType::Cs },
    { "Db", TonalityType::Db },
    { "Ab", TonalityType::Ab },
    { "Eb", TonalityType::Eb },
    { "Bb", TonalityType::Bb },
    { "F", TonalityType::F },

    // Majors again, with "M"
    { "CM", TonalityType::C },
    { "GM", TonalityType::G },
    { "DM", TonalityType::D },
    { "AM", TonalityType::A },
    { "EM", TonalityType::E },
    { "BM", TonalityType::B },
    { "F#M", TonalityType::Fs },
    { "GbM", TonalityType::Gb },
    { "C#M", TonalityType::Cs },
    { "DbM", TonalityType::Db },
    { "AbM", TonalityType::Ab },
    { "EbM", TonalityType::Eb },
    { "BbM", TonalityType::Bb },
    { "FM", TonalityType::F },
    
    // minors
    { "a", TonalityType::a },
    { "e", TonalityType::e },
    { "b", TonalityType::b },
    { "f#", TonalityType::fs },
    { "c#", TonalityType::cs },
    { "g#", TonalityType::gs },
    { "d#", TonalityType::ds },
    { "eb", TonalityType::eb },
    { "bb", TonalityType::bb },
    { "f", TonalityType::f },
    { "c", TonalityType::c },
    { "g", TonalityType::g },
    { "d", TonalityType::d },
    
    // minors again
    { "Am", TonalityType::a },
    { "Em", TonalityType::e },
    { "Bm", TonalityType::b },
    { "F#m", TonalityType::fs },
    { "C#m", TonalityType::cs },
    { "G#m", TonalityType::gs },
    { "D#m", TonalityType::ds },
    { "Ebm", TonalityType::eb },
    { "Bbm", TonalityType::bb },
    { "Fm", TonalityType::f },
    { "Cm", TonalityType::c },
    { "Gm", TonalityType::g },
    { "Dm", TonalityType::d }
};

using CircleOfFifthTable=std::map<TonalityType, TonalityType>;
const CircleOfFifthTable _CIRCLE_OF_FIFTH_TABLE {
    // Major to minor
    {TonalityType::C, TonalityType::a},
    {TonalityType::G, TonalityType::e},
    {TonalityType::D, TonalityType::b},
    {TonalityType::A, TonalityType::fs},
    {TonalityType::E, TonalityType::cs},
    {TonalityType::B, TonalityType::gs},
    {TonalityType::Fs, TonalityType::eb},
    {TonalityType::Gb, TonalityType::eb},
    {TonalityType::Cs, TonalityType::bb},
    {TonalityType::Db, TonalityType::bb},
    {TonalityType::Ab, TonalityType::f},
    {TonalityType::Eb, TonalityType::c},
    {TonalityType::Bb, TonalityType::g},
    {TonalityType::F, TonalityType::d},

    // minor to Major
    {TonalityType::a, TonalityType::C},
    {TonalityType::e, TonalityType::G},
    {TonalityType::b, TonalityType::D},
    {TonalityType::fs, TonalityType::A},
    {TonalityType::cs, TonalityType::E},
    {TonalityType::gs, TonalityType::B},
    {TonalityType::ds, TonalityType::Fs},
    {TonalityType::eb, TonalityType::Fs},
    {TonalityType::bb, TonalityType::Cs},
    {TonalityType::f, TonalityType::Ab},
    {TonalityType::c, TonalityType::Eb},
    {TonalityType::g, TonalityType::Bb},
    {TonalityType::d, TonalityType::F}
};

}