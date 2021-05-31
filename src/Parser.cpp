#include<assert.h>
#include <errno.h>   /* errno, ERANGE */
#include <math.h>    /* HUGE_VAL */

#include"Parser.h"
#include"JsonValue.h"

Parser::Parser() :val(NULL),iter(NULL){
}

Parser::~Parser() {

}

void Parser::setJsonResource(const string& context, JsonValue* _val) {
	json_context = context + "\0";
	iter = context.c_str();
	val = _val;
	
}

int Parser::ExcuteParse() {
	int ret;
	val->set_type(JSON_NULL);
	parse_whitespace();
	if ((ret = parse_value()) == JSON_PARSE_OK) {
		parse_whitespace();
		if (*iter != '\0') {
			val->set_type(JSON_NULL);
			ret = JSON_PARSE_ROOT_NOT_SINGULAR;
		}
	}
	return ret;	
}

int Parser::parse_value(){
	if (*iter == '\0')
		return JSON_PARSE_EMPTY_VALUE;
	switch (*iter) {
		case 'n': return parse_literal("null", JSON_NULL);
		case 't': return parse_literal("true", JSON_TRUE);
		case 'f': return parse_literal("false", JSON_FALSE);
		case '"': return parse_string();
		case '[': return parse_array();
		case '{': return parse_object();
		default:  return parse_number();
		case '\0': return JSON_PARSE_EMPTY_VALUE;
	}
}


void Parser::parse_whitespace()
{
	while (*iter != '\0' && (*iter == ' ' || *iter == '\n' || *iter == '\t' || *iter == '\r'))
		iter++;
}

#define EXPECT(c, ch)        do { assert(*c == (ch)); ++c; } while(0)
int Parser::parse_literal(const char* literal, json_type _type)
{
	size_t i;
	assert(*iter == literal[0]);
	int len = strlen(literal);
	if (strncmp(iter, literal, len) == 0) {
		for (i = 0; literal[i]; i++) {
			if (*(iter++) != literal[i])
				return JSON_PARSE_INVALID_VALUE;
		}
		val->set_type(_type);
		return JSON_PARSE_OK;
	}
	else
		return JSON_PARSE_INVALID_VALUE;
	
}

#define ISDIGIT(ch)          ((ch) >= '0' && (ch) <= '9')
#define ISDIGIT_1_TO_9(ch)   ((ch) >= '1' && (ch) <= '9')
//#define ISEMPTY(it)          (it == json_context.end()) 
int Parser::parse_number() {
	//string::const_iterator iter_tmp = iter;
	const char *iter_tmp = iter;
	
	if (*iter_tmp == '-') iter_tmp++;
	if (*iter_tmp == '0') iter_tmp++;
	else {
		if (!ISDIGIT_1_TO_9(*iter_tmp)) return JSON_PARSE_INVALID_VALUE; //如果在以0为开头，后面还有数字，那这样的格式是错误的，返回非法值错误
		for (iter_tmp++; ISDIGIT(*iter_tmp); iter_tmp++);
	}
	if (*iter_tmp == '.') {
		iter_tmp++;
		if (!ISDIGIT(*iter_tmp)) return JSON_PARSE_INVALID_VALUE;
		for (iter_tmp++; ISDIGIT(*iter_tmp); iter_tmp++);
	}
	if (*iter_tmp == 'e' || *iter_tmp == 'E') {
		iter_tmp++;
		if (*iter_tmp == '+' || *iter_tmp == '-') iter_tmp++;
		if(!ISDIGIT(*iter_tmp)) return JSON_PARSE_INVALID_VALUE;
		for (iter_tmp++; ISDIGIT(*iter_tmp); iter_tmp++);
	}
	errno = 0;
	double num = strtod(&(*iter), NULL);
	if (errno == ERANGE && (num == HUGE_VAL || num == -HUGE_VAL))
		return JSON_PARSE_NUMBER_TOO_BIG;
	val->set_number(num);
	iter = iter_tmp;
	return JSON_PARSE_OK;
}
int Parser::parse_string() {

	string s;
	int ret = parse_string_raw(s);
	if (ret == JSON_PARSE_OK)  // 当字符串解析成功时才设置初始化value值
		val->set_string(s);
	else
		val->init();
	return ret;
}
int Parser::parse_string_raw(string& _strTmp){
	assert(*iter == '\"');
	iter++;
	const char* p = iter;
	unsigned u = 0, u2 = 0;
	while (1) {
		char ch = *p++;
		switch (ch) {
		case '\"':
			iter = p;
			return JSON_PARSE_OK;
		case '\\':
			switch (*p++) {
			case '\"': _strTmp += '\"'; break;
			case '\\': _strTmp += '\\'; break;
			case '/': _strTmp += '/'; break;
			case 'b': _strTmp += '\b'; break;
			case 'f': _strTmp += '\f'; break;
			case 'n': _strTmp += '\n'; break;
			case 'r': _strTmp += '\r'; break;
			case 't': _strTmp += '\t'; break;
			case 'u':
				if ((parse_hex4(p, u) != JSON_PARSE_OK))
					return JSON_PARSE_INVALID_UNICODE_HEX;
				if (u >= 0xD800 && u <= 0xDBFF) { /* surrogate pair */
					if (*p++ != '\\')
						return JSON_PARSE_INVALID_UNICODE_SURROGATE;
					if (*p++ != 'u')
						return JSON_PARSE_INVALID_UNICODE_SURROGATE;
					if (parse_hex4(p, u2) != JSON_PARSE_OK)
						return JSON_PARSE_INVALID_UNICODE_HEX;
					if (u2 < 0xDC00 || u2 > 0xDFFF)
						return JSON_PARSE_INVALID_UNICODE_SURROGATE;
					u = (((u - 0xD800) << 10) | (u2 - 0xDC00)) + 0x10000;
				}
				parse_encode_utf8(_strTmp, u); break;
			default:
				return JSON_PARSE_INVALID_STRING_ESCAPE;
			}break;
		case '\0':
			return JSON_PARSE_MISS_QUOTATION_MARK;
		default:
			if ((unsigned char)ch < 0x20)
				return JSON_PARSE_INVALID_STRING_CHAR;
			_strTmp += ch;
			break;
		}
	}	
}

