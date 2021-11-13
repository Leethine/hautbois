#pragma once
#include "base_types.hpp"
#include <map>

namespace hautbois
{
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

using TonalityNameTypeTable=std::map<NoteName, TonalityType>;

TonalityNameTypeTable tonality_str_type_table {
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

std::map<TonalityType, TonalityType> circle_of_fifth {
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