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

    // ��ѯ
    Json json;
    json.parser(json_txt); // ������json�����У���Json�ı���������״���ݽṹ�б��棩
    assert(json.isObject());
    assert(json["s"].isString());
    std::cout << json["s"].get_string() << std::endl;

    assert(json["a"].isArray());
    std::cout << json["a"][0].get_number() << std::endl;

    assert(json["o"].isObject());
    std::cout << json["o"]["1"].get_number() << std::endl;

    //�޸�
     json["o"]["2"] = 3.0;
    json["o"]["0"] = "abc";
    std::cout << json["o"]["2"].get_number() << std::endl;
    std::cout << json["o"]["0"].get_string() << std::endl;

    // �������
    Json a,item;
    a.set_array(vector<JsonValue>{});
    item.set_number(1.22);
    a.pushback_array_element(item);  // β�˲���
    item.set_string("abc");
    a.insert_array_element(item, 1); // ��ָ��λ�ý��в���

    // ��Ӷ���
    Json o, item1;
    o.set_object(vector<std::pair<string, JsonValue>>{});
    string key = "a";
    item1.set_number(123.123);
    o.set_object_value(key, item1);
    
    // ɾ��
    a.erase_array_element(0, 1); // ��0λ������ɾ��1��Ԫ��
    o.remove_object_value(0);

    // ���
    Json v1;
    v1 = json;

    // �ƶ�������
    Json v2, v3,v4;
    v2 = std::move(v1);

    v3.set_string("Hello");
    v4.set_string("World!");
    swap(v3, v4);

	system("pause");
 	return 0;
}