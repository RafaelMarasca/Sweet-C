#include "Lexer.h"
#include "parser.h"
#include <iostream>


int main(int argc, char **argv)
{
	if(argc != 2)
	{
		std::cout<<"Invalid number of arguments!"<<std::endl;
		return 0;
	}
	
	bool comp = false;
	Lexer l(argv[1]);
	LL1 prs;

	try
	{
		std::vector<token_t> token_str = l.getTokenString();
		
		if(!token_str.empty())
		{
			comp = prs.parse(token_str);
		}
	
	}
	catch(LexicalException err)
	{
		std::cout<<err.what()<<std::endl;
		return -1;
	}
	
	
	if(comp)
		std::cout<<"Compiled Successfully!"<<std::endl;

	return 0;
}
