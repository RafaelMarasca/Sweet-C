#ifndef PARSER_H_
#define PARSER_H_

#include <unordered_map>
#include <string>
#include <stack>
#include <utility>
#include <vector>
#include <fstream>
#include <sstream>

#include <iostream>

//{"*", {"TK_ID", "-"}}, {"*", {"TK_LOGOP", "-"}},{"*", {"TK_RELOP", "-"}},{"*", {"TK_ARITH", "-"}},{"*", {"TK_LOGVAL", "-"}},{"*", {"TK_CHAR", "-"}},{"*", {"TK_FRAC", "-"}},{"*", {"TK_WHOLE", "-"}},{"*", {"TK_TYPE", "-"}},{"*", {"TK_FUNC", "-"}},{"*", {"TK_COMMA", "-"}},{"*", {"TK_START_SCOPE", "-"}},{"*", {"TK_END_SCOPE", "-"}},{"*", {"TK_LPAR", "-"}},{"*", {"TK_RPAR", "-"}},{"*", {"TK_SEMICOLON", "-"}},{"*", {"TK_COLON", "-"}},{"*", {"TK_WHEN", "-"}},{"*", {"TK_OTHERWISE", "-"}},{"*", {"TK_FOR", "-"}},{"*", {"TK_RETURN", "-"}},{"*", {"TK_SELECT", "-"}},{"*", {"TK_ASSIGNMENT", "-"}},{"*", {"TK_ARROW", "-"}},{"*", {"TK_COLON", "-"}},{"*", {"$", "-"}}, 

class Node
{
    private:
	std::pair<std::string, std::string> _value;
	std::unordered_map<std::string, std::string> _annotation;
	
    public:
	std::vector<Node*> _children;
    
	Node(std::pair<std::string, std::string> val)
	{
		this->_value = val;
	}
	
	~Node()
	{
		for(auto n : this->_children)
		{	
			delete n;
		} 
	}
	
	void insert(std::pair<std::string, std::string> val)
	{
		Node *child = new Node(val);
		this->_children.push_back(child);	
	}
	
	void annotate()
	{
	
	}
};

class LL1
{
    private:
        static std::unordered_map<std::string, std::unordered_map<std::string, std::string>> _parse_table;
        static std::unordered_map<std::string, std::vector<std::string>> _parse_table_sync;
        static std::unordered_map<std::string, std::string> _parse_table_error;
        
        std::stack<std::string> _parse_stack;
        std::vector<std::string> _input_vec;
        std::vector<std::pair<std::string, std::string>> _input_pos;
        std::vector<std::string> _input_val;
        
        std::ifstream _src;
        std::stringstream _buffer;

    public:
        LL1();
        ~LL1();

        bool parse(std::string src);
};

#endif
