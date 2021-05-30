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
’’’
Json::Json() : v(new JsonValue) ,p(new Parser), g(new JsonGenerator) { }

Json::~Json() { 
	delete v;
	delete p;
	delete g;
}
‘‘‘


