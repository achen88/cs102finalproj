#ifndef TEXTURE_LOADER_H
#define TEXTURE_LOADER_H

#include "color.h"
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <iomanip>

void junk_header(std::ifstream& input_file, unsigned int& x_size, unsigned int& y_size);
void read_pixel(std::ifstream& input_file, Color& c);

#endif