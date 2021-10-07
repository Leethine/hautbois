#pragma once
#include "defs.hpp"

#define NOTE_MODEL_1

#ifdef NOTE_MODEL_1
#include "note_model1/note_model1.hpp"
#else
#include "note_model2/note_model2.hpp"
#endif


