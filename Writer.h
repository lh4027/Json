#include"Json.h"
#include<fstream>

namespace Writer {
	void SimpleWriter(Json& v, string file_name) {
		
		string buf;
		v.convert_value();
		buf = v.get_convert_value();

		std::ofstream ofs;
		ofs.open(file_name,std::ios::out);
		ofs << buf;
		ofs.close();
	}//, std::ios::trunc
	void PrettyWriter(Json& v, string file_name) {
		string buf;
		
		buf = v.get_pretty_convert_value();

		std::ofstream ofs;
		ofs.open(file_name, std::ios::out);
		ofs << buf;
		ofs.close();
	}
}