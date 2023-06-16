/**
 * @file lexer.cpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2023-04-23
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include "Lexer.h"
#include "Automata.h"
#include "Symbol.h"

#include <string>
#include <fstream>
#include <sstream>
#include <exception>

const static std::vector<Automata::transition_t> transitions = TRANSITIONS;

Lexer::Lexer(std::string src)
{
    _src.open(src);
    _start_index = 0;
    _current_index = 0;
    _current_line = 0;
    _current_col = 1;
    _keywords = RESERVED;

    _automata = new Automata::FDA(INITIAL_STATE, ACCEPTING_STATES);

    for(auto i = transitions.begin(); i != transitions.end(); i++)
        _automata->addTransition(*i);

    _token_return = ACCEPTING_STATES_TOKENS;
    _buffer << _src.rdbuf();
    _line_buffer = "";

}

Lexer::~Lexer()
{
    delete _automata;
    _src.close();
}

bool Lexer::update_buffer()
{
    while(!_buffer.eof())
    {
        std::getline(_buffer, _line_buffer);
    
        _current_line++;
        _current_col = 1;
        _current_index = 0;
        _start_index = 0;
        return true;
    }  

    return false;
}

std::vector<token_t> Lexer::getTokenString()
{
    bool skip = false;
    std::vector<token_t> tokens;

    while(update_buffer())
    {
        _automata->clear();

        std::string lexeme;   
        std::string last_valid_state = "";
        int last_valid_index = -1; 
        
        while(_current_index < (_line_buffer.size()))
        {
            if(_line_buffer[_current_index] == '#')
                break;

            if( _line_buffer[_current_index] == ' '  || 
                _line_buffer[_current_index] == '\t' || 
                _line_buffer[_current_index] == '\n' || 
                _line_buffer[_current_index] == '\r')
            {
                _start_index++;
                _current_index++;
                _current_col++;
                continue;
            }

            if(_line_buffer[_current_index] == '!')
            {
                skip = !skip;
                _current_index++;
                _start_index ++;
                _current_col++;
                continue;
            }

            if(skip)
            {
                _start_index++;
                _current_index++;
                _current_col++;
                continue;
            }

            Automata::transition_info_t step_info = _automata->step(_line_buffer[_current_index]);

            while(step_info.is_valid)
            {
                if(_current_index > (_start_index + MAX_LEXEME_SIZE))
                    throw LexicalException("Lexeme Size Error!", _current_line, _current_col);

                last_valid_index = _current_index;
                last_valid_state = step_info.state;
                _current_index++;
                step_info = _automata->step(_line_buffer[_current_index]);
            }
            
            if(last_valid_index == -1)
            {
                lexeme = _line_buffer.substr(_start_index, _current_index - _start_index + 1);
                throw LexicalException(lexeme + " - Invalid Lexeme!", _current_line, _current_col);
            }

            token_t tk = _token_return[last_valid_state];

            lexeme = _line_buffer.substr(_start_index, last_valid_index - _start_index + 1);
           

            if(tk.token_type == TK_ID)
            {
                if(_keywords.find(lexeme) != _keywords.end())
                {
                    tk = _keywords[lexeme];
                }else
                {
                    Symbol s (lexeme, "global", tk.token_type);
                    tk.table_pointer = _symbol_table.addSymbol(s);
                }  
            }else if(tk.token_type == TK_WHOLE || tk.token_type == TK_FRAC || tk.token_type == TK_LOGVAL)
            {
                tk.value = lexeme;
            }   

             _current_col += lexeme.size();
            _start_index = last_valid_index + 1;
            _current_index = _start_index;

            tk.column = _current_col;
            tk.line = _current_line;

            tokens.push_back(tk);

            _automata->clear();
            lexeme = "";   
            last_valid_state = "";
            last_valid_index = -1; 
        }
    }
    token_t endtk;
    endtk.token_type = TK_EOF;
    endtk.line = _current_line;
    endtk.column = _current_col;
    endtk.table_pointer = nullptr;
    tokens.push_back(endtk);

    return tokens;
}
