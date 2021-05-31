//// 记得看看能不能加入智能指针
#include"JsonValue.h"
#include<assert.h>

JsonValue::JsonValue() {
	type = JSON_NULL;
}

JsonValue::~JsonValue() {

}

void JsonValue::init()
{
	type = JSON_NULL;
	n = 0;
	str = "";
	arr.clear();
	obj.clear();
}

json_type JsonValue::get_type()const {
	return type;
}

void JsonValue::set_type(json_type _type) 
{
	type = _type;
}

void JsonValue::set_number(double _n)
{
	this->n = _n;
	type = JSON_NUMBER;
}

double JsonValue::get_number()const
{
	assert(type == JSON_NUMBER);
	return n;
}

void JsonValue::set_string(string _str){
	str = _str;
	type = JSON_STRING;
}

const string JsonValue::get_string()const {
	//assert(type == JSON_STRING);
	return str;
}

size_t JsonValue::get_array_size()const
{
	assert(type == JSON_ARRAY);
	return arr.size();
}

const JsonValue JsonValue::get_array_element(size_t index)const
{
	assert(type == JSON_ARRAY);
	return arr[index];
}

void JsonValue::set_array(vector<JsonValue> _arr)
{
	arr = _arr;
	type = JSON_ARRAY;
}

vector<JsonValue> JsonValue::get_arr()
{
	return arr;
}

void JsonValue::pushback_array_element(const JsonValue &_val)
{
	assert(type == JSON_ARRAY);
	arr.push_back(_val);
}

void JsonValue::popback_array_element()
{
	assert(type == JSON_ARRAY);
	arr.pop_back();
}

void JsonValue::insert_array_element(const JsonValue& _val, size_t index)
{
	assert(type == JSON_ARRAY);
	arr.insert(arr.begin() + index, _val);
}

void JsonValue::erase_array_element(size_t index, size_t count)
{
	assert(type == JSON_ARRAY);
	arr.erase(arr.begin() + index, arr.begin() + index + count);
}

void JsonValue::clear_array()
{
	//assert(type == JSON_ARRAY);
	arr.clear();
}

size_t JsonValue::get_object_size()const
{
	//assert(type == JSON_OBJECT);
	return obj.size();
}

const string JsonValue::get_object_key(size_t index)const
{
	assert(type == JSON_OBJECT && !obj.empty());
	return obj[index].first;
}

size_t JsonValue::get_object_key_length(size_t index)const
{
	assert(type == JSON_OBJECT && !obj.empty());
	return obj[index].first.size();
}

const JsonValue JsonValue::get_object_value(size_t index)const
{
	assert(type == JSON_OBJECT && !obj.empty());
	return obj[index].second;
}

void JsonValue::set_object_value(const string &key, const JsonValue &val)
{
	assert(type == JSON_OBJECT);
	obj.push_back(make_pair(key, val));//是否考虑重复的问题
}

void JsonValue::set_object(const vector<std::pair<string, JsonValue>> &_obj)
{
	obj = _obj;
	this->type = JSON_OBJECT;
}

const vector<std::pair<string, JsonValue>> JsonValue::get_obj()const
{
	return obj;
}

long JsonValue::find_object_index(const std::string& key)const
{
	assert(type == JSON_OBJECT && !obj.empty());
	for (size_t i = 0; i < obj.size(); i++) {
		if (obj[i].first == key)
			return i;
	}
	return -1;
}

void JsonValue::remove_object_value(size_t index)
{
	assert(type == JSON_OBJECT);
	obj.erase(obj.begin() + index, obj.begin() + index + 1);
}

void JsonValue::clear_object()
{
	//assert(type == JSON_OBJECT);
	obj.clear();
}

bool JsonValue::isNull()
{
	return type == JSON_NULL;
}

bool JsonValue::isBool()
{
	return type == JSON_TRUE || type == JSON_FALSE;
}

bool JsonValue::isDouble()
{
	return type == JSON_NUMBER;
}

bool JsonValue::isString()
{
	return type == JSON_STRING;
}

bool JsonValue::isObject()
{
	return type == JSON_OBJECT;
}

bool JsonValue::isArray()
{
	return type == JSON_ARRAY;
}

//bool JsonValue::isEqual(const JsonValue& lhs, const JsonValue& rhs)
//{
//	return lhs.arr == rhs.arr;
//
//}

