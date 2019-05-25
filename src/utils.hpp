#include <vector>
#include <iostream>
#include <fstream>
#include <iomanip>

namespace utils{
	const std::vector<uint8_t> file_to_byte_vector(const char* filename);
	//*	Convert hexadecimal code into an array of bytes
	//* 
	const std::vector<uint8_t> string_to_byte_vector(const std::string s);
}