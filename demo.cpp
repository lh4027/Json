#include<iostream>
#include<assert.h>

#include"Json.h"
#include"Reader.h"
#include"Writer.h"

#define TEST_SIMPLE 
#define TEST_PRETTY

int main() {
    string res;
    string json_txt = " { "
        "\"n\" : null , "
        "\"f\" : false , "
        "\"t\" : true , "
        "\"i\" : 123 , "
        "\"s\" : \"abc\", "
        "\"a\" : [ 1, 2, 3 ],"
        "\"o\" : { \"1\" : 1, \"2\" : 2, \"3\" : 3 }"
        " } ";
    Json j;
    Reader::reader(json_txt, j);

    Json v;
    std::ifstream ifs;
    Reader::reader(ifs, "test.json", v);


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

    // 查询
    Json json;
    json.parser(json_txt); // 解析至json对象中（将Json文本解析到树状数据结构中保存）
    assert(json.isObject());
    assert(json["s"].isString());
    std::cout << json["s"].get_string() << std::endl;

    assert(json["a"].isArray());
    std::cout << json["a"][0].get_number() << std::endl;

    assert(json["o"].isObject());
    std::cout << json["o"]["1"].get_number() << std::endl;

    //修改
     json["o"]["2"] = 3.0;
    json["o"]["0"] = "abc";
    std::cout << json["o"]["2"].get_number() << std::endl;
    std::cout << json["o"]["0"].get_string() << std::endl;

    // 添加数组
    Json a,item;
    a.set_array(vector<JsonValue>{});
    item.set_number(1.22);
    a.pushback_array_element(item);  // 尾端插入
    item.set_string("abc");
    a.insert_array_element(item, 1); // 在指定位置进行插入

    // 添加对象
    Json o, item1;
    o.set_object(vector<std::pair<string, JsonValue>>{});
    string key = "a";
    item1.set_number(123.123);
    o.set_object_value(key, item1);
    
    // 删除
    a.erase_array_element(0, 1); // 在0位置连续删除1个元素
    o.remove_object_value(0);

    // 深拷贝
    Json v1;
    v1 = json;

    // 移动、交换
    Json v2, v3,v4;
    v2 = std::move(v1);

    v3.set_string("Hello");
    v4.set_string("World!");
    swap(v3, v4);

	system("pause");
 	return 0;
}