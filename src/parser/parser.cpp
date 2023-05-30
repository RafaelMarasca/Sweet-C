#include "parser.h"
#include "parse_table.h"

#include <iostream>

std::unordered_map<std::string, std::unordered_map<std::string, std::string>> LL1::_parse_table = PARSE_TABLE;

LL1::LL1()
{
	_parse_stack = std::stack<std::string>();
	_input_vec = std::vector<std::string>();

	_parse_stack.push("$");
}

LL1::~LL1()
{
    
}

bool LL1::parse(std::string src)
{
	_src.open(src);

	std::string s1;
	std::string s2 = "";

	while(std::getline(_src, s1))
	{
		for(auto c : s1)
		{
			if(c == ',')
				break;
			if(c != '<' && c != ' ')
				s2 += c;
		}
		_input_vec.push_back(s2);
		s2 = "";
	}

	//for(auto j : _input_vec)
	//	std::cout<<j<<std::endl;

	_src.close();  

	_parse_stack.push("<program>");
	
	int input_pos = 0;
	int test = 0;
	while(_parse_stack.top() != "$" || _input_vec[input_pos] != "$")
	{
		std::vector<std::string> aux_vec;
		std::string aux_string = "";
		
		if(_parse_stack.top() == _input_vec[input_pos])
		{
			//std::cout<<"gotcha: "<<_parse_stack.top()<<std::endl;
			_parse_stack.pop();

			if(input_pos < _input_vec.size())
				input_pos++;
				
			//std::cout<<"next input: "<<_input_vec[input_pos]<<std::endl;
			//std::cout<<"next nonter: "<<_parse_stack.top()<<std::endl;
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
			std::cout<<_parse_stack.top()<<"::="<<_parse_table[_parse_stack.top()][_input_vec[input_pos]]<<std::endl;
			
			/*
			if(_parse_stack.top() == "asasdsad")
			{
				std::cout<<"input: "<<_input_vec[input_pos]<<std::endl;
				while(!_parse_stack.empty())
				{
					std::cout<<_parse_stack.top()<<std::endl;
					_parse_stack.pop();
				}
				std::cout<<aux_vec.empty()<<std::endl;
				break;
			}
			*/
			
			
			//pop current non-terminal
			//std::cout<<"top: "<<_parse_stack.top()<<std::endl;
			//std::cout<<"input: "<<_input_vec[input_pos]<<std::endl;
			_parse_stack.pop();
			
			
			//push derivation
			for(std::vector<std::string>::reverse_iterator i = aux_vec.rbegin(); i != aux_vec.rend(); i++)			
			{
				_parse_stack.push(*i);
			}
			
			
			/*
			while(!_parse_stack.empty())
			{
				std::cout<<_input_vec[input_pos]<<std::endl;
				std::cout<<_parse_stack.top()<<std::endl;
				_parse_stack.pop();
			}
			
			std::cout<<";;;;;;;;;;;;;;;"<<std::endl;
			for(auto j : aux_vec)
			{
				std::cout<<j<<std::endl;

			}
			*/	
		}	
	}
	
	return (_parse_stack.top() == "$" && _input_vec[input_pos] != "$");
}
