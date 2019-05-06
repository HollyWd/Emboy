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
		template <class T1, class T2>
		void test_assert(T1 actual_value, T2 expected_value, int line){
			bool value = actual_value==expected_value;
			test_assert(value, line);
			if (value==false) std::cout<<" 		Actual value: "<< (int)actual_value << ",	Expected value: "<<(int)expected_value<<std::endl;
		};
		void result();

};