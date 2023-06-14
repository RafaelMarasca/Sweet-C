#ifndef PARSE_TABLE_SYNC_H_
#define PARSE_TABLE_SYNC_H_

#define PARSE_TABLE_SYNC {\
{"<program>", {"$"}},\
{"<program'>", {"TK_TYPE", "TK_FUNC"}},\
{"<func>", {"TK_FUNC", "$"}},\
{"<func_specifier>", {"TK_ID"}},\
{"<arg_list>", {"TK_RPAR"}},\
{"<arg_list'>", {"TK_RPAR"}},\
{"<scope_block>", {"TK_TYPE", "TK_FOR", "TK_SELECT", "TK_ID", "TK_ARITH", "TK_LOGOP", "TK_WHOLE", "TK_CHAR", "TK_LOGVAL", "TK_RETURN", "TK_WHEN", "TK_OTHERWISE"}},\
{"<scope_block'>", {"TK_SEMICOLON", "TK_END_SCOPE", "TK_TYPE", "TK_FOR", "TK_SELECT", "TK_ID", "TK_ARITH", "TK_LOGOP", "TK_WHOLE", "TK_CHAR", "TK_LOGVAL", "TK_RETURN", "TK_WHEN", "TK_OTHERWISE"}},\
{"<code_block>", {"TK_TYPE", "TK_FOR", "TK_SELECT", "TK_ID", "TK_ARITH", "TK_LOGOP", "TK_WHOLE", "TK_CHAR", "TK_LOGVAL", "TK_RETURN", "TK_WHEN", "TK_OTHERWISE"}},\
{"<de>", {"TK_FUNC", "TK_TYPE", "TK_FOR", "TK_SELECT", "TK_ID", "TK_ARITH", "TK_LOGOP", "TK_WHOLE", "TK_CHAR", "TK_LOGVAL", "TK_RETURN", "TK_WHEN", "TK_OTHERWISE", "TK_COMMA"}},\
{"<finition>", {"TK_FUNC", "TK_SEMICOLON", "TK_TYPE", "TK_FOR", "TK_SELECT", "TK_ID", "TK_ARITH", "TK_LOGOP", "TK_WHOLE", "TK_CHAR", "TK_LOGVAL", "TK_RETURN" }},\
{"<statement>", {"TK_TYPE", "TK_FOR", "TK_SELECT", "TK_ID", "TK_ARITH", "TK_LOGOP", "TK_WHOLE", "TK_CHAR", "TK_LOGVAL", "TK_RETURN", "TK_WHEN", "TK_OTHERWISE"}},\
{"<type>", {"TK_ID", "TK_START_SCOPE"}},\
{"<expression>", {"TK_COMMA", "TK_SEMICOLON"}},\
{"<lhs>", {"TK_ID", "TK_ARITH", "TK_LOGOP", "TK_WHOLE", "TK_FRAC", "TK_CHAR", "TK_LOGVAL"}},\
{"<eq>", {"TK_ID", "TK_ARITH", "TK_LOGOP", "TK_WHOLE", "TK_FRAC", "TK_CHAR", "TK_LOGVAL"}},\
{"<rhs>", {"TK_FUNC", "TK_SEMICOLON", "TK_TYPE", "TK_FOR", "TK_SELECT", "TK_ID", "TK_ARITH", "TK_LOGOP", "TK_WHOLE", "TK_CHAR", "TK_LOGVAL", "TK_RETURN" }},\
{"<rhs'>", {"TK_FUNC", "TK_SEMICOLON", "TK_TYPE", "TK_FOR", "TK_SELECT", "TK_ID", "TK_ARITH", "TK_LOGOP", "TK_WHOLE", "TK_CHAR", "TK_LOGVAL", "TK_RETURN" }},\
{"<operator>", {"TK_ID", "TK_ARITH", "TK_LOGOP", "TK_WHOLE", "TK_FRAC", "TK_CHAR", "TK_LOGVAL"}},\
{"<condition_statement>", {"TK_SEMICOLON", "TK_TYPE", "TK_FOR", "TK_SELECT", "TK_ID", "TK_ARITH", "TK_LOGOP", "TK_WHOLE", "TK_CHAR", "TK_LOGVAL", "TK_RETURN" }},\
{"<select_statement>", {"TK_SEMICOLON", "TK_TYPE", "TK_FOR", "TK_SELECT", "TK_ID", "TK_ARITH", "TK_LOGOP", "TK_WHOLE", "TK_CHAR", "TK_LOGVAL", "TK_RETURN" }},\
{"<iteration_statement>", {"TK_SEMICOLON", "TK_TYPE", "TK_FOR", "TK_SELECT", "TK_ID", "TK_ARITH", "TK_LOGOP", "TK_WHOLE", "TK_CHAR", "TK_LOGVAL", "TK_RETURN" }},\
{"<return_statement>", {"TK_SEMICOLON", "TK_TYPE", "TK_FOR", "TK_SELECT", "TK_ID", "TK_ARITH", "TK_LOGOP", "TK_WHOLE", "TK_CHAR", "TK_LOGVAL", "TK_RETURN" }},\
{"<return_statement'>", {"TK_SEMICOLON", "TK_TYPE", "TK_FOR", "TK_SELECT", "TK_ID", "TK_ARITH", "TK_LOGOP", "TK_WHOLE", "TK_CHAR", "TK_LOGVAL", "TK_RETURN" }},\
{"<value>", {"TK_ID", "TK_ARITH", "TK_LOGOP", "TK_WHOLE", "TK_FRAC", "TK_CHAR", "TK_LOGVAL", "TK_START_SCOPE"}},\
{"<value'>", {"TK_ID", "TK_ARITH", "TK_LOGOP", "TK_WHOLE", "TK_FRAC", "TK_CHAR", "TK_LOGVAL", "TK_START_SCOPE"}},\
{"<var_value>", {"TK_ID", "TK_ARITH", "TK_LOGOP", "TK_WHOLE", "TK_FRAC", "TK_CHAR", "TK_LOGVAL", "TK_START_SCOPE"}},\
{"<con_value>", {"TK_ID", "TK_ARITH", "TK_LOGOP", "TK_WHOLE", "TK_FRAC", "TK_CHAR", "TK_LOGVAL", "TK_START_SCOPE"}},\
{"<constant>", {"TK_ID", "TK_ARITH", "TK_LOGOP", "TK_WHOLE", "TK_FRAC", "TK_CHAR", "TK_LOGVAL", "TK_START_SCOPE"}},\
{"<int_con>", {"TK_ID", "TK_ARITH", "TK_LOGOP", "TK_WHOLE", "TK_FRAC", "TK_CHAR", "TK_LOGVAL", "TK_START_SCOPE"}},\
{"<float_con>", {"TK_ID", "TK_ARITH", "TK_LOGOP", "TK_WHOLE", "TK_FRAC", "TK_CHAR", "TK_LOGVAL", "TK_START_SCOPE"}},\
{"<char_con>", {"TK_ID", "TK_ARITH", "TK_LOGOP", "TK_WHOLE", "TK_FRAC", "TK_CHAR", "TK_LOGVAL", "TK_START_SCOPE"}},\
{"<bool_con>", {"TK_ID", "TK_ARITH", "TK_LOGOP", "TK_WHOLE", "TK_FRAC", "TK_CHAR", "TK_LOGVAL", "TK_START_SCOPE"}},\
{"<arith>", {"TK_ID", "TK_ARITH", "TK_LOGOP", "TK_WHOLE", "TK_FRAC", "TK_CHAR", "TK_LOGVAL"}},\
{"<relational>", {"TK_ID", "TK_ARITH", "TK_LOGOP", "TK_WHOLE", "TK_FRAC", "TK_CHAR", "TK_LOGVAL"}},\
{"<logic>", {"TK_ID", "TK_ARITH", "TK_LOGOP", "TK_WHOLE", "TK_FRAC", "TK_CHAR", "TK_LOGVAL"}},\
{"<identifier>", {"TK_LPAR", "TK_ID", "TK_ARITH", "TK_LOGOP", "TK_WHOLE", "TK_FRAC", "TK_CHAR", "TK_LOGVAL", "TK_START_SCOPE"}}\
}

#endif
