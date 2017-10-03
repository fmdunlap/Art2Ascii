#define cimg_display 0
#include "CImg.h"
#include "art2ascii_main.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace cimg_library;




int main(int argc, char** argv) {
	if(argc != 3 && argc != 4){
		std::cout << "USAGE: ./Art2Ascii /path/to/input /path/to/output (resolution)\n";
		return -1;
	}

	int resolution;

	if(argc == 4){
		resolution = atoi(argv[3]);
	} else {
		resolution = 6;
	}

	char* input_filepath = argv[1];
	char* output_filepath = argv[2];

	CImg<unsigned char> image(argv[1]);

	std::string output = get_image_ascii(image, resolution);

	print_ascii_to_file(output_filepath, output);

	return 0;
}

std::string get_image_ascii(CImg<unsigned char> img, int res){

	std::string ascii_string = "";

	for(int row = 0; row < img.height(); row += res){
		for(int col = 0; col < img.width(); col += res){

			int avg = compute_block_average(img, col, row, res);
			if(avg == 255 || avg == 0){
				ascii_string += " ";
			} else if(avg > 150){
				ascii_string += "@";
			} else if(avg > 60){
				ascii_string += "*";
			} else {
				ascii_string += " ";
			}
		}
		ascii_string += '\n';
	}

	return ascii_string;

}

char get_char_by_brightness(int brightnes){
	switch(brightness){
		
	}
}

int compute_block_average(CImg<unsigned char> img, int start_x, int start_y, int res){
	int average = 0;
	int n = 0;

	for(int row = start_y; row < start_y + res; row++){
		for(int col = start_x; col < start_x + res; col++){
			const int
			valR = img(col,row,0), // Read red value at coordinates (10,10).
			valG = img(col,row,1), // Read green value at coordinates (10,10)
			valB = img(col,row,2),
			pixel_avg = (valR + valG + valB)/3;   // Read blue value at coordinates (10,10) (Z-coordinate can be omitted).
			average = (pixel_avg + (n*average)) / (n+1);
		}
	}

	return average;
}

void print_ascii_to_file(char* of_path, std::string output_ascii){
	std::ofstream ofile;
	ofile.open(of_path);
	ofile << output_ascii;
	ofile.close();
}