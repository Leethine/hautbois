#include "../onebar.hpp"
#include <numeric>
#include <algorithm>
#include <regex>
#include <boost/algorithm/string.hpp>

namespace hautbois
{

using BarPtrArray=std::vector<std::unique_ptr<OneBar>>;
using TokenString=std::string;

class ParserUtl {
public:
    static bool isBracket(char i) { 
        return i == '(' || i == ')' || i == '{' || i == '}';
    }

    TokenString rmSpace(const TokenString& cstr) {
        TokenString str { cstr };
        str.erase(remove_if(str.begin(), str.end(), isspace), str.end());
        return str;
    }

    Duration readDurationFromStr(const TokenString& durationstr) {
        std::vector<TokenString> result;
        boost::split(result, durationstr, boost::is_any_of("/"));
        // make sure the meter is well formated
        assert(result.size() == 2);
        Duration duration { Beat(std::stoi(result[0])), 
                            Beat(std::stoi(result[1])) };
        return duration;
    }

    TokenString deBracket(const TokenString& token_ns) {
        // remove the most outside bracket
        TokenString content_str;
        if ( token_ns.front() == '(' && token_ns.back() == ')' ) {
            content_str = token_ns.substr(1, token_ns.length()-2);
        }
        else if ( token_ns.front() == '{' && token_ns.back() == '}' )
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

    std::vector<TokenString> splitNoteToken(const TokenString& token) {
    } 

    // TODO
    NoteType checkType(const TokenString& token) {
        TokenString token_ns = rmSpace(token);
        
        // check if it's chord
        if ( token_ns.front() == '{' && token_ns.back() == '}' ) {
            return NoteType::GroupNote;
        }

        // check if it's rest
        else if ( token_ns.front() == '(' && token_ns.back() == ')' ) {
        }
        // must return invalid type
        else { return NoteType::TYPE_INVALID; }
    }

    bool checkFormatting(NoteType type, TokenString& token_ns) {
    }
    
    bool checkRestNoteFormatting(TokenString& token) const {}

    bool checkSingleNoteFormatting(TokenString& token) const {}
    
    bool checkGroupNoteFormatting(TokenString& token) const {}

    
};

}