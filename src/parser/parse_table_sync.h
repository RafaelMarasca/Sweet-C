#ifndef PARSE_TABLE_SYNC_H_
#define PARSE_TABLE_SYNC_H_

#define {\
{"<program>", {"$"}},\
{"<program'>", {"TK_TYPE", "TK_FUNC"}}\
{"<func>", {"TK_FUNC", "$"}}\
{"<func_specifier>", {"TK_ID"}}\
{"<arg_list>", {TK_RPAR}}\
{"<arg_list'>", {TK_RPAR}}\
{"<scope_block>", {"$"}}\
{"<scope_block'>", {"TK_END_SCOPE"}}\
{"<code_block>", {"TK_TYPE", "TK_FOR", "TK_SELECT", "TK_ID", "TK_ARITH", "TK_LOGOP", "TK_WHOLE", "TK_CHAR", "TK_LOGVAL", "TK_RETURN", "TK_WHEN", "TK_OTHERWISE"}}\
{"<de>", {"TK_TYPE", "TK_FOR", "TK_SELECT", "TK_ID", "TK_ARITH", "TK_LOGOP", "TK_WHOLE", "TK_CHAR", "TK_LOGVAL", "TK_RETURN", "TK_WHEN", "TK_OTHERWISE", "TK_COMMA"}}\
{"<finition>", {"TK_SEMICOLON"}}\
{"<statement", {"TK_TYPE", "TK_FOR", "TK_SELECT", "TK_ID", "TK_ARITH", "TK_LOGOP", "TK_WHOLE", "TK_CHAR", "TK_LOGVAL", "TK_RETURN", "TK_WHEN", "TK_OTHERWISE"}}\
}

#endif
