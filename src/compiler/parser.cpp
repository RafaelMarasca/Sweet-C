#include "parser.h"
#include "parse_table.h"
#include "parse_table_sync.h"
#include "parse_table_error.h"

#include <iostream>
#include <fstream>

//initialize aux tables
std::unordered_map<std::string, std::unordered_map<std::string, std::string>> LL1::_parse_table = PARSE_TABLE;
std::unordered_map<std::string, std::vector<std::string>> LL1::_parse_table_sync = PARSE_TABLE_SYNC;
std::unordered_map<std::string, std::string> LL1::_parse_table_error = PARSE_TABLE_ERROR;

LL1::LL1()
{
	//initialize parse stack and vector
	_parse_stack = std::stack<std::string>();
	_input_vec = std::vector<std::string>();
	_input_pos = std::vector<std::pair<int, int>>();
	_input_val = std::vector<std::string>();
	_parse_tree = nullptr;

	//push end of string token
	_parse_stack.push("$");
}

LL1::~LL1()
{
    if(_parse_tree)
    	delete _parse_tree;
}

Node* LL1::parse(std::vector<token_t> token_str)
{
	for(auto tk : token_str)
	{
		_input_vec.push_back(token_to_string(tk.token_type));
		_input_val.push_back(tk.value);
		_input_pos.push_back({tk.line, tk.column});
	}
	
	//for(auto c : _input_vec)
	//	std::cout<<c<<std::endl;
	
	
	//push starting nonterminal into the parsing stack
	_parse_stack.push("<program>");
	_parse_tree = new Node({"<program>", ""}, _parse_tree, {0, 0});
	Node *aux_next_node = _parse_tree;
	
	int input_pos = 0;
	bool parse_success = true;
	//std::ofstream fileOutput("parser_output.txt");
	while(_parse_stack.top() != "$" || _input_vec[input_pos] != "$")
	{
		std::vector<std::string> aux_vec;
		std::string aux_string = "";
		
		//if the current symbol at the top of the stack is a terminal
		if(_parse_stack.top()[0] != '<')
		{
			//match the current input symbol
			if(_parse_stack.top() == _input_vec[input_pos])
			{
				_parse_stack.pop();
				
				aux_next_node->_value.second = _input_val[input_pos];
				aux_next_node->_pos = _input_pos[input_pos];
				//std::cout<<"////////////////"<<aux_next_node->_value.first<<";;;;;;;;;;;"<<_input_vec[input_pos]<<std::endl;
				
				if(aux_next_node)
				{
					while(aux_next_node && aux_next_node->_children.size() <= aux_next_node->_cur_child)
					{
						aux_next_node = aux_next_node->_father;
					}
		
					if(aux_next_node)					
						aux_next_node = aux_next_node->_children[aux_next_node->_cur_child++];
				}
				
				if(input_pos < _input_vec.size())
					input_pos++;
			}
			//error if not matched
			else
			{				
				parse_success = false;
				std::cout<<"SYNTAX ERROR: missing '"<<_parse_stack.top()<<"' before L:"<<_input_pos[input_pos].first<<" C:"<<_input_pos[input_pos].second<<"."<<std::endl;
				_parse_stack.pop();
				
				
				if(aux_next_node && !aux_next_node->_children.empty() && aux_next_node->_children.size() > aux_next_node->_cur_child+1)
				{
					aux_next_node = aux_next_node->_children[++aux_next_node->_cur_child];
				}
				else
				{
					aux_next_node = aux_next_node->_father;
				}
			}
		}
		//if derivation is valid
		else if(_parse_table[_parse_stack.top()][_input_vec[input_pos]] != "-")
		{		
			//"tokenizes" the derivation
			bool flag = false;
			for(auto c : _parse_table[_parse_stack.top()][_input_vec[input_pos]])
			{
				if(c == ' ')
					continue;
					
				if((c == '<' || c == '>') && aux_string != "")
				{
					if(c == '>')
						aux_string += c;
						
					aux_vec.push_back(aux_string);
					aux_string = "";
					flag = true;
				}
				if(c != '>')
					aux_string += c;
			}
			
			if(!aux_string.empty())
				aux_vec.push_back(aux_string);
			
			//print derivation
			//fileOutput<<_parse_stack.top()<<"::="<<_parse_table[_parse_stack.top()][_input_vec[input_pos]]<<std::endl;
						
			//pop current non-terminal
			_parse_stack.pop();			
			
			//push derivation into the parse stack
			for(std::vector<std::string>::reverse_iterator i = aux_vec.rbegin(); i != aux_vec.rend(); i++)			
			{
				_parse_stack.push(*i);
			}
			
			//insert derivation into the parse tree
			if(aux_next_node)
			{
				for(auto d : aux_vec)
				{
					std::string straux = ""; //d[0] != '<' ? d : "";	
					aux_next_node->insert({d, straux}, aux_next_node, {0, 0});
				}
				
				//std::cout<<aux_next_node->_value.first<<"------>";
				for(auto nd : aux_next_node->_children)
				{
				//	std::cout<<"#"<<nd->_value.first<<" ";	
				}
				//std::cout<<std::endl;
			}
			
			//next step on parse tree or go back to parent
			if(aux_next_node && !aux_next_node->_children.empty() && aux_next_node->_children.size() > aux_next_node->_cur_child)
			{
				aux_next_node = aux_next_node->_children[aux_next_node->_cur_child++];
				//std::cout<<"::::::"<<aux_next_node->_value.first<<";;;;;;;;;;"<<_parse_stack.top()<<std::endl;
			}
			else
			{
				while(aux_next_node && aux_next_node->_children.size() <= aux_next_node->_cur_child)
				{
					aux_next_node = aux_next_node->_father;
				}
				
				if(aux_next_node)
					aux_next_node = aux_next_node->_children[aux_next_node->_cur_child++];
			}
	
		}
		// Error detected
		else if(_parse_table[_parse_stack.top()][_input_vec[input_pos]] == "-")
		{
			parse_success = false;
			std::cout<<"SYNTAX ERROR: "<<_parse_table_error[_parse_stack.top()]<<" before L:"<<_input_pos[input_pos].first<<" C:"<<_input_pos[input_pos].second<<"."<<std::endl;
			std::cout<<_parse_stack.top()<<"//////////////"<<_input_vec[input_pos]<<std::endl;
			
			// Try to find synchronizing token then pop nonterminal
			bool sync_matched = false;
			for(input_pos; input_pos < _input_vec.size()-1; input_pos++)
			{
				for(auto s : _parse_table_sync[_parse_stack.top()])
				{
				
					if(s == _input_vec[input_pos])
					{
						sync_matched = true;
						break;
					}
				}
				if(sync_matched)
					break;
			}
			std::string aux = _parse_stack.top();
			_parse_stack.pop();
			
			if(aux_next_node && !aux_next_node->_children.empty() && aux_next_node->_children.size() > aux_next_node->_cur_child+1)
			{
				aux_next_node = aux_next_node->_children[++aux_next_node->_cur_child];
			}
			else
			{
				aux_next_node = aux_next_node->_father;
			}
			
			if(aux == "<scope_block>")
			{
				_parse_stack.push("TK_END_SCOPE");
				_parse_stack.push("<scope_block'>");
			}
		}	
	}
	return parse_success ? this->_parse_tree : nullptr; 
}
