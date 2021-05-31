#include "Generator.h"

#define PUSH_TAB(str)\
        do {\
            for (size_t tab_num = 0; tab_num < tab_count; tab_num++)\
                str += "    ";\
        } while(0)

JsonGenerator::JsonGenerator(){
    res = "";
}

JsonGenerator::~JsonGenerator(){
}

string JsonGenerator::get_convert_string()
{
    return res;
}

string JsonGenerator::get_pretty_convert_string() {
    return PrettyRes;
}

void JsonGenerator::convert_value(const JsonValue &_val)
{
    switch (_val.get_type()) {
    case JSON_NULL:  res += "null";  break;
    case JSON_TRUE:  res += "true";  break;
    case JSON_FALSE: res += "false"; break;
    case JSON_NUMBER: {
        char buffer[32] = { 0 };
        sprintf(buffer, "%.17g", _val.get_number());
        res += buffer;
    }break;       
    case JSON_STRING:convert_string(_val.get_string());
        break;
    case JSON_ARRAY:
        res += '[';
        for (size_t i = 0; i < _val.get_array_size(); ++i) {
            if (i > 0) res += ',';
            convert_value(_val.get_array_element(i));
        }
        res += ']';
        break;  
    case JSON_OBJECT:
        res += '{';
        for (size_t i = 0; i < _val.get_object_size(); ++i) {
            if (i > 0) res += ',';
            convert_string(_val.get_object_key(i));
            res += ':';
            convert_value(_val.get_object_value(i));
        }
        res += '}';
        break;
    }
}

size_t JsonGenerator::get_convert_value_length()
{
    return res.size();
}

void JsonGenerator::PrettyConvert(const JsonValue& _val)
{
    switch (_val.get_type()) {
    case JSON_NULL:  PrettyRes += "null";  break;
    case JSON_TRUE:  PrettyRes += "true";  break;
    case JSON_FALSE: PrettyRes += "false"; break;
    case JSON_NUMBER: {
        char buffer[32] = { 0 };
        sprintf(buffer, "%.17g", _val.get_number());
        PrettyRes += buffer;
    }break;
    case JSON_STRING:pretty_convert_string(_val.get_string());
        break;
    case JSON_ARRAY:
        PrettyRes += "[\n";
        tab_count++;
        for (size_t i = 0; i < _val.get_array_size(); ++i) {
            PUSH_TAB(PrettyRes);
            PrettyConvert(_val.get_array_element(i));
            if(i + 1 != _val.get_array_size())
                PrettyRes += ",\n";
            else {
                PrettyRes += '\n';
                tab_count--;
            } 
        }
        PUSH_TAB(PrettyRes);
        PrettyRes += ']';
        break;
    case JSON_OBJECT:
        PrettyRes += "{\n";
        tab_count++;
        for (size_t i = 0; i < _val.get_object_size(); ++i) {
            PUSH_TAB(PrettyRes);
            pretty_convert_string(_val.get_object_key(i));
            PrettyRes += ':';
            PrettyConvert(_val.get_object_value(i));
            if (i + 1 != _val.get_object_size()) 
                PrettyRes += ",\n";
            else{
                tab_count--;
                PrettyRes += '\n';
            }                   
        }
        PUSH_TAB(PrettyRes);
        PrettyRes += '}';
        break;
    }
}

void JsonGenerator::convert_string(const string& _str)
{
    res += '\"';
    for (auto it = _str.begin(); it < _str.end(); ++it) {
        unsigned char ch = *it;
        switch (ch) {
        case '\"': res += "\\\""; break;
        case '\\': res += "\\\\"; break;
        case '\b': res += "\\b";  break;
        case '\f': res += "\\f";  break;
        case '\n': res += "\\n";  break;
        case '\r': res += "\\r";  break;
        case '\t': res += "\\t";  break;
        default:
            if (ch < 0x20) {
                char buffer[7] = { 0 };
                sprintf(buffer, "\\u%04X", ch);
                res += buffer;
            }
            else
                res += *it;

        }
    }
    res += '\"';
}

void JsonGenerator::pretty_convert_string(const string& _str)
{
    PrettyRes += '\"';
    for (auto it = _str.begin(); it < _str.end(); ++it) {
        unsigned char ch = *it;
        switch (ch) {
        case '\"': PrettyRes += "\\\""; break;
        case '\\': PrettyRes += "\\\\"; break;
        case '\b': PrettyRes += "\\b";  break;
        case '\f': PrettyRes += "\\f";  break;
        case '\n': PrettyRes += "\\n";  break;
        case '\r': PrettyRes += "\\r";  break;
        case '\t': PrettyRes += "\\t";  break;
        default:
            if (ch < 0x20) {
                char buffer[7] = { 0 };
                sprintf(buffer, "\\u%04X", ch);
                PrettyRes += buffer;
            }
            else
                PrettyRes += *it;

        }
    }
    PrettyRes += '\"';
}


