#ifndef PARSE_TABLE_ERROR_H_
#define PARSE_TABLE_ERROR_H_

#define PARSE_TABLE_ERROR {\
{"<program>", "expected function definition or variable declaration"},\
{"<program'>", "expected function definition or variable declaration"},\
{"<func>", "expected function definition"},\
{"<func'>", "expected function definition or variable declaration"},\
{"<func_specifier>", "expected 'func' keyword before function definition"},\
{"<arg_list>", "expected argument(s) definition or ')'"},\
{"<arg_list'>", "expected argument(s) definition or ')'"},\
{"<scope_block>", "expected '{'"},\
{"<scope_block'>", "expected statement, variable definition or variable declaration"},\
{"<code_block>", "invalid sentence"},\
{"<de>", "expected type keyword"},\
{"<finition>", "expected operator or sentence delimiter"},\
{"<statement>", "expected statement"},\
{"<type>", "expected type keyword"},\
{"<expression>", "expected lvalue"},\
{"<lhs>", "expected lvalue"},\
{"<eq>", "expected operator"},\
{"<rhs>", "expected rvalue"},\
{"<rhs'>", "expected operator or sentence delimiter"},\
{"<operator>", "expected operator"},\
{"<condition_statement>", "expected 'select' keyword"},\
{"<select_statement>", "expected conditional keyword"},\
{"<iteration_statement>", "expected 'for' keyword"},\
{"<return_statement>", "expected 'return' keyword"},\
{"<return_statement'>", "expected value"},\
{"<value>", "expected value"},\
{"<value'>", "expected value"},\
{"<var_value>", "expected variable"},\
{"<con_value>", "expected constant"},\
{"<constant>", "expected constant"},\
{"<int_con>", "expected integer constant"},\
{"<float_con>", "expected float constant"},\
{"<char_con>", "expected character constant"},\
{"<bool_con>", "expected boolean constant"},\
{"<arith>", "expected arithmetic operator"},\
{"<relational>", "expected relational operator"},\
{"<logic>", "expected logical operator"},\
{"<identifier>", "expected identifier"}\
}

#endif
