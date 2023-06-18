#ifndef SYMBOL_H_
#define SYMBOL_H_

#include <unordered_map>
#include <string>
#include <iostream>

enum token_type_t
{
    TK_ID,
    TK_WHOLE,
    TK_FRAC,
    TK_IF,
    TK_ELSE,
    TK_LOGOP,
    TK_LOGVAL,
    TK_RELOP,
    TK_ARITH,
    TK_TYPE,
    TK_FUNC,
    TK_SELECT,
    TK_WHEN,
    TK_OTHERWISE,
    TK_FOR,
    TK_LPAR,
    TK_RPAR,
    TK_START_SCOPE,
    TK_END_SCOPE,
    TK_SEMICOLON,
    TK_COLON,
    TK_COMMA,
    TK_WHITE,
    TK_ASSIGNMENT,
    TK_CHAR,
    TK_INVALID,
    TK_RETURN,
    TK_ARROW,
    TK_EOF
};

enum token_values_t
{
    AND,
    OR,
    XOR,
    NOT,
    LESS,
    GRETER,
    LESS_EQUAL,
    GREATER_EQUAL,
    PLUS,
    MINUS,
    MULT,
    DIV,
    MOD,
    INT,
    FLOAT,
    CHAR,
    BOOL,
    TRUE,
    FALSE,
    DIFF,
    EQUAL
};

static std::string token_to_string(token_type_t tk)
{
    switch (tk)
    {
        case TK_ID: return "TK_ID";
        case TK_WHOLE: return "TK_WHOLE";
        case TK_FRAC: return "TK_FRAC";
        case TK_WHITE: return "TK_WHITE";
        case TK_IF: return "TK_IF";
        case TK_ELSE: return "TK_ELSE";
        case TK_LOGOP: return "TK_LOGOP";
        case TK_LOGVAL: return "TK_LOGVAL";
        case TK_RELOP: return "TK_RELOP";
        case TK_ARITH: return "TK_ARITH";
        case TK_TYPE: return "TK_TYPE";
        case TK_FUNC: return "TK_FUNC";
        case TK_SELECT: return "TK_SELECT";
        case TK_WHEN: return "TK_WHEN";
        case TK_OTHERWISE: return "TK_OTHERWISE";
        case TK_FOR: return "TK_FOR";
        case TK_LPAR: return "TK_LPAR";
        case TK_RPAR: return "TK_RPAR";
        case TK_START_SCOPE: return "TK_START_SCOPE";
        case TK_END_SCOPE: return "TK_END_SCOPE";
        case TK_SEMICOLON: return "TK_SEMICOLON";
        case TK_COLON: return "TK_COLON";
        case TK_COMMA: return "TK_COMMA";
        case TK_ASSIGNMENT: return "TK_ASSIGNMENT";
        case TK_CHAR: return "TK_CHAR";
        case TK_INVALID: return "TK_INVALID";
        case TK_RETURN: return "TK_RETURN";
        case TK_ARROW: return "TK_ARROW";
        case TK_EOF: return "$";
    }
    return "";
}


class Symbol
{
    private:
        std::string _lexeme;
        std::string _lexeme_type;
        token_type_t _token_type;

    public:
        Symbol() : _lexeme(""), _lexeme_type(""), _token_type(TK_EOF){};
        Symbol(std::string lexeme, std::string lexeme_type, token_type_t token_type) : _lexeme(lexeme), _lexeme_type(lexeme_type), _token_type(token_type){};
        ~Symbol(){/*std::cout<<"Deletando"<<std::endl;*/};

        std::string get_lexeme(){return _lexeme;};
	std::string get_lexeme_type(){return _lexeme_type;};

        operator std::string() const {return std::string({std::string("<") + std::to_string(int(_token_type)) + std::string(",") + _lexeme  + std::string(",") + _lexeme_type + std::string(">")}); } 
};  

struct token_t
{
    token_type_t token_type;
    Symbol* table_pointer;
    std::string value;
    int column;
    int line;

    friend std::ostream & operator << (std::ostream &out, const token_t &t)
    {
        if(t.table_pointer != NULL)
            out << "@ " << t.line << ":" << t.column << "  <" << token_to_string(t.token_type) << ", " << t.table_pointer << ">" << std::endl;
        else
            out<< "@ " << t.line << ":" << t.column<< "  <" << token_to_string(t.token_type) << ", " << t.value << ">" << std::endl;
        return out;
    }
};

class SymbolTable
{
    private:
        std::unordered_map<std::string, Symbol> _table;

    public:
        
        SymbolTable(){};
        
        ~SymbolTable(){
        	for (auto& entry : _table) {
                //std::cout<< "deletando "<<std::string(*entry.second) <<std::endl;
                //delete entry.second;
            }       
            _table.clear();
        };

        Symbol addSymbol(Symbol& s)
        {
            if(_table.find(s.get_lexeme()) == _table.end())
            {
                _table[s.get_lexeme()] = Symbol(s);
            }

            return _table[s.get_lexeme()];
        }
        
        bool getSymbol(std::string lex)
        {
        	return _table.find(lex) != _table.end();
        }
        
        std::string getType(std::string lex)
        {
        	if(_table.find(lex) != _table.end())
        	{
        		return _table[lex].get_lexeme_type();
        	}
        
        	return "";
        }


        friend std::ostream & operator << (std::ostream &out, const SymbolTable &s)
        {
            for(auto it = s._table.begin(); it != s._table.end(); it++)
                out << std::string((it->second)) << std::endl;
            return out;
        }
};


#endif //SYMBOL_H_
