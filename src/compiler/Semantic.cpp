#include "Semantic.h"

Semantic_analyzer::Semantic_analyzer(Node *der_tree)
{
	_derivation_tree = der_tree;
	_context_stack = std::vector<SymbolTable>();
	_func_stack = std::stack<std::pair<std::string, std::string>>();
	
	SymbolTable s;
	
	_context_stack.push_back(s);
}


Semantic_analyzer::~Semantic_analyzer()
{

}

bool Semantic_analyzer::find_var(Node *no)
{
		for(auto &cs : _context_stack)
		{
			if(cs.getSymbol(no->_value.second))				
			{
				return 1;
			}
		}
	return 0;
}

bool Semantic_analyzer::check_de(Node *no)
{
	if(no)
	{
		if(find_var(no->_children[1]))
		{
			std::cout<<"SEMANTIC ERROR: redefinition of variable '"<<no->_children[1]->_value.second<<"' before L:"<<no->_children[1]->_pos.first<<" C:"<<no->_children[1]->_pos.second<<std::endl;
			return 0;
		}
		
		Symbol symb(no->_children[1]->_value.second, no->_children[0]->_children[0]->_value.second, TK_ID);
		_context_stack[_context_stack.size() - 1].addSymbol(symb);

		if(no->_children[2]->_children.size() == 2)
		{	
			

			std::cout<<"bbbbbbbBBBBBBBBBBBBbbbbbbbbbbb"<<std::endl;
		}
	}
	return 1;
}

/*
void Semantic_analyzer::check_expr(Node *no)
{

}

*/


void Semantic_analyzer::check_func(Node *no)
{
	_func_stack.push({no->_children[1]->_children[0]->_value.second, no->_children[5]->_children[0]->_value.second});
	
	return;
}

bool Semantic_analyzer::check_arglist(Node *no)
{
	if(!no->_children.empty())
	{
		SymbolTable st;
		_context_stack.push_back(st);

		Node *auxDe = no->_children[0];
		Node *auxArglist = no->_children[1];
		
		if(find_var(auxDe->_children[1]))
		{
			std::cout<<"SEMANTIC ERROR: redefinition of variable '"<<auxDe->_children[1]->_value.second<<"' before L:"<<auxDe->_children[1]->_pos.first<<" C:"<<auxDe->_children[1]->_pos.second<<std::endl;
			return 0;
		}
		
		Symbol symb(auxDe->_children[1]->_value.second, auxDe->_children[0]->_children[0]->_value.second, TK_ID);
		
		this->_context_stack[_context_stack.size() - 1].addSymbol(symb);
	}
	
	return 1;
}


bool Semantic_analyzer::check_return(Node *no)
{
	if(!_func_stack.empty())
		_func_stack.pop();
	
	if(!_context_stack.empty())
	{
		_context_stack.pop_back();
	}
	
	return 1;
}


bool Semantic_analyzer::preorder(Node *cur_node)
{
	
	if(cur_node)
	{	
		std::cout<<cur_node->_value.first<<"\t"<<cur_node->_value.second<<std::endl;
		
		if(cur_node->_value.first == "<func>")
		{
			this->check_func(cur_node);
		}
		else if(cur_node->_value.first == "<arg_list>")
		{
			check_arglist(cur_node);
			return 1;
		}
		else if(cur_node->_value.first == "TK_START_SCOPE")
		{
			SymbolTable s;
			this->_context_stack.push_back(s);
			
			return 1;
		}
		else if(cur_node->_value.first == "TK_END_SCOPE")
		{
			this->_context_stack.pop_back();
			return 1;
		}
		else if(cur_node->_value.first == "<expression>")
		{
			std::cout<<";;;;;;;;;;;;;cheguei expressão"<<std::endl;
			return 1;
		}
		else if(cur_node->_value.first == "<de>")
		{
			return this->check_de(cur_node);
		}
		else if(cur_node->_value.first == "<return_statement>")
		{
			this->check_return(cur_node);
			return 1;
		}
		
		for(auto &c : cur_node->_children)
		{
			if(this->preorder(c) == 0)
				break;	
		}
	}
	
	return 1;
}

bool Semantic_analyzer::tree_traverse()
{
	return this->preorder(this->_derivation_tree);
}
