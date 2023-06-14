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
	_input_pos = std::vector<std::pair<std::string, std::string>>();
	_input_val = std::vector<std::string>();

	//push end of string token
	_parse_stack.push("$");
}

LL1::~LL1()
{
    
}

bool LL1::parse(std::string src)
{
	_src.open(src);

	std::string s1;

	while(std::getline(_src, s1))
	{
		std::string tokStr = "";
		std::string lineStr = "";
		std::string colStr = "";
	
		bool line = false;
		bool col = false;
		
		for(auto c : s1)
		{
			if(c == '@')
			{
				line = true;
				continue;
			}
			if(c == '|')
			{
				line = false;
				col = true;
				continue;
			}
			if(c == '\t')
			{
				col = false;
				continue;
			}
			
			if(line)
			{
				lineStr += c;
				continue;
			}
			if(col)
			{
				colStr += c;
				continue;
			}
			
			if(c == ',')
				break;
			if(c != '<' && c != ' ')
				tokStr += c;
		}
		_input_vec.push_back(tokStr);
		_input_pos.push_back({lineStr, colStr});
	}
	_src.close();  

	//push starting nonterminal into the parsing stack
	_parse_stack.push("<program>");
	
	int input_pos = 0;
	bool parse_success = true;
	std::ofstream fileOutput("parser_output.txt");
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

				if(input_pos < _input_vec.size())
					input_pos++;
			}
			//error if not matched
			else
			{	
				parse_success = false;
				std::cout<<"Syntax error: missing '"<<_parse_stack.top()<<"' before L:"<<_input_pos[input_pos].first<<" C:"<<_input_pos[input_pos].second<<"."<<std::endl;
				_parse_stack.pop();
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
			fileOutput<<_parse_stack.top()<<"::="<<_parse_table[_parse_stack.top()][_input_vec[input_pos]]<<std::endl;
						
			//pop current non-terminal
			_parse_stack.pop();
			
			//push derivation into the parse stack
			for(std::vector<std::string>::reverse_iterator i = aux_vec.rbegin(); i != aux_vec.rend(); i++)			
			{
				_parse_stack.push(*i);
			}
			
	
		}
		// Error detected
		else if(_parse_table[_parse_stack.top()][_input_vec[input_pos]] == "-")
		{
			parse_success = false;
			std::cout<<"Syntax error: "<<_parse_table_error[_parse_stack.top()]<<" before L:"<<_input_pos[input_pos].first<<" C:"<<_input_pos[input_pos].second<<"."<<std::endl;
			
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
			
			if(aux == "<scope_block>")
			{
				_parse_stack.push("TK_END_SCOPE");
				_parse_stack.push("<scope_block'>");
			}
		}	
	}
	
	return parse_success;
}
