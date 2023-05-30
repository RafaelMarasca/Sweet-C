#ifndef PARSER_H_
#define PARSER_H_

#include <unordered_map>
#include <string>
#include <stack>
#include <utility>
#include <vector>
#include <fstream>
#include <sstream>

//{"*", {"TK_ID", "-"}}, {"*", {"TK_LOGOP", "-"}},{"*", {"TK_RELOP", "-"}},{"*", {"TK_ARITH", "-"}},{"*", {"TK_LOGVAL", "-"}},{"*", {"TK_CHAR", "-"}},{"*", {"TK_FRAC", "-"}},{"*", {"TK_WHOLE", "-"}},{"*", {"TK_TYPE", "-"}},{"*", {"TK_FUNC", "-"}},{"*", {"TK_COMMA", "-"}},{"*", {"TK_START_SCOPE", "-"}},{"*", {"TK_END_SCOPE", "-"}},{"*", {"TK_LPAR", "-"}},{"*", {"TK_RPAR", "-"}},{"*", {"TK_SEMICOLON", "-"}},{"*", {"TK_COLON", "-"}},{"*", {"TK_WHEN", "-"}},{"*", {"TK_OTHERWISE", "-"}},{"*", {"TK_FOR", "-"}},{"*", {"TK_RETURN", "-"}},{"*", {"TK_SELECT", "-"}},{"*", {"TK_ASSIGNMENT", "-"}},{"*", {"TK_ARROW", "-"}},{"*", {"TK_COLON", "-"}},{"*", {"$", "-"}}, 


class LL1
{
    private:
        static std::unordered_map<std::string, std::unordered_map<std::string, std::string>> _parse_table;
        std::stack<std::string> _parse_stack;
        std::vector<std::string> _input_vec;
        
        std::ifstream _src;
        std::stringstream _buffer;

    public:
        LL1();
        ~LL1();

        bool parse(std::string src);
};

#endif