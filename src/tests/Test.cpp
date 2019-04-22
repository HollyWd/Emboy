class Test {
	private:
		test_number=0;
	public:
		int assert(bool value);
}

Test::assert(bool value){
	std::cout<<"Test "<<test_number<<": ";	
	if(value==true){
		std::cout<<"OK";
	}
	else{
		std::cout<<"False";
	}
	std::cout<<endl;
	test_number++;
}