int Parser::parse_hex4(const char* &p, unsigned &u){
	u = 0;
	char ch = 0;
	for (int i = 0; i < 4; ++i) {
		char ch = *p++;
		u <<= 4;
		if (ch >= '0' && ch <= '9')       u |= ch - '0';
		else if (ch >= 'A' && ch <= 'F')  u |= ch - ('A' - 10);
		else if (ch >= 'a' && ch <= 'f')  u |= ch - ('a' - 10);
		else return JSON_PARSE_INVALID_UNICODE_HEX;
	}
	return JSON_PARSE_OK;
}

void Parser::parse_encode_utf8(string& _str, unsigned u){
	if (u <= 0x7F)
		_str += (u & 0xFF);
	else if (u <= 0x7FF) {
		_str += (0xC0 | (0xFF & (u >> 6)));
		_str += (0x80 | (0x3F & u));
	}
	else if (u <= 0xffff) {
		_str += (0xE0 | (0xFF & (u >> 12)));
		_str += (0x80 | (0x3F & (u >> 6)));
		_str += (0x80 | (0x3F & u));
	}
	else {
		_str += (0xF0 | (0xFF & (u >> 18)));
		_str += (0x80 | (0x3F & (u >> 12)));
		_str += (0x80 | (0x3F & (u >> 6)));
		_str += (0x80 | (0x3F & u));
	}
}

int Parser::parse_array(){
	
	int ret = 0;
	assert(*iter == '[');
	iter++;
	parse_whitespace();
	vector<JsonValue> arr_tmp;
	if (*iter == ']') {
		iter++;		
		val->set_array(arr_tmp);
		return JSON_PARSE_OK;
	}
	while (1) {

		if (ret = parse_value() != JSON_PARSE_OK)
			break;

		arr_tmp.push_back(*val);
		val->init();
		parse_whitespace();
		if (*iter == ',') {
			iter++;
			parse_whitespace();
			if (*iter == ']') {/* [1,2,]错误类型*/
				val->init();
				return  JSON_PARSE_MORE_COMMA;
			}
		}
		else if (*iter == ']') {
			iter++;
			val->set_array(arr_tmp);
			return JSON_PARSE_OK;
		}
		else {
			val->init();
			ret =  JSON_PARSE_MISS_COMMA_OR_SQUARE_BRACKET;
			break;
		}
	}
	return ret;
}

int Parser::parse_object()
{
	int ret = 0;
	assert(*iter == '{');
	iter++;
	parse_whitespace();
	vector<std::pair<string,JsonValue>> obj_tmp;
	string key;
	if (*iter == '}') {
		iter++;
		val->set_object(obj_tmp);
		return JSON_PARSE_OK;
	}
	while (1) {
		if (*iter != '\"') {
			ret = JSON_PARSE_MISS_KEY; break;
		}
		if (ret = parse_string_raw(key) != JSON_PARSE_OK) 
			break;
		parse_whitespace();
		/* parse ws colon ws */
		if (*iter != ':') {
			val->init();
			ret = JSON_PARSE_MISS_COLON;
			break;
		}
		iter++;
		parse_whitespace();
		/* parse value */
		if (ret = parse_value() != JSON_PARSE_OK)
			break;
		obj_tmp.push_back(make_pair(key, *val));
		val->init();
		key.clear();
		parse_whitespace();
		if (*iter == ',') {
			iter++;
			parse_whitespace();
			if (*iter == '}') {/* {"as": 1 ,"as: : true ,}错误类型*/
				val->init();
				ret = JSON_PARSE_MORE_COMMA;
			}
		}
		else if (*iter == '}') {
			iter++;
			val->set_object(obj_tmp);
			return JSON_PARSE_OK;
		}
		else {
			val->init();
			ret = JSON_PARSE_MISS_COMMA_OR_CURLY_BRACKET; break;
		}
		
	}
	return ret;
}


