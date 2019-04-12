#include "utils.hpp"
#include<vector>

#include <termios.h>
#include <stdio.h>



//Expects a valid filename
//store a bynary file in a byte vector
const std::vector<char> utils::file_to_byte_vector(const char* filename){

	std::ifstream myfilestream(filename, std::ios::binary | std::ios::in);
	std::istreambuf_iterator<char> file_it_start(myfilestream), file_it_end;

	return std::vector<char>(file_it_start, file_it_end);	
}

static struct termios old_termios, new_termios;
/* Read one character from the standard inptut without echo */
char utils::getch(void) {
  char ch;
  int echo = 0;

  //init termios
  tcgetattr(0, &old_termios); /* grab old terminal i/o settings */
  new_termios = old_termios; /* make new settings same as old settings */
  new_termios.c_lflag &= ~ICANON; /* disable buffered i/o */
  if (echo) {
      new_termios.c_lflag |= ECHO; /* set echo mode */
  } else {
      new_termios.c_lflag &= ~ECHO; /* set no echo mode */
  }
  tcsetattr(0, TCSANOW, &new_termios); /* use these new terminal i/o settings now */

  ch = getchar();

  //reset termios
  tcsetattr(0, TCSANOW, &old_termios);

  return ch;
}




