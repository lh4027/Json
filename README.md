# Json库
C++实现的轻量级Json库，实现符合标准的JSON解析器和生成器。
## 特性
* 能够解析Json语法里面的null、true、false、数字（double）、字符串、数组、对象
* 能够对Json对象进行查询、修改、添加和删除
* 支持Json对象转换成字符串格式化输出
* 支持Json对象转换成字符串美观化输出
* 支持UTF-8 Json文本，仅支持double类型数字存储与解析
* 添加Reader文件，能够快速从文本读取Json, 并解析到Json对象保存
* 添加Writer文件，能够将Json对象转换成Json文件保存

## 实现
###  内部架构

![图片3](https://user-images.githubusercontent.com/66367559/120108253-f08d9d80-c196-11eb-9f34-433fd6ed920f.jpg)

将接口与实现分离，JsonValue类管理Json值，Parser类实现Json的解析功能，JsonGenerator类实现生成器的功能，三者在Json类中生成实例，Json类调用这三个类的接口，对外提供解析，生成功能。
```
Json::Json() : v(new JsonValue) ,p(new Parser), g(new JsonGenerator) {}
Json::~Json() { 
	delete v;
	delete p;
	delete g;
}
```

### JSON对象的类型表示
```
enum json_type {
    JSON_NULL,
    JSON_FALSE,
    JSON_TRUE,
    JSON_NUMBER,
    JSON_STRING,
    JSON_ARRAY,
    JSON_OBJECT
}; 
使用JsonValue类管理Json各类型成员
class JsonValue{
private:
    double n;                   // 存储json中的数字     
    string str;                 // json中的字符串
    vector<JsonValue> arr; /* array */
    vector<std::pair<string, JsonValue>> obj; /*object*/
    
    json_type type;            // json类型
}
```
### 解析器的实现
解析器封装在类Parser中，在Json类中生成实例，Parser类中有三个成员变量，JsonValue对象指针val，和一个指向json字符串当前解析位置的char指针以及一个需要解析的Json字符串。
下为解析的最终执行函数
```
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
```
若解析成功，返回JSON_PARSE_OK正确码，若解析错误返回其他错误码。
### 生成器实现
生成器JsonGenerator类中包含的成员为res和PrettyRes，分别存储格式化Json字符串和美化（加入缩进）的Json字符串，生成器的实现比较简单：
```
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
```

### 单元测试
错误码
```
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
```
宏的编写技巧：反斜线代表该行未结束，会串接下一行。而如果宏里有多过一个语句，就需要用 do { /*...*/ } while(0) 包裹成单个语句
```
#define EXPECT_EQ_BASE(equality, expect, actual, format)\
    do{\
        test_count++;\
        if(equality)\
            test_pass++;\
        else{\
            fprintf(stderr, "%s:%d: expect: " format "  actual: " format "\n", __FILE__, __LINE__, expect, actual);\
            main_ret = 1;\
        }\
    }while(0)
```
使用宏EXPECT_EQ_BASE(expect, actual)判断两个参数的值是否相等, 如果expect != actual(预期值不等于实际值)遍会输出错误信息，可根据错误信息定位错误到具体行。 

## 教程

通过添加辅助函数以及对[]=等运算符进行重载，可以比较直观方便地对Json对象进行查询、修改、添加和删除操作。支持深拷贝，移动和交换，具体使用方法可见demo.cpp文件。
### Reader 和 Writer文件
使用时可添加Reader.h头文件，使用时包含命名空间，可以实现从程序内存或者.Json文件中直接解析。
```
Json j;
    Reader::reader(json_txt, j);

    Json v;
    std::ifstream ifs;
    Reader::reader(ifs, "test.json", v);
```
Writer 文件能够将Json对象转换成Json文件保存，支持格式化输出和美化输出
```
#ifdef TEST_SIMPLE
    Reader::SimpleShow(j);
    Reader::SimpleShow(v);
    Writer::SimpleWriter(v, "simple_test.json");

#endif
#ifdef TEST_PRETTY
    Reader::PrettyShow(j);
    Reader::PrettyShow(v);
    Writer::PrettyWriter(v, "pretty_test.json");
#endif
```

![image](https://user-images.githubusercontent.com/66367559/120109960-431e8800-c19e-11eb-8cb4-ae99a8017e98.png)
![image](https://user-images.githubusercontent.com/66367559/120109986-5b8ea280-c19e-11eb-88f2-169f9bc7e54d.png)


参考和学习资料来自[miloyip的github教程json-tutorial](https://github.com/miloyip/json-tutorial)
和
[Syopain](https://github.com/Syopain/Json)




















