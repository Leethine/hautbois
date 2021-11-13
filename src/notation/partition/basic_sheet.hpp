#pragma once
#include "sheet_defs.hpp"
#include "one_voice.hpp"

namespace hautbois 
{

using VoiceVec=std::vector<OneVoice>;

class BasicSheet {
    protected:
    UIntValue nb_voice;
    std::vector<InstrumentType> instrusment_list;
    std::vector<myPairClef> clefs_list;
    std::vector<ScaleName> scale_list;
    std::vector<Meter> meter_list;
    VoiceVec voices;

    public:
    BasicSheet(UIntValue nbvoices) :
    nb_voice { nbvoices }
    {
        instrusment_list.reserve(nbvoices);
        clefs_list.reserve(nbvoices);
        scale_list.reserve(nbvoices);
        voices.reserve(nbvoices);
    }
};



}
