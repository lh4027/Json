#ifndef JSON_H__
#define JSON_H__
#include<memory>
#include "JsonValue.h"
#include "Parser.h"
#include "Generator.h"

class JsonValue;
class Json {
public:
	Json();
	~Json();

	//void parser(const string& context, string& status);
	int parser(const string& context);
	void convert_value();

	string get_pretty_convert_value();
	string get_convert_value();

	size_t get_convert_value_length();

	void init();

	json_type get_type()const;
	void set_null();
	void set_boolean(bool b);
	//int get_boolean();

	void set_number(double _n);
	double get_number()const;

	void set_string(string _str);
	const string get_string()const;

	size_t get_array_size()const;
	JsonValue get_array_element(size_t index) const;
	void set_array(vector<JsonValue> _val);
	const vector<JsonValue> get_arr()const;
	void pushback_array_element(Json &_val);
	void popback_array_element();
	void insert_array_element(Json &_val, size_t index);
	void erase_array_element(size_t index, size_t count);
	void clear_array();

	size_t get_object_size()const;
	const string get_object_key(size_t index)const;
	size_t get_object_key_length(size_t index)const;
	JsonValue get_object_value(size_t index)const;
	void set_object_value(const string& key, const Json &val);
	void set_object(vector<std::pair<string, JsonValue>> _val);
	const vector<std::pair<string, JsonValue>> get_obj()const;
	long long find_object_index(const std::string& key)const;
	void remove_object_value(size_t index);
	void clear_object();

	//bool isEqual(const Json& lhs, const Json& rhs);

	void operator=(const Json& rhs);
	void swap(Json& rhs);

	bool isNull();
	bool isBool();
	bool isDouble();
	bool isString();
	bool isObject();
	bool isArray();

	
	
	JsonValue &operator[] (const string key) {	  //此处的字符到数字再到字符的转化仅仅是为了重载多种形式的[]
		char s[10] = {};
		sprintf(s, "%d", v->find_object_index(key));
		return (*v)[s];
	}
	const JsonValue& operator[] (const string key)const {

		return (*v)[v->find_object_index(key)];
	}

	JsonValue& operator[](size_t index) {
		return (*v)[index];
	}
	const JsonValue& operator[](size_t index) const{
		return (*v)[index];
	}

private:
	//std::unique_ptr<JsonValue> v;
	JsonValue* v;
	Parser* p;
	JsonGenerator* g;

};

void swap(Json& lhs, Json& rhs);

#endif
