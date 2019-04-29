#include <vector>
#include <iostream>
#include <fstream>
#include <iomanip>

namespace utils{
	const std::vector<char> file_to_byte_vector(const char* filename);
	//*	Convert hexadecimal code into an array of bytes
	//* 
	const std::vector<char> string_to_byte_vector(const std::string s);
}