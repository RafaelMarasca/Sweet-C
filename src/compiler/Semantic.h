#ifndef SEMANTIC_H_
#define SEMANTIC_H_

#include "parser.h"
#include "Symbol.h"

class Semantic_analyzer{
	private:
		Node *_derivation_tree;
		std::vector<SymbolTable> _context_stack;
		std::stack<std::pair<std::string, std::string>> _func_stack;
		
		bool preorder(Node *cur_node);
		bool check_de(Node *no);
		void check_func(Node *no);
		bool check_arglist(Node *no);
		bool check_return(Node *no);
		bool find_var(Node *no);
		
		
	public: 
		Semantic_analyzer(Node *der_tree);
		~Semantic_analyzer();
		
		bool tree_traverse();
};

#endif
