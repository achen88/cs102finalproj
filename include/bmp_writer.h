#ifndef BMP_WRITER_H
#define BMP_WRITER_H

#include "color.h"
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <iomanip>
#include <cmath>

int string_to_int(std::string s);
std::string int_to_string(int i);
void write_bmp_header(std::ofstream& output_file, int px, int pz);
void write_bmp_pixel(std::ofstream& output_file, Color c);
void write_bmp_padding(std::ofstream& output_file, int px, int pz);

#endif