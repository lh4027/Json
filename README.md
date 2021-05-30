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
### 单元测试
> 错误码
> enum {
>    JSON_PARSE_OK = 0,
>    JSON_PARSE_EMPTY_VALUE,      // 一个 JSON 只含有空白
>    JSON_PARSE_INVALID_VALUE,     // 值不是那三种字面值
>    JSON_PARSE_ROOT_NOT_SINGULAR,  // 一个值之后，在空白之后还有其他字符
>    JSON_PARSE_NUMBER_TOO_BIG,        // json数字过大时的错误码
>    JSON_PARSE_INVALID_STRING_ESCAPE, // 不合法字符串错误码
>    JSON_PARSE_MISS_QUOTATION_MARK,
>    JSON_PARSE_INVALID_STRING_CHAR,
>
>    JSON_PARSE_INVALID_UNICODE_SURROGATE,  // 编码成 UTF-8。如果只有高代理项而欠缺低代理项，或是低代理项不在合法码点范围
>    JSON_PARSE_INVALID_UNICODE_HEX, //如果 \u 后不是 4 位十六进位数字
>
>    JSON_PARSE_MORE_COMMA,                   // [1,2,]多了逗号的格式错误
>    JSON_PARSE_MISS_COMMA_OR_SQUARE_BRACKET, // 数组中缺失正确的逗号或者方括号

>    JSON_PARSE_MISS_KEY,                      // 对象中缺失键key
>    JSON_PARSE_MISS_COLON,                    // 对象中缺失冒号
>    JSON_PARSE_MISS_COMMA_OR_CURLY_BRACKET // 对象中缺失正确的逗号或者大括号
> };























