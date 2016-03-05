#include "texture_loader.h"
#include <iostream>

//**************** loads bmp textures ****************

//******** read header + image size ********
void junk_header(std::ifstream& input_file, unsigned int& x_size, unsigned int& y_size) {
	unsigned char jnk; //2 bytes
	unsigned int size_of_header2;
	for(int i = 0; i < 10; i++) input_file.read((char*)&jnk, sizeof(unsigned char));
	input_file.read((char*)&size_of_header2, sizeof(unsigned int));
	for(int i = 0; i < 4; i++) input_file.read((char*)&jnk, sizeof(unsigned char));
	input_file.read((char*)&x_size, sizeof(unsigned int));
	input_file.read((char*)&y_size, sizeof(unsigned int));
	for(int i = 0; i < size_of_header2-18-8; i++) input_file.read((char*)&jnk, sizeof(unsigned char));
}

//******** reads single pixel ********
void read_pixel(std::ifstream& input_file, Color& c) {
	unsigned char r, g, b;
	input_file.read((char*)&b, sizeof(unsigned char));
	input_file.read((char*)&g, sizeof(unsigned char));
	input_file.read((char*)&r, sizeof(unsigned char));
	c = Color((double)r/255.0, (double)g/255.0, (double)b/255.0);
}