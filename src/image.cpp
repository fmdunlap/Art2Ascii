#include "../libs/CImg.h"
#include "image.h"
#include <fstream>

image::image(char* file_name){

	raw_image = new cimg_library::CImg<unsigned char>(file_name);;

}


std::string image::get_image_ascii(int res){

	std::string ascii_string = "";

	for(int row = 0; row < this->raw_image->height(); row += res){
		for(int col = 0; col < this->raw_image->width(); col += res){

			int avg = compute_block_average(col, row, res);
			ascii_string += get_char_by_brightness(avg);
		}
		ascii_string += '\n';
	}

	return ascii_string;

}


char image::get_char_by_brightness(int brightness){

	double index = (((double)brightness)*((double)this->ascii_darkness_string.size()))/((double) MAX_BRIGHTNESS) -.25;
	return this->ascii_darkness_string.at((int)index);
}

int image::compute_block_average(int start_x, int start_y, int res){
	int average = 0;
	int n = 0;

	for(int row = start_y; row < start_y + res; row++){
		for(int col = start_x; col < start_x + res; col++){
			const int
			valR = this->raw_image->atXYZ(col,row,0),
			valG = this->raw_image->atXYZ(col,row,1),
			valB = this->raw_image->atXYZ(col,row,2),
			pixel_avg = (valR + valG + valB)/3;   // Read blue value at coordinates (10,10) (Z-coordinate can be omitted).
			average = (pixel_avg + (n*average)) / (n+1);
		}
	}

	return average;
}


void image::print_ascii_to_file(char* of_path, std::string output_ascii){
	std::ofstream ofile;
	ofile.open(of_path);
	ofile << output_ascii;
	ofile.close();
}

bool has_suffix(const std::string &str, const std::string &suffix)
{
	return str.size() >= suffix.size() && str.compare(str.size() - suffix.size(), suffix.size(), suffix) == 0;
}
