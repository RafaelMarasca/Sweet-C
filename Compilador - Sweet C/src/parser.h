#ifndef PARSER_H_
#define PARSER_H_

#include <unordered_map>
#include <string>
#include <stack>
#include <utility>
#include <vector>
#include <fstream>
#include <sstream>
#include "Symbol.h"

#include <iostream>

//{"*", {"TK_ID", "-"}}, {"*", {"TK_LOGOP", "-"}},{"*", {"TK_RELOP", "-"}},{"*", {"TK_ARITH", "-"}},{"*", {"TK_LOGVAL", "-"}},{"*", {"TK_CHAR", "-"}},{"*", {"TK_FRAC", "-"}},{"*", {"TK_WHOLE", "-"}},{"*", {"TK_TYPE", "-"}},{"*", {"TK_FUNC", "-"}},{"*", {"TK_COMMA", "-"}},{"*", {"TK_START_SCOPE", "-"}},{"*", {"TK_END_SCOPE", "-"}},{"*", {"TK_LPAR", "-"}},{"*", {"TK_RPAR", "-"}},{"*", {"TK_SEMICOLON", "-"}},{"*", {"TK_COLON", "-"}},{"*", {"TK_WHEN", "-"}},{"*", {"TK_OTHERWISE", "-"}},{"*", {"TK_FOR", "-"}},{"*", {"TK_RETURN", "-"}},{"*", {"TK_SELECT", "-"}},{"*", {"TK_ASSIGNMENT", "-"}},{"*", {"TK_ARROW", "-"}},{"*", {"TK_COLON", "-"}},{"*", {"$", "-"}}, 

struct Node
{
	std::pair<std::string, std::string> _value;
	std::unordered_map<std::string, std::string> _annotation;
	std::pair<int, int> _pos;
	
	std::vector<Node*> _children;
	int _cur_child;
    Node *_father;
    
	Node(std::pair<std::string, std::string> val, Node *father, std::pair<int, int> pos)
	{
		_cur_child = 0;

		this->_father = father;
		this->_value = val;
		this->_pos = pos; 
	}
	
	void printdel()
	{
		std::cout<<"deletando: "<<this->_value.first<<std::endl;
	}
	
	~Node()
	{
		//printdel();
		for(auto n : this->_children)
		{	
			delete n;
		} 
	}
	
	void insert(std::pair<std::string, std::string> val, Node *father, std::pair<int, int> pos)
	{
		Node *child = new Node(val, father, pos);
		this->_children.push_back(child);	
	}
	
	void print()
	{
		std::ofstream fileOutput("parser_output.txt");
		printHierarchy(this, 0, fileOutput);
		fileOutput.close();
	}

	void printHierarchy(Node* n, int depth, std::ofstream& fileOutput)
	{
		std::vector<Node*>::iterator it;

		for(int i = 0; i<(depth)*5; i++)
		{
			if(i%5 == 0)
			{
				fileOutput<<"|";
			}else
			{
				fileOutput<<" ";
			}
		}

		fileOutput<<"|";

		for(int i = 0; i<4; i++)
			fileOutput<<"-";
		
		fileOutput<<n->_value.first<<std::endl;


		for(it = n->_children.begin(); it != n->_children.end(); it++)
			printHierarchy(*it, depth+1, fileOutput);
		}
};

class LL1
{
    	private:
        static std::unordered_map<std::string, std::unordered_map<std::string, std::string>> _parse_table;
        static std::unordered_map<std::string, std::vector<std::string>> _parse_table_sync;
        static std::unordered_map<std::string, std::string> _parse_table_error;
        
        Node* _parse_tree;
        std::stack<std::string> _parse_stack;
        std::vector<std::string> _input_vec;
        std::vector<std::pair<int, int>> _input_pos;
        std::vector<std::string> _input_val;
        
        std::ifstream _src;
        std::stringstream _buffer;

    public:
        LL1();
        ~LL1();

        Node* parse(std::vector<token_t>);
};

#endif
