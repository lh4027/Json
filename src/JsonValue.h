#ifndef JSONVALUE_H__
#define JSONVALUE_H__
#include<vector>
#include<utility>
#include<iostream>
#include<string>
#include<assert.h>
using std::string;
using std::vector;

enum json_type {
    JSON_NULL,
    JSON_FALSE,
    JSON_TRUE,
    JSON_NUMBER,
    JSON_STRING,
    JSON_ARRAY,
    JSON_OBJECT
};  //json 的几种类型null，false,true,number,字符串,数组,对象


//错误码
enum {
    JSON_PARSE_OK = 0,
    JSON_PARSE_EMPTY_VALUE,      // 一个 JSON 只含有空白
    JSON_PARSE_INVALID_VALUE,     // 值不是那三种字面值
    JSON_PARSE_ROOT_NOT_SINGULAR,  // 一个值之后，在空白之后还有其他字符
    JSON_PARSE_NUMBER_TOO_BIG,        // json数字过大时的错误码
    JSON_PARSE_INVALID_STRING_ESCAPE, // 不合法字符串错误码
    JSON_PARSE_MISS_QUOTATION_MARK,
    JSON_PARSE_INVALID_STRING_CHAR,

    JSON_PARSE_INVALID_UNICODE_SURROGATE,  // 编码成 UTF-8。如果只有高代理项而欠缺低代理项，或是低代理项不在合法码点范围
    JSON_PARSE_INVALID_UNICODE_HEX, //如果 \u 后不是 4 位十六进位数字

    JSON_PARSE_MORE_COMMA,                   // [1,2,]多了逗号的格式错误
    JSON_PARSE_MISS_COMMA_OR_SQUARE_BRACKET, // 数组中缺失正确的逗号或者方括号

    JSON_PARSE_MISS_KEY,                      // 对象中缺失键key
    JSON_PARSE_MISS_COLON,                    // 对象中缺失冒号
    JSON_PARSE_MISS_COMMA_OR_CURLY_BRACKET // 对象中缺失正确的逗号或者大括号
};

class JsonValue {
public:
    JsonValue();
  /*  JsonValue(const double value) : type(JSON_NUMBER), n(value) {}
    JsonValue(const string& value) : type(JSON_STRING), str(value) {}
    JsonValue(const string key, const JsonValue value) : type(JSON_OBJECT) {
        obj.push_back(std::pair<string, JsonValue>(key, value));
    }*/

    
    ~JsonValue();

    void init();

    json_type get_type()const;
    void set_type(json_type _type);
    

    void set_number(double _n);
    double get_number()const;      //访问结果的函数，获取json数字的数值

    void set_string(string _str);
    const string get_string()const;

    size_t get_array_size() const;
    const JsonValue get_array_element(size_t index)const;
    void set_array(vector<JsonValue> _arr);
    vector<JsonValue> get_arr();
    void pushback_array_element(const JsonValue &_val);
    void popback_array_element();
    void insert_array_element(const JsonValue &_val, size_t index);
    void erase_array_element(size_t index, size_t count);
    void clear_array();

    size_t get_object_size() const;
    const string get_object_key(size_t index)const;
    size_t get_object_key_length(size_t index)const;
    const JsonValue get_object_value(size_t index)const;
    void set_object_value(const string &key, const JsonValue &val);
    void set_object(const vector<std::pair<string, JsonValue>> &_obj);
    const vector<std::pair<string, JsonValue>> get_obj()const;
    long find_object_index(const std::string& key)const;
    void remove_object_value(size_t index);
    void clear_object();
    
    bool isNull();
    bool isBool();
    bool isDouble();
    bool isString();
    bool isObject();
    bool isArray();

    JsonValue &operator[] (string index) {
        int i = atoi(index.c_str());
        assert(i < obj.size());

        return obj[i].second;
    }
    const JsonValue& operator[] (string index)const {
        int i = atoi(index.c_str());
        assert(i < obj.size());

        return obj[i].second;
    }

    JsonValue& operator[](size_t index) {
        assert(index < arr.size());
        return arr[index];
    }
    const JsonValue& operator[](size_t index) const{
        assert(index < arr.size());
        return arr[index];
    }

    void operator=(bool boolean) {
        switch (boolean) {
            case true:type = JSON_TRUE; break;
            case false:type = JSON_FALSE; break;
        }
    }
    void operator=(double dst_num) {
        type = JSON_NUMBER;
        n = dst_num;
    }
    void operator=(string& s) {
        type = JSON_STRING;
        str = s;
    }
    void operator=(const char* s) {
        type = JSON_STRING;
        str = s;
    }
    void operator=(vector<JsonValue>& dst_array) {
        type = JSON_ARRAY;
        arr = dst_array;
    }
    void operator=(vector<std::pair<string, JsonValue>>& dst_obj) {
        type = JSON_OBJECT;
        obj = dst_obj;
    }
    void operator=(const JsonValue& dst_val) {
        switch (dst_val.get_type()) {
            case JSON_NULL:break;
            case JSON_TRUE: operator=(true); break;
            case JSON_FALSE: operator=(false); break;
            case JSON_NUMBER: operator=(dst_val.get_number()); break;
            case JSON_STRING: operator=(dst_val.get_string().c_str()); break;
            case JSON_ARRAY:        
                for (size_t i = 0; i < dst_val.get_array_size(); i++)
                    arr.push_back(dst_val[i]);
                break;
            case JSON_OBJECT:
                for (size_t i = 0; i < dst_val.get_object_size(); i++)
                {
                    string name = dst_val.get_object_key(i);
                    obj.push_back(std::pair<string, JsonValue>(name, dst_val[name]));
                }                
                break;        
        }
    }
    


private:
    //void json_init(const JsonValue& v);
    //void json_free(const JsonValue& v);

    double n;                   // 存储json中的数字     
    string str;                 // json中的字符串
    vector<JsonValue> arr; /* array */
    vector<std::pair<string, JsonValue>> obj; /*object*/
    
    json_type type;            // json类型

};




#endif