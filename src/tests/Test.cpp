#include "Test.hpp"

void Test::assert(bool value,int line){
	if(value==true){
		std::cout<<"	[OK]	";
		passed_number+=1;
	}
	else{
		std::cout<<"	[FAIL]	";
	}
	//std::c "<< __func__ << " in "<<__FILE__ <<" line "<<__LINE__<<std::endl;
	std::cout<< file << " in "<< func <<"function, line "<<line<<std::endl;
	test_number++;
}

Test::Test(std::string test_name, std::string file_name, std::string func_name){
	name = test_name;
	file = file_name;
	func = func_name;
	std::cout<<"[====] Running test "<< name<<std::	endl;
}

void Test::result(){
	if(passed_number==test_number){
		std::cout<<"[OK]	";
	}
	else{
		std::cout<<"[FAIL]	";
	}
	std::cout<<passed_number<<"/"<<test_number<<" passed"<<std::endl<<std::endl;
}

// int main(){
// 	Test t("main",__FILE__,__FUNCTION__);
// 	t.assert(0==0,__LINE__);
// 	t.assert(0==0,__LINE__);
// 	t.assert(0==0,__LINE__);
// 	t.assert(0==0,__LINE__);
// 	t.assert(0==0,__LINE__);
// 	t.assert(0==0,__LINE__);
// 	t.assert(0==1,__LINE__);
// 	t.result();
// 	return 0;
// }