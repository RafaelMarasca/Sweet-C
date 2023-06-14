/**
 * @file Lexer.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2023-04-23
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include <exception>
#include <string>
#include <vector>
#include <unordered_map>
#include <fstream>
#include <sstream>
#include "Automata.h"
#include "Symbol.h"


#ifndef LEXER_H_
#define LEXER_H_

#define MAX_LEXEME_SIZE 64
#define BUFFER_SIZE 512

#define INITIAL_STATE "s0"
#define ACCEPTING_STATES {"WHOLE",\
                          "FRAC",\
                          "ID",\
                          "WHITE_SPACE",\
                          "PLUS_SIGN",\
                          "MINUS_SIGN",\
                          "MULT_SIGN",\
                          "DIV_SIGN",\
                          "MOD_SIGN",\
                          "DIFF",\
                          "EQUAL",\
                          "APPROX_EQUAL",\
                          "APPROX_DIFF",\
                          "ASSIGNMENT",\
                          "GREATER",\
                          "GREATER_EQUAL",\
                          "LESS",\
                          "LESS_EQUAL",\
                          "CHAR",\
                          "SEMICOLON",\
                          "COLON",\
                          "COMMA",\
                          "L_PAR",\
                          "R_PAR",\
                          "L_BRACE",\
                          "R_BRACE",\
                          "ARROW",\
                          "COMMENT"}


#define ACCEPTING_STATES_TOKENS {{"WHOLE", {TK_WHOLE, NULL, ""}},\
                                 {"FRAC", {TK_FRAC, NULL, ""}},\
                                 {"ID", {TK_ID, NULL, ""}},\
                                 {"WHITE_SPACE", {TK_WHITE, NULL, ""}},\
                                 {"PLUS_SIGN", {TK_ARITH, NULL, "PLUS"}},\
                                 {"MINUS_SIGN", {TK_ARITH, NULL, "MINUS"}},\
                                 {"MULT_SIGN", {TK_ARITH, NULL, "MULT"}},\
                                 {"DIV_SIGN", {TK_ARITH, NULL, "DIV"}},\
                                 {"MOD_SIGN", {TK_ARITH, NULL, "MOD"}},\
                                 {"DIFF", {TK_RELOP, NULL, "DIFF"}},\
                                 {"EQUAL", {TK_RELOP, NULL, "EQUAL"}},\
                                 {"APPROX_EQUAL", {TK_RELOP, NULL, "APPROX_EQUAL"}},\
                                 {"APPROX_DIFF", {TK_RELOP, NULL, "APPROX_DIFF"}},\
                                 {"ASSIGNMENT", {TK_ASSIGNMENT, NULL, ""}},\
                                 {"GREATER", {TK_RELOP, NULL, "GREATER"}},\
                                 {"LESS", {TK_RELOP, NULL, "LESS"}},\
                                 {"GREATER_EQUAL", {TK_RELOP, NULL, "GREATER_EQUAL"}},\
                                 {"LESS_EQUAL", {TK_RELOP, NULL, "LESS_EQUAL"}},\
                                 {"CHAR", {TK_CHAR, NULL, ""}},\
                                 {"SEMICOLON", {TK_SEMICOLON, NULL, ""}},\
                                 {"COLON", {TK_COLON, NULL, ""}},\
                                 {"COMMA", {TK_COMMA, NULL, ""}},\
                                 {"L_PAR", {TK_LPAR, NULL, ""}},\
                                 {"R_PAR", {TK_RPAR, NULL, ""}},\
                                 {"L_BRACE", {TK_START_SCOPE, NULL, ""}},\
                                 {"R_BRACE", {TK_END_SCOPE, NULL, ""}},\
                                 {"ARROW", {TK_ARROW, NULL, ""}},\
                                 {"COMMENT", {TK_WHITE, NULL, ""}}}


#define RESERVED {{"if", {TK_IF, NULL, ""}},\
                  {"else",{TK_ELSE, NULL, ""}},\
                  {"and", {TK_LOGOP, NULL, "AND"}},\
                  {"or", {TK_LOGOP, NULL, "OR"}},\
                  {"xor", {TK_LOGOP, NULL, "XOR"}},\
                  {"not", {TK_LOGOP, NULL, "NOT"}},\
                  {"true", {TK_LOGVAL, NULL, "TRUE"}},\
                  {"false", {TK_LOGVAL, NULL, "FALSE"}},\
                  {"when", {TK_WHEN, NULL, ""}},\
                  {"otherwise", {TK_OTHERWISE, NULL, ""}},\
                  {"select", {TK_SELECT, NULL, ""}},\
                  {"func", {TK_FUNC, NULL, ""}},\
                  {"int", {TK_TYPE, NULL, "INT"}},\
                  {"float", {TK_TYPE, NULL, "FLOAT"}},\
                  {"char", {TK_TYPE, NULL, "CHAR"}},\
                  {"bool", {TK_TYPE, NULL, "BOOL"}},\
                  {"return", {TK_RETURN, NULL, ""}},\
                  {"for", {TK_FOR, NULL, ""}}}

//const static std::vector<Automata::transition_t> transitions = {
#define TRANSITIONS {\
{"s0", {'0','9'}, "WHOLE"},\
{"s0", {'a', 'z'}, "ID"},\
{"s0", {'A', 'Z'}, "ID"},\
{"s0", {'_'}, "ID"},\
{"s0", {' '}, "WHITE_SPACE"},\
{"s0", {'\t'}, "WHITE_SPACE"},\
{"s0", {'\n'}, "WHITE_SPACE"},\
{"s0", {'\r'}, "WHITE_SPACE"},\
{"s0", {'+'}, "PLUS_SIGN"},\
{"s0", {'-'}, "MINUS_SIGN"},\
{"s0", {'*'}, "MULT_SIGN"},\
{"s0", {'/'}, "DIV_SIGN"},\
{"s0", {'%'}, "MOD_SIGN"},\
{"s0", {'('}, "L_PAR"},\
{"s0", {')'}, "R_PAR"},\
{"s0", {'{'}, "L_BRACE"},\
{"s0", {'}'}, "R_BRACE"},\
{"s0", {'>'}, "GREATER"},\
{"s0", {'<'}, "LESS"},\
{"s0", {'='}, "ASSIGNMENT"},\
{"s0", {','}, "COMMA"},\
{"s0", {'\''}, "s2"},\
{"s0", {'!'}, "s4"},\
{"s0", {'~'}, "s5"},\
{"s0", {';'}, "SEMICOLON"},\
{"s0", {':'}, "COLON"},\
{"WHITE_SPACE", {' '}, "WHITE_SPACE"},\
{"WHITE_SPACE", {'\t'}, ""},\
{"WHITE_SPACE", {'\n'}, "WHITE_SPACE"},\
{"WHITE_SPACE", {'\r'}, "WHITE_SPACE"},\
{"ID", {'A', 'Z'}, "ID"},\
{"ID", {'a', 'z'}, "ID"},\
{"ID", {'0', '9'}, "ID"},\
{"ID", {'_'}, "ID"},\
{"WHOLE", {'0', '9'},"WHOLE"},\
{"WHOLE", {'.'}, "s1"},\
{"s1", {'0', '9'}, "FRAC"},\
{"FRAC", {'0', '9'}, "FRAC"},\
{"s2", {0,127}, "s3"},\
{"s3", {'\''}, "CHAR"},\
{"s4", {'='}, "DIFF"},\
{"s5", {'='}, "s6"},\
{"s6", {'='}, "APPROX_EQUAL"},\
{"s5", {'!'}, "s7"},\
{"s7", {'='}, "APPROX_DIFF"},\
{"ASSIGNMENT", {'='}, "EQUAL"},\
{"GREATER", {'='}, "GREATER_EQUAL"},\
{"LESS", {'='}, "LESS_EQUAL"},\
{"MINUS_SIGN", {">"}, "ARROW"},\
{"s0", {'#'}, "COMMENT"}}

class LexicalException : public std::exception
{
    private:
        std::string _msg;
    public:
        LexicalException(const std::string& message, const int line, const int column): _msg(std::to_string(line) + ":" + std::to_string(column) + " " + "LEXICAL_ERROR \n" + message){}

        const char* what() const noexcept {return _msg.c_str();}
};

class Lexer
{
    private:
        Automata::FDA* _automata;
        std::ifstream _src;
        std::stringstream _buffer;
        std::string _line_buffer;
        int _start_index;
        int _current_index;
        int _current_line;
        int _current_col;

        SymbolTable _symbol_table;

        std::unordered_map<std::string, token_t> _token_return;
        std::unordered_map<std::string, token_t> _keywords;

    public:
        Lexer(std::string src);
        ~Lexer();

        bool update_buffer();
        
        token_t getNextToken();
        
        bool scan();
};

#endif //LEXER_H_
