//#include"Json.h"
//#include<iostream>
//
//static int main_ret = 0;
//static int test_count = 0;
//static int test_pass = 0;
//
//// 单元测试模块
//#define EXPECT_EQ_BASE(equality, expect, actual, format)\
//    do{\
//        test_count++;\
//        if(equality)\
//            test_pass++;\
//        else{\
//            fprintf(stderr, "%s:%d: expect: " format "  actual: " format "\n", __FILE__, __LINE__, expect, actual);\
//            main_ret = 1;\
//        }\
//    }while(0)
//
//#define EXPECT_EQ_DOUBLE(expect, actual) EXPECT_EQ_BASE((expect)==(actual), expect, actual, "%.17g")
//#define EXPECT_EQ_STRING(expect, actual, alength) \
//        EXPECT_EQ_BASE(sizeof(expect) - 1 == alength && memcmp(expect, actual, alength) == 0, expect, actual, "%s")
//
//#define EXPECT_EQ_SIZE_T(expect, actual) EXPECT_EQ_BASE((expect) == (actual), (size_t)expect, (size_t)actual, "%zu")
//
//#define EXPECT_EQ_INT(expect, actual) EXPECT_EQ_BASE((expect)==(actual), expect, actual, "%d")
//static void test_parse_null() {
//    Json v;
//    //v.set_null();
//    EXPECT_EQ_INT(JSON_PARSE_OK, v.parser("null"));
//    EXPECT_EQ_INT(JSON_NULL, v.get_type());
//}
//
//#define EXPECT_TRUE(actual) EXPECT_EQ_BASE((actual) != 0, "true", "false", "%s")
//
//static void test_parse_true() {
//    Json v;
//    //v.set_boolean(true);
//    EXPECT_EQ_INT(JSON_PARSE_OK, v.parser("true"));
//    EXPECT_EQ_INT(JSON_TRUE, v.get_type());
//}
//
//#define EXPECT_FALSE(actual) EXPECT_EQ_BASE((actual) == 0, "false", "true", "%s")
//
//static void test_parse_false() {
//    Json v;
//   // v.set_boolean(false);
//    EXPECT_EQ_INT(JSON_PARSE_OK, v.parser("false"));
//    EXPECT_EQ_INT(JSON_FALSE, v.get_type());
//}
//
//
//// json数字测试，使用多行的宏的减少重复代码
//#define TEST_NUMBER(expect, json)\
//    do{\
//        Json  v;\
//        EXPECT_EQ_INT(JSON_PARSE_OK, v.parser(json));\
//        EXPECT_EQ_INT(JSON_NUMBER, v.get_type());\
//        EXPECT_EQ_DOUBLE(expect, v.get_number());\
//    }while(0)
//static void test_parse_number() {
//
//    TEST_NUMBER(0.0, "0");
//    TEST_NUMBER(0.0, "-0");
//    TEST_NUMBER(0.0, "-0.0");
//    TEST_NUMBER(1.0, "1");
//    TEST_NUMBER(-1.0, "-1");
//    TEST_NUMBER(1.5, "1.5");
//    TEST_NUMBER(-1.5, "-1.5");
//    TEST_NUMBER(3.1416, "3.1416");
//    TEST_NUMBER(1E10, "1E10");
//    TEST_NUMBER(1e10, "1e10");
//    TEST_NUMBER(1E+10, "1E+10");
//    TEST_NUMBER(1E-10, "1E-10");
//    TEST_NUMBER(-1E10, "-1E10");
//    TEST_NUMBER(-1e10, "-1e10");
//    TEST_NUMBER(-1E+10, "-1E+10");
//    TEST_NUMBER(-1E-10, "-1E-10");
//    TEST_NUMBER(1.234E+10, "1.234E+10");
//    TEST_NUMBER(1.234E-10, "1.234E-10");
//    TEST_NUMBER(0.0, "1e-10000"); /* must underflow */
//
//}
//
//// json字符串测试
//#define TEST_STRING(expect, json)\
//    do {\
//         Json  v;\
//        EXPECT_EQ_INT(JSON_PARSE_OK, v.parser(json));\
//        EXPECT_EQ_INT(JSON_STRING, v.get_type());\
//        EXPECT_EQ_STRING(expect, v.get_string().c_str(), v.get_string().size());\
//    } while(0)
//
//static void test_parse_string() {
//    TEST_STRING("", "\"\"");
//    TEST_STRING("Hello", "\"Hello\"");
//    TEST_STRING("Hello\nWorld", "\"Hello\\nWorld\"");
//    TEST_STRING("\" \\ / \b \f \n \r \t", "\"\\\" \\\\ \\/ \\b \\f \\n \\r \\t\"");
//
//    // utf-8 编码测试
//    TEST_STRING("\x24", "\"\\u0024\"");         /* Dollar sign U+0024 */
//    TEST_STRING("\xC2\xA2", "\"\\u00A2\"");     /* Cents sign U+00A2 */
//    TEST_STRING("\xE2\x82\xAC", "\"\\u20AC\""); /* Euro sign U+20AC */
//    TEST_STRING("\xF0\x9D\x84\x9E", "\"\\uD834\\uDD1E\"");  /* G clef sign U+1D11E */
//    TEST_STRING("\xF0\x9D\x84\x9E", "\"\\ud834\\udd1e\"");  /* G clef sign U+1D11E */
//}
//
//static void test_parse_array() {
//    size_t i, j;
//    Json v;
//    EXPECT_EQ_INT(JSON_PARSE_OK, v.parser("[ ]"));
//    EXPECT_EQ_INT(JSON_ARRAY, v.get_type());
//    EXPECT_EQ_SIZE_T(0, v.get_array_size());
//    
//
//    v.init();
//    EXPECT_EQ_INT(JSON_PARSE_OK, v.parser("[ null , false , true , 123 , \"abc\" ]"));
//    EXPECT_EQ_INT(JSON_ARRAY, v.get_type());
//    EXPECT_EQ_SIZE_T(5, v.get_array_size());
//    EXPECT_EQ_INT(JSON_NULL, v.get_array_element(0).get_type());
//    EXPECT_EQ_INT(JSON_FALSE, v.get_array_element(1).get_type());
//    EXPECT_EQ_INT(JSON_TRUE, v.get_array_element(2).get_type());
//    EXPECT_EQ_INT(JSON_NUMBER, v.get_array_element(3).get_type());
//    EXPECT_EQ_INT(JSON_STRING, v.get_array_element(4).get_type());
//    EXPECT_EQ_DOUBLE(123.0, v.get_array_element(3).get_number());
//    EXPECT_EQ_STRING("abc", v.get_array_element(4).get_string().c_str(), v.get_array_element(4).get_string().size());
//  
//    v.init();
//    EXPECT_EQ_INT(JSON_PARSE_OK, v.parser("[ [ ] , [ 0 ] , [ 0 , 1 ] , [ 0 , 1 , 2 ] ]"));
//    EXPECT_EQ_INT(JSON_ARRAY, v.get_type());
//    EXPECT_EQ_SIZE_T(4, v.get_array_size());
//    for (i = 0; i < 4; i++) {
//        
//        JsonValue a = v.get_array_element(i);
//        
//        EXPECT_EQ_INT(JSON_ARRAY, a.get_type());
//        EXPECT_EQ_SIZE_T(i, a.get_array_size());
//        for (j = 0; j < i; j++) {
//            JsonValue e = a.get_array_element(j);
//            EXPECT_EQ_INT(JSON_NUMBER, e.get_type());
//            EXPECT_EQ_DOUBLE((double)j, e.get_number());
//        }
//    }
//}
//
//static void test_parse_object() {
//    Json v;
//    size_t i;
//
//    EXPECT_EQ_INT(JSON_PARSE_OK, v.parser(" { } "));
//    EXPECT_EQ_INT(JSON_OBJECT, v.get_type());
//    EXPECT_EQ_SIZE_T(0, v.get_object_size());
//
//    v.init();
//    EXPECT_EQ_INT(JSON_PARSE_OK, v.parser(
//        " { "
//        "\"n\" : null , "
//        "\"f\" : false , "
//        "\"t\" : true , "
//        "\"i\" : 123 , "
//        "\"s\" : \"abc\", "
//        "\"a\" : [ 1, 2, 3 ],"
//        "\"o\" : { \"1\" : 1, \"2\" : 2, \"3\" : 3 }"
//        " } "
//    ));
//    EXPECT_EQ_INT(JSON_OBJECT, v.get_type());
//    EXPECT_EQ_SIZE_T(7, v.get_object_size());
//    EXPECT_EQ_STRING("n", v.get_object_key(0).c_str(), v.get_object_key_length(0));
//    EXPECT_EQ_INT(JSON_NULL, v.get_object_value(0).get_type());
//    EXPECT_EQ_STRING("f", v.get_object_key(1).c_str(), v.get_object_key_length(0));
//    EXPECT_EQ_INT(JSON_FALSE, v.get_object_value(1).get_type());
//    EXPECT_EQ_STRING("t", v.get_object_key(2).c_str(), v.get_object_key_length(0));
//    EXPECT_EQ_INT(JSON_TRUE, v.get_object_value(2).get_type());
//    EXPECT_EQ_STRING("i", v.get_object_key(3).c_str(), v.get_object_key_length(0));
//    EXPECT_EQ_INT(JSON_NUMBER, v.get_object_value(3).get_type());
//    EXPECT_EQ_STRING("s", v.get_object_key(4).c_str(), v.get_object_key_length(0));
//    EXPECT_EQ_INT(JSON_STRING, v.get_object_value(4).get_type());
//
//
//    EXPECT_EQ_STRING("abc", v.get_object_value(4).get_string().c_str(), v.get_object_value(4).get_string().size());
//    EXPECT_EQ_STRING("a", v.get_object_key(5).c_str(), v.get_object_key_length(5));
//    EXPECT_EQ_INT(JSON_ARRAY, v.get_object_value(5).get_type());
//    EXPECT_EQ_SIZE_T(3, v.get_object_value(6).get_object_size());
//    for (i = 0; i < 3; i++) {
//        JsonValue e = v.get_object_value(5).get_array_element(i);
//        EXPECT_EQ_INT(JSON_NUMBER, e.get_type());
//        EXPECT_EQ_DOUBLE(i + 1.0, e.get_number());
//    }
//    EXPECT_EQ_STRING("o", v.get_object_key(6).c_str(), v.get_object_key_length(6));
//    {
//        JsonValue o = v.get_object_value(6);
//        EXPECT_EQ_INT(JSON_OBJECT, o.get_type());
//        for (i = 0; i < 3; i++) {
//            JsonValue ov = o.get_object_value(i);
//            EXPECT_TRUE('1' + i == o.get_object_key(i)[0]);
//            EXPECT_EQ_SIZE_T(1, o.get_object_key_length(i));
//            EXPECT_EQ_INT(JSON_NUMBER, ov.get_type());
//            EXPECT_EQ_DOUBLE(i + 1.0, ov.get_number());
//        }
//    }
//}
//
//
//#define TEST_ERROR(error, json)\
//    do {\
//        Json v;\
//        v.set_boolean(false);\
//        EXPECT_EQ_INT(error, v.parser(json));\
//        EXPECT_EQ_INT(JSON_NULL, v.get_type());\
//    } while(0)
//
//static void test_parse_expect_value() {
//    TEST_ERROR(JSON_PARSE_EMPTY_VALUE, "");
//    TEST_ERROR(JSON_PARSE_EMPTY_VALUE, "\0");
//    TEST_ERROR(JSON_PARSE_EMPTY_VALUE, " ");
//}
//
//static void test_parse_invalid_value() {
//    TEST_ERROR(JSON_PARSE_INVALID_VALUE, "nul");
//    TEST_ERROR(JSON_PARSE_INVALID_VALUE, "?");
//
//#if 1
//    /* invalid number */
//    TEST_ERROR(JSON_PARSE_INVALID_VALUE, "+0");
//    TEST_ERROR(JSON_PARSE_INVALID_VALUE, "+1");
//    TEST_ERROR(JSON_PARSE_INVALID_VALUE, ".123"); /* at least one digit before '.' */
//    TEST_ERROR(JSON_PARSE_INVALID_VALUE, "1.");   /* at least one digit after '.' */
//    TEST_ERROR(JSON_PARSE_INVALID_VALUE, "INF");
//    TEST_ERROR(JSON_PARSE_INVALID_VALUE, "inf");
//    TEST_ERROR(JSON_PARSE_INVALID_VALUE, "NAN");
//    TEST_ERROR(JSON_PARSE_INVALID_VALUE, "nan");
//#endif
//}
//
//static void test_parse_root_not_singular() {
//    TEST_ERROR(JSON_PARSE_ROOT_NOT_SINGULAR, "null x");
//
//#if 1
//    /* invalid number */
//    TEST_ERROR(JSON_PARSE_ROOT_NOT_SINGULAR, "0123"); /* after zero should be '.' , 'E' , 'e' or nothing */
//    TEST_ERROR(JSON_PARSE_ROOT_NOT_SINGULAR, "0x0");
//    TEST_ERROR(JSON_PARSE_ROOT_NOT_SINGULAR, "0x123");
//#endif
//}
//static void test_parse_number_too_big() {
//#if 1
//    TEST_ERROR(JSON_PARSE_NUMBER_TOO_BIG, "1e309");
//    TEST_ERROR(JSON_PARSE_NUMBER_TOO_BIG, "-1e309");
//#endif
//}
//static void test_parse_miss_quotation_mark() {
//    TEST_ERROR(JSON_PARSE_MISS_QUOTATION_MARK, "\"");
//    TEST_ERROR(JSON_PARSE_MISS_QUOTATION_MARK, "\"abc");
//}
//
//static void test_parse_invalid_string_escape() {
//    TEST_ERROR(JSON_PARSE_INVALID_STRING_ESCAPE, "\"\\v\"");
//    TEST_ERROR(JSON_PARSE_INVALID_STRING_ESCAPE, "\"\\'\"");
//    TEST_ERROR(JSON_PARSE_INVALID_STRING_ESCAPE, "\"\\0\"");
//    TEST_ERROR(JSON_PARSE_INVALID_STRING_ESCAPE, "\"\\x12\"");
//}
//
//static void test_parse_invalid_string_char() {
//    TEST_ERROR(JSON_PARSE_INVALID_STRING_CHAR, "\"\x01\"");
//    TEST_ERROR(JSON_PARSE_INVALID_STRING_CHAR, "\"\x1F\"");
//}
//
//static void test_parse_invalid_unicode_hex() {
//    TEST_ERROR(JSON_PARSE_INVALID_UNICODE_HEX, "\"\\u\"");
//    TEST_ERROR(JSON_PARSE_INVALID_UNICODE_HEX, "\"\\u0\"");
//    TEST_ERROR(JSON_PARSE_INVALID_UNICODE_HEX, "\"\\u01\"");
//    TEST_ERROR(JSON_PARSE_INVALID_UNICODE_HEX, "\"\\u012\"");
//    TEST_ERROR(JSON_PARSE_INVALID_UNICODE_HEX, "\"\\u/000\"");
//    TEST_ERROR(JSON_PARSE_INVALID_UNICODE_HEX, "\"\\uG000\"");
//    TEST_ERROR(JSON_PARSE_INVALID_UNICODE_HEX, "\"\\u0/00\"");
//    TEST_ERROR(JSON_PARSE_INVALID_UNICODE_HEX, "\"\\u0G00\"");
//    TEST_ERROR(JSON_PARSE_INVALID_UNICODE_HEX, "\"\\u00/0\"");
//    TEST_ERROR(JSON_PARSE_INVALID_UNICODE_HEX, "\"\\u00G0\"");
//    TEST_ERROR(JSON_PARSE_INVALID_UNICODE_HEX, "\"\\u000/\"");
//    TEST_ERROR(JSON_PARSE_INVALID_UNICODE_HEX, "\"\\u000G\"");
//    TEST_ERROR(JSON_PARSE_INVALID_UNICODE_HEX, "\"\\u 123\"");
//}
//
//static void test_parse_invalid_unicode_surrogate() {
//    TEST_ERROR(JSON_PARSE_INVALID_UNICODE_SURROGATE, "\"\\uD800\"");
//    TEST_ERROR(JSON_PARSE_INVALID_UNICODE_SURROGATE, "\"\\uDBFF\"");
//    TEST_ERROR(JSON_PARSE_INVALID_UNICODE_SURROGATE, "\"\\uD800\\\\\"");
//    TEST_ERROR(JSON_PARSE_INVALID_UNICODE_SURROGATE, "\"\\uD800\\uDBFF\"");
//    TEST_ERROR(JSON_PARSE_INVALID_UNICODE_SURROGATE, "\"\\uD800\\uE000\"");
//}
//static void test_parse_miss_comma_or_square_bracket() {
//    TEST_ERROR(JSON_PARSE_MISS_COMMA_OR_SQUARE_BRACKET, "[1");
//    TEST_ERROR(JSON_PARSE_MISS_COMMA_OR_SQUARE_BRACKET, "[1}");
//    TEST_ERROR(JSON_PARSE_MISS_COMMA_OR_SQUARE_BRACKET, "[1 2");
//    TEST_ERROR(JSON_PARSE_MISS_COMMA_OR_SQUARE_BRACKET, "[[]");
//    TEST_ERROR(JSON_PARSE_MORE_COMMA, "[1,2,]");
//}
//static void test_parse_miss_key() {
//    TEST_ERROR(JSON_PARSE_MISS_KEY, "{:1,");
//    TEST_ERROR(JSON_PARSE_MISS_KEY, "{1:1,");
//    TEST_ERROR(JSON_PARSE_MISS_KEY, "{true:1,");
//    TEST_ERROR(JSON_PARSE_MISS_KEY, "{false:1,");
//    TEST_ERROR(JSON_PARSE_MISS_KEY, "{null:1,");
//    TEST_ERROR(JSON_PARSE_MISS_KEY, "{[]:1,");
//    TEST_ERROR(JSON_PARSE_MISS_KEY, "{{}:1,");
//    TEST_ERROR(JSON_PARSE_MISS_KEY, "{\"a\":1,");
//}
//
//static void test_parse_miss_colon() {
//    TEST_ERROR(JSON_PARSE_MISS_COLON, "{\"a\"}");
//    TEST_ERROR(JSON_PARSE_MISS_COLON, "{\"a\",\"b\"}");
//}
//
//static void test_parse_miss_comma_or_curly_bracket() {
//    TEST_ERROR(JSON_PARSE_MISS_COMMA_OR_CURLY_BRACKET, "{\"a\":1");
//    TEST_ERROR(JSON_PARSE_MISS_COMMA_OR_CURLY_BRACKET, "{\"a\":1]");
//    TEST_ERROR(JSON_PARSE_MISS_COMMA_OR_CURLY_BRACKET, "{\"a\":1 \"b\"");
//    TEST_ERROR(JSON_PARSE_MISS_COMMA_OR_CURLY_BRACKET, "{\"a\":{}");
//}
//
//
//#define TEST_ROUNDTRIP(json)\
//    do {\
//        Json v;\
//        string json2;\
//        EXPECT_EQ_INT(JSON_PARSE_OK, v.parser(json));\
//        v.convert_value();\
//        json2 = v.get_convert_value();\
//        EXPECT_EQ_STRING(json, json2.c_str(), json2.size());\
//        std::cout << "json:" << json << "  " << "json2:" << json2 << std::endl; \
//    } while (0)
//
//static void test_convert_number() {
//    
//    TEST_ROUNDTRIP("0");
//    TEST_ROUNDTRIP("-0");
//    TEST_ROUNDTRIP("1");
//    TEST_ROUNDTRIP("-1");
//    TEST_ROUNDTRIP("1.5");
//    TEST_ROUNDTRIP("-1.5");
//    TEST_ROUNDTRIP("3.25");
//    TEST_ROUNDTRIP("1e+20");
//    TEST_ROUNDTRIP("1.234e+20");
//    TEST_ROUNDTRIP("1.234e-20");
//
//    TEST_ROUNDTRIP("1.0000000000000002"); /* the smallest number > 1 */
//    TEST_ROUNDTRIP("4.9406564584124654e-324"); /* minimum denormal */
//    TEST_ROUNDTRIP("-4.9406564584124654e-324");
//    TEST_ROUNDTRIP("2.2250738585072009e-308");  /* Max subnormal double */
//    TEST_ROUNDTRIP("-2.2250738585072009e-308");
//    TEST_ROUNDTRIP("2.2250738585072014e-308");  /* Min normal positive double */
//    TEST_ROUNDTRIP("-2.2250738585072014e-308");
//    TEST_ROUNDTRIP("1.7976931348623157e+308");  /* Max double */
//    TEST_ROUNDTRIP("-1.7976931348623157e+308");
//}
//
//static void test_convert_string() {
//    TEST_ROUNDTRIP("\"\"");
//    TEST_ROUNDTRIP("\"Hello\"");
//    TEST_ROUNDTRIP("\"Hello\\nWorld\"");
//    TEST_ROUNDTRIP("\"\\\" \\\\ / \\b \\f \\n \\r \\t\"");
//    TEST_ROUNDTRIP("\"Hello\\u0000World\"");
//}
//
//static void test_convert_array() {
//    TEST_ROUNDTRIP("[]");
//    TEST_ROUNDTRIP("[null,false,true,123,\"abc\",[1,2,3]]");
//}
//
//static void test_convert_object() {
//    TEST_ROUNDTRIP("{}");
//    TEST_ROUNDTRIP("{\"n\":null,\"f\":false,\"t\":true,\"i\":123,\"s\":\"abc\",\"a\":[1,2,3],\"o\":{\"1\":1,\"2\":2,\"3\":3}}");
//}
//
//static void test_convert_value() {
//    TEST_ROUNDTRIP("null");
//    TEST_ROUNDTRIP("false");
//    TEST_ROUNDTRIP("true");
//    test_convert_number();
//    test_convert_string();
//    test_convert_array();
//    test_convert_object();
//}
//
//static void test_access_null() {
//    Json v;  
//    v.set_string("a");
//    v.set_null();
//    EXPECT_EQ_INT(JSON_NULL, v.get_type());
//}
//
//static void test_access_boolean() {
//    Json v;
//    v.set_string("a");
//    v.set_boolean(true);
//    EXPECT_EQ_INT(JSON_TRUE, v.get_type());
//    v.set_boolean(false);
//    EXPECT_EQ_INT(JSON_FALSE, v.get_type());
//}
//
//static void test_access_number() {
//    Json v;
//    v.set_string("a");
//    v.set_number(1234.56);
//    EXPECT_EQ_INT(JSON_NUMBER, v.get_type()); 
//    EXPECT_EQ_DOUBLE(1234.56, v.get_number());
//}
//static void test_access_string() {
//    Json v;
//    v.set_string("");
//    EXPECT_EQ_STRING("", v.get_string().c_str(), v.get_string().size());
//    v.set_string("Hello");
//    EXPECT_EQ_STRING("Hello", v.get_string().c_str(), v.get_string().size());
//}
//
//static void test_access_array() {
//    Json a, e;
//    size_t i;
//
//    a.init();
//    e.init();
//
//    
//    a.set_array(vector<JsonValue>{});
//    EXPECT_EQ_SIZE_T(0, a.get_array_size());
//    for (i = 0; i < 10; i++) {
//        //e.init();
//        e.set_number(i);         
//        a.pushback_array_element(e);
//    }
//
//    EXPECT_EQ_SIZE_T(10, a.get_array_size());
//    for (i = 0; i < 10; i++)
//        EXPECT_EQ_DOUBLE((double)i, a.get_array_element(i).get_number());
//    
//    a.popback_array_element();
//    EXPECT_EQ_SIZE_T(9, a.get_array_size());
//    for (int i = 0; i < 9; ++i)
//        EXPECT_EQ_DOUBLE((double)i, a.get_array_element(i).get_number());
//
//    a.erase_array_element(0, 1);
//    EXPECT_EQ_SIZE_T(8, a.get_array_size());
//    for (int i = 1; i < 9; ++i)
//        EXPECT_EQ_DOUBLE((double)i, a.get_array_element(i-1).get_number());
//
//    a.erase_array_element(7, 1);
//    EXPECT_EQ_SIZE_T(7, a.get_array_size());
//    for (int i = 1; i < 8; ++i)
//        EXPECT_EQ_DOUBLE((double)i, a.get_array_element(i-1).get_number());
//
//    a.erase_array_element(0, 2);
//    EXPECT_EQ_SIZE_T(5, a.get_array_size());
//    for (int i = 3; i < 8; ++i)
//        EXPECT_EQ_DOUBLE((double)i, a.get_array_element(i-3).get_number());
//
//    for (int i = 0; i < 2; ++i) {
//        e.set_number(i);
//        a.insert_array_element(e, i);
//    }
//
//    EXPECT_EQ_SIZE_T(7, a.get_array_size());
//    for (int i = 0; i < 2; ++i)
//        EXPECT_EQ_DOUBLE((double)i, a.get_array_element(i).get_number());
//    for (int i = 3; i < 8; ++i)
//        EXPECT_EQ_DOUBLE((double)i, a.get_array_element(i - 1).get_number());
//
//    e.set_string("Hello");
//    a.pushback_array_element(e);
//
//    a.clear_array();
//    EXPECT_EQ_SIZE_T(0, a.get_array_size());
//}
//static void test_access_object()
//{
//    Json o;
//    Json v;
//    o.set_object(vector<std::pair<string, JsonValue>>{});
//    EXPECT_EQ_SIZE_T(0, o.get_object_size());
//    for (int i = 0; i < 10; ++i) {
//        string key = "a";
//        key[0] += i;
//        v.set_number(i);
//        o.set_object_value(key, v);
//    }
//    EXPECT_EQ_SIZE_T(10, o.get_object_size());
//    for (int i = 0; i < 10; ++i) {
//        string key = "a";
//        key[0] += i;
//        auto index = o.find_object_index(key);
//        EXPECT_TRUE(1==int(index >= 0));
//        v = o;
//        EXPECT_EQ_DOUBLE((double)i, v.get_object_value(i).get_number());
//    }
//
//
//    auto index = o.find_object_index("j");
//    EXPECT_TRUE(1 == int(index >= 0));
//    o.remove_object_value(index);
//    index = o.find_object_index("j");
//    EXPECT_TRUE(1 == int(index < 0));
//    EXPECT_EQ_SIZE_T(9, o.get_object_size());
//
//    index = o.find_object_index("a");
//    EXPECT_TRUE(1 == int(index >= 0));
//    o.remove_object_value(index);
//    index = o.find_object_index("a");
//    EXPECT_TRUE(1 == int(index < 0));
//    EXPECT_EQ_SIZE_T(8, o.get_object_size());
//
//    for (int i = 0; i < 8; i++) {
//        string key = "a";
//        key[0] += i + 1;
//        EXPECT_EQ_DOUBLE((double)i + 1, o.get_object_value(o.find_object_index(key)).get_number());
//    }
//
//
//    v.clear_object();
//    v.set_string("Hello");
//    o.init();
//    o.set_object(vector<std::pair<string, JsonValue>>{});
//    o.set_object_value("World", v);
//
//    index = o.find_object_index("World");
//    EXPECT_TRUE(1 == int(index >= 0));
//    v = o;
//    EXPECT_EQ_STRING("Hello", v.get_object_value(0).get_string().c_str(), 5);
//
//    o.clear_object();
//    EXPECT_EQ_SIZE_T(0, o.get_object_size());
//}
//
//
//static void test_copy() {
//    Json v1, v2;
//    v1.parser("{\"t\":true,\"f\":false,\"n\":null,\"d\":1.5,\"a\":[1,2,3]}");
//    v2 = v1;
//    //EXPECT_TRUE(1, int(v2 == v1));
//}
//
//static void test_move() {
//    Json v1, v2, v3;
//    v1.parser("{\"t\":true,\"f\":false,\"n\":null,\"d\":1.5,\"a\":[1,2,3]}");
//    v2 = v1;
//    v3 = std::move(v2);
//    EXPECT_TRUE(JSON_OBJECT==v2.get_type());
//    //EXPECT_EQ_BASE(1, int(v3 == v1));
//}
//
//static void test_swap() {
//    Json v1, v2;
//    v1.set_string("Hello");
//    v2.set_string("World!");
//    swap(v1, v2);
//    EXPECT_EQ_STRING("World!", v1.get_string().c_str(), 6);
//    EXPECT_EQ_STRING("Hello", v2.get_string().c_str(), 5);
//}
//void test_parse() {
//    test_parse_null();
//    test_parse_true();
//    test_parse_false();
//    test_parse_number();
//    test_parse_string();
//    test_parse_array();
//    test_parse_object();
//    test_convert_value();
//
//    test_parse_expect_value();
//    test_parse_invalid_value();
//    test_parse_root_not_singular();
//    test_parse_number_too_big();
//    test_parse_miss_quotation_mark();
//    test_parse_invalid_string_escape();
//    test_parse_invalid_string_char();
//    test_parse_invalid_unicode_hex();
//    test_parse_invalid_unicode_surrogate();
//    test_parse_miss_comma_or_square_bracket();
//    test_parse_miss_key();
//    test_parse_miss_colon();
//    test_parse_miss_comma_or_curly_bracket();
//}
//
//void test_access() {
//    test_access_null();
//    test_access_boolean();
//    test_access_number();
//    test_access_string();
//    test_access_array();
//    test_access_object();
//
//    test_copy();
//    test_move();
//    test_swap();
//}
//int main() {
//
//    test_parse();   
//    test_access();
//    std::cout << test_pass << "/" << test_count << "(" << test_pass * 100.0 / test_count << "%)" << std::endl;
//     system("pause");
//     return main_ret;
//}
