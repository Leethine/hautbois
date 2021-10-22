#pragma once
#include "../onebar.hpp"
#include <numeric>
#include <algorithm>
#include <regex>
#include <boost/algorithm/string.hpp>
#include "regex_pattern.hpp"

namespace hautbois
{

using BarPtrArray=std::vector<std::unique_ptr<ListNote>>;
using TokenString=std::string;
using TokenVector=std::vector<TokenString>;
using TokenStrVector=std::vector<TokenString>;

class ParserUtl {
public:
    static bool isBracket(char i) { 
        return i == '(' || i == ')' || 
               i == '{' || i == '}' ||
               i == '[' || i == ']' ;
    }

    TokenString rmSpace(const TokenString& cstr) {
        TokenString str { cstr };
        str.erase(remove_if(str.begin(), str.end(), ::isspace), str.end());
        return str;
    }

    Duration readDurationFromStr(const TokenString& durationstr) {
        TokenVector result;
        boost::split(result, durationstr, boost::is_any_of("/"));
        // make sure the meter is well formated
        assert(result.size() == 2);
        Duration duration { Beat(std::stoi(result[0])), 
                            Beat(std::stoi(result[1])) };
        assert(duration.num != 0 && duration.denom != 0);
        return duration;
    }

    GroupDuration readGroupDurationFromStr(const TokenStrVector& vec) {
        GroupDuration durations;
        for (auto d : vec) {
            durations.push_back(readDurationFromStr(d));
        }
        return durations;
    }

    TokenString deBracket(const TokenString& token_ns) {
        // remove the most outside bracket
        TokenString content_str;
        if ( token_ns.front() == '(' && token_ns.back() == ')' ) {
            content_str = token_ns.substr(1, token_ns.length()-2);
        }
        else if ( token_ns.front() == '{' && token_ns.back() == '}' )
            content_str = token_ns.substr(1, token_ns.length()-2);
        else if ( token_ns.front() == '[' && token_ns.back() == ']' )
            content_str = token_ns.substr(1, token_ns.length()-2);
        else
            content_str = token_ns;
        
        return content_str;
    }
    
    TokenString rmBracket(const TokenString& token_ns) {
        // remove ALL brackets
        TokenString content_str { token_ns };

        content_str.erase(
            std::remove_if(
                content_str.begin(),
                content_str.end(),
                ParserUtl::isBracket
            ),
            content_str.end()
        );

        return content_str;
    }

    TokenVector splitToken(const TokenString& token_ns, const std::string& sep) {
        TokenVector result;
        boost::split(result, token_ns, boost::is_any_of(sep), 
                                       boost::token_compress_on);
        return result;
    }

    NoteType checkType(const TokenString& token_ns) {
        
        // check if it's chord
        if ( token_ns.front() == '{' && token_ns.back() == '}' ) {
            return NoteType::GroupNote;
        }

        else if ( token_ns.front() == '(' && token_ns.back() == ')' ) {
            // check if it's rest
            auto found1 = token_ns.find("Rest");
            auto found2 = token_ns.find("rest");
            auto found3 = token_ns.find("R");
            auto found4 = token_ns.find("r");

            if ( found1 != std::string::npos || found2 != std::string::npos ||
                 found3 != std::string::npos || found4 != std::string::npos )
                return NoteType::RestNote;
            
            // it must be a single note
            else
                return NoteType::SingleNote; 
        }
        // none of above, invalid type
        else { return NoteType::TYPE_INVALID; }
    }

    bool checkFormatting(NoteType type, const TokenString& token_ns) {
        std::regex rx;
        switch (type)
        {
        case NoteType::RestNote:
            rx = std::regex(RXPTN_RESTNOTE);
            break;
        case NoteType::SingleNote:
            rx = std::regex(RXPTN_SINGLENOTE);
            break;
        case NoteType::GroupNote:
            rx = std::regex(RXPTN_CHORD);
            break;
        default:
            break;
        }

        // if matched, formatting is validated, otherwiser not
        if ( std::regex_match(token_ns, rx) )
            return true;
        else 
            return false;
    }
    
};

}