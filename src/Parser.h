#ifndef PARSER_H__
#define PARSER_H__

#include"JsonValue.h"

class Parser {
public:
	Parser();
	~Parser();
	
	int ExcuteParse();
    void setJsonResource(const string& context, JsonValue* _val);

private:
    void parse_whitespace();
    int  parse_value();
    int  parse_literal(const char* literal, json_type _type);
    int  parse_number();
    int  parse_string_raw(string& _strTmp);
    int  parse_hex4(const char* &p, unsigned &u);
    int  parse_string();
    void parse_encode_utf8(string& _str, unsigned u);

    int  parse_array();
    int  parse_object();

    JsonValue *val;
    string json_context;
    const char* iter;

};



#endif


