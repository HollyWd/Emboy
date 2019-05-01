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
		void test_assert(bool b,int line);
		template <class T>
		void test_assert(T actual_value, T expected_value, int line){
			bool value = actual_value==expected_value;
			test_assert(value, line);
			if (value==false) std::cout<<" 		Actual value: "<< actual_value << ",	Expected value: "<<expected_value<<std::endl;
		};
		void result();

};