#ifndef GENERATOR_H__
#define GENERATOR_H__

#include"JsonValue.h"

class JsonGenerator {
public:
	JsonGenerator();
	~JsonGenerator();

	string get_convert_string();
	string get_pretty_convert_string();

	void convert_value(const JsonValue &_val);
	void PrettyConvert(const JsonValue& _val);

	size_t get_convert_value_length();
	
	
	
private:
	
	void convert_string(const string &_str);
	void pretty_convert_string(const string& _str);
	string res;
	string PrettyRes;
	int tab_count = 0;
};























#endif