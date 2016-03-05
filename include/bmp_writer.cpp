#include "bmp_writer.h"

//******** converts string to int ********
int string_to_int(std::string s) {
	std::istringstream strm;
	strm.str(s);
	int n = 0;
	strm >> n;
	return n;
}

//******** converts int to string ********
std::string int_to_string(int i) {
	std::stringstream strm;
	std::string s;
	strm << i;
	strm >> s;
	return s;
}

//******** writes bmp header ********
void write_bmp_header(std::ofstream& output_file, int px, int pz) {
	unsigned short int bfType;
	bfType = 0x4D42;
	output_file.write((char*)&bfType, sizeof (short int));

	unsigned int bfSize;
	int rem = 3*px%4;
	int padding;
	if(rem == 0)
		padding=0;
	else
		padding=4-rem;

	bfSize = 14 + 40 + (3 * px+padding) * pz;
	//bfSize = 14 + 40 + (3 * px+padding) * pz + 2;
	output_file.write((char*)&bfSize, sizeof (int));

	unsigned short int bfReserved1;
	bfReserved1 = 0;
	output_file.write((char*)&bfReserved1, sizeof (short int));

	unsigned short int bfReserved2;
	bfReserved2 = 0;
	output_file .write((char*)&bfReserved2, sizeof (short int));

	unsigned int bfOffsetBits;
	bfOffsetBits = 14 + 40;
	output_file.write((char*)&bfOffsetBits, sizeof (int));

	unsigned int biSize;
	biSize = 40;
	output_file.write((char*)&biSize, sizeof (int));

	int biWidth;
	biWidth = px;
	output_file.write((char*)&biWidth, sizeof (int));

	int biHeight;
	biHeight = pz;
	output_file.write((char*)&biHeight, sizeof (int));

	unsigned short int biPlanes;
	biPlanes = 1;
	output_file.write((char*)&biPlanes, sizeof (short int));

	unsigned short int biBitCount;
	biBitCount = 24;
	output_file.write((char*)&biBitCount, sizeof (short int));

	unsigned int biCompression;
	//#define BI_RGB 0
	unsigned int bi_rgb = 0;
	//biCompression=BI_RGB;
	biCompression = bi_rgb;
	output_file.write((char*)&biCompression, sizeof (int));

	unsigned int biSizeImage;
	biSizeImage = 0;
	output_file.write((char*)&biSizeImage, sizeof (int));

	unsigned int biXPelsPerMeter;
	biXPelsPerMeter = 0;
	output_file.write((char*)&biXPelsPerMeter, sizeof (int));

	unsigned int biYPelsPerMeter;
	biYPelsPerMeter = 0;
	output_file.write((char*)&biYPelsPerMeter, sizeof (int));

	unsigned int biClrUsed;
	biClrUsed = 0;
	output_file.write((char*)&biClrUsed, sizeof (int));

	unsigned int biClrImportant;
	biClrImportant = 0;
	output_file.write((char*)&biClrImportant, sizeof (int));
}

//******** writes 1 bmp pixel ********
void write_bmp_pixel(std::ofstream& output_file, Color c) {
	unsigned char buffer[3];
	buffer[0] = (unsigned char)(std::min(255.0,255*c.getB()));
	buffer[1] = (unsigned char)(std::min(255.0,255*c.getG()));
	buffer[2] = (unsigned char)(std::min(255.0,255*c.getR()));
	output_file.write((char*)(buffer), 3 * sizeof(unsigned char));
}

//******** writes bmp padding ********
void write_bmp_padding(std::ofstream& output_file, int px, int pz) {
	int rem = 3*px%4;
	int padding;
	if(rem == 0)
		padding = 0;
	else
		padding = 4 - rem;
	unsigned char p_buffer[4];
	p_buffer[0] = 0;
	p_buffer[1] = 0;
	p_buffer[2] = 0;
	p_buffer[3] = 0;
	output_file.write((char*)p_buffer, padding * sizeof(unsigned char));
}