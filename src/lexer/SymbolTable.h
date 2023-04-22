#ifndef SYMBOL_TABLE_H_
#define SYMBOL_TABLE_H_

#include <unordered_map>
#include <string>
#include <iostream>

enum token_type
{
    TK_ID,
    TK_NUM,
    TK_WHITE,
    TK_INVALID,
    TK_EOF
};

std::string token_to_string(token_type tk)
{
    switch (tk)
    {
        case TK_ID: return "TK_ID";
        case TK_NUM: return "TK_NUM";
        case TK_WHITE: return "TK_WHITE";
        case TK_INVALID: return "TK_INVALID";
        case TK_EOF: return "TK_EOF";
    }
    return "";
}


class Symbol
{
    private:
        std::string _lexeme;
        std::string _scope;
        token_type _token_type;

    public:
        Symbol(std::string lexeme, std::string scope, token_type token) : _lexeme(lexeme), _scope(scope), _token_type(token){};
        ~Symbol(){};

        std::string get_lexeme(){return _lexeme;};

        operator std::string() const {return std::string({std::string("<") + std::to_string(int(_token_type)) + std::string(",") + _lexeme  + std::string(",") + _scope + std::string(">")}); } 
};  

struct token
{
    token_type tk;
    Symbol* table_pointer;
    std::string value;

    friend std::ostream & operator << (std::ostream &out, const token &t)
    {
        out << "<" << token_to_string(t.tk) << "," << t.value << ">";
        if(t.table_pointer != NULL)
            out << std::string(*t.table_pointer);
        out<<std::endl;
        return out;
    }
};


class SymbolTable
{
    private:
        std::unordered_map<std::string, Symbol*> _table;

    public:
        
        SymbolTable(){};
        ~SymbolTable(){ for(auto it = _table.begin(); it != _table.end(); it++){delete it->second;}};

        Symbol* addSymbol(Symbol& s)
        {
            if(_table.find(s.get_lexeme()) == _table.end())
            {
                _table[s.get_lexeme()] = new Symbol(s);
            }

            return _table[s.get_lexeme()];
        }

        friend std::ostream & operator << (std::ostream &out, const SymbolTable &s)
        {
            for(auto it = s._table.begin(); it != s._table.end(); it++)
                out << std::string(*(it->second)) << std::endl;
            return out;
        }
};


#endif //SYMBOL_TABLE_H_