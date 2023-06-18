#include "Lexer.h"
#include "parser.h"
#include "Semantic.h"

#include <iostream>

int main(int argc, char **argv)
{
	if(argc != 2)
	{
		std::cout<<"Invalid number of arguments!"<<std::endl;
		return 0;
	}
	
	Node *d_tree = nullptr;
	Lexer l(argv[1]);
	LL1 prs;
	bool notsemerror = true;

	try
	{
		std::vector<token_t> token_str = l.getTokenString();
		
		if(!token_str.empty())
		{
			std::ofstream fileOutput("lexer_output.txt");
			for(auto &to : token_str)
			{
				fileOutput<<to<<std::endl;
			}
			
			d_tree = prs.parse(token_str);
		
			if(d_tree)
			{
				Semantic_analyzer sem(d_tree);
				
				notsemerror = sem.tree_traverse();
			}
		}
	
	}
	catch(LexicalException err)
	{
		std::cout<<err.what()<<std::endl;
		return -1;
	}
	
	if(d_tree && notsemerror)
	{
		std::cout<<"Compiled successfully!"<<std::endl;
	}

	d_tree->print();

	return 0;
}
