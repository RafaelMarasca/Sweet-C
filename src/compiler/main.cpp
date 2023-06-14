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
	Lexer l(argv[1]);

	bool isLexicallyAccepted = l.scan();
	
	LL1 prs;
	if(isLexicallyAccepted)
	{
		prs.parse("lexer_output.txt");
	}

	return 0;
}
