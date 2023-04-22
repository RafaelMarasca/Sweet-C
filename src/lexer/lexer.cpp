#include "Automata.h"
#include "SymbolTable.h"

#include <string>
#include <fstream>
#include <sstream>
#include <exception>

#define MAX_LEXEME_SIZE 64
#define BUFFER_SIZE 512

#define INITIAL_STATE "s0"
#define ACCEPTING_STATES {"TK_NUM1", "TK_NUM2", "TK_ID1", "TK_WHITE"}
#define ACCEPTING_STATES_TOKENS {{"TK_NUM1", TK_NUM}, {"TK_NUM2", TK_NUM}, {"TK_ID1", TK_ID}, {"TK_WHITE", TK_WHITE}}


class LexicalException :public std::exception
{
    private:
        std::string _msg;
    public:
        LexicalException(const std::string& message, const int line, const int column): _msg(std::to_string(line) + ":" + std::to_string(column) + " " + "LEXICAL_ERROR \n" + message){}

        const char* what() const noexcept {return _msg.c_str();}
};

std::vector<Transition> transitions = {
{"s0", {'0','9'}, "TK_NUM1"},
{"s0", {'a', 'z'}, "TK_ID1"},
{"s0", {'A', 'Z'}, "TK_ID1"},
{"s0", {' '}, "TK_WHITE"},
{"s0", {'\t'}, "TK_WHITE"},
{"s0", {'\n'}, "TK_WHITE"},
{"s0", {'\r'}, "TK_WHITE"},


{"TK_WHITE", {' '}, "TK_WHITE"},
{"TK_WHITE", {'\t'}, "TK_WHITE"},
{"TK_WHITE", {'\n'}, "TK_WHITE"},

{"TK_ID1", {'A', 'Z'}, "TK_ID1"},
{"TK_ID1", {'a', 'z'}, "TK_ID1"},
{"TK_ID1", {'0', '9'}, "TK_ID1"},

{"TK_NUM1", {'0', '9'},"TK_NUM1"},
{"TK_NUM1", {'.'}, "s1"},

{"s1", {'0', '9'}, "TK_NUM2"},

{"TK_NUM2", {'0', '9'}, "TK_NUM2"}};


class Lexer
{
    private:
        FDA* _automata;
        std::ifstream _src;
        std::stringstream _buffer;
        std::string _line_buffer;
        int _start_index;
        int _current_index;
        int _current_line;
        int _current_col;

        SymbolTable _symbol_table;

        std::unordered_map<std::string, token_type> _token_return;

    public:
        Lexer(std::string src);
        ~Lexer();

        bool update_buffer();

        token getNextToken();

};

Lexer::Lexer(std::string src)
{
    _src.open(src);
    _start_index = 0;
    _current_index = _start_index;
    _current_line = 0;
    _current_col = 1;

    _automata = new FDA(INITIAL_STATE, ACCEPTING_STATES);
    for(auto i = transitions.begin(); i != transitions.end(); i++)
        _automata->addTransition(*i);

    _token_return = ACCEPTING_STATES_TOKENS;
    _buffer<<_src.rdbuf();
    _line_buffer = "";

}

Lexer::~Lexer()
{
    delete _automata;
    _src.close();
}

bool Lexer::update_buffer()
{
    if(!_buffer.eof())
    {
        std::getline(_buffer, _line_buffer);
        if(_line_buffer.size())
        {
            _current_line++;
            _current_col = 1;
            _current_index = 0;
            _start_index = 0;
            return true;
        }
    }  

    return false;
    
}

token Lexer::getNextToken()
{
    _automata->clear();

    std::string lexeme;   
    std::string last_valid_state = "";
    int last_valid_index = -1; 

    if(_current_index >= _line_buffer.size())
    {
        if(!update_buffer())
            return {TK_EOF, NULL, ""};
    }

    while(_current_index < (_start_index + MAX_LEXEME_SIZE))
    {
        info step_info = _automata->step(_line_buffer[_current_index]);

        if(!step_info.is_valid)
        {
            if(last_valid_index == -1)
            {
                lexeme = _line_buffer.substr(_start_index, _current_index - _start_index + 1);
                throw LexicalException(lexeme + " - Invalid Lexeme!", _current_line, _current_col);
            }
                
    
            lexeme = _line_buffer.substr(_start_index, last_valid_index - _start_index + 1);
            _current_col += lexeme.size();
            _start_index = last_valid_index + 1;
            _current_index = _start_index;

            
            if(_token_return[last_valid_state] != TK_WHITE)
            {
                token t;
                t.tk = _token_return[last_valid_state];
                Symbol s (lexeme, "global", t.tk);
                t.table_pointer = _symbol_table.addSymbol(s);
                t.value = lexeme;
                return t;
            }else{
                _automata->clear();
                lexeme = "";   
                last_valid_state = "";
                last_valid_index = -1; 
            }
        }else
        {
            if(step_info.is_accepting)
            {
                last_valid_index = _current_index;
                last_valid_state = step_info.state;
            }
            _current_index++;
        }
    }

    throw LexicalException("Lexeme Size Error!", _current_line, _current_col);


    // while(_current_index < (_start_index + MAX_LEXEME_SIZE))
    // {
    //     //std::cout<<last_valid_index;
    //     if((_current_index >= BUFFER_SIZE) || (_current_index > buffer.size()))
    //     {
    //         if(last_valid_index == -1)
    //             return t;

    //          lexeme = buffer.substr(_start_index, last_valid_index - _start_index+1);
    //         _start_index = last_valid_index + 1;
    //         _current_index = _start_index;

    //         token_type tk_type = states_token[last_valid_state];

    //         Symbol s(lexeme, "global", tk_type);
    //         t.table_pointer = st.addSymbol(s);
    //         t.tk = tk_type;
    //         t.value = lexeme;
    //         return t;
    //     }

    //     info step_info = _automata->step(buffer[_current_index]);
    //     std::cout<<step_info.state<<std::endl;
    //     if(! step_info.is_valid)
    //     {
    //         std::cout<<buffer[_current_index]<<std::endl;
    //         if(last_valid_index == -1)
    //             return t;
                
    //         lexeme = buffer.substr(_start_index, last_valid_index - _start_index);
    //         _start_index = last_valid_index + 1;
    //         _current_index = _start_index;

    //         token_type tk_type = states_token[last_valid_state];

    //         Symbol s(lexeme, "global", tk_type);
    //         t.table_pointer = st.addSymbol(s);
    //         t.tk = tk_type;
    //         t.value = lexeme;
    //         return t;
    //     }else
    //     {
    //         if(step_info.is_accepting)
    //         {
    //             last_valid_index = _current_index;
    //             last_valid_state = step_info.state;
    //             std::cout<<buffer[_current_index]<<std::endl;
    //         }
    //         _current_index ++;
    //     } 
    // }

    // throw std::string("LEXEME SIZE IS TOO BIG");
}


int main()
{
    Lexer l("input.txt");

    token t;

    do
    {
        try{
            t = l.getNextToken();
            std::cout<<t;
        }catch(LexicalException e)
        {
            std::cout<<e.what();
            t.tk = TK_INVALID;
        }

    }while(t.tk != TK_EOF && t.tk != TK_INVALID);
    
    
}