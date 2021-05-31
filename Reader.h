#include"Json.h"
#include<fstream>
#include<sstream>
#include<string>
namespace Reader{
	void reader(string json, Json& v)
	{
		v.parser(json);			
	}
	void reader(std::ifstream& file, const string filename, Json& v) {
		file.open(filename, std::ios::in);
		if (!file.is_open()) {
			std::cout << "文件打开失败！" << std::endl;
			return;
		}

		string buf, buf_all;
		while (getline(file, buf))
			buf_all += buf;
		file.close();
		v.parser(buf_all);
	}
	void SimpleShow(Json& v) {
		v.convert_value();
		string s = v.get_convert_value();
		std::cout << s << std::endl;
	}
	void PrettyShow(Json& v) {
		std::cout << v.get_pretty_convert_value()<< std::endl;
	}

}