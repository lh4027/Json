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

为降低文件间的编译依赖关系，把接口从从实现中分离，Json类只提供接口，Value类负责实现该接口，Json类通过一个std::unique_ptr实现对Value的访问。 解析一个JSON字符串的一般用法是：

![图片2](https://user-images.githubusercontent.com/66367559/120108192-b2907980-c196-11eb-8bf1-d8180f754b4b.jpg)



