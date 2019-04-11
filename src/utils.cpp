#include "utils.hpp"
#include<vector>

//Expects a valid filename
const std::vector<char> utils::file_to_byte_vector(const char* filename){

	std::ifstream myfilestream(filename, std::ios::binary | std::ios::in);
	std::istreambuf_iterator<char> file_it_start(myfilestream), file_it_end;

	return std::vector<char>(file_it_start, file_it_end);	
}



