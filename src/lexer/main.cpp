#include "Lexer.h"
#include "Symbol.h"
#include <iostream>


int main()
{
    Lexer l("input.txt");

    token_t t;

    do
    {
        try{
            t = l.getNextToken();
            std::cout<<t;
        }catch(LexicalException e)
        {
            std::cout<<e.what();
            t.token_type = TK_INVALID;
        }

    }while(t.token_type != TK_EOF && t.token_type != TK_INVALID);

}