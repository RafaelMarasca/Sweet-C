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
			Node *auxRHS = no->_children[2]->_children[1];
			std::string rhs_type;
			std::string lhs_type = no->_children[0]->_children[0]->_value.second;
			
			while(!auxRHS->_children.empty())
			{
				std::pair<int, int> errpos = {0, 0};
				if(auxRHS->_children[0]->_value.first == "<var_value>")
				{
					Node *auxID = auxRHS->_children[0]->_children[0]->_children[0]; 
					
					bool errflag = true; 
					for(auto &cs : _context_stack)
					{
						if(cs.getSymbol(auxID->_value.second))
						{
							rhs_type = cs.getType(auxID->_value.second);
							errpos = auxID->_pos;
							errflag = false;
							
							break;
							
						}
					}
					if(errflag)
					{
						std::cout<<"SEMANTIC ERROR: undeclared variable '"<<auxID->_value.second<<"' before L:"<<auxID->_pos.first<<" C:"<<auxID->_pos.second<<std::endl;
						return 0;
					}
				}
				else if(auxRHS->_children[0]->_value.first == "<con_value>")
				{
					Node *auxCon = auxRHS->_children[0]->_children[0]->_children[0];
					
					if(auxCon->_value.first == "<int_con>")
						rhs_type = "INT";
					else if(auxCon->_value.first == "<float_con>")
						rhs_type = "FLOAT";
					else if(auxCon->_value.first == "<char_con>")
						rhs_type = "CHAR";
					else if(auxCon->_value.first == "<bool_con>")
						rhs_type = "BOOL";
						
					errpos = auxCon->_children[0]->_pos;
				}
				if(rhs_type != lhs_type)
				{
					std::cout<<"SEMANTIC ERROR: incompatible types"<<" before L:"<<errpos.first<<" C:"<<errpos.second<<std::endl;
					return 0;
				}
				
				auxRHS = auxRHS->_children[1];
				if(!auxRHS->_children.empty())
					auxRHS = auxRHS->_children[1];
			}

				
		}
	}
	return 1;
}


bool Semantic_analyzer::check_expr(Node *no)
{
	Node *auxLHS = no->_children[0];
	Node *auxRHS = no->_children[1];
	std::string lhs_type;
	std::string rhs_type;
	
	if(auxLHS->_children[0]->_value.first == "<var_value>")
	{
		Node *auxID = auxLHS->_children[0]->_children[0]->_children[0]; 
		
		bool errflag = true; 
		for(auto &cs : _context_stack)
		{
			if(cs.getSymbol(auxID->_value.second))
			{
				lhs_type = cs.getType(auxID->_value.second);
				errflag = false;
				break;
				
			}
		}
		if(errflag)
		{
			std::cout<<"SEMANTIC ERROR: undeclared variable '"<<auxID->_value.second<<"' before L:"<<auxID->_pos.first<<" C:"<<auxID->_pos.second<<std::endl;
			return 0;
		}
	}
	else if(auxLHS->_children[0]->_value.first == "<con_value>")
	{
		Node *auxCon = auxLHS->_children[0]->_children[0]->_children[0]->_children[0];
		
		if(auxCon->_value.first == "<int_con>")
			lhs_type = "INT";
		else if(auxCon->_value.first == "<float_con>")
			lhs_type = "FLOAT";
		else if(auxCon->_value.first == "<char_con>")
			lhs_type = "CHAR";
		else if(auxCon->_value.first == "<bool_con>")
			lhs_type = "BOOL";
	}
	
	while(!auxRHS->_children.empty())
	{
		std::pair<int, int> errpos = {0, 0};
		if(auxRHS->_children[0]->_value.first == "<var_value>")
		{
			Node *auxID = auxRHS->_children[0]->_children[0]->_children[0]; 
			
			bool errflag = true; 
			for(auto &cs : _context_stack)
			{
				if(cs.getSymbol(auxID->_value.second))
				{
					rhs_type = cs.getType(auxID->_value.second);
					errpos = auxID->_pos;
					errflag = false;
					
					break;
					
				}
			}
			if(errflag)
			{
				std::cout<<"SEMANTIC ERROR: undeclared variable '"<<auxID->_value.second<<"' before L:"<<auxID->_pos.first<<" C:"<<auxID->_pos.second<<std::endl;
				return 0;
			}
		}
		else if(auxRHS->_children[0]->_value.first == "<con_value>")
		{
			Node *auxCon = auxRHS->_children[0]->_children[0]->_children[0];
			
			if(auxCon->_value.first == "<int_con>")
				rhs_type = "INT";
			else if(auxCon->_value.first == "<float_con>")
				rhs_type = "FLOAT";
			else if(auxCon->_value.first == "<char_con>")
				rhs_type = "CHAR";
			else if(auxCon->_value.first == "<bool_con>")
				rhs_type = "BOOL";
				
			errpos = auxCon->_children[0]->_pos;
		}
		if(rhs_type != lhs_type)
		{
			std::cout<<"SEMANTIC ERROR: incompatible types"<<" before L:"<<errpos.first<<" C:"<<errpos.second<<std::endl;
			return 0;
		}
		
		auxRHS = auxRHS->_children[1];
		if(!auxRHS->_children.empty())
			auxRHS = auxRHS->_children[1];
	}
		
	
	return 1;
}



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
		
		do
		{
			if(find_var(auxDe->_children[1]))
			{
				std::cout<<"SEMANTIC ERROR: redefinition of variable '"<<auxDe->_children[1]->_value.second<<"' before L:"<<auxDe->_children[1]->_pos.first<<" C:"<<auxDe->_children[1]->_pos.second<<std::endl;
				return 0;
			}
			
			Symbol symb(auxDe->_children[1]->_value.second, auxDe->_children[0]->_children[0]->_value.second, TK_ID);
			
			this->_context_stack[_context_stack.size() - 1].addSymbol(symb);
			
			if(!auxArglist->_children.empty())
			{
				auxDe = auxArglist->_children[0];
				auxArglist = auxArglist->_children[1];
			}
		}
		while(!auxArglist->_children.empty());

	}
	
	return 1;
}


bool Semantic_analyzer::check_return(Node *no)
{
	if(!_func_stack.empty())
	{
		_func_stack.pop();
	}
	
	if(_context_stack.size() > 1)
	{
		_context_stack.pop_back();
	}
	
	return 1;
}


bool Semantic_analyzer::preorder(Node *cur_node)
{
	
	if(cur_node)
	{	
		//std::cout<<cur_node->_value.first<<"\t"<<cur_node->_value.second<<std::endl;
		
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
			return this->check_expr(cur_node);
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
