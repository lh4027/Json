#include"Json.h"

//
Json::Json() : v(new JsonValue) ,p(new Parser), g(new JsonGenerator) { }

Json::~Json() { 
	delete v;
	delete p;
	delete g;
}

int Json::parser(const string& context)
{
	p->setJsonResource(context, v);
	return p->ExcuteParse();
	
}

void Json:: convert_value()
{
	g->convert_value(*v);
}
 string Json::get_pretty_convert_value()
{
	g->PrettyConvert(*v);
	return g->get_pretty_convert_string();
}

 string Json::get_convert_value()
{
	return g->get_convert_string();
}

size_t Json::get_convert_value_length()
{
	return g->get_convert_value_length();
}

void Json::init()
{
	string s = "";
	v->clear_array();
	v->clear_object();
	v->set_string(s);
	v->set_number(0);
	v->set_type(JSON_NULL);
}

json_type Json::get_type() const {
	return v->get_type();
}

void Json::set_null()
{
	v->set_type(JSON_NULL);
}
void Json::set_boolean(bool b)
{
	if (b) v->set_type(JSON_TRUE);
	else v->set_type(JSON_FALSE);
}


void Json::set_number(double _n){
	v->set_number(_n);
}

double Json::get_number()const {
	return v->get_number();
}

void Json::set_string(string _str)
{
	v->set_string(_str);
}

const string Json::get_string()const
{
	return v->get_string();
}

size_t Json::get_array_size()const
{
	return v->get_array_size();
}

JsonValue Json::get_array_element(size_t index)const
{
	return v->get_array_element(index);
}

void Json::set_array(vector<JsonValue> _val)
{
	v->set_type(JSON_ARRAY);
	v->set_array(_val);
}

const vector<JsonValue> Json::get_arr()const
{
	return v->get_arr();
}

void Json::pushback_array_element(Json &_val)
{
	v->pushback_array_element(*_val.v);
}

void Json::popback_array_element()
{
	v->popback_array_element();
}

void Json::insert_array_element(Json &_val, size_t index)
{
	v->insert_array_element(*_val.v, index);
}

void Json::erase_array_element(size_t index, size_t count)
{
	v->erase_array_element(index, count);
}

void Json::clear_array()
{
	v->clear_array();
}

size_t Json::get_object_size()const
{
	return v->get_object_size();
}

const string Json::get_object_key(size_t index)const
{
	return v->get_object_key(index);
}

size_t Json::get_object_key_length(size_t index)const
{
	return v->get_object_key_length(index);
}

JsonValue Json::get_object_value(size_t index)const
{
	return v->get_object_value(index);
}

void Json::set_object_value(const string& key, const Json &val)
{
	v->set_object_value(key, *val.v);
}

void Json::set_object(vector<std::pair<string, JsonValue>> _val)
{
	v->set_object(_val);
}

const vector<std::pair<string, JsonValue>> Json::get_obj() const
{
	return v->get_obj();
}

long long Json::find_object_index(const std::string& key)const
{
	return v->find_object_index(key);
}

void Json::remove_object_value(size_t index)
{
	v->remove_object_value(index);
}

void Json::clear_object()
{
	v->clear_object();
}

void Json::operator=(const Json& rhs)
{
	(*v) = *rhs.v;
}

void Json::swap(Json& rhs)
{
	using std::swap;
	swap(v, rhs.v);
}
void swap(Json& lhs, Json& rhs)
{
	lhs.swap(rhs);
}

bool Json::isNull() {
	return v->get_type() == JSON_NULL;
}
bool Json::isBool(){
	return v->get_type() == JSON_TRUE || v->get_type() == JSON_FALSE;
}
bool Json::isDouble(){
	return v->get_type() == JSON_NUMBER;
}
bool Json::isString() {
	return v->get_type() == JSON_STRING;
}
bool Json::isObject()
{
	return v->get_type() == JSON_OBJECT;
}

bool Json::isArray() {
	return v->get_type() == JSON_ARRAY;
}



//bool Json::isArrayEqual(const JsonValue& lhs, const JsonValue& rhs) {
//	
//}
//bool Json::isEqual(const Json& lhs, const Json& rhs)
//{
//	if (lhs.v->get_type() != rhs.v->get_type())
//		return false;
//	switch (lhs.v->get_type()) {
//	case JSON_STRING:return lhs.v->get_string() == rhs.v->get_string();
//	case JSON_NUMBER:return lhs.v->get_number() == rhs.v->get_number();
//	case JSON_ARRAY:
//		
//		if (lhs.v->get_array_size() != rhs.v->get_array_size())
//			return false;
//		for (size_t i = 0; i < lhs.v->get_array_size(); i++) {
//			while()
//			
//		}
//	case JSON_OBJECT:
//		
//
//	}
//}




