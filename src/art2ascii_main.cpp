#define cimg_display 0
#include <iostream>
#include <fstream>
#include <string>
#include "image.h"


int main(int argc, char** argv) {
	if(argc != 3 && argc != 4){
		std::cout << "USAGE: ./Art2Ascii /path/to/input /path/to/output (resolution)\n";
		return -1;
	}

	char* input_filepath = argv[1];
	char* output_filepath = argv[2];

	image* img;

	char type_select;

	std::cout << "Would you like to compute a (s)tandard image? Or an image by (c)olor difference?\n";
	std::cin >> type_select;

	if(type_select == 'c'){
		img = new image(input_filepath, color);
	} else {
		img = new image(input_filepath);
	}

	//Sets up the image to have either the default resolution,
	//or the user specified resolution.
	if(argc == 4){
		img->set_resolution(atoi(argv[3]));
	}

	img->print_ascii_to_file(output_filepath);


	delete img;
	return 0;
}