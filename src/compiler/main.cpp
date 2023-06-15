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
	
	/*
	Lexer l(argv[1]);

	bool isLexicallyAccepted = l.scan();
	
	LL1 prs;
	if(isLexicallyAccepted)
	{
		prs.parse("lexer_output.txt");
	}
	*/
	
	Node *tree = new Node({"foo", "bar"});
	tree->insert({"filho1", "aaaaa"});
	tree->_children[0]->insert({"filho do filho 1", "aaaa"});
	tree->insert({"filho2", "aaaaa"});
	tree->insert({"filho3", "aaaaa"});
	tree->insert({"filho4", "aaaaa"});
	
	delete tree;

	return 0;
}
