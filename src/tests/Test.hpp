#include <iostream>
#include <string>

struct Result{
	bool passed;
	std::string file;
	int line;
};

class Test {
	private:
		std::string name;
		///file where the test was instanciated
		std::string file;
		///function name where the test was instanciated
		std::string func;
		int test_number=0;
		int passed_number=0;
		//std::list<Result>result_list;
	public:
		Test(std::string test_name, std::string file_name, std::string func_name);
		void assert(bool b,int line);
		void result();

};