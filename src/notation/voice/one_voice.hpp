#pragma once
#include "../bar/one_bar.hpp"
namespace hautbois 
{

using ListBar=std::list<std::unique_ptr<OneBar>>;

class TempVoice {
    mutable size_t begins_at;
    ListBar temp_bars;
public:
    TempVoice():
    begins_at { 1 }
    {}
    virtual void setBeginningBar();
    virtual size_t getBeginningBar();
    virtual void addNote();
    virtual void finalize();
};

using ListTempVoice=std::vector<TempVoice>;

class OneVoice {
    ListBar bars;
    ListTempVoice temp_voices;
public:
    OneVoice() {}
    virtual void addNote();
    virtual void newTempVoice();
    virtual void addNoteTempVoice();
};

}
