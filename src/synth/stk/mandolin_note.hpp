#pragma once

#ifndef STK_MANDOLIN_NOTE_HPP
#define STK_MANDOLIN_NOTE_HPP

#include "mandolin/singlenote_stk_mandolin.hpp"
#include "mandolin/chord_stk_mandolin.hpp"
#include "mandolin/gracenote_stk_mandolin.hpp"
#include "mandolin/tuplet_stk_mandolin.hpp"

#define STK_MANDOLIN_NOTE synth::SingleNoteStkMandolin,synth::ChordStkMandolin,synth::GraceNoteStkMandolin,synth::TupletStkMandolin

#endif