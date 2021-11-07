#pragma once
#include "../measure/one_bar.hpp"
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
        Duration duration { static_cast<Beat>(std::stoi(result[0])), 
                            static_cast<Beat>(std::stoi(result[1])) };
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

    NoteType checkFormatting(const TokenString& token_ns) {
        std::regex rx_rest { std::regex(RXPTN_RESTNOTE) }; 
        std::regex rx_single { std::regex(RXPTN_SINGLENOTE) };
        std::regex rx_chord { std::regex(RXPTN_CHORD) };

        // try 3 types, return matched type 
        if ( std::regex_match(token_ns, rx_rest) ) {
            return NoteType::RestNote;
        }
        else if ( std::regex_match(token_ns, rx_single) ) {
            return NoteType::SingleNote;
        }
        else if ( std::regex_match(token_ns, rx_chord) ) {
            return NoteType::GroupNote;
        }
        else {
            throw std::domain_error("Check formatting failed: " + token_ns);
            return NoteType::TYPE_INVALID;
        }
    }

    bool isPropertyValid(const TokenString& property_token_ns) {
        std::regex rx { RXPTN_PROPERTY };
        return std::regex_match(property_token_ns, rx);
    }
    
};

}